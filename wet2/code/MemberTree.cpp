
#include "MemberTree.h"

void MemberTree::insert(Customer* customer)
{
    insertAux(m_root, new Node(customer));
}


void MemberTree::insertAux(unique_ptr<Node>& curNode, Node* newNode)
{
    if(!curNode)
    {
        curNode.reset(newNode);
    }
    else if (curNode->customer->getId() < newNode->customer->getId()) 
    {
        insertAux(curNode->right, newNode);
    }
    else if(curNode->customer->getId() > newNode->customer->getId())
    {
        insertAux(curNode->left, newNode);
    }
    else
    {
        delete newNode;
        throw KeyAlreadyExists();
    }
    balance(curNode);
}

void MemberTree::addPrize(int lowerLimit, int upperLimit, int amount)
{
    addPrizeAux(m_root, lowerLimit, upperLimit, amount);
}
void MemberTree::addPrizeAux(unique_ptr<Node>& curNode, int lowerLimit, int upperLimit, int amount)
{
    if(!curNode || curNode->getMinId()>= upperLimit || curNode->getMaxId()< lowerLimit)
    {
        return;
    }
    else if (curNode->getMinId() >= lowerLimit && curNode->getMaxId() < upperLimit)
    {
        curNode->increaseDiscount(amount);
    }
    else
    {
        if(curNode->customer->getId() >= lowerLimit && curNode->customer->getId() < upperLimit)
        {
            curNode->customer->discount(amount);
        }
        addPrizeAux(curNode->left, lowerLimit, upperLimit, amount);
        addPrizeAux(curNode->right, lowerLimit, upperLimit, amount);
    }
    
}

Customer& MemberTree::get(int id) const
{
    return getAux(m_root, id);
}

Customer& MemberTree::getAux(const unique_ptr<Node>& curNode, int id) const
{
    if (!curNode)
    {
        throw KeyMissing();
    }
    else if (curNode->customer->getId() < id) 
    {
        curNode->propogate();
        return getAux(curNode, id);
    }
    else if(curNode->customer->getId() > id)
    {
        curNode->propogate();
        return getAux(curNode->left, id);
    }
    else
    {
        curNode->propogate();
        return *curNode->customer;
    }
    
}


void MemberTree::rightRotate(unique_ptr<typename MemberTree::Node>& B)
{
    unique_ptr<MemberTree::Node> A = move(B->left);
    unique_ptr<MemberTree::Node> Ar = move(A->right);
    A->right = move(B);
    A->right->left = move(Ar);
    A->right->update();
    A->update();
    B = move(A);
}

void MemberTree::leftRotate(unique_ptr<MemberTree::Node>& A)
{
    unique_ptr<MemberTree::Node> B = move(A->right);
    unique_ptr<MemberTree::Node> Bl = move(B->left);
    B->left = move(A);
    B->left->right = move(Bl);
    B->left->update();
    B->update();
    A = move(B);
}

void MemberTree::balance(unique_ptr<MemberTree::Node>& node)
{
    node->update();
    int balance = node->getBalanceFactor();
    int leftBalance = node->left->getBalanceFactor();
    int rightBalance = node->right->getBalanceFactor();
    
    if (balance == 2 && leftBalance >= 0) //LL
    {
        return rightRotate(node);
    }
    else if (balance == 2 && leftBalance < 0) //LR
    {
        leftRotate(node->left);
        rightRotate(node);
    }
    else if (balance == -2 && rightBalance <= 0) //RR
    {
        leftRotate(node);
    }
    else if (balance == -2 && rightBalance > 0) //RL
    {
        rightRotate(node->right);
        leftRotate(node);
    }
}

void MemberTree::resetExpenses()
{
    resetExpensesAux(m_root);
}

void MemberTree::resetExpensesAux(unique_ptr<Node>& curNode)
{
    if (!curNode)
    {
        return;
    }
    curNode->customer->resetExpenses();
    resetExpensesAux(curNode->left);
    resetExpensesAux(curNode->right);
}

std::ostream& operator<<(std::ostream& os, MemberTree& tree)
{
    tree.inOrder(tree.m_root, os);
    os << endl;
    return os;
}

void MemberTree::inOrder(unique_ptr<Node>& curNode, ostream& os)
{
    if (!curNode)
    {
        return;
    }
    curNode->propogate();
    
    inOrder(curNode->left, os);
    os << curNode->customer->getId() << "(" << curNode->customer->getExpenses() << "),";
    inOrder(curNode->right, os);
}

int MemberTree::Node::getBalanceFactor()
{
    if(!this)
    {
        return 0;
    }
    return left->getHeight() - right->getHeight();
}
int MemberTree::Node::getMinId()
{
    if(!this)
    {
        return 0x7FFFFFFF; //Max int
    }
    return minId;
}
int MemberTree::Node::getMaxId()
{
    if (!this)
    {
        return -0x7FFFFFFF; //Min int
    }
    return maxId;   
}

int MemberTree::Node::getHeight()
{
    if (!this)
    {
        return -1;
    }
    return height;
}

void MemberTree::Node::increaseDiscount(int amount)
{
    if (this)
    {
        discount+=amount;
    }
    
}

void MemberTree::Node::propogate()
{
    if (discount!=0)
    {
        left->increaseDiscount(discount);
        right->increaseDiscount(discount);
        customer->discount(discount);
        discount = 0;
    }
}

//Updates all of a node's special values assuming its children's special values are updated
void MemberTree::Node::update()
{
    if(left->getHeight() > right->getHeight())
    {
        height = left->getHeight() + 1;
    }
    else
    {
        height = right->getHeight() + 1;
    }

    if (right->getMaxId() > maxId)
    {
        maxId = right->getMaxId();
    }
    if (left->getMinId() < minId)
    {
        minId = left->getMinId();
    }
}

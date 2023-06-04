
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
        curNode->lazyDiscount(amount);
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
    int leftBalance = (node->left) ? node->left->getBalanceFactor() : 0;
    int rightBalance = (node->right) ? node->right->getBalanceFactor() : 0;
    
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
    int leftHeight = (left) ? left->getHeight() : -1;
    int rightHeight = (right) ? right->getHeight() : -1;

    return leftHeight - rightHeight;
}
int MemberTree::Node::getMinId()
{
    return minId;
}
int MemberTree::Node::getMaxId()
{
    return maxId;   
}

int MemberTree::Node::getHeight()
{
    return height;
}

void MemberTree::Node::lazyDiscount(int amount)
{
     discount+=amount;
}

void MemberTree::Node::propogate()
{
    if (discount!=0)
    {
        if (left)
        {
            left->lazyDiscount(discount);
        }
        if (right)
        {
            right->lazyDiscount(discount);
        }
        customer->discount(discount);
        discount = 0;
    }
}

void MemberTree::Node::update()
{
    int leftHeight = (left) ? left->getHeight() : -1;
    int rightHeight = (right) ? right->getHeight() : -1;
    height = (leftHeight > rightHeight) ? leftHeight + 1 : rightHeight + 1;
    
    maxId = (right) ? right->getMaxId() : customer->getId();
    minId = (left) ? left->getMinId() : customer->getId();
}

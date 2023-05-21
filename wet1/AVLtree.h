#ifndef __tree_h__
#define __tree_h__
#include <memory>
#include <iostream>

using namespace std;

template <class Key, class Val>
class AVLtree
{

public:

    AVLtree(): m_root(nullptr), m_count(0) {}
    AVLtree(const AVLtree<Key, Val>& other) : m_root(nullptr), m_count(other.m_count)
    {
        m_root = unique_ptr<Node>(copyNodes(other.m_root.get(), nullptr));

    }
    AVLtree& operator=(const AVLtree& other)
    {
        if (this != &other) 
        {
            m_root = nullptr;
            m_count = other.m_count; 
            this->m_root = unique_ptr<Node>(copyNodes(other.m_root.get(), nullptr));

        }
        return *this;
    }
    class Node
    {
    public:
        Key key;
        Val val;
        unique_ptr<Node> left, right;
        int height;
        
    private:
        friend AVLtree;
        Node(): key(Key()), val(Val()), left(nullptr), right(nullptr), height(0) {}
        Node(Key key, Val val): key(key), val(val), left(nullptr), right(nullptr), height(0) {}
        
        void updateHeight()
        {
            int leftHeight = -1, rightHeight = -1;
            if (left)
            {
                leftHeight = left->height;
            }
            if (right)
            {
                rightHeight = right->height;
            }
            height = (leftHeight > rightHeight) ? leftHeight+1 : rightHeight+1;
            
        }
    };

    void insert(Key key, Val val);
    Val& get(const Key& key) const;
    void remove(const Key& key);
    

    void update(const Key& oldKey, const Key& newKey);

    int getNodeCount() const {  return m_count; }

    template <class K,class V>
    friend ostream& operator<<(ostream& os, AVLtree<K, V>& tree);
    Node* getRoot() { return m_root.get(); }
    Node* getMin() { return m_min; }

private:
    unique_ptr<Node> m_root;
    Node* m_min;
    int m_count;

    void insertAux(unique_ptr<Node>& curNode, const Key& key, const Val& val);
    Val& getAux(const unique_ptr<Node>& curNode, const Key& key) const;
    Node* removeAux(unique_ptr<Node>& curNode, const Key& key);
    void removeNode(unique_ptr<Node>& toDelete);

    void preOrder(unique_ptr<Node>& curNode);
    void inOrder(unique_ptr<Node>& curNode);
    unique_ptr<Node>& getLeftmost(unique_ptr<Node>& curNode);
    unique_ptr<Node> copyNodes(Node* other_node, Node* parent);

    int getBalanceFactor(Node* node);
};
template <class Key, class Val>
void AVLtree<Key,Val>::insert(Key key, Val val)
{
    insertAux(m_root, key, val);
    m_count++;
    m_min = getLeftmost(m_root).get();
}
template <class Key, class Val>
void AVLtree<Key,Val>::insertAux(unique_ptr<Node>& curNode, const Key& key, const Val& val)
{
    if(!curNode)
    {
        curNode.reset(new Node(key, val));
    }
    else if (curNode->key < key) 
    {
        insertAux(curNode->right, key, val);
    }
    else if(key < curNode->key)
    {
        insertAux(curNode->left, key, val);
    }
    else
    {
        throw runtime_error("Insert failed because key already exists");
    }
    
}

template <class Key, class Val>
void AVLtree<Key,Val>::update(const Key& oldKey, const Key& newKey)
{
    const Val val = get(oldKey);
    release(oldKey);
    insert(newKey, val);
}
template <class Key, class Val>
Val& AVLtree<Key,Val>::get(const Key& key) const
{
    return getAux(m_root, key);
}
template <class Key, class Val>
Val& AVLtree<Key,Val>::getAux(const unique_ptr<Node>& curNode, const Key& key) const
{
    if (!curNode)
    {
        throw runtime_error("Get failed because node doesn't exist");
    }
    else if (curNode->key < key) 
    {
        return getAux(curNode->right, key);
    }
    else if(key < curNode->key)
    {
        return getAux(curNode->left, key);
    }
    else
    {
        return curNode->val;
    }
    
}
template <class Key, class Val>
void AVLtree<Key,Val>::remove(const Key& key)
{
    removeAux(m_root, key);
    m_count--;
    if (m_root)
    {
        m_min = getLeftmost(m_root).get();
    }
    else
    {
        m_min = nullptr;
    }
    
}


template <class Key, class Val>
typename AVLtree<Key,Val>::Node* AVLtree<Key,Val>::removeAux(unique_ptr<Node>& curNode, const Key& key)
{
    if (!curNode)
    {
        throw runtime_error("Remove failed because node doesn't exist");
    }
    else if (curNode->key < key) 
    {
        return removeAux(curNode->right, key);
    }
    else if(key < curNode->key)
    {
        return removeAux(curNode->left, key);
    }
    else
    {
        Node* node = curNode.get();
        removeNode(curNode);
        return node;
    }
}

template <class Key, class Val>
void AVLtree<Key,Val>::removeNode(unique_ptr<Node>& toDelete)
{
    if (toDelete->right && toDelete->left)
    {
        
        unique_ptr<Node>& next = getLeftmost(toDelete->right);
        unique_ptr<Node> temp = move(next);
        if (toDelete->right == next)
        {
            toDelete->right = std::move(temp->right);
            temp->left = std::move(toDelete->left);
            temp->right = move(toDelete);
            toDelete = std::move(temp); 
            removeNode(toDelete->right);
        }
        else
        {
            unique_ptr<Node> right = move(toDelete->right);
            unique_ptr<Node> left = move(toDelete->left);

            toDelete->right = move(temp->right);
            temp->right = move(right);
            temp->left = move(left);
            next = move(toDelete);
            toDelete = move(temp);
            removeNode(next);
        }
        
    }
    else if(toDelete->right)
    {
        
        Node* temp = toDelete->right.release();
        toDelete.reset(temp);
    }
    else if(toDelete->left)
    {
        Node* temp = toDelete->left.release();
        toDelete.reset(temp);
    }
    else
    {
        toDelete.reset();
    }
    
}

template <class Key, class Val>
unique_ptr<typename AVLtree<Key,Val>::Node>& AVLtree<Key,Val>::getLeftmost(unique_ptr<Node>& curNode)
{
    if (curNode->left)
    {
        return getLeftmost(curNode->left);
    }
    return curNode;
    
}

template <class Key,class Val>
ostream& operator<<(ostream& os, AVLtree<Key, Val>& tree)
{
    cout << "Inorder: ";
    tree.inOrder(tree.m_root);
    cout << endl << "Preorder: ";
    tree.preOrder(tree.m_root);
    cout << endl;
    return os;
}

template <class Key, class Val>
void AVLtree<Key,Val>::inOrder(unique_ptr<Node>& curNode)
{
    if (!curNode)
    {
        return;
    }
    
    inOrder(curNode->left);
    cout << curNode->key << ", ";
    inOrder(curNode->right);
}

template <class Key, class Val>
void AVLtree<Key,Val>::preOrder(unique_ptr<Node>& curNode)
{
    if (!curNode)
    {
        return;
    }
    
    cout << curNode->key << ", ";
    preOrder(curNode->left);
    preOrder(curNode->right);
}


template <class Key, class Val>
unique_ptr<typename AVLtree<Key, Val>::Node> AVLtree<Key, Val>::copyNodes(Node* other_node, Node* parent)
{
    if (other_node == nullptr)
    {
        return nullptr; 
    }
    
    // Use unique_ptr for new_node
    Key key = other_node->key;
    Val val = other_node->val;
    std::unique_ptr<Node> new_node = unique_ptr<Node>(new Node(key,val));
    new_node->height = other_node->height;
    new_node->left = copyNodes(other_node->left.get(), new_node.get());
    new_node->right = copyNodes(other_node->right.get(), new_node.get());

    // Return unique_ptr to ensure memory management
    return new_node;
}

#endif
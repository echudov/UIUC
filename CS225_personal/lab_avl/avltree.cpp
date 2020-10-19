/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include <algorithm>

template <class K, class V>
V AVLTree<K, V>::find(const K &key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node *subtree, const K &key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else
    {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node *&t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    Node *left = t;
    t = t->right;
    left->right = t->left;
    left->height = std::max(heightOrNeg1(left->left), heightOrNeg1(left->right)) + 1;
    t->left = left;
    t->height = std::max(heightOrNeg1(t->right), heightOrNeg1(t->left)) + 1;
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node *&t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node *&t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    Node *left = t->left;
    Node *tmp = left->right;
    t->left = tmp;
    left->right = t;
    t->height = std::max(heightOrNeg1(t->left), heightOrNeg1(t->right)) + 1;
    t = left;
    t->height = std::max(heightOrNeg1(t->right), heightOrNeg1(t->left)) + 1;
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node *&t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node *&subtree)
{
    // your code here

    if (subtree == NULL)
    {
        return;
    }
    int balance = heightOrNeg1(subtree->left) - heightOrNeg1(subtree->right);
    if (balance == -2)
    {
        Node *right = subtree->right;
        int rbalance = heightOrNeg1(right->left) - heightOrNeg1(right->right);
        if (rbalance == -1)
        {
            rotateLeft(subtree);
        }
        else
        {
            rotateRightLeft(subtree);
        }
    }
    else if (balance == 2)
    {
        Node *left = subtree->left;
        int lbalance = heightOrNeg1(left->left) - heightOrNeg1(left->right);
        if (lbalance == 1)
        {
            rotateRight(subtree);
        }
        else
        {
            rotateLeftRight(subtree);
        }
    }
    subtree->height = std::max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right)) + 1;
}

template <class K, class V>
void AVLTree<K, V>::insert(const K &key, const V &value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node *&subtree, const K &key, const V &value)
{
    // your code here
    if (subtree == NULL)
    {
        subtree = new Node(key, value);
    }
    else if (subtree->key > key)
    {
        insert(subtree->left, key, value);
    }
    else
    {
        insert(subtree->right, key, value);
    }
    rebalance(subtree);
}

template <class K, class V>
void AVLTree<K, V>::remove(const K &key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node *&subtree, const K &key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key)
    {
        remove(subtree->left, key);
        // your code here
    }
    else if (key > subtree->key)
    {
        remove(subtree->right, key);
        // your code here
    }
    else
    {
        if (subtree->left == NULL && subtree->right == NULL)
        {
            /* no-child remove */
            // your code here
            delete subtree;
            subtree = NULL;
        }
        else if (subtree->left != NULL && subtree->right != NULL)
        {
            Node *temp = subtree->left;
            while (temp->right != NULL)
            {
                temp = temp->right;
            }
            swap(subtree, temp);
            remove(subtree->left, key);
            /* two-child remove */
            // your code here
        }
        else
        {
            /* one-child remove */
            // your code here
            Node *left = subtree->left;
            Node *right = subtree->right;
            if (left != NULL)
            {
                delete subtree;
                subtree = left;
            }
            else if (right != NULL)
            {
                delete subtree;
                subtree = right;
            }
            else
            {
                delete subtree;
                subtree = NULL;
            }
        }
        // your code here
    }
    rebalance(subtree);
}

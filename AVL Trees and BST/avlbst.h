#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <cstdlib>
#include <string>
#include "rotateBST.h"

/**
* A special kind of node for an AVL tree, which adds the height as a data member, plus 
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
	// Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int getHeight() const;
    void setHeight(int height);

    // Getters for parent, left, and right. These need to be redefined since they 
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int mHeight;



};

/*
--------------------------------------------
Begin implementations for the AVLNode class.
--------------------------------------------
*/

/**
* Constructor for an AVLNode. Nodes are initialized with a height of 0.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent)
    : Node<Key, Value>(key, value, parent)
    , mHeight(0)
{

}

/**
* Destructor.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* Getter function for the height. 
*/
template<typename Key, typename Value>
int AVLNode<Key, Value>::getHeight() const
{
    return mHeight;
}

/**
* Setter function for the height. 
*/
template<typename Key, typename Value>
void AVLNode<Key, Value>::setHeight(int height)
{
    mHeight = height;
}

/**
* Getter function for the parent. Used since the node inherits from a base node.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key,Value>*>(this->mParent);
}

/**
* Getter function for the left child. Used since the node inherits from a base node.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key,Value>*>(this->mLeft);
}

/**
* Getter function for the right child. Used since the node inherits from a base node.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key,Value>*>(this->mRight);
}

/*
------------------------------------------
End implementations for the AVLNode class.
------------------------------------------
*/

/**
* A templated balanced binary search tree implemented as an AVL tree.
*/
template <class Key, class Value>
class AVLTree : public rotateBST<Key, Value>
{
public:
	// Methods for inserting/removing elements from the tree. You must implement
	// both of these methods. 
    virtual void insert(const std::pair<Key, Value>& keyValuePair) override;
    void remove(const Key& key);

private:
	/* Helper functions are strongly encouraged to help separate the problem
	   into smaller pieces. You should not need additional data members. */
    void insertBalance(AVLNode<Key, Value> *parent, AVLNode<Key, Value> *child);
    void removeBalance(AVLNode<Key, Value> *node, int diff);
};

/*
--------------------------------------------
Begin implementations for the AVLTree class.
--------------------------------------------
*/

/**
* Insert function for a key value pair. Finds location to insert the node and then balances the tree. 
*/
template<typename Key, typename Value>
void AVLTree<Key, Value>::insert(const std::pair<Key, Value>& keyValuePair)
{
    // TODO
    AVLNode<Key, Value>* curr = dynamic_cast<AVLNode<Key,Value>*>(this->mRoot);
    AVLNode<Key, Value>* newNode = new AVLNode<Key, Value>(keyValuePair.first,keyValuePair.second, NULL);


    if(curr == NULL) //deals with inserting into an empty tree
    {
        newNode->setLeft(NULL);
        newNode->setRight(NULL);
        this->mRoot = newNode;
        return;
        
    }

    while(curr)
    {
        if(curr->getKey() > keyValuePair.first) //new key greater than current key
        {
            if(!curr->getLeft()) //if no left child
            {
                newNode->setParent(curr);
                curr->setLeft(newNode);
                //return;
                break;
            }
            else //if curr already has left child: continue traversal
            {
                curr = curr->getLeft();
            }
        }
        else if(curr->getKey() < keyValuePair.first) //new key less than current key
        {
            if(!curr->getRight()) //if no right child
            {
                newNode->setParent(curr);
                curr->setRight(newNode);
                //return;
                break;
            }
            else //if curr already has a right child: continue traversal
            {
                curr = curr->getRight();
            }
        }
        else //new key is equivalent to current key
        {
            curr->setValue(keyValuePair.second);
            delete newNode;
            //return;
            break;
        }
    }

    //balance after insert
    AVLNode<Key, Value>* statCurr = dynamic_cast<AVLNode<Key,Value>*>(curr);
    if(statCurr->getHeight() != 0)
    {
        statCurr->setHeight(0);
    }
    else
    {
        if(statCurr->getLeft() == newNode)
        {
            statCurr->setHeight(-1);
        }
        else
        {
            statCurr->setHeight(1);
        }
        insertBalance(statCurr, newNode);
    }
    
}

template<typename Key, typename Value>
void AVLTree<Key, Value>::insertBalance(AVLNode<Key, Value>* parent, AVLNode<Key, Value>* child)
{
    AVLNode<Key, Value>* g_parent = parent->getParent();
    if(parent == NULL || g_parent == NULL) return;

    if(parent == g_parent->getLeft()) //parent is left child of g_parent
    {
        g_parent->setHeight(-1);
        if(g_parent->getHeight() == 0)return; //return if balanced already
        if(g_parent->getHeight() == -1)
        {
            insertBalance(g_parent,parent);
            return;
        }
        if(child == parent->getLeft()) //indicated zig zig: one right rotation
        {
            this->rightRotate(g_parent);
            parent->setHeight(0);
            g_parent->setHeight(0);
        }
        else //2 rotations needed to balance zig zag
        {
            this->leftRotate(parent);
            this->rightRotate(g_parent);
            if(child->getHeight() == -1)
            {
                parent->setHeight(0);
                g_parent->setHeight(1);
            }
            else if(child->getHeight() == 0)
            {
                parent->setHeight(0);
                g_parent->setHeight(0);
            }
            else
            {
                parent->setHeight(-1);
                g_parent->setHeight(0);
            }
            child->setHeight(0);
        }
    }
    else //parent is right child of g_parent 
    {
        g_parent->setHeight(1);
        if(g_parent->getHeight() == 0)return;
        if(g_parent->getHeight() == 1)
        {
            insertBalance(g_parent,parent);
            return;
        }
        //g_parent balance = 2
        if(child == parent->getRight()) //1 rotation zig zag
        {
            this->leftRotate(g_parent);
            parent->setHeight(0);
            g_parent->setHeight(0);
        }
        else // 2 rotation zig zag
        {
            this->rightRotate(parent);
            this->leftRotate(g_parent);
            if(child->getHeight() == 1)
            {
                parent->setHeight(0);
                g_parent->setHeight(0);
            }
            else if(child->getHeight() == 0)
            {
                parent->setHeight(0);
                g_parent->setHeight(0);
            }
            else
            {
                parent->setHeight(1);
                g_parent->setHeight(0);
            }
            child->setHeight(0);

        }

    }


}




/**
* Remove function for a given key. Finds the node, reattaches pointers, and then balances when finished. 
*/
template<typename Key, typename Value>
void AVLTree<Key, Value>::remove(const Key& key)
{
   // TODO
AVLNode<Key, Value>* toDelete = dynamic_cast<AVLNode<Key,Value>*>(this->internalFind(key));
//if key can be found: set toDelete = to node at key

    if(!this->internalFind(key))return; //if node in the tree cannot be found: do nothing

    int children = 0; //will keep track of the number of children the node to be deleted has
    if(toDelete->getLeft()) children++;  //if node to delete has a left child increment children
    if(toDelete->getRight()) children++; //if node to delete has a right child increment children
    //Node<Key, Value>* parent = toDelete->getParent();


    if(children == 0)
    {
        if(!toDelete->getParent()) // if node to delete is root
        {
            this->clearHelp(this->mRoot);
            this->mRoot = NULL;
        }
        else
        {
            if(toDelete->getParent()->getLeft() == toDelete) //if node to delete is left child of its parent
            {
                toDelete->getParent()->setLeft(NULL);
            }
            else //otherwise node to delete is right child of its parent
            {
                toDelete->getParent()->setRight(NULL);
            }
            delete toDelete;
        }
    }

    else if(children == 1)
    {
        if(!toDelete->getParent()) //if root node 
        {
            if(toDelete->getLeft()) // if the child is a left child
            {
                this->mRoot = toDelete->getLeft();
                toDelete->getLeft()->setParent(NULL);
            }
            else // otherwise it is a right child
            {
                this->mRoot = toDelete->getRight();
                toDelete->getRight()->setParent(NULL);
            }

            delete toDelete;
        }
        else //not root node 
        {
            if(toDelete->getLeft()) //if child is a left child
            {
                toDelete->getLeft()->setParent(toDelete->getParent());
                if(toDelete->getParent()->getLeft() == toDelete) // if todelete is a left child of parent
                {
                    toDelete->getParent()->setLeft(toDelete->getLeft());
                }
                else // else toDelete is right child of its parent
                {
                    toDelete->getParent()->setRight(toDelete->getLeft());
                }
            }
            else //otherwise child is a right child
            {
                toDelete->getRight()->setParent(toDelete->getParent());
                if(toDelete->getParent()->getLeft() == toDelete) // if todelete is a left child of parent
                {
                    toDelete->getParent()->setLeft(toDelete->getRight());
                }
                else // else toDelete is right child of its parent
                {
                    toDelete->getParent()->setRight(toDelete->getRight());
                }
            }
            delete toDelete;
        }
    }

    else if(children == 2)
    {
        //find predecessor
        Node<Key, Value>* pred = toDelete->getLeft(); //originally set pred to left child of deleted node
        while(pred->getRight()) //traverse right until pred reaches rightmost node of deleted nodes left tree
        {
            pred = pred->getRight();
        }

        if(toDelete->getLeft() == pred) //if pred is direct neighbor of node to be deleted
        {
            if(!toDelete->getParent()) //if root node
            {
                pred->setParent(NULL);
                this->mRoot = pred;
            }
            else  //not the root node
            {
                if(toDelete->getParent()->getLeft() == pred)
                {
                    toDelete->getParent()->setLeft(pred);
                }
                else //else parent of the right node 
                {
                    toDelete->getParent()->setRight(pred);
                }
                pred->setParent(toDelete->getParent());
            }
            pred->setRight(toDelete->getRight());
            toDelete->getRight()->setParent(pred);
        }
        else
        {
            if(pred->getLeft()) //if pred has a left child
            {
                pred->getParent()->setRight(pred->getLeft()); // set paren to the new child
                pred->getLeft()->setParent(pred->getParent()); //set the childs parent
            }
            else
            {
                pred->getParent()->setRight(NULL);
            }
            if(toDelete->getParent()) //if not root node
            {
                if(toDelete->getParent()->getLeft() == toDelete) //set the children of toDelete's parent
                {
                    toDelete->getParent()->setLeft(pred);
                }
                else
                {
                    toDelete->getParent()->setRight(pred);
                }
                pred->setParent(toDelete->getParent());
            }
            else //node to be removed is the root
            {
                this->mRoot = pred;
                pred->setParent(NULL);
            }
            pred->setLeft(toDelete->getLeft());
            toDelete->getLeft()->setParent(pred);
            pred->setRight(toDelete->getRight());
            toDelete->getRight()->setParent(pred);
        }
        delete toDelete;
    }


}

/*
------------------------------------------
End implementations for the AVLTree class.
------------------------------------------
*/

#endif

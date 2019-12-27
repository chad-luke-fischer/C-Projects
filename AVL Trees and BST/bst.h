#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>
#include <algorithm>

/**
* A templated class for a Node in a search tree. The getters for parent/left/right are virtual so that they
* can be overridden for future kinds of search trees, such as Red Black trees, Splay trees, and AVL trees.
*/
template <typename Key, typename Value>
class Node
{
public:
	Node(const Key& key, const Value& value, Node<Key, Value>* parent);
	virtual ~Node();

	const std::pair<Key, Value>& getItem() const;
	std::pair<Key, Value>& getItem();
	const Key& getKey() const;
	const Value& getValue() const;
	Key& getKey();
	Value& getValue();

	virtual Node<Key, Value>* getParent() const;
	virtual Node<Key, Value>* getLeft() const;
	virtual Node<Key, Value>* getRight() const;

	void setParent(Node<Key, Value>* parent);
	void setLeft(Node<Key, Value>* left);
	void setRight(Node<Key, Value>* right);
	void setValue(const Value &value);

protected:
	std::pair<Key, Value> mItem;
	Node<Key, Value>* mParent;
	Node<Key, Value>* mLeft;
	Node<Key, Value>* mRight;
};

/*
	-----------------------------------------
	Begin implementations for the Node class.
	-----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent)
	: mItem(key, value)
	, mParent(parent)
	, mLeft(NULL)
	, mRight(NULL)
{

}

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed within the deleteAll() helper method in the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<Key, Value>& Node<Key, Value>::getItem() const
{
	return mItem;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<Key, Value>& Node<Key, Value>::getItem()
{
	return mItem;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
	return mItem.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
	return mItem.second;
}

/**
* A non-const getter for the key.
*/
template<typename Key, typename Value>
Key& Node<Key, Value>::getKey()
{
	return mItem.first;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
	return mItem.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
	return mParent;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
	return mLeft;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
	return mRight;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
	mParent = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
	mLeft = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
	mRight = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
	mItem.second = value;
}

/*
	---------------------------------------
	End implementations for the Node class.
	---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree
{
	public:
		BinarySearchTree(); //TODO
		virtual ~BinarySearchTree(); //TODO
  		virtual void insert(const std::pair<Key, Value>& keyValuePair); //TODO
        virtual void remove(const Key& key); //TODO
  		void clear(); //TODO
  		void print() const;
  		bool isBalanced() const; //TODO

	public:
		/**
		* An internal iterator class for traversing the contents of the BST.
		*/
		class iterator
		{
			public:
				iterator(Node<Key,Value>* ptr);
				iterator();

				std::pair<Key,Value>& operator*() const;
				std::pair<Key,Value>* operator->() const;

				bool operator==(const iterator& rhs) const;
				bool operator!=(const iterator& rhs) const;
				iterator& operator=(const iterator& rhs);

				iterator& operator++();

			protected:
				Node<Key, Value>* mCurrent;

				friend class BinarySearchTree<Key, Value>;
		};

	public:
		iterator begin() const;
		iterator end() const;
		iterator find(const Key& key) const;

	protected:
		Node<Key, Value>* internalFind(const Key& key) const; //TODO
		Node<Key, Value>* getSmallestNode() const; //TODO
		void printRoot (Node<Key, Value>* root) const;

	protected:
		Node<Key, Value>* mRoot;

	public:
		void print() {this->printRoot(this->mRoot);}
		void clearHelp(Node<Key, Value>* root); //added this helper function to help clear tree
		int height(Node<Key, Value>* root) const; //gets height for isBalanced 
		bool balanceHelp(Node<Key, Value>* root) const;
};

/*
	---------------------------------------------------------------
	Begin implementations for the BinarySearchTree::iterator class.
	---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<typename Key, typename Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value>* ptr)
	: mCurrent(ptr)
{

}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<typename Key, typename Value>
BinarySearchTree<Key, Value>::iterator::iterator()
	: mCurrent(NULL)
{

}

/**
* Provides access to the item.
*/
template<typename Key, typename Value>
std::pair<Key, Value>& BinarySearchTree<Key, Value>::iterator::operator*() const
{
	return mCurrent->getItem();
}

/**
* Provides access to the address of the item.
*/
template<typename Key, typename Value>
std::pair<Key, Value>* BinarySearchTree<Key, Value>::iterator::operator->() const
{
	return &(mCurrent->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::iterator::operator==(const BinarySearchTree<Key, Value>::iterator& rhs) const
{
	return this->mCurrent == rhs.mCurrent;
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::iterator::operator!=(const BinarySearchTree<Key, Value>::iterator& rhs) const
{
	return this->mCurrent != rhs.mCurrent;
}

/**
* Sets one iterator equal to another iterator.
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator &BinarySearchTree<Key, Value>::iterator::operator=(const BinarySearchTree<Key, Value>::iterator& rhs)
{
	this->mCurrent = rhs.mCurrent;
	return *this;
}

/**
* Advances the iterator's location using an in-order traversal.
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator& BinarySearchTree<Key, Value>::iterator::operator++()
{
	if(mCurrent->getRight())
	{
		mCurrent = mCurrent->getRight();
		while(mCurrent->getLeft())
		{
			mCurrent = mCurrent->getLeft();
		}
	}
	else if(!mCurrent->getRight())
	{
		Node<Key, Value>* parent = mCurrent->getParent();
		while(parent != NULL && mCurrent == parent->getRight())
		{
			mCurrent = parent;
			parent = parent->getParent();
		}
		mCurrent = parent;
	}
	return *this;
}

/*
	-------------------------------------------------------------
	End implementations for the BinarySearchTree::iterator class.
	-------------------------------------------------------------
*/

/*
	-----------------------------------------------------
	Begin implementations for the BinarySearchTree class.
	-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<typename Key, typename Value>
BinarySearchTree<Key, Value>::BinarySearchTree()
{
	// TODO
	mRoot = NULL;
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
	// TODO
	clear();
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
	printRoot(mRoot);
	std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator BinarySearchTree<Key, Value>::begin() const
{
	BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
	return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator BinarySearchTree<Key, Value>::end() const
{
	BinarySearchTree<Key, Value>::iterator end(NULL);
	return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator BinarySearchTree<Key, Value>::find(const Key& key) const
{
	Node<Key, Value>* curr = internalFind(key);
	BinarySearchTree<Key, Value>::iterator it(curr);
	return it;
}

/**
* An insert method to insert into a Binary Search Tree. The tree will not remain balanced when
* inserting.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<Key, Value>& keyValuePair)
{
	// TODO
	Node<Key, Value>* curr = mRoot;
	Node<Key, Value>* newNode = new Node<Key, Value>(keyValuePair.first,keyValuePair.second, NULL);


	if(!curr) //deals with inserting into an empty tree
	{
		mRoot = newNode;
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
				return;
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
				return;
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
			return;
		}
	}
}

/**
* An remove method to remove a specific key from a Binary Search Tree. The tree may not remain balanced after
* removal.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
	// TODO
	
	Node<Key, Value>* toDelete = internalFind(key);//if key can be found: set toDelete = to node at key

	if(!internalFind(key))return; //if node in the tree cannot be found: do nothing

	int children = 0; //will keep track of the number of children the node to be deleted has
	if(toDelete->getLeft()) children++;  //if node to delete has a left child increment children
	if(toDelete->getRight()) children++; //if node to delete has a right child increment children
	//Node<Key, Value>* parent = toDelete->getParent();


	if(children == 0)
	{
		if(!toDelete->getParent()) // if node to delete is root
		{
			clearHelp(mRoot);
			mRoot = NULL;
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
				mRoot = toDelete->getLeft();
				toDelete->getLeft()->setParent(NULL);
			}
			else // otherwise it is a right child
			{
				mRoot = toDelete->getRight();
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
				mRoot = pred;
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
				mRoot = pred;
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
/**
* A method to remove all contents of the tree and reset the values in the tree
* for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
	// TODO
	clearHelp(mRoot);
	mRoot = NULL;

}

//helper function to aid in clearing the tree
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clearHelp(Node<Key, Value>* root)
{
	if(root!=NULL)
	{
		clearHelp(root->getLeft());
		clearHelp(root->getRight());
		delete root;
	}

}

/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::getSmallestNode() const
{
	// TODO
	//traverse left side of the tree until smallest leaf is found
	Node<Key, Value>* curr = mRoot;
	if(!curr) return curr;
	
	while(curr)
	{
		if(curr->getLeft())
		{
			curr = curr->getLeft();
		}
		else break;
	}
	return curr;
}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
	// TODO
	Node<Key, Value>* cnode = mRoot;
	while(cnode)
	{
		if(cnode->getKey() == key) return cnode;
		else if (key > cnode->getKey()) cnode =  cnode->getRight();
		else if(key < cnode->getKey()) cnode = cnode->getLeft();
	}
	return NULL;
}

 template<typename Key, typename Value>
 int BinarySearchTree<Key, Value>::height(Node<Key, Value>* root) const //gets height for isBalanced 
 {
 	if(root == nullptr)return 0;
 	return 1 + std::max(height(root->getLeft()), height(root->getRight()));
	}

template<typename Key, typename Value>
 bool BinarySearchTree<Key, Value>::balanceHelp(Node<Key, Value>* root) const
 {
 	Node<Key, Value>* cnode = root;
	int rhs, lhs;

	if(cnode == nullptr) return true;
	lhs = height(cnode->getLeft());
	rhs = height(cnode->getRight());
	if((abs(lhs-rhs) <= 1) && balanceHelp(cnode->getLeft()) && balanceHelp(cnode->getRight()))return true;
	return false;

 }

// /**
//  * Return true iff the BST is an AVL Tree.
//  */
 template<typename Key, typename Value>
 bool BinarySearchTree<Key, Value>::isBalanced() const
 {
 	Node<Key, Value>* cnode = mRoot;
 	return balanceHelp(cnode);
 }


/**
 * Lastly, we are providing you with a print function, BinarySearchTree::printRoot().
   Just call it with a node to start printing at, e.g:
   this->printRoot(this->mRoot)

   It will print up to 5 levels of the tree rooted at the passed node, in ASCII graphics format.
   We hope it will make debugging easier!
  */

// include print function (in its own file because it's fairly long)
#include "print_bst.h"

/*
	---------------------------------------------------
	End implementations for the BinarySearchTree class.
	---------------------------------------------------
*/

#endif

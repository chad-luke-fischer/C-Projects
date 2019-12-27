#include "bst.h"
#include <iostream>
#include <algorithm>
#include <vector>

template<typename Key, typename Value>
class rotateBST:public BinarySearchTree<Key, Value>
{
public:
	bool sameKeys(const rotateBST& t2)const;
	void transform(rotateBST& t2) const;
protected:
	void leftRotate(Node<Key, Value>* r);
	void rightRotate(Node<Key, Value>* r);
private:
	void transformHelp(Node<Key, Value>* first,Node<Key, Value>* second, rotateBST<Key, Value>& t2) const;

};

template<typename Key, typename Value>
bool rotateBST<Key, Value>::sameKeys(const rotateBST& t2)const
{
	typename rotateBST<Key, Value>::iterator first(this->getSmallestNode());
	typename rotateBST<Key, Value>::iterator second(t2.getSmallestNode());

	while(first!=NULL && second!=NULL)
	{
		if(first->first != second->first)
		{
			return false;
		}
		++first;
		++second;
	}

	if(first!=NULL || second!=NULL)return false;
	else return true;
}

template<typename Key, typename Value>
void rotateBST<Key, Value>::transform(rotateBST& t2) const
{
	//t2.rightRotate(t2.mRoot);
	// Perform right rotations on the root node of t2 until it has no left child.
	// Recursively move to the right child and repeat the above operation.
	// This should produce a tree which is effectively a linked list.
	// Now perform left rotations on the root node of t2, until the root of t2 is the same as the root of this.
	// Recursively do rotations on the left child and the right child until they match the node at that position of this.
	// This should produce the specified tree using only rotations.
		if(sameKeys(t2) == false)return;
		else transformHelp(NULL, NULL, t2);
}

template<typename Key, typename Value>
void rotateBST<Key, Value>::transformHelp(Node<Key, Value>* first,Node<Key, Value>* second, rotateBST<Key, Value>& t2) const 
{
	if(!first && !second) //on first call: first and second both are NULL
	{
		while(t2.mRoot->getLeft())
		{
			t2.rightRotate(t2.mRoot);
		}
		Node<Key, Value>* temp = t2.mRoot;
		while(temp->getRight())
		{
			while(temp->getRight()->getLeft()) //infinite loop here
			{
				t2.rightRotate(temp->getRight());
			}
			temp = temp->getRight();
		}
		while(this->mRoot->getKey() != t2.mRoot->getKey())
		{
			t2.leftRotate(t2.mRoot);
		}
		transformHelp(this->mRoot, t2.mRoot, t2);
	}

	else //not the first call to helper
	{
		if(second->getLeft()) //make the left of second a linked list
		{
			while(second->getLeft()->getLeft())
			{
				t2.rightRotate(second->getLeft());
			}
			Node<Key, Value>* temp2 = second->getLeft();
			while(temp2->getRight())
			{
				while(temp2->getRight()->getLeft())
				{
					t2.rightRotate(temp2->getRight());
				}
				temp2 = temp2->getRight();
			}
			while(first->getLeft()->getKey() != second->getLeft()->getKey()) //make the key the same value
			{
				t2.leftRotate(second->getLeft());
			}
			transformHelp(first->getLeft(), second->getLeft(), t2);
		}
		if(second->getRight())
		{
			while(second->getRight()->getLeft())
			{
				t2.rightRotate(second->getRight());
			}
			Node<Key, Value>* temp3 = second->getRight();
			while(temp3->getRight())
			{
				while(temp3->getRight()->getLeft())
				{
					t2.rightRotate(temp3->getRight());
				}
				temp3 = temp3->getRight();
			}
			while(first->getRight()->getKey() != second->getRight()->getKey())
			{
				t2.leftRotate(second->getRight());
			}
			transformHelp(first->getRight(), second->getRight(), t2);
		}
	}
 }

template<typename Key, typename Value>
void rotateBST<Key, Value>::leftRotate(Node<Key, Value>* r)
{
	Node<Key, Value>* z = r;

	if(!z->getRight())return; //check if z has a right child: if not return
	else
	{
		Node<Key, Value>* y = z->getRight();
		if(!z->getParent()) //case where z is the root node
		{
			this->mRoot = y;
			y->setParent(NULL);
		}
		else //case where z is not root node
		{
			if(z->getParent()->getLeft() == z) //if z is the right child of its parent
			{
				y->setParent(z->getParent());
				z->getParent()->setLeft(y);
			}
			else //otherwise z is the left child of its parent
			{	
				y->setParent(z->getParent());
				z->getParent()->setRight(y);
			}

		}
		z->setParent(y); //y becomes parent of z as it is rotated down
		if(y->getLeft())
		{
		 z->setRight(y->getLeft()); //if y has a left child... set it as right child of z
		 y->getLeft()->setParent(z);
		}
		else
		{
			z->setRight(NULL);
		}
		y->setLeft(z); //make z the left child of y
	}

}

template<typename Key, typename Value>
void rotateBST<Key, Value>::rightRotate(Node<Key, Value>* r)
{
	Node<Key, Value>* z = r;

	if(!z->getLeft())return; //check if z has a left child: if not return
	else
	{
		Node<Key, Value>* y = z->getLeft();
		if(!z->getParent()) //case where z is the root node
		{
			this->mRoot = y;
			y->setParent(NULL);
		}
		else //case where z is not the root node
		{
			if(z->getParent()->getLeft() == z) //if z is the right child of its parent
			{
				y->setParent(z->getParent());
				z->getParent()->setLeft(y);
			}
			else //otherwise z is the left child of its parent
			{	
				y->setParent(z->getParent());
				z->getParent()->setRight(y);
			}

		}
		z->setParent(y); //y becomes parent of z as it is rotated down
		if(y->getRight())
		{
			z->setLeft(y->getRight());
			y->getRight()->setParent(z);
		}
		else
		{
			z->setLeft(NULL);
		}
		y->setRight(z);
	}


}







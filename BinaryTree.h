// Binary tree abstract base class
// Created by Frank M. Carrano and Tim Henry.
// Modified by:
 
#ifndef _BINARY_TREE
#define _BINARY_TREE

#include "BinaryNode.h"
#include "QueueADT.h"

template<class ItemType>
class BinaryTree
{
protected:
	BinaryNode<ItemType>* rootPtr;		// ptr to root node
	int count;							// number of nodes in tree

public:
	// "admin" functions
 	BinaryTree() {rootPtr = 0; count = 0;}
	BinaryTree(const BinaryTree<ItemType> & tree){ }
	virtual ~BinaryTree() { clear(); }
	BinaryTree & operator = (const BinaryTree & sourceTree);
   
	// common functions for all binary trees
 	bool isEmpty() const	{return count == 0;}
	int size() const	    {return count;}
	void clear()			{destroyTree(rootPtr); rootPtr = 0; count = 0;}
	void preOrder(void visit(ItemType &)) const {_preorder(visit, rootPtr);}
	void inOrder(void visit(ItemType &)) const  {_inorder(visit, rootPtr);}
	void postOrder(void visit(ItemType &)) const{_postorder(visit, rootPtr);}

	void breadthOrder(void visit(ItemType &)) const{_breadthorder(visit, rootPtr);}

	void inOrderTree(void visit(ItemType &, int)) const  {_inordertree(visit, rootPtr, 1);}

	// abstract functions to be implemented by derived class
	virtual bool insert(const ItemType & newData) = 0; 
	virtual bool remove(const ItemType & data) = 0; 
	virtual bool getEntry(const ItemType & anEntry, ItemType & returnedItem) const = 0;

private:   
	// delete all nodes from the tree
	void destroyTree(BinaryNode<ItemType>* nodePtr);

	// copy from the tree rooted at nodePtr and returns a pointer to the copy
	BinaryNode<ItemType>* copyTree(const BinaryNode<ItemType>* nodePtr);

	// internal traverse
	void _preorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
	void _inorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
	void _postorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
//_breadthorder
	void _breadthorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
	void _inordertree(void visit(ItemType &, int), BinaryNode<ItemType>* nodePtr, int level) const;
   
}; 

//////////////////////////////////////////////////////////////////////////

template<class ItemType>
BinaryNode<ItemType>* BinaryTree<ItemType>::copyTree(const BinaryNode<ItemType>* nodePtr) 
{
	BinaryNode<ItemType>* newNodePtr = 0;
    
   
    return newNodePtr;
}  

template<class ItemType>
void BinaryTree<ItemType>::destroyTree(BinaryNode<ItemType>* nodePtr)
{
	if (nodePtr == 0){
		return;
	}
	destroyTree(nodePtr->getLeftPtr());
	destroyTree(nodePtr->getRightPtr());
	delete nodePtr;
}  

template<class ItemType>
void BinaryTree<ItemType>::_preorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
	if (nodePtr != 0)
	{
		ItemType item = nodePtr->getItem();
		visit(item);
		_preorder(visit, nodePtr->getLeftPtr());
		_preorder(visit, nodePtr->getRightPtr());
	} 
}  

template<class ItemType>
void BinaryTree<ItemType>::_inorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
	if (nodePtr != 0)
	{
		ItemType item = nodePtr->getItem();
		_inorder(visit, nodePtr->getLeftPtr());
		visit(item);
		_inorder(visit, nodePtr->getRightPtr());
	}
}  

template<class ItemType>
void BinaryTree<ItemType>::_postorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
	if (nodePtr != 0)
	{
		ItemType item = nodePtr->getItem();
		_postorder(visit, nodePtr->getLeftPtr());
		_postorder(visit, nodePtr->getRightPtr());
		visit(item);
	}
}  

template<class ItemType>
void BinaryTree<ItemType>::_breadthorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const{
	Queue<BinaryNode<ItemType>*> q;
	q.enqueue(nodePtr);
	BinaryNode<ItemType>* currPtr;
	while(!q.isEmpty()){
		q.dequeue(currPtr);
		ItemType item = currPtr->getItem();
		visit(item);
		if (currPtr->getLeftPtr() != 0){
			q.enqueue(currPtr->getLeftPtr());
		}
		if (currPtr->getRightPtr() != 0){
			q.enqueue(currPtr->getRightPtr());
		}
	}
}

template<class ItemType>
void BinaryTree<ItemType>::_inordertree(void visit(ItemType &, int), BinaryNode<ItemType>* nodePtr, int level) const
{
	if (nodePtr != 0)
	{
		ItemType item = nodePtr->getItem();
		_inordertree(visit, nodePtr->getLeftPtr(), level + 1);
		visit(item, level);
		_inordertree(visit, nodePtr->getRightPtr(), level + 1);
	}
}

template<class ItemType>
BinaryTree<ItemType> & BinaryTree<ItemType>::operator=(const BinaryTree<ItemType> & sourceTree)
{

}  


#endif


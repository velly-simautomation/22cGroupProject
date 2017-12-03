// Binary Search Tree ADT
// Created by Frank M. Carrano and Tim Henry.
// Modified by:
 
#ifndef _BINARY_SEARCH_TREE
#define _BINARY_SEARCH_TREE

#include "BinaryTree.h"

template<class ItemType>
class BinarySearchTree : public BinaryTree<ItemType>
{   
private:
	// internal insert node: insert newNode in nodePtr subtree
	BinaryNode<ItemType>* _insert(BinaryNode<ItemType>* nodePtr, BinaryNode<ItemType>* newNode);
   
	// internal remove node: locate and delete target node under nodePtr subtree
	BinaryNode<ItemType>* _remove(BinaryNode<ItemType>* nodePtr, const ItemType target, bool & success);
   
	// delete target node from tree, called by internal remove node
	BinaryNode<ItemType>* deleteNode(BinaryNode<ItemType>* targetNodePtr);
   
	// remove the leftmost node in the left subtree of nodePtr
	BinaryNode<ItemType>* removeLeftmostNode(BinaryNode<ItemType>* nodePtr, ItemType & successor);
   
	// search for target node
	BinaryNode<ItemType>* findNode(BinaryNode<ItemType>* treePtr, const ItemType & target) const;

	// compare function
	int (*comp)( ItemType &,  ItemType &) = nullptr;
   
public:  
	//constructor
	BinarySearchTree(int compare( ItemType &,  ItemType &)){ comp = compare; }

	// insert a node at the correct location
    bool insert(const ItemType & newEntry);
	// remove a node if found
	bool remove(const ItemType & anEntry);
	// find a target node
	bool getEntry(const ItemType & target, ItemType & returnedItem) const;
	bool getMinEntry(ItemType & returnedItem) const;
	bool getMaxEntry(ItemType & returnedItem) const;

	//set compare function.
	//void setCompareFcn(int compare(ItemType &, ItemType &)){ compareNode = compare; }
};


///////////////////////// public function definitions ///////////////////////////

template<class ItemType>
bool BinarySearchTree<ItemType>::insert(const ItemType & newEntry)
{
	if (comp == nullptr){
		return false;
	}

	BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(newEntry);
	this->rootPtr = _insert(this->rootPtr, newNodePtr);
	return true;
}  

template<class ItemType>
bool BinarySearchTree<ItemType>::remove(const ItemType & target)
{
	if (comp == nullptr){
		return false;
	}
	bool isSuccessful = false;
	this->rootPtr = _remove(this->rootPtr, target, isSuccessful);
	return isSuccessful; 
}  

template<class ItemType>
bool BinarySearchTree<ItemType>::getEntry(const ItemType& anEntry, ItemType & returnedItem) const
{
	if (comp == nullptr){
		return false;
	}
	BinaryNode<ItemType>* targetNodePtr;
	bool isSuccessful = false;

	//BinaryNode<ItemType>* findNode(BinaryNode<ItemType>* treePtr, const ItemType & target)
	targetNodePtr = findNode(this->rootPtr, anEntry);
	if (targetNodePtr != 0){
		isSuccessful = true;
		returnedItem = targetNodePtr->getItem();
	}
    return isSuccessful;
}  



//////////////////////////// private functions ////////////////////////////////////////////

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_insert(BinaryNode<ItemType>* nodePtr,
                                                          BinaryNode<ItemType>* newNodePtr)
{
	if (nodePtr == 0){
		nodePtr = newNodePtr;
	}
	else{
		ItemType lhs = nodePtr->getItem();
		ItemType rhs = newNodePtr->getItem();
		if (comp(lhs, rhs) > 0){ //if (nodePtr->getItem() > newNodePtr->getItem())
			nodePtr->setLeftPtr(_insert(nodePtr->getLeftPtr(), newNodePtr));
		}
		else { //if (nodePtr->getItem() <= newNodePtr->getItem())
			nodePtr->setRightPtr(_insert(nodePtr->getRightPtr(), newNodePtr));
		}
	}
	return nodePtr;
}  

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_remove(BinaryNode<ItemType>* nodePtr,
                                                          const ItemType target,
                                                          bool & success)

{
	if (nodePtr == 0)                   
	{
		success = false;
		return 0;
	}
	ItemType lhs = nodePtr->getItem();
	ItemType rhs = target;
	if (comp(lhs, rhs) > 0) //	nodePtr->getItem() > target
		nodePtr->setLeftPtr(_remove(nodePtr->getLeftPtr(), target, success));
	else if (comp(lhs, rhs) < 0)	 //nodePtr->getItem() < target
		nodePtr->setRightPtr(_remove(nodePtr->getRightPtr(), target, success));
	else		
	{
		nodePtr = deleteNode(nodePtr);
		success = true;
	}      
	return nodePtr;   
}  

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::deleteNode(BinaryNode<ItemType>* nodePtr)
{
	if (nodePtr->isLeaf())				
	{
		delete nodePtr;
		nodePtr = 0;
		return nodePtr;
	}
	else if (nodePtr->getLeftPtr() == 0)  
	{
		BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getRightPtr();
		delete nodePtr;
		nodePtr = 0;
		return nodeToConnectPtr;
	}
	else if (nodePtr->getRightPtr() == 0) 
	{
		BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getLeftPtr();
		delete nodePtr;
		nodePtr = 0;
		return nodeToConnectPtr;      
	}
	else                                  
	{
		ItemType newNodeValue;
		nodePtr->setRightPtr(removeLeftmostNode(nodePtr->getRightPtr(), newNodeValue));
		nodePtr->setItem(newNodeValue);
		return nodePtr;
	}  
}  

template<class ItemType> 
BinaryNode<ItemType>* BinarySearchTree<ItemType>::removeLeftmostNode(BinaryNode<ItemType>* nodePtr,
                                                                     ItemType & successor)
{
	if (nodePtr->getLeftPtr() == 0)
	{
		successor = nodePtr->getItem();
		return deleteNode(nodePtr);
	}
	else 
	{
		nodePtr->setLeftPtr(removeLeftmostNode(nodePtr->getLeftPtr(), successor));
		return nodePtr;
	}       
}


template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::findNode(BinaryNode<ItemType>* nodePtr,
                                                           const ItemType & target) const 
{
	BinaryNode<ItemType>* targetNode;
	if (nodePtr == 0)
	{
		//success = false;
		return 0;
	}
	ItemType lhs = nodePtr->getItem();
	ItemType rhs = target;
	if (comp(lhs, rhs) > 0){ //nodePtr->getItem() > target
		targetNode = findNode(nodePtr->getLeftPtr(), target);
	}
	else if (comp(lhs, rhs) < 0){ //nodePtr->getItem() < target
		targetNode = findNode(nodePtr->getRightPtr(), target);
	}
	else
	{
		targetNode = nodePtr;
		//success = true;
	}
	return targetNode;
}  

template<class ItemType>
bool BinarySearchTree<ItemType>::getMinEntry(ItemType & returnedItem) const{
	BinaryNode<ItemType>* nodePtr;
	nodePtr = this->rootPtr;
	if (nodePtr == 0){
		return false;
	}

	while (nodePtr->getLeftPtr() != 0){
		nodePtr = nodePtr->getLeftPtr();
	}
	returnedItem = nodePtr->getItem();
	return true;
}

template<class ItemType>
bool BinarySearchTree<ItemType>::getMaxEntry(ItemType & returnedItem) const{
	BinaryNode<ItemType>* nodePtr;
	nodePtr = this->rootPtr;
	if (nodePtr == 0){
		return false;
	}

	while (nodePtr->getRightPtr() != 0){
		nodePtr = nodePtr->getRightPtr();
	}
	returnedItem = nodePtr->getItem();
	return true;
}

#endif

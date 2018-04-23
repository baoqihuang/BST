/*
 * BinarySearchTree.h
 *
 *  Created on: Jul 18, 2017
 *      Author: michaelhuang
 */

#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H
#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
using namespace std;
// BinarySearTree template class
template <class T>
class BinarySearchTree
{
private:
   struct TreeNode
   {
      T value;           // The value in the node
      TreeNode *left;    // Pointer to left child node
      TreeNode *right;   // Pointer to right child node
   };

   TreeNode *root;       // Pointer to the root node

   // Private member functions
   void insert(TreeNode *&, TreeNode *&);
   void destroySubTree(TreeNode *&);
   void deleteNode(T, TreeNode *&);
   void makeDeletion(TreeNode *&);
   void displayInOrder(TreeNode *) const;
   void displayPreOrder(TreeNode *) const;
   void displayPostOrder(TreeNode *) const;
   void insertInOrder(vector<T>&, TreeNode *) ;

public:
   // Constructor
   BinarySearchTree()
      { root = nullptr; }

   // Destructor
   ~BinarySearchTree()
      { destroySubTree(root); }

   // Binary tree operations
   void insertNode(T);
   bool searchNode(T);
   void remove(T);

   void displayInOrder() const
      {  displayInOrder(root); }

   void displayPreOrder() const
      { displayPreOrder(root); }

   void displayPostOrder() const
      {  displayPostOrder(root); }

   void insertInOrder() const
      {  vector<T>v;
      insertInOrder(v,root); }

   void printTraversals() const;

   void recursiveInsert(vector<T> const &, int, int) ;

   void balance() ;
};

//*************************************************************
// insert accepts a TreeNode pointer and a pointer to a node. *
// The function inserts the node into the tree pointed to by  *
// the TreeNode pointer. This function is called recursively. *
//*************************************************************
template <class T>
void BinarySearchTree<T>::insert(TreeNode *&nodePtr, TreeNode *&newNode)
{
   if (nodePtr == nullptr)
      nodePtr = newNode;                  // Insert the node.
   else if (newNode->value < nodePtr->value)
      insert(nodePtr->left, newNode);     // Search the left branch
   else
      insert(nodePtr->right, newNode);    // Search the right branch
}

//**********************************************************
// insertNode creates a new node to hold num as its value, *
// and passes it to the insert function.                   *
//**********************************************************
template <class T>
void BinarySearchTree<T>::insertNode(T item)
{
   TreeNode *newNode = nullptr;	// Pointer to a new node.

   // Create a new node and store num in it.
   newNode = new TreeNode;
   newNode->value = item;
   newNode->left = newNode->right = nullptr;

   // Insert the node.
   insert(root, newNode);

}

//***************************************************
// destroySubTree is called by the destructor. It   *
// deletes all nodes in the tree.                   *
//***************************************************
///*
template <class T>
void BinarySearchTree<T>::destroySubTree(TreeNode *&nodePtr)
{
   if (nodePtr)
   {

      if (nodePtr->left)
         destroySubTree(nodePtr->left);
      if (nodePtr->right)
         destroySubTree(nodePtr->right);
      delete nodePtr;
      nodePtr = nullptr;
   }
}
//***************************************************
// searchNode determines if a value is present in   *
// the tree. If so, the function returns true.      *
// Otherwise, it returns false.                     *
//***************************************************
template <class T>
bool BinarySearchTree<T>::searchNode(T item)
{
   TreeNode *nodePtr = root;

   while (nodePtr)
   {
      if (nodePtr->value == item)
         return true;
      else if (item < nodePtr->value)
         nodePtr = nodePtr->left;
      else
         nodePtr = nodePtr->right;
   }
   return false;
}

//**********************************************
// remove calls deleteNode to delete the       *
// node whose value member is the same as num. *
//**********************************************
template <class T>
void BinarySearchTree<T>::remove(T item)
{
   deleteNode(item, root);
}

//********************************************
// deleteNode deletes the node whose value   *
// member is the same as num.                *
//********************************************
template <class T>
void BinarySearchTree<T>::deleteNode(T item, TreeNode *&nodePtr)
{
   if (item < nodePtr->value)
      deleteNode(item, nodePtr->left);
   else if (item > nodePtr->value)
      deleteNode(item, nodePtr->right);
   else
      makeDeletion(nodePtr);
}

//***********************************************************
// makeDeletion takes a reference to a pointer to the node  *
// that is to be deleted. The node is removed and the       *
// branches of the tree below the node are reattached.      *
//***********************************************************
template <class T>
void BinarySearchTree<T>::makeDeletion(TreeNode *&nodePtr)
{
   // Define a temporary pointer to use in reattaching
   // the left subtree.
   TreeNode *tempNodePtr = nullptr;

   if (nodePtr == nullptr)
      cout << "Cannot delete empty node.\n";
   else if (nodePtr->right == nullptr)
   {
      tempNodePtr = nodePtr;
      nodePtr = nodePtr->left;   // Reattach the left child
      delete tempNodePtr;
   }
   else if (nodePtr->left == nullptr)
   {
      tempNodePtr = nodePtr;
      nodePtr = nodePtr->right;  // Reattach the right child
      delete tempNodePtr;
   }
   // If the node has two children.
   else
   {
      // Move one node the right.
      tempNodePtr = nodePtr->right;
      // Go to the end left node.
      while (tempNodePtr->left)
         tempNodePtr = tempNodePtr->left;
      // Reattach the left subtree.
      tempNodePtr->left = nodePtr->left;
      tempNodePtr = nodePtr;
      // Reattach the right subtree.
      nodePtr = nodePtr->right;
      delete tempNodePtr;
   }
}

//****************************************************************
// The displayInOrder member function displays the values        *
// in the subtree pointed to by nodePtr, via inorder traversal.  *
//****************************************************************
template <class T>
void BinarySearchTree<T>::displayInOrder(TreeNode *nodePtr) const
{
   if (nodePtr)
   {
      displayInOrder(nodePtr->left);
      cout << nodePtr->value << " ";
      displayInOrder(nodePtr->right);
   }
}


//****************************************************************
// The displayPreOrder member function displays the values       *
// in the subtree pointed to by nodePtr, via preorder traversal. *
//****************************************************************
template <class T>
void BinarySearchTree<T>::displayPreOrder(TreeNode *nodePtr) const
{
   if (nodePtr)
   {
      cout << nodePtr->value << " ";
      displayPreOrder(nodePtr->left);
      displayPreOrder(nodePtr->right);
   }
}

//****************************************************************
// The displayPostOrder member function displays the values      *
// in the subtree pointed to by nodePtr, via postorder traversal.*
//****************************************************************
template <class T>
void BinarySearchTree<T>::displayPostOrder(TreeNode *nodePtr) const
{
   if (nodePtr)
   {
      displayPostOrder(nodePtr->left);
      displayPostOrder(nodePtr->right);
      cout << nodePtr->value << " ";
   }
}

//****************************************************************
// The printTraversals member function displays the values       *
// in three orders: pre-order, post-order, in-order separately.  *
//****************************************************************
template <class T>
void BinarySearchTree<T>::printTraversals() const
{
	cout  << setw(12) << left << "Pre-order:";
	displayPreOrder();
	cout << endl;
	cout  << setw(12) << left << "In-order:";
	displayInOrder();
	cout << endl;
	cout << setw(12) << left << "Post-order:";
	displayPostOrder();
	cout << endl;

}

//******************************************************************
// The balances the BST by creating a new tree with the middle     *
//element as the root, and then recursively does the same with the *
//leftand right subtrees of the new tree using the elements that   *
//are less than the middle element and greaterthan the middle      *
//element,respectively.                                            *
//******************************************************************
template <class T>
void BinarySearchTree<T>::balance()
{
	vector<T> v;
	insertInOrder(v, root);
	destroySubTree(root);
	recursiveInsert(v, 0, v.size()-1);
}

//****************************************************************
//The recursiveInsert member function recursively get entry form *
//vector to a new tree                                           *
//****************************************************************
template <class T>
void BinarySearchTree<T>::recursiveInsert(vector<T> const &v, int lowIdx, int highIdx)
{
	if(lowIdx <= highIdx)
	{
		int midIdx = floor((lowIdx + highIdx)/2);
		insertNode(v[midIdx]);
		recursiveInsert(v, lowIdx,midIdx - 1);
		recursiveInsert(v, midIdx + 1, highIdx);
	}
}

//****************************************************************
// The insertInOrder member function insert the values           *
// in the subtree pointed to by nodePtr, via inorder traversal.  *
// and insert one by one into a vector*                          *
//****************************************************************
template <class T>
void BinarySearchTree<T>::insertInOrder(vector<T> &v, TreeNode *nodePtr)
{
   if (nodePtr)
   {
      insertInOrder(v,nodePtr->left);
      v.push_back(nodePtr->value);
      insertInOrder(v,nodePtr->right);
   }
}
#endif



//============================================================================
// Name        : project2.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <vector>
#include "BinarySearchTree.h"

using namespace std;

int main() {
	int numOfTree = 0, numOfNode = 0;
	int newEntry;
	BinarySearchTree<int> *treePtr = nullptr;
	ifstream inputFile;
	// greeting information and intraduction
	cout << "Hello ! This a binary search tree project " <<endl;
	cout << "It going to read a input.txt file" <<endl;
	cout << "Print each nodes in each trees respectively in in-order, pre-order, post-order" <<endl;
	cout << "Balanced each tree and print three orders again" <<endl;
	inputFile.open("input.txt");
	//read input.txt successfully
	if (inputFile)
	{

		//get the number of trees from file
		inputFile >> numOfTree;
		//create BST
		treePtr = new BinarySearchTree<int> [numOfTree];
		for(int i = 0; i < numOfTree; i++)
		{
			//get the number of nodes for each trees from file
			inputFile >> numOfNode;

			for(int j = 0; j < numOfNode; j++)
			{
				//get each entries for each trees from file
				inputFile >> newEntry;
				//insert entries one by one into each trees
				treePtr[i].insertNode(newEntry);
			}
		}
	}
	else
		cout << "Fail to read from file";

	for(int k = 0; k < numOfTree; k++)
	{
		cout << "Tree  " << k + 1  << endl;
		//print each trees in three order
		treePtr[k].printTraversals();
		treePtr[k].balance();
		cout << "Balanced Tree  " << k + 1 << endl;
		//print each trees in three order and print again after balanced
		treePtr[k].printTraversals();
	}

	cout << "Thank you !" <<endl;
	return 0;
}

/*******************************************************************************************************************************************************************************

Triangle
By starting at the top of the triangle and moving to adjacent numbers on the row below, the maximum total from top to 
bottom is 27.

        5
      9   6
    4   6   8
  0   7   1   5

I.e. 5 + 9 + 6 + 7 = 27.

Write a program in a language of your choice to find the maximum total from top to bottom in triangle.txt, a text file 
containing a triangle with 100 rows. 
Send your solution and resume to [123456 AT yodle dot com], replacing 123456 with the maximum sum for the triangle. 
********************************************************************************************************************************************************************************/


// TriangleTree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <string>

#define EOF -1
using namespace std;

class Node
{
public:
	Node(int valpassed)		// constructor
	{
		data = valpassed;
		next = NULL;
	}

	int data;	// data stored in this node
	Node *left, *right;
	Node *next, *prev;
};


int _tmain(int argc, _TCHAR* argv[])
{
	ifstream triangleInputFile;

	Node *head= NULL;
	Node *curr = NULL; 
	int nodeValue, nodeCount=0;
	char c = 0;

	Node *firstNode = NULL;							// keeps track of the 1st Node on each tree level (line)
	Node *prevNode = NULL;

	// Now let's read in the Triangle.txt file
	/******************************************
		5
		8 9
		1 3 7
	*******************************************/
	triangleInputFile.open("triangle.txt", ios::in);
	if (triangleInputFile.is_open())
	{
		//cout << endl << endl;
		do {
				triangleInputFile >> nodeValue; // read in the next int value 5
				curr = new Node(nodeValue);		// 5
				nodeCount++;
				//cout << nodeValue << "\t";
				// test if we need to link firstNode->left to the next Node being read in which is the firstNode of the next line
				if (c == '\n'){					// lets add 86
					firstNode->left = curr;		// links 51-->left to 86
					firstNode = firstNode->left;// need to move firstNode to the new line below
					prevNode = curr;
					c = 0;
				}
				else{	// we need to link previously created Node to newly created Node
					if (head == NULL){
						head = curr;
						firstNode = head;			
						//curr = head;
						}
					else {
						prevNode->next = curr;		// links 86-->next to 9
						curr->prev = prevNode;		// links 9--->prev to 86
						prevNode = curr;			// update the prevNode
						}
				}

				c = triangleInputFile.get();	// test for end of line
				if (c == '\n') {				// if a newline is found, let's update the line counter
												// there are no more items to attach to the right of the current Node
					//cout << "NEW LINE found" << endl;
				}
		} while (c != EOF);

	}

	// hopefully the tree was properly linked up
	// Let's display it using a nested forloop
	//cout << endl << endl << "---------------------------------------------------------" << endl << endl;
	/*
	curr = head;
	firstNode = curr;

	while (firstNode != NULL)
	{
		// traverse the entire line and display Nodes
		//cout << curr->data << "\t";
		if (curr->next == NULL)				// are we at end of the line?
		{
			firstNode = firstNode->left;	// jump down to next line
			curr = firstNode;
		}
		else
			curr = curr->next;				// advance the pointer to next Node
	}
	*/
	/************************************************************************
		Now let's try to fully link up the Nodes and form the triangle tree

			  5				5 + 9 + 7 = 21
			 / \
			8   9
		   / \ / \
		  1   3   7

	*************************************************************************
		Traverse the tree using 2 Line pointers: Top, Bottom

		Ex: Linking Levels 2nd, 3rd 
		Top = 8
		Bottom = 1
		for Loop focuses on Top line, links downward
		8->left = 1
		8->right= 3
		9->left = 3
		9->right= 7
	*************************************************************************/
	Node *topNode, *bottomNode;

	topNode = head;
	bottomNode = topNode->left;
	firstNode = topNode;

	while (topNode != NULL){

		topNode->left = bottomNode; // this will be a bit redundant for the left-most Node
		topNode->right = bottomNode->next;

		topNode = topNode->next;
		if (topNode == NULL)
		{
			topNode = firstNode->left;
			bottomNode = topNode->left;
			if (bottomNode != NULL)
				firstNode = firstNode->left;
			else
				topNode = NULL;
		}
		else
			bottomNode = bottomNode->next;
	}

	// Traverse the tree to get totals
	curr = head;
	int total = 0;

	do
	 {
		total += curr->data;
		
		if (curr->left != NULL && (curr->left->data > curr->right->data))
			curr = curr->left;
		else
			curr = curr->right;
		
	}while (curr != NULL);


	cout << "Node Count: " << nodeCount << endl <<  "Max Sum is: "<< total << endl << endl;
	triangleInputFile.close();
	return 0;
}


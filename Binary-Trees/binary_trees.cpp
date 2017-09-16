/*
 * project.cpp
 *
 *  Created on: 27 Mar 2015
 *      Author: Asad
 */
#include <iostream>
using namespace std;

// Declare the data structure
struct CP {
	int id;			// id of the node
	int data;		// data of the node
	CP * left;		// pointer to the left subtree
	CP * right;		// pointer to the right subtree
};

typedef CP * CPPtr;


// Function prototypes

// Generate an instance of the structure
void constructStructure(CPPtr &hdTree);
int numberNodes (const CPPtr hdtree);
int oddNodes (const CPPtr hdtree);
CPPtr minvalue (const CPPtr hdtree);
int sumvalues (const CPPtr hdtree);
int DepthNode (const CPPtr hdtree, const int ID, int depth);
bool balanced (const CPPtr hdtree);
int main(int argc, char ** argv)
{
	int ID;
	bool balancing;
	int depth = 0;

	// Declare a pointer to the head of the tree
	CPPtr hdTree  = NULL;

	// Construct a tree structure.
	constructStructure(hdTree);

	// =================================
	// Your functions should go here
		cout << "Total number of nodes: " << numberNodes (hdTree) << endl;
		CPPtr min = minvalue (hdTree);
		if (min == NULL){
			cout<< "empty binary tree" << endl;
		}
		else{
		cout << "Minnimum value:" <<  min -> data << endl;
		}
		cout <<"Number of odd nodes: " << oddNodes (hdTree) << endl;
		cout << "Sum of values: " << sumvalues (hdTree) << endl;
		cout << "Please enter the ID you want the depth of node for: " << endl;
		cin >> ID;
		int result = DepthNode(hdTree, ID, depth);
		if (result == -1){
			cout << "Node not found " << endl;
		}
		else{
		cout << "Depth of tree: " << result << endl;
		}
		balancing = balanced (hdTree);
		if (balancing == true){
			cout << "the tree is balanced " << endl;
		}
		else if (balancing == false){
			cout << "the tree is not balanced " << endl;
		}


    // =================================

    // Just to freeze the console window (not always necessary)
    // getchar();

    return 0;
}



// The function generates an instance of the structure (the same as in the description of the assignement document). The SP pointer
// points to the head of the tree
void constructStructure(CPPtr &SP){
    // Declare a structure with 5 nodes


    CPPtr SP0 = NULL;
    CPPtr SP1 = NULL;
    CPPtr SP2 = NULL;
    CPPtr SP3 = NULL;
    CPPtr SP4 = NULL;

    // build the structure tree
    // State 0
    SP0 = new CP;
    SP0->id = 1;
    SP0->data = 9;
    SP0->left = NULL;
    SP0->right = NULL;
    // State 1
    SP1 = new CP;
    SP1->id = 4;
    SP1->data = 5;
    SP1->left = NULL;
    SP1->right = NULL;
    // State 2
    SP2 = new CP;
    SP2->id = 8;
    SP2->data = 9;
    SP2->left = NULL;
    SP2->right = NULL;
    // State 3
    SP3 = new CP;
    SP3->id = 6;
    SP3->data = 8;
    SP3->left = NULL;
    SP3->right = NULL;
    // State 4
    SP4 = new CP;
    SP4->id = 5;
    SP4->data = 2;
    SP4->left = NULL;
    SP4->right = NULL;

    // Make the connections
    SP0->left = SP1;
    SP0->right = SP4;

    SP1->left = SP2;
    SP1->right = SP3;

    // Make the head pointer to point to the head of the tree
    SP = SP0;
}


int numberNodes (const CPPtr hdtree){
	if (hdtree == NULL){					//if the tree is empty then return 0 since there are no nodes.
		return 0;
	}
	else{
		int count = 1;						//if the tree is not empty then set keep on incrementing count by calling the function numberNodes recursively until the base case has been reached (hdtree -> left == NULL).
		count = count + numberNodes(hdtree -> left);
		count = count + numberNodes(hdtree -> right);
		return count;
	}
}

int oddNodes (const CPPtr hdtree){
int count = 0;
	if (hdtree == NULL){						//if the tree is empty then return 0 since there are no nodes.
		return 0;
	}
	else{
		count = oddNodes(hdtree -> right) + oddNodes (hdtree -> left); //store all the elements of the binary tree in the stack and upon every return of the call increment variable if the data value is odd.
		if (hdtree -> data % 2 == 1){
			count++;
		}
			return count;

	}
}

CPPtr minvalue (const CPPtr hdtree){
	CPPtr minValue;
	if (hdtree == NULL){								//if the tree is empty return NULL since there no nodes in the tree.
		return NULL;
	}
	else{
	if  (hdtree -> left != NULL){						//keep on recursively calling minvalue (hdtree -> left) until the base case has been reached.
		minValue = minvalue (hdtree -> left);
	}
	if (hdtree -> left == NULL ){						//when the base case has been reached then set minValue's equal to the base case.
		minValue = hdtree;
	}
	}
	return minValue;
	}

int sumvalues (const CPPtr hdtree){
	if(hdtree == NULL){										//if the tree is empty then return 0 since there are no nodes in the tree
		return 0;
	}
	else{
		int sum = hdtree -> data;							//set the value of sum equal to the data value of the head node
		CPPtr left = hdtree -> left;
		CPPtr right = hdtree -> right;
		return sumvalues(left) + sumvalues(right) + sum;	//keep on adding the values of a sub - tree in the binary tree until the base case has been reached.
	}

	}


int DepthNode (CPPtr hdtree, const int ID, int depth ){
	int resultright;
	int resultleft;
	if (hdtree == NULL){						//since the tree is empty there exists no node in the binary tree with the ID which user is searching for
		return -1;
	}
		if (hdtree -> id == ID){				//if the ID of the current node matches with the ID which the user is searching for return the depth.
			return depth;
		}
		 resultright = DepthNode (hdtree -> right , ID, 1 + depth); //else keep on incrementing depth by 1 until the base case has been attained.
		 resultleft = DepthNode (hdtree -> left, ID, 1 + depth);

	if (resultright != -1){		//resultright is equal to - 1 indicates that the base case has been reached. This means that the node doesn't exist in that paticular path
		return resultright;
	}
	if (resultleft != -1){		//the same case as resultright applies for resultleft.
		return resultleft;
	}
	return -1;				//indicates the tree is not empty and there is no node in the tree with ID equal to what the user is looking for.
}

bool balanced (CPPtr hdtree){
	bool balancingright;
	bool balancingleft;
	if (hdtree == NULL){			//if the binary tree is empty then the tree is balanced.
		return true;
	}
	if (hdtree -> right == NULL && hdtree -> left == NULL){		//if the tree only consists of a single element then the tree is balanced.
		return true;
	}
	else{
		return false;
	}
	 if (hdtree -> right != NULL && hdtree -> left != NULL){ //if the tree consists of more than elements recursively call the function again and check whether hdtree -> right and hdtree -> left lie in the same plan
		balancingright = balanced (hdtree -> right);
		balancingleft = balanced (hdtree -> left);
	}
	if (balancingright == true && balancingleft == true){
		return true;
	}
	return false;
}




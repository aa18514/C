/*
 * prog1.cpp
 *
 *  Created on: 25 Feb 2015
 *      Author: Asad
 */
#include<iostream>
#include<cstdlib>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

typedef int Item;

struct Node{
	Item Data;
	Node* next;
};
struct Command{
	string cmd;
	int numba;
};
struct InputFile{
	int n;

	string str(){
		stringstream ss;
		ss << "data_" << n << ".txt";
		return ss.str();
	}

};

struct	OutputFile{
	int n;

	string str(){
		stringstream ss;
		ss << "output_" << n << ".txt";
		return ss.str();
	}

};

typedef Node* NodePtr;

void linkedlist (ifstream &commandfile, NodePtr &hdlist, int &filenumber);
void writetofile (ifstream &commandfile, string &filename, NodePtr &hdlist, int &filenumber);
void minValue ( NodePtr hdlist, int &filenumber);
void numentries( NodePtr hdlist, int &filenumber);
void Bubblesort (NodePtr hdlist);
void Delete (ifstream &commandfile, NodePtr hdlist);
void Insert (ifstream &commandfile, NodePtr &hdlist, bool &BubbleSort);
void Smooth (NodePtr hdlist);
int main(int argc, char*argv[]){
	string filename;
	Command filecmd;
	ifstream commandfile;
	NodePtr hdlist;
	bool BubbleSort;
	BubbleSort = false;

	commandfile.open (argv[1]); //name of command-file passed as argument
	if(!commandfile.is_open()){
		cout << "could not open command file " << endl;
		exit (EXIT_FAILURE);
	}
	string command;
	int filenumber;
	while (commandfile >> command){ //(symbols in command-file representing different functions)

		if (command == "r"){
			linkedlist (commandfile, hdlist, filenumber); //read data from file data_x.txt where x is an integer determined by reading the next line in command - file.
		}
		if (command == "s"){
			Bubblesort (hdlist);
			BubbleSort = true; //sort the data in ascending order
		}
		if (command == "e"){
		 numentries (hdlist, filenumber); //calculate the number of entries in the linked list structure.

		}
		if(command == "w"){
		writetofile (commandfile, filename, hdlist, filenumber); //write entries in the linked list structure to the output file output_x.txt where x is determined from data_x.txt.
		}

		if (command == "m"){
			minValue ( hdlist, filenumber); //calculate the minimum value in the linked list structure.
		}

		if(command == "i"){
			Insert (commandfile, hdlist, BubbleSort); //insert a value in the linked list structure without destroying the ordering. If no ordering exists then just add entry to the structure.

		}
		if(command == "d"){
			Delete (commandfile, hdlist); //delete entry from the linked list without destroying the ordering. Entry is determined by the next line in the command-file.
		}
		if (command == "a"){
			Smooth (hdlist); //function which results in the difference between every two adjacent nodes to be less than or equal to five in a linked list structure. If the difference is greater than five, then  an extra node between the two nodes is added and it's value is determined as the average of the data values between them.
		}
	}
	return 0;

}


void linkedlist (ifstream &commandfile, NodePtr &hdlist, int &filenumber){
	hdlist = new Node;
	int i = 0;
	Item dat2;

	commandfile >> filenumber;
	InputFile infile;
				infile.n = filenumber;
				string filename = infile.str();
				ifstream inputfile;
				inputfile.open (filename.c_str());

	if (!inputfile.is_open()){
		cout << "data file does not exist " << endl;
		exit (EXIT_FAILURE);
	}
	while (inputfile >> dat2){
		if (i == 0){
			hdlist -> Data = dat2;
			hdlist -> next = NULL;
		}
		else{
			NodePtr newNode = new Node;
			newNode -> Data = dat2;
			newNode -> next = hdlist;
			hdlist = newNode;
}
		i++;
}
}

void writetofile(ifstream &commandfile, string &filename, NodePtr &hdlist, int &filenumber){
	OutputFile outfile;
	outfile.n = filenumber;
	filename = outfile.str();										//write data to output file 'output_x.txt' where x has the same value as in 'data_x.txt'. If the output file already exists then append data to the end of the file.
	ofstream outputfile (filename.c_str(), std:: ios:: app );
	if (outputfile.is_open()){
	while (hdlist != NULL){
		outputfile << hdlist -> Data << endl;
		hdlist = hdlist -> next;
	}
	}
}

void minValue(NodePtr hdlist, int &filenumber){
	string filename;
	OutputFile outfile;
	outfile.n = filenumber;
	filename = outfile.str();
	ofstream outputfile (filename.c_str(), std::ios::app);
	if (outputfile.is_open()){
	int i = 0;
	int minnimumvalue;
	while (hdlist != NULL){
	if (i == 0){
		minnimumvalue = Item (hdlist -> Data);   					//set the minimum value to the first element in the linked list and then compare with the remaining elements in the linked list
	}
	else if (i != 0){
		if (minnimumvalue > Item(hdlist -> Data)){
		minnimumvalue = Item (hdlist -> Data);
		}
		}
	hdlist = hdlist -> next;
	i++;
	}
	outputfile << "Minimum value: " << minnimumvalue << endl;		//write the minimum value to output file;
	}
}

void numentries( NodePtr hdlist, int &filenumber){
	string filename;
	OutputFile outfile;
	outfile.n = filenumber;
	filename = outfile.str();
	ofstream outputfile (filename.c_str(), std::ios::app);
	if (outputfile.is_open()){
	int i = 0;
	int numentries;
	while (hdlist != NULL){											//until hdlist hits NULL, i keeps on iterating to give the total number of elements in the list.
		i = i + 1;
		hdlist = hdlist -> next;
		}
	numentries = i;
	outputfile << "Number of elements in the list: " << numentries << endl;
	}
}

void Bubblesort (NodePtr hdlist){
	if (hdlist == NULL){											//if the list is empty then do nothing!
		return;
	}
	if (hdlist != NULL){
		Node *parent = hdlist;
		int counter = 0;
		while (parent !=NULL)
		{
			counter++;												//capture the number of elements in the linked list
			parent = parent -> next;
		}
		for (int i = 0; i < counter; i++){
			NodePtr current = hdlist -> next;
			NodePtr newcurrent = hdlist -> next;
			NodePtr parent = hdlist;								//swapping of nodes;
			NodePtr newparent = hdlist;
			NodePtr temp = new Node;
	while (current != NULL){
		if (parent -> Data > current -> Data){
			newcurrent = hdlist -> next;
			newparent = hdlist;
			while( newcurrent ) {
				if( newparent-> Data > newcurrent->Data ) {
					if( newparent == hdlist ) {
						temp->Data = newcurrent->Data;
						newcurrent->Data = newparent->Data;
						newparent->Data = temp->Data;
						hdlist = newparent;
					} else {
						temp->Data = newcurrent->Data;
						newcurrent->Data = newparent->Data;
						newparent->Data = temp->Data;
					}
				}
				newcurrent = newcurrent->next;
				newparent = newparent->next;
				current = hdlist ->next;
				parent =  hdlist;
			}
		}
			current = current->next;
			parent = parent->next;
	}
		}

	}
	}




void Delete (ifstream &commandfile, NodePtr hdlist){
	int val;
	commandfile >> val;
	Node* prev = hdlist;
		if (hdlist == NULL){
			return;																	//if no elements exist in the list exit from the functional call.
		}
		else if (hdlist -> Data == val){											//removal of the first element of the linked list if equal to the value that needs to be deleted
			prev = hdlist;
			hdlist = hdlist -> next;
			delete prev;
		}
		else{
			Node* search = hdlist;													//search for the element to be removed and then update the pointers.
			Node* last = hdlist;													//if the value that needs to be removed does not exist in the list than perform no changes.
			while (search != NULL){
				if(search -> Data == val){
					last -> next = search -> next;
					delete search;
					return;
				}
				else{
					last = search;
					search = search -> next;
				}
			}
		}
}
void Insert (ifstream &commandfile, NodePtr &hdlist, bool &BubbleSort){
		int val;
		bool ascendingorder = true;
		Node* head = hdlist;
		commandfile >> val;
		while (head  -> next != NULL && ascendingorder == true){
			if (head -> Data <= head -> next -> Data){
				ascendingorder = true;
			}
			else if (head -> Data > head -> next -> Data){
				ascendingorder = false;
			}

			head = head -> next;
		}

if (BubbleSort == false){										//(if there is no previous command in the command file to order the elements in the linked list, just add element to the linked list;
		NodePtr newnode = new Node;
		newnode -> Data = val;
		newnode -> next = hdlist;
		hdlist = newnode;
	if (ascendingorder == true){								//it is not important that the list is only sorted when there is a previous command in the command-file to sort the elements. The user could also enter the elements in the data file in an ascending order!
	Bubblesort (hdlist);
}
}
		if (BubbleSort == true){
			 NodePtr newnode;
			NodePtr searchnode;
			NodePtr last;
			bool found = false;
			newnode = new Node;
			newnode -> Data = val;
			newnode -> next = NULL;
			if (hdlist == NULL){								//special case. If no elements exist in the linked list, set the first element equal to the value.
				hdlist = newnode;
				return;
			}
			else if (hdlist -> Data >= val ){					//also a special case. Element to be inserted at the start of the linked list
				newnode -> next = hdlist;
				hdlist = newnode;
			}
			else{												//normal circumstances for inserting an element.
				found = false;									//initialise things
				searchnode = hdlist;
				last = hdlist;
				while ((searchnode != NULL) && (! found)){
					if (searchnode -> Data >= val){
						found = true;
					}
					else{
						last = searchnode;
						searchnode = searchnode -> next;
					}
				}
				newnode -> next = searchnode;					//insert the item into the correct place
				last -> next = newnode;

			}

		}

}

void Smooth (NodePtr hdlist){
	if (hdlist == NULL || hdlist -> next == NULL){                  //if the list contains no element or just one element the function does nothing
		return;
	}
	else{
	Node* val;
		while (hdlist -> next != NULL){
			if ( Item(hdlist -> Data)  - Item (hdlist -> next -> Data) > 5 || Item(hdlist -> next -> Data) - Item(hdlist -> Data) > 5){
				val = new Node;
				val -> Data = (Item (hdlist -> Data) + Item (hdlist -> next -> Data))*0.5;
				val -> next = hdlist -> next;
				hdlist -> next = val;
				Smooth (hdlist);                                   //multiples passes through the linked list may be required to ensure that the difference between every two adjacent nodes is less than five
			}
			hdlist = hdlist -> next;
		}
	}
	}





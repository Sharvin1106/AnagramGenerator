#include "DynamicStack.h"
#include <iostream>
using namespace std;

//Destructor
DynamicStack::~DynamicStack() {
	StackNode* nodePtr; //to move the list
	StackNode* nextNode; //to save the next node
 
	nodePtr = top; //Initialize nodePtr to top

	//Traverse the list deleting each node
	while (nodePtr != nullptr) {
		nextNode = nodePtr->next;
		delete nodePtr;
		nodePtr = nextNode;
	}
}

//Function pushes the argument onto the stack
void DynamicStack::push(char item) {
	StackNode* newNode = nullptr; //pointer for new node
	newNode = new StackNode(item); //Allocate new node with item
	
	//If top is empty
	if (isEmpty()) {
		//make the newNode as top
		top = newNode;
		newNode->next = nullptr;
	}
	else {
		//Otherwise make the newNode next points to top
		//and top as newNode
		newNode->next = top;
		top = newNode;
	}
}

//Function pops the value at the top of the stack, and copies it into the variable
// passed as an argument
void DynamicStack::pop(char& item) {
	StackNode* temp = nullptr; //Pointer to hold next node
	//If the stack is empty do nothing
	if (isEmpty()) {
		cout << "The stack is empty." << endl;
	}
	else {
		//Otherwise copy the value in top to item
		//temp points to next node of top
		//delete top and make temp as top
		item = top->value;
		temp = top->next;
		delete top;
		top = temp;
	}
}

//Function return true is the stack is empty, otherwise false
bool DynamicStack::isEmpty() {
	bool status;
	
	//if the top is null, return true
	if (!top) {
		status = true;
	}
	else {
		//otherwise return false
		status = false;
	}
	return status;
}

#ifndef DYNAMICSTACK_H
#define DYNAMICSTACK_H
#include <iostream>
using namespace std;

//Class for stack node
class StackNode {
public:
	char value; //value in the node
	StackNode* next; //pointer to point the next node
	//Constructor
	StackNode(char nodeValue) {
		value = nodeValue;
		next = nullptr;
	}
};

//Class for dynamic stack
class DynamicStack
{
private:
	StackNode* top; //pointer to the stack top
public:
	//Constructor
	DynamicStack() { top = nullptr; }
	//Destructor
	~DynamicStack();
	//Stack operations
	void push(char);
	void pop(char&);
	bool isEmpty();
};


#endif


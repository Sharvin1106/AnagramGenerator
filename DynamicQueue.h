#ifndef DYNAMICQUEUE_H
#define DYNAMICQUEUE_H
#include <iostream>
using namespace std;

//Class for queue nodes
class QueueNode {
public:
	char value; //node value
	QueueNode* next; //pointer to the next node
	//Constructor 
	QueueNode(char nodeValue) {
		value = nodeValue;
		next = nullptr;
	}
};


class DynamicQueue
{
private:
	QueueNode* front; //The front of the queue
	QueueNode* rear; //The rear of the queue
	int numofItems; //number of items in the queue
public:
	//Constructor
	DynamicQueue() { front = nullptr; rear = nullptr; numofItems = 0; }
	//Destructor
	~DynamicQueue() { clear(); }
	//Queue operations
	void enqueue(char);
	void dequeue(char&);
	bool isEmpty();
	void clear();
	int getItems() { return numofItems; }
};


#endif


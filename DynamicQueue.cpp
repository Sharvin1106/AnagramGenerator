#include "DynamicQueue.h"
#include <iostream>
using namespace std;

//Function enqueue inserts the new value in newItem
//At the rear of the queue
void DynamicQueue::enqueue(char newItem) {
	QueueNode* newNode; //pointer for new node
	//Allocate new node and store newItem
	newNode = new QueueNode(newItem);

	//Adjust front and rear as necessary
	//If the queue is empty 
	//Initialize newNode to front and rear
	if (isEmpty()) {
		front = newNode;
		rear = newNode;
	}
	else { //Otherwise
	//Insert newNode after rear
	//make rear point to newNode
		rear->next = newNode;
		rear = newNode;
	}
	numofItems++; //update number of items
}

//Function dequeue removes the value at the front and copies to
//oldItem
void DynamicQueue::dequeue(char& oldItem) {
	QueueNode* temp; //Pointer to hold node to be deleted
	
	//If the queue is empty do nothing
	if (isEmpty()) {
		cout << "The list is empty" << endl;
	}
	//Otherwise
	else {
		//Save the front node value in oldItem
		oldItem = front->value;
		//Remove the front node and delete it
		temp = front;
		front = front->next;
		delete temp;
		numofItems--; //update number of items
	}
}

//Function isEmpty returns true if the queue is empty, or false otherwise
bool DynamicQueue::isEmpty() {
	bool status;
	
	//If the number of items more than 0
	if (numofItems > 0) {
		status = false; //status set to false
	}
	else { 
	//Otherwise set to true
		status = true;
	}

	return status;
}
//Function clear dequeue all the items
void DynamicQueue::clear() {
	char value; //Dummy variable
	while (!isEmpty()) {
		dequeue(value);
	}
}



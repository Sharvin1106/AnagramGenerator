#include "LinkedList.h"
#include <iostream>
#include <iomanip>
using namespace std;


void LinkedList::appendNode(string newValue)
{
	/* appendNode will allow to allocate newNode, and store the word
	in first data field, then it will save the word of the node in currentWrd
	to add anagrams in the second field of nested list later*/
	
    ListNode* newNode; //To point to a new node 
    ListNode* nodePtr; //To move through the list
    //Allocate new node and store the word
    newNode = new ListNode(newValue);
   
   	//If there are no nodes in the list
   	//Make newNode the first node
    if (!head){
        head = newNode;
		//cout << "Im here" << endl; 
    }
    else //otherwise, insert newNode at the end
    {
        //Initialize nodePtr to the head of list
        nodePtr = head;
       
       	//Find the last node in the list
        while (nodePtr->next)
            nodePtr = nodePtr->next;
        //Insert newNode as the last node
        nodePtr->next = newNode;
    }
    //Initialize currentWrd to the word in newNode, to add anagrams in second data field of list
    currentWrd = newNode->word;
}

void LinkedList::appendAnagram(string newValue)
{
	/* appendAnagram will allow to allocate newNode, and store the anagrams
	in second data field of nested linked list*/
	
    AnagramNode* newNode; //To point to a new node
    AnagramNode* nodePtr; //To move through the nested list in second data field
    ListNode* nodePtr2; //To move through the list and search on first data field
    //Allocate new node and store the anagram
    newNode = new AnagramNode(newValue);
   	
   	//Initializing nodePtr2 to head of the list
   	nodePtr2 = head;
   	//cout << "im here 2" << endl;
   	//Search for the currentWrd in list
   	while(nodePtr2->word != currentWrd){
   		//cout << nodePtr2->word << endl;
   		nodePtr2 = nodePtr2->next;
	}
	
   	//Check if the anagramhead in nodePtr2 is empty
   	//If empty, make newNode as first node
    if (!nodePtr2->anagramhead){
        nodePtr2->anagramhead = newNode;
    }
    else //otherwise, insert newNode at end
    {
    	//Initialize nodePtr to anagramhead
        nodePtr = nodePtr2->anagramhead;
        //Find the last node in the list
        while (nodePtr->nextAnagram)
            nodePtr = nodePtr->nextAnagram;
       //Insert newNode as the lastNode
        nodePtr->nextAnagram = newNode;
    }
}

void LinkedList::displayList() const
{
	/*displayList shows all the words and its anagrams*/
	
    ListNode* nodePtr; //To move through the list
    AnagramNode* nodePtr2; //To move through the nested list in second data field
    
    //Output formatting setting
  // *************************************************************************
    const int anagram_width = 7; //anagram width                            //      //
    const int columns = 7; //columns to print                               //          //
    string sep = " |"; //separator                                             		//
    const int total_width = anagram_width * 4 + sep.size() * columns;  		//
    const string line = sep + string(total_width - 1, '-') + '|';      		//
  // *************************************************************************
    //Initialize nodePtr to head of the list
	nodePtr = head;
    
    //While nodePtr points to a node, traverse the list
    while (nodePtr) {
        int count = 1; //counter to control the numbering when display
        int count2 = 1; //counter to control the printing of next line
        cout <<"\n\t\t\t\t\t\t" << line <<  endl;
        cout << "\t\t\t\t\t\t\tAnagrams For Word :- "<< nodePtr->word << endl;
        cout << "\t\t\t\t\t\t" << line <<  endl;
        cout << '\n';
        //nodePtr2 initialize to the anagramhead of nodePtr
        nodePtr2 = nodePtr->anagramhead;
        //While nodePtr2 points to a node, traverse the list
        while (nodePtr2)
        {
        	//If the count2 is equals to 7 print the anagrams in next line
            if (count2 == 7) {
                cout << setw(anagram_width) << count << ". " << nodePtr2->anagram << sep; //Display anagram
                nodePtr2 = nodePtr2->nextAnagram; //Move to next node
                cout << '\n'; //Print next line
                count2 = 1;
                count++;
            }
            else {
                cout << setw(anagram_width) << count << ". " << nodePtr2->anagram << sep;
                nodePtr2 = nodePtr2->nextAnagram;
                count2++;
                count++;
            }
        }
        //nodePtr move to the next node
        nodePtr = nodePtr->next;

    }
}

void LinkedList::insertNode(string newValue)
{
	/*insertNode will allow a word to be added after the searched word,
	in which the searched word is saved in searchWrd, and save the
	newly added node word to currentWrd to add anagrams later*/
	
    ListNode* newNode; //A new node
    ListNode* nodePtr; //To traverse the list
    ListNode* previousNode = nullptr;  //The previous node
   
   //Allocate new node and store the word
    newNode = new ListNode(newValue);

	//If there's no nodes in the list
	//make newNode the first node
    if (!head)
    {
        head = newNode;
        newNode->next = nullptr;
    }
    else //otherwise, insert newNode
    {
        //Inititalize nodePtr to head of the list
        nodePtr = head;
        //Initialize previousNode to null
        previousNode = nullptr;
        
        //Skip all nodes whose word is not same as the word in searchWrd
        while (nodePtr != nullptr && nodePtr->word != searchWrd)
        {
            previousNode = nodePtr;
            nodePtr = nodePtr->next;
        }
        //Move the pointers to insert after the node
        previousNode = nodePtr;
        nodePtr = nodePtr->next;
        
     	//If the new node to be the 1st in the list
     	//Insert it before all other nodes
        if (previousNode == nullptr)
        {
            head = newNode;
            newNode->next = nodePtr;
        }
        else //otherwise insert after the previousNode
        {
        	//if the new node to be last in the list
            if (nodePtr == nullptr) {
                previousNode->next = newNode;
            }
            else {
                previousNode->next = newNode;
                newNode->next = nodePtr;
            }
        }
    }
    //Save the newNode word in currentWrd, to add the anagrams in the second
    //data field of nested list
    currentWrd = newNode->word;
  
}

void LinkedList::deleteNode()
{
	/*deleteNode function delete node with the same value of searchWrd from the list*/
	
    ListNode* nodePtr; //to traverse the list
    ListNode* previousNode = nullptr;  //to point to the previousNode
    //If the list is empty do nothing
	if (!head)
        cout << "List is Empty\n";
	
	//Determine if the first node is the one
    if (head->word == searchWrd)
    {
        nodePtr = head;
        head = head->next;
        delete nodePtr;
    }
    else
    {
    	//Initialize nodePtr to head of the list
        nodePtr = head;
        //Skip all nodes whose words are not same as the word in searchWrd
        while (nodePtr != nullptr && nodePtr->word != searchWrd)
        {
            previousNode = nodePtr;
            nodePtr = nodePtr->next;
        }
       
       //If nodePtr is not at the end of the list
       //link the previous node to the node after
       //nodePtr, then delete nodePtr
        if (nodePtr)
        {
            previousNode->next = nodePtr->next;
            delete nodePtr;
        }
    }
}

bool LinkedList::searchNode(string w) {
	/*To check the existence of the word in the list, if the word exists the word will
	be saved in searchWrd for future processing in main menu for the anagrams*/
	
    ListNode* nodePtr; //To move through the list
    //searchPtr = nullptr; //Initializing the searchPtr to null
    nodePtr = head; //Initializing nodePtr to head
    bool status = false; //status initialized to false
    //While the nodePtr is not null
    while (nodePtr != nullptr) {
    	//If the word in nodePtr equals to w
        if (nodePtr->word == w) {
            break;
        }
        else {
        	//Otherwise move to next node
            nodePtr = nodePtr->next;
        }
    }
    //if the nodePtr found, save the word to searchWrd
    if (nodePtr) {
        searchWrd = nodePtr->word;
        status = true; //set status to true
    }
    
    return status;
}

bool LinkedList::checkDuplicate(string w) {
	/*checkDuplicate will check if the new word 
	to be added to the list already exists*/
	
    ListNode* nodePtr; //To move through the list
    nodePtr = head; //Initialize nodePtr to head
    bool status = false; //set status to false
    //While nodePtr is not empty
    while (nodePtr != nullptr) {
    	//If the word in nodePtr is equals to the w
        if (nodePtr->word == w) {
            status = true;
            break;
        }
        else {
        	//Otherwise move to next node
            nodePtr = nodePtr->next;
        }
    }
    
    return status;
}

void LinkedList::searchCharac(char a) {
    /*searchCharac will search for anagrams with specific first
    character*/
	
	AnagramNode* nodePtr; //To move through the nested list in second data field
	ListNode* nodePtr2; //To move through the list 
	nodePtr2 = head; //Initializing nodePtr2 with head
	
	//Search for word first before finding its anagrams
	while(nodePtr2->word != searchWrd){
		nodePtr2 = nodePtr2->next;
	}
	
    nodePtr = nodePtr2->anagramhead; //Initializing nodePtr to anagramhead of searchPtr
	
	int count = 1; //Counter control numbering
    int count2 = 1; //Counter to control rows for printing
    //Output formatting setting
   /****************************************************************************************/
    const int anagram_width = 7; //width of anagram
    const int columns = 7; //number of columns
    string sep = " |"; //separator
    const int total_width = anagram_width * 8 + sep.size() * columns;
    const string line = sep + string(total_width - 1, '-') + '|';
   /****************************************************************************************/
    cout <<"\n\t\t\t\t\t\t" << line <<  endl;
    cout << "\t\t\t\t\t\t\tAnagrams of Word :- "<< nodePtr2->word << " for character " << a << endl;
    cout << "\t\t\t\t\t\t" << line <<  endl;
    cout << '\n';
    
    //While nodePtr is not empty
    while (nodePtr != nullptr) {
    	//If the first character of anagram in nodePtr equals to a
    	//Display anagram
        if (nodePtr->anagram[0] == a) {
        	//If count2 equals to 7, print anagrams in the next row
           if (count2 == 7) {
                cout << setw(anagram_width) << count << ". " << nodePtr->anagram << sep;
                cout << '\n';
                count2 = 1;
                count++;
            }
            else {
                cout << setw(anagram_width) << count << ". " << nodePtr->anagram << sep;
                count2++;
                count++;
            }
        }
        //Move nodePtr to the next node
        nodePtr = nodePtr->nextAnagram;
        
    }
}

void LinkedList::searchAnagram(string w) {
	/*searchAnagram search for a specific anagram in the list*/
	
    AnagramNode* nodePtr; //To move through the nested list in second data field
    ListNode* nodePtr2; //To move through the list
    
    nodePtr2 = head; //initialize nodePtr2 to head
    
    //Search for the word before searching for the anagram
    while(nodePtr2->word != searchWrd){
    	nodePtr2 = nodePtr2->next;
	}
	
    nodePtr = nodePtr2->anagramhead; //Initializing nodePtr to anagramhead of searchPtr

	//While nodePtr is not empty
    while (nodePtr != nullptr) {
    	//If anagram in nodePtr is not equals to w
    	if(nodePtr->anagram != w)
    	//move to next node
           nodePtr = nodePtr->nextAnagram;
        else
    		break;
    }
	//If anagram found, display anagram in nodePtr
	if(nodePtr)
    	cout << "\n\t\tAnagram found: " << nodePtr->anagram << endl;
    else
    	cout << "\n\t\tNot found" << endl;
}

string LinkedList::getWord() {
    return searchWrd;
}

void LinkedList::updateNode(string w) {
	/*updates the word in node which has the same word as in searchWrd in the list*/
	ListNode* nodePtr; //To move in the list
	nodePtr = head; //Initialize nodePtr to head
	
	//Search for word
	while(nodePtr->word != searchWrd){
		nodePtr = nodePtr->next;
	}
    nodePtr->word = w;
    //save the updated word in currentWrd, to update anagrams as well
    currentWrd = nodePtr->word;
    //save the word in searchWrd
    searchWrd = nodePtr->word;
}

void LinkedList::clearAnagram() {
	/*clearAnagram will clear all the anagrams in the second data field of nested list*/
    AnagramNode* nodePtr; //to move through the nested list in the second data field
    AnagramNode* nextNode;  //to save the next node in the list
    ListNode* nodePtr2; //to move through the list 
    
    nodePtr2 = head; //Initialize nodePtr2 to head
    
    //Search for the word, before clearing
    while(nodePtr2->word != searchWrd){
    	nodePtr2 = nodePtr2->next;
	}
    
    nodePtr = nodePtr2->anagramhead->nextAnagram;
    nodePtr2->anagramhead = nullptr; //initialize anagramhead to null

	//While nodePtr is not empty
	
    while (nodePtr != nullptr)
    {
    	//If nodePtr is not at the end of the list
       //link the nextNode to the node after
       //nodePtr, then delete nodePtr
        nextNode = nodePtr->nextAnagram;
        delete nodePtr;
        nodePtr = nextNode;
    }
}

void LinkedList::displayAnagram() {
    /*Display all anagrams of the word in searchPtr*/
    
	AnagramNode* nodePtr; //To move through the nested list in the second data field
	ListNode* nodePtr2; //To move through the list
	
	nodePtr2 = head; //Initialize nodePtr2 to head
	
	//Search for the word, before displaying anagrams
	while(nodePtr2->word != searchWrd){
		nodePtr2 = nodePtr2->next;
	}
	
    int count = 1; //To control the numbering
    int count2 = 1; //To control the rows for printing
    //Output formatting setting
   /****************************************************************************************/
    const int anagram_width = 7; //width of anagram                                                          //
    const int columns = 7; //number of columns                                                                //
    string sep = " |";    //separator                                                                 //
    const int total_width = anagram_width * 4 + sep.size() * columns;                     //
    const string line = sep + string(total_width - 1, '-') + '|';                         //
   /****************************************************************************************/
    //Initialize nodePtr to anagramhead of nodePtr2
	nodePtr = nodePtr2->anagramhead;
    cout <<"\n\t\t\t\t\t\t" << line <<  endl;
    cout << "\t\t\t\t\t\t\tAnagrams of Word :- "<< nodePtr2->word << endl;
    cout << "\t\t\t\t\t\t" << line <<  endl;
    cout << '\n';
   
       //While nodePtr is not empty
        while (nodePtr)
        {
        	//If count2 equals to seven print next row
           if (count2 == 7) {
                //cout << '\n';
                cout << setw(anagram_width) << count << ". " << nodePtr->anagram << sep; //display anagram
                nodePtr = nodePtr->nextAnagram; //Move to next anagram
                cout << '\n';
                count2 = 1;
                count++;
            }
            else {
                cout << setw(anagram_width) << count << ". " << nodePtr->anagram << sep;
                nodePtr = nodePtr->nextAnagram;
                count2++;
                count++;
            }
        }
       
}

LinkedList::~LinkedList()
{
	/*Destructor*/
	
    ListNode* nodePtr;  //To traverse the list
    ListNode* nextNode; //To point to the next node
   
   	//Initialize nodePtr to head
    nodePtr = head;
    
    //While nodePtr is not empty
    while (nodePtr != nullptr)
    {
       //Save a pointer
        nextNode = nodePtr->next;
        //Delete the current node
        delete nodePtr;
        //Initialize nodePtr to nextNode
        nodePtr = nextNode;
    }
    
    searchWrd = "";
    currentWrd = "";
}

#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <iostream>
using namespace std;

//Class for nodes to hold anagrams
class AnagramNode {
public:
    string anagram; //Anagram
    AnagramNode* nextAnagram; //next pointer for anagram nodes
    //constructor
    AnagramNode(string nodeValue)
    {
        anagram = nodeValue; 
        nextAnagram = nullptr;
    }
};

class ListNode
{
public:
	//ListNode structure with two data fields
    string word; // Node value
    AnagramNode* anagramhead;
    ListNode* next; // Pointer to the next node
    // Constructor
    ListNode (string nodeValue)
    {
        word = nodeValue;
        anagramhead = nullptr;
        next = nullptr;
    }
};

class LinkedList
{
private:
    ListNode* head; // List head pointer
    string currentWrd; //To save a word after a node is allocated, to add the anagrams later
    string searchWrd; //To save the searched word
public:
    // Constructor
    LinkedList()
    {
        head = nullptr;
        currentWrd = "";
        searchWrd = "";
    }


    // Destructor
    ~LinkedList(); //destructor

    // Linked list operations
    void appendNode(string); //to append node/word
    void appendAnagram(string); //to append anagram
    void insertNode(string); //to insert node/word 
    bool searchNode(string); //to search node/word
    bool checkDuplicate(string); //to check the duplicate word
    void searchCharac(char); //to search anagrams by characters
    void updateNode(string); //update the searched node
    string getWord(); //return the word in searched node
    void searchAnagram(string); //Search for a specific anagrams
    void clearAnagram(); //Destroy the list with anagrams
    void displayAnagram(); //Display anagrams of a specific word
    void deleteNode(); //to delete node
    void displayList() const; //to display all words and its anagrams
};


#endif

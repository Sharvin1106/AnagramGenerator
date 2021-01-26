#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include "LinkedList.h"
#include "DynamicQueue.h"
#include "DynamicStack.h"
using namespace std;
void MainMenu(); //Menu that views choices of operation to perform
void startMenu(); //Primary menu for entering or importing data
void searchMenu(); //Menu for operations based on searched word
void AddData(DynamicQueue&, DynamicStack& , DynamicStack&, string, LinkedList&, int); //Function to add new word
bool deleteWord(char, LinkedList&); //Function to delete a word
void searchFunc(DynamicQueue&, DynamicStack& , DynamicStack&, string, LinkedList&); //Function to perform various operations based on searched word
void generateAnagrams(DynamicQueue&, DynamicStack&, DynamicStack&, string, LinkedList&); //Function to generate anagrams
void processStack(int, int, DynamicQueue&, DynamicStack&, DynamicStack&, string); //Function to process stack for generating anagrams
void processQueue(DynamicQueue&, DynamicStack&, int, int[], int[], int, string); //Function to process queue for generating anagrams
void backtracking(DynamicQueue&, DynamicStack&, int&, int, int, int, int [], int [], string); //Function for backtracking of possible words generated
bool checkArr(int []); //Function to check level arrays for generating anagrams
int checkFun(int [], int[], int); //Function to check level arrays for generating anagrams

int main() {
	string Word, filename;
	fstream inputFile; 
	DynamicQueue queue; //Declaration of queue object
	DynamicStack stack1; //Declaration of stack1 object
	DynamicStack stack2; //Declaration of stack2 object
	LinkedList list; //Declaration of list object
	int choice = 0; //Declaration of choice for menu
	startMenu(); //Calling the start menu
	cin >> choice;
	//Input Validation for choice
	while ((choice < 1 || choice > 3) || (cin.fail())) {
		cin.clear();
		cin.ignore();
		cout << "Invalid input. Try again" << endl;
		cin >> choice;
	}
	if (choice != 3) {
		switch (choice) {
		//If the users choice is 1, the words will be imported from the
		//textfile
		case 1:
			cout << "\n\n\t\tEnter file name(No .txt needed): ";
			cin >> filename; //Input the filename
			filename += ".txt";
			//File open member function
			inputFile.open(filename, ios::in);
			//Validation for inputFile, if the file couldnt open the user will be prompted
			//to enter the filename again till the file successfully opened 
			while (!inputFile) {
				cout << "\t\tError opening file." << endl;
				cout << "\t\tFile doesn't exist." << endl;
				cout << "\t\tEnter file name: ";
				cin >> filename; //User re-enter the filename if doesn't exists
				filename += ".txt";
				inputFile.open(filename, ios::in);
		    }
		    //If the file is successfully opened, the data from the file will be read
		    while (inputFile) {
				inputFile >> Word;
				//Check whether the word from textfile is already existed in linkedlist
				if(list.checkDuplicate(Word)){
					cout << "Word already exists" << endl; 
				}
				//If the word from text file doesnt exist in the linked list,
				//the word will be appended in the linked list
				else{
					//Function to append word
					list.appendNode(Word);
					//Function to generate anagram
					generateAnagrams(queue, stack1, stack2, Word, list);
				}
			    inputFile.ignore();
		    }
		    break;
		//If the user's choice is 2, the program will ask the user to enter
		// at least a name before the program directs to main menu
		case 2:
				cout << "\n\n\t\tEnter at least a word to start the program" << endl;
				cout << "\t\tEnter a word: ";
				cin >> Word;
				//Function to add word in the linked list and generate anagrams with the
				//entered word
				AddData(queue, stack1, stack2, Word, list, 1);
				break;
			}
		}
	inputFile.close();

	do {
		//Calling the function containing the main menu
		MainMenu();
		cin >> choice;
		//Choice validation
		while ((choice < 1 || choice > 5) || (cin.fail())) {
			cout << "\n\n\t\tInvalid input. Try again" << endl;
			cout << "\t\tEnter choice: ";
			cin.clear();
			cin.ignore();
			cin >> choice;
		}
		if (choice != 5) {
			switch (choice) {
			case 1:
				//If the user choice is 1, the user are allowed to import words again from other
				//textfiles
				cout << "\n\n\t\tEnter file name(No .txt needed): ";
				cin >> filename;
				filename += ".txt";
				inputFile.open(filename, ios::in);
				while (!inputFile) {
					cout << "\n\n\t\tError opening file." << endl;
					cout << "\t\tFile doesn't exist." << endl;
					cout << "\t\tEnter file name: ";
					cin >> filename; //User re-enter the filename if doesn't exists
					filename += ".txt";
					inputFile.open(filename, ios::in);
				}
				while (inputFile) {
					inputFile >> Word;
					if (list.checkDuplicate(Word)) {
						cout << "\t\tThe word " << Word << " already exists" << endl;
					}
					else {
						list.appendNode(Word);
						generateAnagrams(queue, stack1, stack2, Word, list);
					}
					
					inputFile.ignore();
				}
				cout << "\n\t\t*************************************************" << endl;
				cout << "\t\tWords were successfully imported from " << filename << endl;
				cout << "\t\t***************************************************" << endl;
				cin.get();
				cin.get();
				inputFile.close();
				break;
			case 2:
				//If the user's choice is 2, the user can add new word
				cout << "\n\n\t\tEnter word: ";
				cin >> Word;
				//Function to add the new word in the linked list
				AddData(queue, stack1, stack2, Word, list,1);
				cout << "\n\t\t***************************" << endl;
				cout << "\t\tWord saved" << endl;
				cout << "\t\tPress enter to continue" << endl;
				cout << "\t\t***************************" << endl;
				cin.get();
				cin.get();
				break;
			case 3:
				//If the user's choice 3, the search can search for a word
				//If the word is found, they can perform various operations on the word 
				int choice1;
				cout << "\n\n\t\tEnter the word to search: ";
				cin >> Word;
				//Before the search function called, the searchNode function in
				//linked list is called to verify the existence of the word
				if (list.searchNode(Word)) {
					//If the word exists the search function is called
					searchFunc(queue, stack1, stack2, Word, list);
				}
				else {
					//If the word is not found
					cout << "\t\tNo word found" << endl;
					cin.get();
					cin.get();
				}
				break;
			case 4:
				//If the user's choice is 4, the program will display all the words and its anagrams
				system("CLS");
				cout << "\t\tDisplaying all words and its anagrams" << endl;
				list.displayList();
				cin.get();
				cin.get();
				break;
			}
		}
	} while (choice != 5);
	

}
void startMenu() {
	system("CLS");
	cout << "\t*********************************************************************\n\n";
	cout << "\t\t\t\tAnagram Generator" << endl;
	cout << "\t\t1. Import Words from textfile" << endl;
	cout << "\t\t2. Continue without importing textfile" << endl;
	cout << "\t\t3. Exit" << endl;
	cout << "\t\tYour choice: ";
}

void MainMenu() {
	system("CLS");
	cout << "\t*********************************************************************\n\n";
	cout << "\t\t\t\tAnagram Generator" << endl;
	cout << "\t\t1. Import Words" << endl;
	cout << "\t\t2. Add Word" << endl;
	cout << "\t\t3. Search Word" << endl;
	cout << "\t\t4. Display All Words and Its Anagrams" << endl;
	cout << "\t\t5. Exit" << endl;
	cout << "\t\tYour choice: ";
}

void searchMenu() {
	cout << "\t*********************************************************************\n\n";
	cout << "\t\t\t\tAnagram Generator - Anagram Operation" << endl;
	cout << "\t\t1. Update Word" << endl;
	cout << "\t\t2. Add New Word" << endl;
	cout << "\t\t3. Display Anagrams(Specific Search)" << endl;
	cout << "\t\t4. Display All Anagrams and Words" << endl;
	cout << "\t\t5. Delete Word" << endl;
	cout << "\t\t6. Exit" << endl;
	cout << "\t\tYour choice: ";
}

void generateAnagrams(DynamicQueue &queue, DynamicStack &stack1, DynamicStack &stack2, string word, LinkedList &List) {
	char tempChar; //To hold the data dequeued or popped by queue or stack
	string anagram = ""; //To concatenate the dequeued letter from queue to form a string
	int sizeWord = word.length(); //To find the length of word
	int count1 = 0; //To track the shuffling of last three characters for a given word to form 6 possible anagrams
	int* lvlA = nullptr; //Dynamically allocated array to track the backtracking for next possible anagram
	int* cpylvlA = nullptr; //Copy of the dynamically allocated array above
	int lvl = sizeWord - 5; //The process of permutation of words is based on the number of characters in the word excluding the 
	//first two characters and last three characters, the result of this computation gives the level

	if(sizeWord <= 2){
		//If the size of word is one, the letter itself will be the anagram
		if(sizeWord == 1){
			List.appendAnagram(word);
		}
		//If the size of word is two, the anagrams are generated by pushing the letters in the stack
		else if(sizeWord == 2){
			stack1.push(word[0]);
			stack1.push(word[1]);
			for(int j = 0; j < sizeWord; j++){
			stack1.pop(tempChar);
			//The popped letter from stack1 is pushed to stack2 to form the next possible anagram
			stack2.push(tempChar);
			//The popped letter from stack1 is concatenated to anagram, to form a string
			anagram += tempChar;
			}
			//Appending the anagram to the list
			List.appendAnagram(anagram);
			anagram = ""; //Setting the anagram string to empty
			for(int j = 0; j < sizeWord; j++){
			stack2.pop(tempChar);
			//The letter popped from stack2 is concatenated to empty anagram string to form an anagram
			anagram += tempChar;
			}
			//Appending the anagram to the list
			List.appendAnagram(anagram);
			anagram = "";
		}
		else{
			//If the size of word entered is less than 1
			cout << "Invalid word" << endl;
		}
	}
	
	//If the size of word more than 3, the following statements are executed to generate anagrams
	else{
		//If the size of word is less than or equals to 5
		if (sizeWord <= 5) {
			//The size of dynamically allocated array will be 1
			lvlA = new int[1];
			cpylvlA = new int[1];
		}
		//If the size of word more than 5
		else {
			//The dynamically allocated array will be initialized to the size based on the lvl value
			lvlA = new int[lvl];
			cpylvlA = new int[lvl];
		}

		//
		for (int i = 0; i < sizeWord; i++) {
			queue.clear();
			queue.enqueue(word[i]); // Enqueue the letter in the ith index
			for (int j = 0; j < sizeWord; j++) {
				if (word[j] != word[i]) {
					stack1.push(word[j]); // Push the alphabets which are not in the queue into stack 1
					//stack 1 holds the second possible chracters of anagrams
					
				}
				else {
					continue;
				}
			}
			//Loop to iterate while stack1 is not empty
			while (!(stack1.isEmpty())) {
				//Function processStack is called to pop a character from stack 1 and enqueue to the queue
				//Then stack 2 is filled with characters that are not in the queue
				processStack(i, sizeWord, queue, stack1, stack2, word);
				//Iterates until the stack2 is not empty
				while (!(stack2.isEmpty())) {
					//Iterates until the queue havent reach the size same as the word size
					while (queue.getItems() != sizeWord) {
						//processQueue function is called to enqueue alphabets to queue, by popping alphabets
						//from stack 2
						processQueue(queue, stack2, sizeWord, lvlA, cpylvlA, lvl, word);
					}
					count1++; //This counter is incremented to backtrack
					//Dequeue the queue and concatenate the anagram
					for (int j = 0; j < sizeWord; j++) {
						queue.dequeue(tempChar);
						anagram += tempChar;
						queue.enqueue(tempChar); // queue the alphabets back
					}
					//Call member function to append anagram
					List.appendAnagram(anagram);
					//cout << "I cannot append" << endl;
					anagram = ""; //Reset the anagram to empty string
					//Function backtracking is called to restore letters according certain condition
					backtracking(queue, stack2, count1, sizeWord, i, lvl, lvlA, cpylvlA, word);
				} 
			}
		}
		//delete dynamically allocated array to avoid memory leak
		delete[] lvlA;
		delete[] cpylvlA;
	}
}

void processStack(int i, int sizeWord, DynamicQueue &queue, DynamicStack &stack1, DynamicStack &stack2, string word) {
	char tempChar;
	stack1.pop(tempChar); // Pop the first element in the stack 1
	queue.enqueue(tempChar); // Queue it inside the queue
	
	for (int j = 0; j < sizeWord; j++) {
		if (word[j] != word[i] && word[j] != tempChar) {
			stack2.push(word[j]); //Push the letters which are not in the queue
		}
		else {
			continue;
		}
	}
	
}

void processQueue(DynamicQueue &queue, DynamicStack &stack2, int sizeWord, int levelA[], int cpylevelA[], int level, string word) {
	char tempChar;
	char sample[sizeWord]; //Array that contains the letters of word
	strcpy(sample, word.c_str()); //Converting the string word into char of arrays
	stack2.pop(tempChar); //Pop the letter from stack 2
	queue.enqueue(tempChar); // Enqueue the popped letter from stack 2
	//If the queue size is equals to 3, the following if statement will be executed
	if (queue.getItems() == 3) {
		//The first value to be stored in the 0th index of  levelA and cpylevelA array
		int temp = sizeWord - 3; 
		levelA[0] = temp; 
		cpylevelA[0] = temp;
		//The rest of the index is filled up with values by deducting 
		//the value by 1 in the previous index
		for (int j = 1; j < level; j++) {
			levelA[j] = levelA[j - 1] - 1;
			cpylevelA[j] = levelA[j - 1] - 1;
		}
	}

	
	//Check for the left possible characters in the queue which can be used 
	for (int j = 0; j < queue.getItems(); j++) {
		char temp1;
		queue.dequeue(temp1);
		for (int z = 0; z < sizeWord; z++) {
			//Check if the alphabet dequeued is same as the alphabet in the same array
			if (temp1 == sample[z]) {
				//If it matches replace the character with zero
				sample[z] = '/';
				break;
			}
		}
		//queue back the letter to avoid any missing data
		queue.enqueue(temp1);
	}
	
	//Push the existing characters which are not zero
	//into the stack 2 to enqueue later
	for(int j = 0; j < sizeWord; j++){
		if(sample[j] == '/'){
			continue;
		}
		else{
			stack2.push(sample[j]);
		}
	}

}

void backtracking(DynamicQueue &queue, DynamicStack &stack2, int &count1, int sizeWord, int I, int level, int levelA[], int cpylevelA[], string word) {
	char tempChar;

	if (stack2.isEmpty()) {
		//If stack 2 is empty, it is known that all possible anagrams
		//are generated from the letter popped from stack 1, so the program has
		//to dequeue all the letters from queue, except for the first letter queued in the
		//beginning of the loop
		queue.clear(); //Member function to clear the letters in anagram
		queue.enqueue(word[I]); //Enqueue back the first letter enqueued in the beginning of the loop
		count1 = 0; //Reset the counter to 0
		
	}
	//If the stack 2 is not empty
	else {
		//If the count1 is less than 6, it means that the anagrams
		//Have not generated 6 successive anagram with last three distinct characters popped from stack 2
		if (count1 < 6) {
			//If the count1 is an even number,
			//The queue have to eliminate the last three characters
			//and enqueue back the rest
			if (count1 % 2 == 0) {
				//loop to restore characters
				for (int j = 0; j < sizeWord - 3; j++) {
					queue.dequeue(tempChar);
					queue.enqueue(tempChar);
				}
				//loop to eliminate characters
				for (int j = 0; j < 3; j++) {
					queue.dequeue(tempChar);
				}
			}
			else {
				//If the count1 is an odd number
				//Eliminate the last two characters, and enqueue back the rest
				//Loop to restore the letters
				for (int j = 0; j < sizeWord - 2; j++) {
					queue.dequeue(tempChar);
					queue.enqueue(tempChar);
				}
				//loop to eliminate the letters
				for (int j = 0; j < 2; j++) {
					queue.dequeue(tempChar);
				}
			}
		}
		//If the count1 is more than equals to six,
		//it shows that the program has generated six successive anagram with
		//last three distinct characters
		else if (count1 >= 6) {
			if (sizeWord > 6) {
				//This level array contains the existing number of characters can be used in stack 2
				//for each level
				levelA[level - 1] -= 1; //Deduct the number in last index
			}
			//Check whether the first index in level array is less than zero
			if (checkArr(levelA) || sizeWord == 6) {
				for (int j = 0; j < 2; j++) {
					queue.dequeue(tempChar);
					queue.enqueue(tempChar);
				}
				for (int j = 0; j < sizeWord - 2; j++) {
					queue.dequeue(tempChar);
				}
			}
			//If the first index of the level array is not zero
			else {
				//Function checkFun is called to check the level array and it will return
				//the index of the level array
				//that index is used to indicate cpylevelArray to determine the number of characters
				//to be restored in the queue
				int counttemp = checkFun(levelA, cpylevelA, level);
				for (int j = 0; j < sizeWord - (cpylevelA[counttemp] + 1); j++) { //change here backwards
					queue.dequeue(tempChar);
					queue.enqueue(tempChar);
				}
				for (int j = 0; j < cpylevelA[counttemp] + 1; j++) {
					queue.dequeue(tempChar);
				}
			}
			count1 = 0; //count1 is reset
		}
	}
}

bool checkArr(int levelA[]) {
	bool status = false;
	if (levelA[0] < 0) {
		//If the first index of the level array is zero
		status = true; //status become true
	}
	return status;
}

int checkFun(int levelA[], int cpylevelA[], int level) {
	int i = level - 1; //counter set to the last index of the level array
	
	//if the level array last index is not zero
	if(levelA[i] >= 0){
		return i; //the last index is returned
	}
	//If the last index is zero
	else {
		i -= 1; //index counter is decremented
		//Checks if the index counter is more than or equals to zero
		while (i >= 0) {
			//Checks if the value in level array is more than or equals to zero
			if (levelA[i] >= 0) {
				//Checks if the value in the level array is less than zero if
				//deducted by one
				if (levelA[i] - 1 < 0) {
					//If the value in the level array is less than zero if deducted by
					// one, the index counter will be decremented by one
					i--;
				}
				else {
					//Else the value in level array will be deducted by one
					levelA[i] = levelA[i] - 1;
					//Restore back the values in level array from index after i
					for (int x = i + 1; x < level; x++) {
						levelA[x] = cpylevelA[x];
					}
					return i; //return the index
				}
			}
			else if (levelA[i] < 0) {
				//If the value in level array is less than 0
				//Decrement the index counter
				i--;
			}
		}

	}
}

void searchFunc(DynamicQueue &queue, DynamicStack &stack1, DynamicStack &stack2, string Word, LinkedList &list){
	int choice1;
	bool status = false;
	char charac;
	do {
		system("CLS");
		cout << "\t\t\tCurrent Word: " << list.getWord() << endl;
		searchMenu(); //Calling the function searchMenu that contains the list of operation
		//can be performed after a word is searched
		cin >> choice1;
		//Choice validation
		while ((choice1 < 1 || choice1 > 6) || (cin.fail())) {
			cout << "\n\n\t\tInvalid input. Try again" << endl;
			cout << "\t\tEnter choice: ";
			cin.clear();
			cin.ignore();
			cin >> choice1;
		}
		switch (choice1) {
		case 1:
			//If the users choice is 1, the user get to update the current word
			//to new one and re-generate the anagrams
			cout << "\n\n\t\tCurrent Word: " << list.getWord() << endl;
			cout << "\t\tEnter new word: ";
			cin >> Word;
			//Function called to update word and re-generate anagram
			AddData(queue, stack1 , stack2, Word, list, 2);				
			break;
		case 2:
			//If the users choice is 3, the user able to add a word after
			//the searched word	
			cout << "\n\n\t\tEnter new word to add after word " << list.getWord() << ":";
			cin >> Word;
			//Calling the function to insert new word
			AddData(queue, stack1, stack2, Word, list, 3);				
			break;
		case 3:
			//If the users choice is 3, the user can search for specific anagrams or
			//anagrams with first character entered by the user
			do {
				//Menu for specific search
				system("CLS");
				cout << "\n\n\t\t*************************************************" << endl;
				cout << "\t\t Specific Search - Anagram Generator" << endl;
				cout << "\t\t1. Search specific anagram" << endl;
				cout << "\t\t2. Search anagrams by character" << endl;
				cout << "\t\t3. Exit" << endl;
				cout << "\t\tEnter choice: ";
				cin >> choice1;
				//choice1 validation
				while ((choice1 < 1 || choice1 > 3) || cin.fail()) {
					cout << "\n\t\tInvalid input. Try again" << endl;
					cout << "\t\tEnter choice: ";
					cin.clear();
					cin.ignore();
					cin >> choice1;
				}
				switch (choice1) {
				case 1:
					//If the users choice is 1, then the user can search
					//for specific anagram
					cout << "\n\n\t\tEnter word: ";
					cin >> Word;
					//Member function to display the searched anagram
					list.searchAnagram(Word);
					cout << "\n\t\tPress enter key to continue" << endl;
					cin.get();
					cin.get();
					break;
				case 2:
					//If the users choice is 2, the user can search anagram with first character
					//entered by them
					cout << "\n\n\t\tEnter character: ";
					cin >> charac;
					//Validation for charac
					while (cin.fail()) {
						cout << "\n\t\tInvalid input. Try again" << endl;
						cout << "\t\tEnter choice: ";
						cin.clear();
						cin.ignore();
						cin >> charac;
					}
					//Member function to display anagrams from the searched character
					list.searchCharac(charac);
					cout << "\n\n\n\t\t********************************************" << endl;
					cout << "\t\tPress enter key to continue" << endl;
					cout << "\t\t**********************************************" << endl;
					cin.get();
					cin.get();
					cin.ignore();
					break;
					}
	
				} while (choice1 != 3);
				break;
			case 4:
				//If the users choice is 4, the  program will display all the words
				//and its anagrams
				cout << "\t\tDisplaying all anagrams and its word" << endl;
				list.displayAnagram(); //Member function to display all words and its anagrams
				cout << "\n\t\t********************************************" << endl;
				cout << "\t\tPress enter key to continue" << endl;
				cout << "\t\t**********************************************" << endl;
				cin.get();
				cin.get();
				break;
			case 5:
				//If the users choice is 5, the user is given a choice of deleting that searched word
				cout << "\n\n\t\tAre you sure you want to delete the word (Y/N) " << list.getWord() << endl;
				cout << "\t\tEnter choice: ";
				cin >> charac;
				//Function will return the status value, if the word is deleted
				status = deleteWord(charac, list);
				break;
			}
		} while (choice1 != 6 && !status);
}

void AddData(DynamicQueue &q, DynamicStack &s1 , DynamicStack &s2, string W, LinkedList &l, int num){
	//Check if the new word to be added is already existed or not
	while(l.checkDuplicate(W)) {
		cout << "\n\n\t\tThe word " << W << " already exists" << endl;
		cout << "\t\tPlease re-enter word: ";
		cin.clear();
		cin.ignore();
		cin >> W;
	}
	//If the new word to be added does not exists in the list before
	if(!l.checkDuplicate(W)) 
	{
		//num = 1 - add new word to the list
		//num = 2 - update word in the list
		//num = 3 - insert word in the list
		switch(num){
		case 1:
			l.appendNode(W); //The new word will be appended to the list
			generateAnagrams(q, s1, s2, W, l); //Function is called to generate anagrams
			break;
		case 2:
			l.updateNode(W); //Member function to update word
			l.clearAnagram(); //Member function to clear existing anagrams
			generateAnagrams(q, s1, s2, W, l); //Member function to re-generate anagrams
			cout << "\n\t\t**************************************" << endl;
			cout << "\t\tWord and its anagram updated" << endl;
			cout << "\t\tPress enter key to continue" << endl;
			cout << "\t\t**************************************" << endl;
			cin.get();
			cin.get();
			break;
		case 3:
			l.insertNode(W); //Member function to insert new word
			generateAnagrams(q, s1, s2, W, l); //Member function to generate new anagrams
			cout << "\n\n\t\t***************************************************************" << endl;
			cout << "\t\t" << W << " was added after the word " << l.getWord() << endl;
			cout << "\t\tPress enter key to continue" << endl;
			cout << "\t\t***************************************************************" << endl;
			cin.get();
			cin.get();	
			break;
		}
		
	}
}

bool deleteWord(char c, LinkedList &l){
	bool status = false;
	//Input validation
	while (((c != 'Y') && (c != 'N')) || cin.fail()) {
		cout << "\n\t\tInvalid input. Try again" << endl;
		cout << "\t\tEnter choice: ";
		cin.clear();
		cin.ignore();
		cin >> c;
	}
	if (c == 'Y' || c == 'y') {
		l.deleteNode(); //member function to delete the word
		cout << "\t\tWord deleted" << endl;
		cin.get();
		cin.get();
		status = true; //the status set to true to indicate the word is deleted
		//break;
	}
	else {
		//The word is not deleted
		cout << "\n\t\tThe word is not deleted" << endl;
		cout << "\t\tPress enter key to continue" << endl;
		cin.get();
		cin.get();
	}
	return status;
}

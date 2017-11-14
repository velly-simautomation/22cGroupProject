/*
	22C Group Project main source file.
	Fall 2017

	Contains entry point and managers which utilize the tools needed for this assignment.

	Team 5 Members:
	Velly Simeonov
	Chejui Chen
	Yuchen Jiang
	Aijun Qin

	Authors: 
	Velly

*/

#include <iostream>
#include <fstream>
#include <string>
#include "Queue.h" // might want to replace this with one of ours, no author on this one
#include "hashtable.h"

/* main menu manager controlling overall flow of user interactions */
int mainMenu();

/* menu text to show to user when requested */
int printMenu();

/* opens a text file and dumps lines into a linked list to be processed */
int readFile(const string &fileName, Queue<string> &output);

/* returns remainder between the sum of all characters in a string over an unsigned int */
unsigned int operator%(const string &lhs, const unsigned int &rhs);

using namespace std;

int main(int argc, char *argv[]) {
	Queue<string> readLines;
	
	//TO DO: do something with return value
	readFile("defaultInput.txt", readLines);

	HashTable<string> table = HashTable<string>(10);

	/* testing */
	table.insert(string("hello"));

	table.print();

	cout << table.at(0) << endl;
	cout << (string("alphabet") % 11) << endl;
	/* end testing */

	// process lines

	mainMenu();

	// save data to file

}

int mainMenu() {
	string input = ""; // using string to avoid flushing stdin
	
	cout << "22C Group Project Main Menu" << endl;
	cout << "\tData base items : " << endl; // add database items count to line
	printMenu();

	while (input[0] != 'Q') {
		cout << "Option : ";
		getline(cin, input);

		if (input.size() != 1) continue; // we only care if we have 1 character as input

		input[0] = toupper(input[0]);


		// TO DO : make all options available, do not forget to update printMenu()
		if (input[0] == 'A');
		else if (input[0] == 'B'); // etc
		else if (input[0] == 'M') printMenu();
	}
	return 0;
}


// TO DO : Update print menu with actual available options.
int printMenu() {
	cout << "\tA for job 1." << endl;
	cout << "\tB for job 2." << endl;
	cout << "\tM to show this menu." << endl;
	cout << "\tQ to quit program." << endl;
	return 0;
}

int readFile(const string &fileName, Queue<string> &output) {
	fstream iFile;
	string tmp;

	iFile.open(fileName, ios_base::in);

	if (!iFile) return 1;

	while (getline(iFile, tmp)) {
		output.enqueue(tmp);
	}

	return 0;
}

unsigned int operator%(const string &lhs, const unsigned int &rhs) {
	unsigned int lhsval = 0;

	for (unsigned int i = 0; i < lhs.size(); ++i) {
		lhsval += lhs.at(i);
	}

	return lhsval % rhs;
}
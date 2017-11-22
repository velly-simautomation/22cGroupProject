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

#include "hashtable.h"
#include "app.h"

using namespace std;

int main(int argc, char *argv[]) {
	Queue<string> readLines;
	int nlines = readFile("defaultInput.txt", readLines);

	HashTable<string> table = HashTable<string>(nlines, stringModHash);

	/* testing */
	HashTable<string> testTable = HashTable<string>(10, stringModHash);
	string h = "group";
	testTable.insert(h);
	testTable.print();
	cout << *testTable.at(testTable.hash(h)) << endl;
	cout << "Find h in hashtable : " << testTable.find(h) << endl;

	string& z = testTable.remove(stringModHash(h, 10));
	cout << z << endl;
	cout << "Find h in hashtable : " << testTable.find(h) << endl;
	testTable.print();
	h = "place";
	cout << z << endl;
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

	if (!iFile) return -1;

	while (getline(iFile, tmp)) {
		output.enqueue(tmp);
	}

	return output.getCount();
}

unsigned int operator%(const string &lhs, const unsigned int &rhs) {
	unsigned int lhsval = 0;

	for (unsigned int i = 0; i < lhs.size(); ++i) {
		lhsval += lhs.at(i);
	}

	return lhsval % rhs;
}

int stringModHash(const string &input, const int &size) {
	return input % size;
}
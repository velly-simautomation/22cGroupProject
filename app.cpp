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

//	HashTable<string> table = HashTable<string>(nlines, stringModHash);
	HashTable<string> testTable = HashTable<string>(10, stringModHash);

	// process lines

	testMenu(testTable);
//	mainMenu(table);

	// save data to file

}

int mainMenu(HashTable<string> &table) {
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
		else if (input[0] == 'B');
		else if (input[0] == 'M') printMenu();
	}
	return 0;
}

int testMenu(HashTable<string> &table) {
	string input = "";
	string h = "group";
	string k = "extra";
	string *z = nullptr;

	cout << "22C Group Project Main Menu" << endl;
	cout << "\tData base items : " << endl;
	printMenu();

	while (input[0] != 'Q') {
		cout << "Option : ";
		getline(cin, input);

		if (input.size() != 1) continue;

		input[0] = toupper(input[0]);

		if (input[0] == 'A') {
			table.insert(h);
			table.print();
			cout << table.count() << " out of " << table.size() << endl;
		}
		else if (input[0] == 'B') {
			z = table.remove(table.find(h));
			table.print();
			cout << table.count() << " out of " << table.size() << endl;
		}
		else if (input[0] == 'C') {
			int x = table.find(h);
			if (x > -1)
				cout << "Found at " << x << "." << endl;
		}
		else if (input[0] == 'D') {
			table.remove(0);
		}
		else if (input[0] == 'E') {
			h = "team";
		}
		else if (input[0] == 'F') {
			h = "group";
		}
		else if (input[0] == 'G') {
			if (z)
				cout << *z << endl;
		}
		else if (input[0] == 'H') {
			table.insert(k);
			table.print();
			cout << table.count() << " out of " << table.size() << endl;
		}
		else if (input[0] == 'I') {
			table.remove(table.find(k));
			table.print();
			cout << table.count() << " out of " << table.size() << endl;
		}
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
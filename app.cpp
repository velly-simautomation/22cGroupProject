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

#include "app.h"

using namespace std;

int main(int argc, char *argv[]) {
	Queue<string> readLines;
	int nlines = readFile("defaultInput.txt", readLines);
	int coll[4] = { 0, 0, 0, 0 }; //good total collisons, good max collisions, bad tot, bad max

	HashTable<Robot> badTable = HashTable<Robot>(getNextPrime(nlines), robot_hash_bad); // change nlines with next prime number
	HashTable<Robot> goodTable = HashTable<Robot>(getNextPrime(nlines), robot_hash_good); // same
	BinarySearchTree<Robot*> primaryBST = BinarySearchTree<Robot*>(comparePrimaryKey),
		secondaryBST = BinarySearchTree<Robot*>(compareSecondaryKey);

	processLines(readLines, badTable, goodTable, primaryBST, secondaryBST, coll);

	mainMenu(badTable, goodTable, primaryBST, secondaryBST, coll);

	writeFile("defaultOutput.txt", goodTable);

}

int mainMenu(HashTable<Robot> &badTable, HashTable<Robot> &goodTable, BinarySearchTree<Robot*> &primaryTable, BinarySearchTree<Robot*> &secondaryTable, int coll[4]){
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
		if (input[0] == 'A') {
			primaryTable.inOrder(printRobot);
			cout << endl;
			secondaryTable.inOrder(printRobot);
			cout << endl;
			printHashTable(goodTable, printRobot, coll[0], coll[1]);
			cout << endl;
			printHashTable(badTable, printRobot, coll[2], coll[3]);
			cout << endl << endl;
			cout << robotString(*goodTable.at(0));
			cout << endl;
		}
		else if (input[0] == 'B') {
			writeFile("defaultInput.txt", goodTable);
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

void lineParser(string &line, Robot *&robot) {
	string delimiter = ";";
	const int ARR_MAX = 5;
	string arr[ARR_MAX];
	int index = 0;
	size_t prev = 0;
	size_t next = 0;
	while ((next = line.find(delimiter, prev)) != string::npos) {
		arr[index++] = line.substr(prev, next-prev);
		prev = next + 1;
	}
	robot = new Robot(arr[0], arr[1], arr[2], arr[3], arr[4]);
//	if (index >= ARR_MAX)
//		index = 0;
}

int processLines(Queue<string> &lines, HashTable<Robot> &badTable,
	HashTable<Robot> &goodTable, BinarySearchTree<Robot*> &primaryBST,
	BinarySearchTree<Robot*> &secondaryBST, int col[4]) {
	string tmp;
	Robot *ptr;
	int x, y;

	while (!lines.isEmpty()) {
		lines.dequeue(tmp);
		lineParser(tmp, ptr);
		x = badTable.insert(*ptr);
		y = goodTable.insert(*ptr);
		primaryBST.insert(&*ptr);
		secondaryBST.insert(&*ptr);
		col[0] += y;
		col[2] += x;
		if (y > col[1]) col[1] = y;
		if (x > col[3]) col[3] = x;
	}
	
	return 0;
}

void printRobot(Robot * &robot) {
	cout << robot->getSerialNumber() << " : " <<
		robot->getModel() << " : " <<
		robot->getAlias() << " : " <<
		robot->getComment() << " : " <<
		robot->getProductionDate() << " : " << endl;
}

void printHashTable(const HashTable<Robot> &table, void print(Robot * & robot), const int &totCol, const int &maxCol) {
	Robot * tmp;
	for (int i = 0; i < table.size(); ++i) {
		if ((tmp = table.at(i)) != nullptr) {
			print(tmp);
		}
		else cout << "empty" << endl;
	}
	cout << "Total collisions : " << totCol << "\t Max Collisions on insert : " << maxCol << endl;

}

string robotString(Robot &robot) {
	string tmp = "";

	tmp += robot.getSerialNumber() + ';';
	tmp += robot.getModel() + ';';
	tmp += robot.getAlias() + ';';
	tmp += robot.getComment() + ';';
	tmp += robot.getProductionDate() + ';';

	return tmp;

}

int writeFile(const string &outName, const  HashTable<Robot> &data) {
	fstream oFile;

	oFile.open(outName, ios_base::out);

	if (!oFile) return -1;

	Robot * robot;
	string tmp;

	for (int i = 0; i < data.size(); ++i) {
		if ((robot = data.at(i)) != nullptr) {
			tmp = robotString(*robot);
			oFile.write(tmp.c_str(), tmp.size());
			oFile.write("\n", 1);
		}
	}

	return data.count();
}
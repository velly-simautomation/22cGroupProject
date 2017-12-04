/*
	22C Group Project main header file.
	Fall 2017

	Robot Database

	Contains function declarations for assisting functions to main.

	Team 5 Members:
	Velly Simeonov
	Chejui Chen
	Yuchen Jiang
	Aijun Qin

	Authors:
	Velly
	Aijun Qin
*/

#pragma once

#ifndef _APP_H
#define _APP_H

#include <string>

#include "Queue.h"  // provided by professor for previous assignment
#include "hashtable.h"
#include "Robot.h"
#include "BinarySearchTree.h"

/* main menu manager controlling overall flow of user interactions */
int mainMenu(HashTable<Robot> &badTable, HashTable<Robot> &goodTable, BinarySearchTree<Robot*> &primaryTree, BinarySearchTree<Robot*> &secondaryTree, int coll[4]);

/* menu text to show to user when requested */
int printMenu();

/* opens a text file and dumps lines into a linked list to be processed
 * returns number of lines in output, or -1 on error */
int readFile(const string &fileName, Queue<string> &output);

/* loop to process all strings from Queue of strings created by readFile */
int processLines(Queue<string> &lines, HashTable<Robot> &badTable, HashTable<Robot> &goodTable, BinarySearchTree<Robot*> &primaryTree, BinarySearchTree<Robot*> &secondaryTree, int col[4]);

/* writes hashtable to file */
int writeFile(const string &outName, const HashTable<Robot> &data);

/* Written by Aijun Qin, makes robot from string assuming proper format */
void lineParser(string &line, Robot *&robot);

/* Function to print a robot pointer, passed to BST and printHashTable */
void printRobot(Robot * &robot);

/* Prints hash table inside class and statistics  for the table. */
void printHashTable(const HashTable<Robot> &table, void print(Robot * & robot));

/* returns string equivalent of robot which can be parsed by lineParser */
string robotString(Robot &robot);

/* crude menu for adding data in database */
void addMenu(HashTable<Robot> &badTable, HashTable<Robot> &goodTable, BinarySearchTree<Robot*> &primaryTree, BinarySearchTree<Robot*> &secondaryTree, int col[4]);

/* search menu for robots */
void searchMenu(HashTable<Robot> &goodTable);

/* delete menu */
void deleteMenu(HashTable<Robot> &badTable, HashTable<Robot> &goodTable, BinarySearchTree<Robot*> &prmaryBST, BinarySearchTree<Robot*> &secondaryBST);

/* list menu */
void listMenu(HashTable<Robot> &badTable, HashTable<Robot> &goodTable, BinarySearchTree<Robot*> &prmaryBST, BinarySearchTree<Robot*> &secondaryBST);

#endif
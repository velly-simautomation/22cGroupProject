/*
	22C Group Project main header file.
	Fall 2017

	Contains function declarations for assisting functions to main.

	Team 5 Members:
	Velly Simeonov
	Chejui Chen
	Yuchen Jiang
	Aijun Qin

	Authors:
	Velly

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
int mainMenu(HashTable<Robot> &badTable, HashTable<Robot> &goodTable, BinarySearchTree<Robot*> &primaryTable, BinarySearchTree<Robot*> &secondaryTable);

/* menu text to show to user when requested */
int printMenu();

/* opens a text file and dumps lines into a linked list to be processed
 * returns number of lines in output, or -1 on error */
int readFile(const string &fileName, Queue<string> &output);

int processLines(Queue<string> lines, HashTable<Robot> &badTable, HashTable<Robot> &goodTable, BinarySearchTree<Robot*> &primaryTable, BinarySearchTree<Robot*> &secondaryTable);

int writeFile(const string &outName, HashTable<Robot> data);

#endif
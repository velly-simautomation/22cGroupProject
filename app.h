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

#ifndef APP_H
#define APP_H

#include <string>

#include "Queue.h"  // might want to replace this with one of ours, no author on this one
#include "hashtable.h"

/* main menu manager controlling overall flow of user interactions */
int mainMenu(HashTable<string> &table);

/* used for testing hashtable adt */
int testMenu(HashTable<string> &table);

/* menu text to show to user when requested */
int printMenu();

/* opens a text file and dumps lines into a linked list to be processed
 * returns number of lines in output, or -1 on error */
int readFile(const string &fileName, Queue<string> &output);

/* simple string hashing algorithm */
int stringModHash(const string &value, const int &hashTableSize);

/* returns remainder between the sum of all characters in a string over an unsigned int */
unsigned int operator%(const string &lhs, const unsigned int &rhs);

#endif
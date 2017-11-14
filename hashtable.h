/*
	Abstract hash table data structure.

	22C Fall 2017

	Authors:
	Velly Simeonov

*/


#pragma once
#ifndef HASHTABLE_H
#define HASHTABLE_H

#define _template template<class T>

#include <iostream>

template <class T>
class HashTable {
private:
	T **table = NULL; // table is a pointer to T pointers
	int _size, _count = 0;
	int _goodHash(T item); // must overload operator%(T,uint)
	int _badHash(T item); // must overload operator%(T,uint)


public:
	HashTable(int size);
	~HashTable();
	
	// returns object and index position
	// should it be T or T pointer for return?
	T at(int index);

	// prints to stdout the contents of the hash table
	// first address is hash table address, second is address of T
	// or address of pointer to T and address of T
	int print();

	// insert item into hash table
	int insert(T &item);

};

_template
HashTable<T>::HashTable(int size) {
	table = new T*[size]{ 0 };
	_size = size;
}

_template
HashTable<T>::~HashTable() {
	delete[] table;
}

_template
T HashTable<T>::at(int index) {
	if ((index >= _count) || (index < 0)) return NULL;
	return *table[index];
}

_template
int HashTable<T>::print() {
	for (int i = 0; i < _size; ++i) {
		std::cout << (&table[i]) << " : " << table[i] << " " << (table[i] == NULL) << std::endl;
		
	}
	return 0;
}


//TO DO : hash the data before inserting, return insert index
_template
int HashTable<T>::insert(T &item) {
	table[0] = &item; // testing
	++_count;
	return 0;
}



#endif
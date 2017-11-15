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
#include <cstdint>

template <class T>
class HashTable {
private:
	T **table = nullptr; // table is a pointer to T pointers
	int32_t _size = 0, _count = 0;
	bool _simple = false;
	int32_t (*_hashFunction)(const T* &item) = NULL;

	int32_t _hash(const T &item); // must overload operator%(T,uint32_t)
	int32_t _simpleHash(const T &item); // must overload operator%(T,uint32_t)


public:
	// do not forget to try/catch for bad alloc
	HashTable(int32_t size, bool simple = false);
	HashTable(int32_t size, int32_t hashFunction(const T* &item));

	~HashTable();
	
	// returns pointer to object at index position
	T* at(int32_t index);

	// prints to stdout the contents of the hash table
	// first address is hash table address, second is address of T
	// or address of pointer to T and address of T
	int print();

	// insert item into hash table
	// on sucess returns insert index
	// otherwise -1
	int32_t insert(T &item);

	// hashes item t without inserting
	// returns -1 on error
	int32_t hash(const T &item);

	// searches for T in table
	// returns index on success
	// otherwise -1
	int32_t find(const T &item);

};



// PUBLIC FUNCTIONS

_template
HashTable<T>::HashTable(int32_t size, bool simple) {
	if (size >= 0)
		table = new T*[size] { 0 };
	_size = size;
	_simple = simple;
}

_template
HashTable<T>::HashTable(int32_t size, int32_t hashFunction(const T* &item)) {
	if (size >= 0)
		table = new T*[size] { 0 };
	_size = size;
	_hashFunction = hashFunction;
}

_template
HashTable<T>::~HashTable() {
	if (table != nullptr)
		delete[] table;
}

_template
T* HashTable<T>::at(int32_t index) {
	if ((index >= _size) || (index < 0)) return NULL;
	return table[index];
}

_template
int HashTable<T>::print() {
	for (int32_t i = 0; i < _size; ++i) {
		std::cout << (&table[i]) << " : " << table[i] << " " << (table[i] == NULL) << std::endl;
		
	}
	return 0;
}

_template
int32_t HashTable<T>::insert(T &item) {
	int32_t x = hash(item), offs = 0;

	for (int32_t i = 1; (table[x] != nullptr) && (i < _size); ++i) {
		offs = i;
		offs *= (i % 2) ? 1 : -1; // even values are subtracted from the last checked index
		x += offs;

		// wrapping on left and right sides
		if (x >= _size) x -= _size;
		else if (x < 0) x += _size;
	}

	if (table[x] == nullptr) {
		table[x] = &item;
		++_count;
		return x;
	}

	else return -1; // could not insert
}

_template
int32_t HashTable<T>::hash(const T &item) {
	if (_size <= 0) return -1; // need a table of at least _size 1
	if (_simple) {
		return _simpleHash(item);
	}
	else {
		return _hash(item);
	}
}

// TO DO:
_template
int32_t HashTable<T>::find(const T &item) {
	return -1;
}




// PRIVATE FUNCTIONS

// TO DO:
_template
int32_t HashTable<T>::_hash(const T &item) {
	return 0;
}

_template
int32_t HashTable<T>::_simpleHash(const T &item) {
	return item % _size;
}


#endif
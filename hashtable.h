/*
	Abstract hash table data structure.

	Uses alternating probe for collision resolution.
	Goes back and forth from the hashed index value until
	first empty index is found. (0 -> 1 -> -1 -> 2 -> -2 etc)

	Constructor needs a hash function using the data type stored
	in hash table.

	Possible for future: constructor should also take collision resolution
	function for more flexibilty.

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
	int32_t _size = 0, _count = 0; // TO DO: getters and setters
	int32_t (*_hashFunction)(const T &item, const int32_t &size) = nullptr;

public:
	// hash table constructor taking in size of table and hash function to use with items stored
	// do not forget to try/catch for a bad alloc exception
	HashTable(int32_t size, int32_t hashFunction(const T &item, const int32_t &size));

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

	// hash wrapper, -1 on error
	int32_t hash(const T &item);

	// searches for T in table
	// returns index on success
	// otherwise -1
	int32_t find(const T &item);

	// remove item at index, return item reference
	T& remove(const int32_t &index);
};


// PUBLIC FUNCTIONS

_template
HashTable<T>::HashTable(int32_t size, int32_t hashFunction(const T &item, const int32_t &size)) {
	if (size > 0)
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
		std::cout << (&table[i]) << " : " << table[i] << " " << (table[i] == nullptr) << std::endl;
		
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

	if (table[x] == nullptr) { // x is never > _size from previous wrap
		table[x] = &item;
		++_count;
		return x;
	}

	else return -1; // could not insert
}

_template
int32_t HashTable<T>::hash(const T &item) {
	if (_size < 1) return -1; // need a table of at least _size 1
	if (_hashFunction != nullptr) {
		return _hashFunction(item,_size);
	}
	return -1;
}

_template
int32_t HashTable<T>::find(const T &item) {
	int32_t x = hash(item), offs = 0;
	if (x == -1) return -1; // table not allocated or function error

	for (int32_t i = 1; (table[x] != nullptr) && (i < _size); ++i) {
		if (*(table[x]) == item)
			return x;

		offs = i;
		offs *= (i % 2) ? 1 : -1; // even values are subtracted from the last checked index
		x += offs;

		// wrapping on left and right sides
		if (x >= _size) x -= _size;
		else if (x < 0) x += _size;
	}

	return -1; // not found
}

_template
T& HashTable<T>::remove(const int32_t &index) {
	T& tmp = *table[index];
	table[index] = nullptr;
	return tmp;
}


#endif
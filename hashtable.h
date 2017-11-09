#pragma once
#ifndef HASHTABLE_H
#define HASHTABLE_H

#define _template template<class T>

#include <iostream>

template <class T>
class HashTable {
private:
	T **table = NULL;
	int _size, _count = 0;


public:
	HashTable(int size);
	~HashTable();

	T at(int index);

	int print();


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
	table[0] = &item;
	++_count;
	return 0;
}

#endif
// Specification file for Robot class
// Created by Aijun Qin
// Modified by: Velly

#ifndef _ROBOT_H
#define _ROBOT_H

#include <iostream>
#include <string>

//using namespace std; do not use in headers

class Robot
{
private:
	string serialNumber;
	string model;
	string alias;
	string comment;
	string productionDate;

public:
	// constructors
	Robot() {};
	Robot(string, string, string, string, string);

	// copy constructor
	Robot(const Robot &obj);

	// destructor
	~Robot();

	// mutators
//	void setSerialNumber(const string s) {serialNumber = s;}
//	void setModel(const string m) {model = m;}
	void setAlias(const string a) {alias = a;}
	void setComment(const string c) {comment = c;}
	void setProductionDate(const string p) {productionDate = p;}

	// accessors
	string getSerialNumber() const	 {return serialNumber;}
	string getModel() const	 {return model;}
	string getAlias() const	 {return alias;}
	string getComment() const	 {return comment;}
	string getProductionDate() const	 {return productionDate;}

	// Overloaded operator functions
	bool operator==(const Robot &r) const;
	bool operator<(const Robot &r) const;
	bool operator>(const Robot &r) const;

	// friends
	friend ostream &operator<<(ostream &stream, const Robot &obj);
};

int robot_hash_good(const Robot &item, const int &size);
int robot_hash_bad(const Robot &item, const int &size);
int comparePrimaryKey(Robot * &p1, Robot * &p2); // changed from const *p1 and *p2 to match with BST : velly
int compareSecondaryKey(Robot * &p1, Robot * &p2); // changed from const *p1 and *p2 to match with BST : velly

#endif

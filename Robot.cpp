// Implementation file for Robot class
// Created by Aijun Qin
// Modified by: Velly

using namespace std;
#include "Robot.h"


// constructor

Robot::Robot(string serialNumber, string model, string alias,
             string comment, string productionDate)
{
    this->serialNumber = serialNumber;
    this->model = model;
    this->alias = alias;
    this->comment = comment;
    this->productionDate = productionDate;
}

// copy constructor
Robot::Robot(const Robot &obj)
{
    serialNumber = obj.serialNumber;
    model = obj.model;
    alias = obj.alias;
    comment = obj.comment;
    productionDate = obj.productionDate;
}

// destructor
Robot::~Robot()
{
}

bool Robot::operator==(const Robot &r) const
{
    return serialNumber == r.serialNumber;
}

bool Robot::operator<(const Robot &r) const
{
    return serialNumber < r.serialNumber;
}

bool Robot::operator>(const Robot &r) const
{
    return serialNumber > r.serialNumber;
}

ostream &operator<<(ostream &strm, const Robot &obj)
{
    strm << "Serial Number: " << obj.serialNumber << "\tModel: " << obj.model
         << "\tAlias: " << obj.alias << "\tComment: " << obj.comment
         << "\tProduction Date: " << obj.productionDate;
    return strm;
}


int robot_hash_good(const Robot &item, const int &size)
{
    int sum = 0;
	string snr = item.getSerialNumber(); // velly : key was being assigned to a tmp variable returned by this which was empty, perhaps undefined behavior works on some machines but not all
	const char *key = snr.c_str();

    while (*key)
    {
        sum += *key * *key * *key;
        key++;
    }
    return sum % size;
}

int robot_hash_bad(const Robot &item, const int &size)
{
    int sum = 0;
	string snr = item.getSerialNumber(); // velly : same as good hash
	const char *key = snr.c_str();

    while (*key)
    {
        sum += *key++;
    }
    return sum % size;
}

int comparePrimaryKey(Robot * &p1, Robot * &p2)
{
    string sn1 = p1->getSerialNumber();
    string sn2 = p2->getSerialNumber();

    if (sn1 > sn2)
        return 1;
    else if (sn1 < sn2)
        return -1;
    else
        return 0;
}

int compareSecondaryKey(Robot * &p1, Robot * &p2)
{
    string model1 = p1->getModel();
    string model2 = p2->getModel();

    if (model1 > model2)
        return 1;
    else if (model1 < model2)
        return -1;
    else
        return comparePrimaryKey(p1, p2);
}

/*
	Utils Header file

	CIS 22C Fall 2017
	Velly Simeonov

	Contains useful function declarations which are not homework exclusive.
*/

#pragma once
#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

namespace vutil {
	/*
	Posted by GManNickG on stack overflow as a method of trimming
	leading and following spaces from a string without using
	boost libraries.
	*/
	std::string trim(const std::string &, const std::string & = " \t\n");

	/*
	Posted by GManNickG on stack overflow as a method of trimming
	spaces in the middle of a string without using boost libraries.
	*/
	std::string reduce(const std::string &, const std::string &, const std::string & = " \t\n");

	/*
	Transforms input string to lowercase.
	*/
	std::string stringToLower(const std::string &string);

	/*
	Transforms input string to uppercase.
	*/
	std::string stringToUpper(const std::string &string);

	/*
	Tokenizes a string into a vector of smaller strings between delimitors.
	*/
	std::vector<std::string> tokenize(const std::string &string, const char &delim);

	/*
	Checks if passed string is a palindrome,
	Passed string is expected to already be only words and
	punctuation with space as the only delimiter.
	*/
	bool checkPalindrome(std::string line);
}


#endif // !UTILS_H


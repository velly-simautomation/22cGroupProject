/*
	Utils Source file

	CIS 22C Fall 2017
	Velly Simeonov

	Contains useful functions which are not homework exclusive.
*/

#include "Utils.h"

#include <string>
#include <algorithm>
#include <cctype>
#include <sstream>
#include <vector>


namespace vutil {

	std::string trim(const std::string& str,
		const std::string& whitespace)
	{
		const auto strBegin = str.find_first_not_of(whitespace);
		if (strBegin == std::string::npos)
			return ""; // no content

		const auto strEnd = str.find_last_not_of(whitespace);
		const auto strRange = strEnd - strBegin + 1;

		return str.substr(strBegin, strRange);
	}


	std::string reduce(const std::string& str,
		const std::string& fill,
		const std::string& whitespace)
	{
		// trim first
		auto result = trim(str, whitespace);

		// replace sub ranges
		auto beginSpace = result.find_first_of(whitespace);
		while (beginSpace != std::string::npos)
		{
			const auto endSpace = result.find_first_not_of(whitespace, beginSpace);
			const auto range = endSpace - beginSpace;

			result.replace(beginSpace, range, fill);

			const auto newStart = beginSpace + fill.length();
			beginSpace = result.find_first_of(whitespace, newStart);
		}

		return result;
	}


	std::string stringToLower(const std::string &string) {
		std::string result = string;
		std::transform(result.begin(), result.end(), result.begin(), ::tolower);
		return result;
	}

	std::string stringToUpper(const std::string &string) {
		std::string result = string;
		std::transform(result.begin(), result.end(), result.begin(), ::toupper);
		return result;
	}


	std::vector<std::string> tokenize(const std::string &string, const char &delim) {
		std::vector<std::string> result;

		std::stringstream stream(string);// = std::stringstream(string); GCC doesnt like
		std::string tmp;

		while (std::getline(stream, tmp, delim)) {
			result.push_back(tmp);
		}

		return result;
	}


	bool checkPalindrome(std::string line) {
		line = vutil::stringToLower(line);
		line = vutil::reduce(line, "", ".!?\'\",:;-\r");
		line = vutil::reduce(line, " ", " ");

		std::vector<std::string> tokens = vutil::tokenize(line, ' ');

		int wcount = static_cast<int>(tokens.size());

		for (int i = 0; i <= (wcount / 2); ++i) {
			if (tokens.at(i) != tokens.at(wcount - i - 1)) // 0 index offset of 1
				return false;
		}
		return true;
	}
}
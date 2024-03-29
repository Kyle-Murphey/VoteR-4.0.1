#ifndef NVRA_RECORD_H
#define NVRA_RECORD_H

#include <iostream>

const int MAX_NUMS = 21;					// the maximum numeric fields in each record
const int MAX_STRINGS = 3;					// the maximum string fields in each record

class NvraRecord {

	// overloaded output operator that sends one formatted record to ostream
	friend std::ostream& operator<<(std::ostream& os, const NvraRecord& record);

private:
	int nums[MAX_NUMS];						// holds the numeric data, in column order
	int numCtr = 0;							// counts the number of numbers added to the record
	std::string strings[MAX_STRINGS];		// holds the string data, in column order
	int strCtr = 0;							// count the number of strings added to the record
public:
	void addNum(int num);					// puts num in array, increments counter
	void addString(std::string string);		// puts string in array, increments counter
	int getNum(int index);					// returns (copy of) num at index in array
	std::string getString(int index);		// returns (copy of) string at index in array
};
#endif
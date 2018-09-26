#include "NvraRecord.h"
#include <string>



/* This class and its header were copied from Lab 3 */



/*
	overloads the '<<' operator to make outputting data cleaner
	puts ';' between each element
	@param:os = output stream e.i. 'std::cout'
	@param:record = reference to the line that needs to be printed
	@return = the output
*/
std::ostream & operator<<(std::ostream & os, const NvraRecord & record)
{
	int stringNum = 0; // keeps track of the index in the strings array
	int intNum = 0; // keeps track of the index in the nums array

	//loops through each element in the line
	for (unsigned int index = 0; index < 24; ++index)
	{
		//string elements
		if (index == 3 || index == 11 || index == 12)
		{
			os << record.strings[stringNum] << ";";
			++stringNum;
		}
		//int elements
		else
		{
			//last element doesn't get a ';' printed after it
			if (index == 23)
			{
				os << record.nums[intNum];
				++intNum;
			}
			//all other elements get a ';' after
			else
			{
				os << record.nums[intNum] << ";";
				++intNum;
			}
		}
	}
	return os;
}

/*
	adds the numbers to the nums array
	@param:num = value to be added to the array
*/
void NvraRecord::addNum(int num)
{
	//invalid data
	if (num < 0)
	{
		numCtr = 0; // resetting index for nums
		strCtr = 0; // restting index for strings
		return;
	}
	//index has reached its limit
	if (numCtr > (MAX_NUMS - 1))
	{
		numCtr = 0; // resetting index for nums
	}
	nums[numCtr] = num; // adds the passed in num to the nums array at index numCtr
	++numCtr; // increment the nums index
}

/*
	adds the string to the strings array
	@param:string = string to be added to the array
*/
void NvraRecord::addString(std::string string)
{
	//index has reached its limit
	if (strCtr > 2)
	{
		strCtr = 0; // resetting index for strings
	}
	strings[strCtr] = string; // adds the passed in string to the strings array at index strCtr
	++strCtr; // increment the strings index
}

/*
	gets value at given index
	@param:index = index of number you are trying to get
	@return = value at given index
*/
int NvraRecord::getNum(int index)
{
	return nums[index];
}

/*
	gets string at given index
	@param:index = index of string you are trying to get
	@return = string at given index
*/
std::string NvraRecord::getString(int index)
{
	return strings[index];
}

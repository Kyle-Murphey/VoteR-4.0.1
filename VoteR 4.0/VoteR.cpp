#include <iostream>
#include <string>
#include <vector>
#include "NvraRecord.h"
#include "TemplatedArray.h"

/*****************************************************************************************************************************
*	VoteR                                                                                                                    *
*	Lab 4: CS 2413                                                                                                           *
*	9/24/18                                                                                                                  *
*	Kyle Murphey                                                                                                             *
*	                                                                                                                         *
*	This application reads in a .csv file while dynamically allocating memory and outputs the contents in reverse order      *
*	Data can be added, replaced, and removed from the array                                                                  *
*	It also filters out errors and prints them first                                                                         *
******************************************************************************************************************************/


/*
	Taken from my previous lab: VoteR 3.0

	loops through the valid record Ids that have already been stored
	@param:id = the id of the line
	@param:recordIds = reference to the where the record ids are stored
	@return = whether or not the id already exists
*/
bool doesIDExist(int id, std::vector<int>& recordIds)
{
	bool doesExist = false;

	for (unsigned int index = 0; index < (unsigned int)recordIds.size(); ++index)
	{
		// id exists
		if (id == recordIds.at(index))
		{
			doesExist = true;
		}
	}
	return doesExist;
}

/*
	much of the code is adapted from my previous lab: VoteR 3.0

	main function for the VoteR 3.0 application
	loops through the file, checks for invalid data and duplicates, then prints out the lines in reverse order with all errors printed first
*/
int main()
{
	const unsigned int COLUMNS = 24; // number of columns in the file
	unsigned long arrCount = 0; // size of the array
	unsigned long lines = 0; // number of lines in the file
	bool idExists = false; // flag for duplicate IDs
	bool isValid = true; // flag for valid lines
	std::vector<int> recordIDs(0); // stores the NvraRecord IDs that aren't duplicates
	std::string input; // data read in from the file is stored here

	TemplatedArray<NvraRecord> nvraArray; // creation of the TemplatedArray<NvraRecord> object
	NvraRecord nvraRecord; // creation of the NvraRecord object

	//skipping the first line of the file (header line)
	std::getline(std::cin, input);
	//loops through the whole file
	while (!std::cin.eof())
	{
		++lines; // incrementing line number
		isValid = true; // setting validity flag to true by default
		//loops through each piece of data in the line
		for (unsigned int index = 0; index < COLUMNS; ++index)
		{
			//checking the last element in the line since it doesn't end in a ';'
			if (index == (COLUMNS - 1))
			{
				getline(std::cin, input, '\n');
				//making sure value is valid
				if (stoi(input) < 0)
				{
					nvraRecord.addNum(stoi(input)); // sending the invalid value to the NvraRecord class so it can reset its counters
					std::cout << "Invalid data at line " << std::to_string(lines) << "." << std::endl;
					isValid = false; // flagging line as invalid
					recordIDs.pop_back(); // removing ID from the recordIDs list
					break;
				}
				else
				{
					nvraRecord.addNum(stoi(input)); // adding value to the nums array
					break;
				}
			}

			//getting the first element of the line
			std::getline(std::cin, input, ',');
			//checking whether or not the line even has data in it
			if (input.empty())
			{
				isValid = false;
				break;
			}
			//checking all int values for validity
			if (index != 3 && index != 11 && index != 12)
			{
				if (stoi(input) < 0)
				{
					nvraRecord.addNum(stoi(input)); // sending the invalid value to the NvraRecord class so it can reset its counters
					std::cout << "Invalid data at line " << std::to_string(lines) << "." << std::endl;
					std::getline(std::cin, input, '\n'); // skipping the rest of the line
					isValid = false; // flagging line as invalid
					recordIDs.pop_back(); // removing ID from the recordIDs list
					break;
				}
			}
			//checking the record id for duplicates
			if (index == 0)
			{
				//sends ID to doesIDExist function to check if it is a duplicate
				idExists = doesIDExist(stoi(input), recordIDs);
				//id doesn't exist
				if (!idExists)
				{
					recordIDs.push_back(stoi(input)); // adding ID to the recordIds list
					nvraRecord.addNum(stoi(input)); // adding ID to the nums array
				}
				//id is a duplicate
				else
				{
					idExists = false; // resetting flag
					std::cout << "Duplicate record ID " << std::to_string(stoi(input)) << " at line " << std::to_string(lines) << "." << std::endl;
					std::getline(std::cin, input, '\n'); // skipping the rest of the line
					isValid = false; // flagging as invalid
					break;
				}
			}
			//all other elements in the line
			else
			{
				//string elements
				if (index == 3 || index == 11 || index == 12)
				{
					nvraRecord.addString(input);
				}
				//int elements
				else
				{
					nvraRecord.addNum(stoi(input));
				}
			}
		}
		//if the line is valid, it gets added to the nvra array
		if (isValid)
		{
			nvraArray.add(&nvraRecord);
			++arrCount; // keeps track of valid lines in the array
		}
	}

	//loops through all the elements in nvraArray and outputs them in reverse order
	for (unsigned long index = arrCount; index > 0; --index)
	{
		std::cout << nvraArray.get(index - 1); // calls the overloaded version of '<<' in the NvraRecord class
		std::cout << std::endl;
	}
}

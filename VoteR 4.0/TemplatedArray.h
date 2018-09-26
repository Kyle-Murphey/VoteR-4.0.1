#include "Exceptions.h"

const int DEFAULT_ARRAY_CAPACITY = 10;					// capacity used in no arg constructor

template<typename T>
class TemplatedArray {
private:
	unsigned long capacity = DEFAULT_ARRAY_CAPACITY;	// maximum capacity, in records
	unsigned long size = 0;								// actual number of items currently in array
	T* data = NULL;										// pointer to array of records
public:
	TemplatedArray();									// constructs array with default capacity
	TemplatedArray(int capacity);						// constructs array with specified capacity
	virtual ~TemplatedArray();							// frees array space as object is deleted
	void add(T* record);								// adds record, increments size, doubles capacity as necessary
	void addAt(T* record, unsigned long index);			// adds record at given index, increments size, doubles capacity as needed
	void replaceAt(T* record, unsigned long index);		// replaces record at given index with passed in record
	void removeAt(unsigned long index);					// removes record at given index and shifts the trailing records left by one index	
	T get(unsigned long index);							// returns (copy of) record at index
};
/*#####################################################################################################################################################################################*/



/*
	default constructor
*/
template<typename T>
TemplatedArray<T>::TemplatedArray()
{
	data = new T[capacity]; // initializes T array with size capacity
}

/*
	constructor taking an int parameter
	@param:capacity = size of the T array
*/
template<typename T>
TemplatedArray<T>::TemplatedArray(int capacity)
{
	this->capacity = capacity; // sets the capacity to the passed in value
	data = new T[capacity]; // initializes T array with size capacity
}

/*
	deconstructor
*/
template<typename T>
TemplatedArray<T>::~TemplatedArray()
{
	delete[] data;
	data = NULL;
}

/*
	Adapted from lab 3

	adds a T to the array and dynamically allocates memory as needed
	@param:record = pointer to a T to be added to the TemplatedArray data array
*/
template<typename T>
void TemplatedArray<T>::add(T* record)
{
	//max capacity reached
	if (size == capacity)
	{
		//temporary T* array with twice the capacity
	    T* temp = new T[capacity * 2];

		//loops through the original TemplatedArray and assigns the values to temp[]
		for (unsigned long index = 0; index < size; ++index)
		{
			temp[index] = data[index];
		}

		//doubles the capacity of the original TemplatedArray
		capacity = capacity * 2;
		data = new T[capacity];

		//loops through the temp[] and puts them back into the original TemplatedArray
		for (unsigned long index = 0; index < size; ++index)
		{
			data[index] = temp[index];
		}
		//clearing memory
		delete[] temp;
		temp = NULL;
	}
	data[size] = *record; // adds the T to the data array
	++size; // increments the value of the size of the array
}

/*
	adds a T to the array at the given index and dynamically allocates memory as needed
	@param:record = pointer to a T to be added to the TemplatedArray data array
	@param:location = index to add record
*/
template<typename T>
void TemplatedArray<T>::addAt(T* record, unsigned long location) 
{
	//index out of bounds
	if (location >= size)
	{
		throw new ExceptionIndexOutOfRange;
	}
	else
	{
		//temporary T* array with twice the capacity
		T* temp = new T[capacity * 2];

		bool added = false; // flag for when the value gets added

		//array needs doubling
		if (size == capacity)
		{
			//populates the temp[] with all the data values
			for (unsigned long index = 0; index < size; ++index)
			{
				temp[index] = data[index];
			}

			//doubles the capacity of your data array
			capacity = capacity * 2;
			data = new T[capacity];

			//putting values back into your data array
			for (unsigned long index = 0; index < size; ++index)
			{
				data[index] = temp[index];
			}
		}

		//adds value at the given index to temp array
		for (unsigned long index = 0; index < size; ++index)
		{
			//index to insert
			if (index == location)
			{
				temp[index] = *record; // inserting record
				added = true; // flagging added
				location = size + 1; // setting location's size to unreachable value
				--index; // goes back to value that was supposed to go in index
			}
			else
			{
				if (added) temp[index + 1] = data[index]; // record* already added so index gets bumped up by one
				else temp[index] = data[index]; // populating temp[]
			}
		}
		//puts values back into your array
		for (unsigned long index = 0; index < size + 1; ++index)
		{
			data[index] = temp[index];
		}
		++size; // data array increases in size by 1

		//clearing memory
		delete[] temp;
		temp = NULL;
	}
}

/*
	replaces a record at a given index
	@param:record = pointer to a T to be added to the TemplatedArray data array
	@param:index = index of record to be replaced by given record
*/
template<typename T>
void TemplatedArray<T>::replaceAt(T* record, unsigned long index)
{
	if (index >= size) throw new ExceptionIndexOutOfRange; // index out of bounds
	else data[index] = *record; // replaces record at index
}

/*
	removes the record at the given index and dynamically deallocates memory as needed
	@param:location = index of record to be removed
*/
template<typename T>
void TemplatedArray<T>::removeAt(unsigned long location)
{
	if (location >= size)
	{
		throw new ExceptionIndexOutOfRange;
	}
	else
	{
		//temporary T* array
		T* temp = new T[capacity];

		bool removed = false; // flag for when the record is removed

		//populates the temp[] with every record except the one at location
		for (unsigned long index = 0; index < size; ++index)
		{
			if (index == location)
			{
				location = size + 1;
				removed = true;
			}
			else
			{
				if (removed) temp[index - 1] = data[index];
				else temp[index] = data[index];
			}
		}

		//puts the records back into your data[] without the record at location
		for (unsigned long index = 0; index < size - 1; ++index)
		{
			data[index] = temp[index];
		}
		--size; // decreases the data array size by 1

		//capacity gets halved when the number of records in the array is less than half of the capacity
		if (size <= (capacity / 2))
		{
			//adds all the values to the temp array
			for (unsigned long index = 0; index < size; ++index)
			{
				temp[index] = data[index];
			}

			//halves the capacity of the data array
			capacity = capacity / 2;
			data = new T[capacity];

			//puts the values back into your data array
			for (unsigned long index = 0; index < size; ++index)
			{
				data[index] = temp[index];
			}
		}
		//clearing memory
		delete[] temp;
		temp = NULL;
	}
}

/*
	gets the T at the given index
	@param:index = index of the requested T
	@return = the T at the given index
*/
template<typename T>
T TemplatedArray<T>::get(unsigned long index)
{
	if (index >= size) throw new ExceptionIndexOutOfRange; // index out of bounds
	else return data[index];
}
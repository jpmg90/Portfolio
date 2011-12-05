/*
 * MyString.cpp
 */

#include "MyString.h"
// Constructors and Destructor
MyString::MyString() : actualSize(0), capacity(INITIAL_SIZE), buffer(new char[capacity])// Initialization list (reason for is in notes)
{ 
	cout << "Default constructor called" << endl;
}

MyString::MyString(char* charArray) : actualSize(strlen(charArray)), capacity(actualSize), buffer(new char[capacity])
{
	strcpy(buffer, charArray);
}

MyString::MyString(string stringString) : actualSize(stringString.size()), capacity(actualSize), buffer(new char[capacity])
{
	strcpy(buffer, stringString.c_str());
}

MyString::~MyString()
{
	delete[] buffer;// if new had '[]' be sure that the delete has '[]'
	cout << "Destructor called" << endl;
}

// Overloaded Copy Constructor
MyString::MyString(const MyString& toBeCopied) 
{
	copyFrom(toBeCopied);
	cout << "Copy constructor called" << endl;
}

// Overloaded assignment operator
MyString& MyString::operator =(const MyString& rhs) 
{
	cout << "Assignment operator called" << endl;
	if (this != &rhs)
	{
		delete[] buffer;
		copyFrom(rhs);
	}
	return *this;
}

const unsigned int MyString::size() const
{
	return actualSize;
}

// Overloaded '+' Operator's
MyString& MyString::operator +(MyString& myString)
{
	concatenate(myString);
	return *this;
}
MyString& MyString::operator +(char* charArray)
{
	concatenate(MyString(charArray));
	return *this;
}
MyString& MyString::operator +(string stringString)
{
	concatenate(MyString(stringString));
	return *this;
}

void MyString::copyFrom(const MyString& toBeCopied)
{
	buffer = new char[toBeCopied.capacity];
	capacity = toBeCopied.capacity;
	actualSize = toBeCopied.actualSize;
	strncpy(buffer, toBeCopied.buffer, toBeCopied.actualSize);
}

void MyString::concatenate(const MyString& toBeConcatenated)
{
	if (actualSize + toBeConcatenated.actualSize <= capacity)
	{
		copyToEndOfBuffer(toBeConcatenated.buffer, toBeConcatenated.actualSize);
		actualSize = actualSize + toBeConcatenated.actualSize;
	}
	else
	{
		char * newBuffer = new char[actualSize + toBeConcatenated.actualSize];
		strncpy(newBuffer, buffer, actualSize);
		delete[] buffer;
		buffer = newBuffer;
		copyToEndOfBuffer(toBeConcatenated.buffer, toBeConcatenated.actualSize);
		capacity = actualSize + toBeConcatenated.actualSize;
		actualSize = capacity;
	}
}

void MyString::copyToEndOfBuffer(char* toBeCopied, unsigned int size)
{
	for (unsigned int index = 0; index < size; ++index)
	{
		buffer[index + actualSize] = toBeCopied[index];
	}
}

ostream& operator<<(ostream& outputStream, const MyString& myString)
{
	outputStream << myString.buffer;

	return outputStream;
}

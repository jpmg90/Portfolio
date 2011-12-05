 /*
 * MyString.h
 */

#ifndef MYSTRING_H_
#define MYSTRING_H_

#include "StandardIncludes.h"

class MyString
{
public:
	MyString();
	MyString(char*);
	MyString(string);
	MyString(const MyString&);// Overloaded Copy constructor (Be sure to add the '&' to prevent infinite loop)
	virtual ~MyString();
	MyString& operator=(const MyString&);// prevents bitwise Copy, same reason why we overloaded the copy constructor
	const unsigned int size() const;
	MyString& substring(int, int);
	MyString& reverse();
	MyString& toUpper();
	MyString& toLower();
	MyString& operator+(MyString&);// Overriding '+' operator, with a reference to a MyString
	MyString& operator+(char *);
	MyString& operator+(string);

	//it’s not a method of this class, but that this overloaded operator when used with a reference of a mystring and an os then it’s a friend
	//Friends have keys to the house, but it is not a member of the class
	friend ostream& operator<<(ostream& outStream, const MyString& thisMyString);

private:
	int actualSize;
	int capacity;
	char* buffer;
	static const int INITIAL_SIZE = 10;
	void copyFrom(const MyString& toBeCopied);
	void concatenate(const MyString&);
	void copyToEndOfBuffer(char* toBeCopied, unsigned int size);
};

#endif /* MYSTRING_H_ */

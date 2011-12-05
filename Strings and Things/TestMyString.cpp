/*
 * TestMyString.cpp
 */

#include "TestMyString.h"
// TODO Ensure you have a StandardInclude.h source file in your project
#include "StandardIncludes.h"

void TestMyString::setUp()
{
	// TODO Your setup code goes here.  Typically you will set your instance
	// variables in this code
}

void TestMyString::tearDown()
{
	// TODO Your tear down code goes here. Typically, you will be deleting any
	// pointers you created in the setUp method
}

void TestMyString::testMyStringConstructor()
{
	cout << "Starting testMyStringConstructor" << endl;
	MyString original;
	MyString copiedVersion(original);
	cout << "End testMyStringConstructor" << endl;
}

void TestMyString::testCharConstructor()
{
	cout << "Starting testCharConstructor" << endl;
	MyString myString((char *) "Hello");
	cout << "End testCharConstructor" << endl;
}

void TestMyString::testStringConstructor()
{
	cout << "Starting testStringConstructor" << endl;
	string testString = "Hello";
	MyString myString(testString);
	cout << "End testStringConstructor" << endl;
}

void TestMyString::testConcatenate()
{
	cout << "Starting testConcatenate" << endl;
	MyString hello((char *) "Hello ");
	MyString world((char *) "World");
	MyString helloWorld = hello + world;
	CPPUNIT_ASSERT(helloWorld.size() == 11);
	cout << "End testConcatenate" << endl;
}

//Miller Code
void TestMyString::testStreamInsertion()
{
	cout << "Starting testStremInsertion" << endl;
	MyString myString((char *) "Hello World");
	ostringstream outputStream;
	outputStream << myString;
	CPPUNIT_ASSERT(outputStream.str() == "Hello World");
	cout << "End testStreamInsertion" << endl;
}

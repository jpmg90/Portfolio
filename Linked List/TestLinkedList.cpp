/*
 * TestLinkedList.cpp 
 */

#include "TestLinkedList.h"
// TODO Ensure you have a StandardInclude.h source file in your project
#include "StandardIncludes.h"

void TestLinkedList::setUp()
{
	// TODO Your setup code goes here.  Typically you will set your instance
	// variables in this code
}

void TestLinkedList::tearDown()
{
	// TODO Your tear down code goes here. Typically, you will be deleting any
	// pointers you created in the setUp method
}

void TestLinkedList::testPushBack()
{
	numberList.clear();
	cout << "Start PushBack test." << endl;
	CPPUNIT_ASSERT(numberList.size() == 0);
	numberList.push_back(0);
	numberList.push_back(1);
	CPPUNIT_ASSERT(numberList[0] == 0);
	CPPUNIT_ASSERT(numberList[1] == 1);
	CPPUNIT_ASSERT(numberList.size() == 2);
	cout << "End PushBack test." << endl;

}

void TestLinkedList::testClear()
{
	numberList.clear();
	cout << "Start Clear test." << endl;
	CPPUNIT_ASSERT(numberList.size() == 0);
	numberList.push_back(0);
	numberList.push_back(1);
	CPPUNIT_ASSERT(numberList.size() == 2);
	numberList.clear();
	CPPUNIT_ASSERT(numberList.size() == 0);
	cout << "End Clear test." << endl << endl;

}

void TestLinkedList::testRemoveIndex()
{
	numberList.clear();
	cout << "Start RemoveIndex test." << endl;
	numberList.push_back(0);
	numberList.push_back(1);
	numberList.push_back(2);
	CPPUNIT_ASSERT(numberList.size()==3);
	CPPUNIT_ASSERT(numberList[1] == 1);
	numberList.removeIndex(1);
	CPPUNIT_ASSERT(numberList[1] == 2);
	cout << "End RemoveIndex test." << endl << endl;
}
void TestLinkedList::testRemoveNodeWithData()
{
	numberList.clear();
	cout << "Start RemoveNodeWithData test." << endl;
	numberList.push_back(10);
	numberList.push_back(11);
	numberList.push_back(12);
	CPPUNIT_ASSERT(numberList.size() == 3);
	CPPUNIT_ASSERT(numberList[1] == 11);
	numberList.removeNodeWithData(11);
	CPPUNIT_ASSERT(numberList[1] == 12);
	cout << "End RemoveNodeWithData test." << endl << endl;
}
void TestLinkedList::testInsert()
{
	numberList.clear();
	cout << "Start Insert test." << endl;
	numberList.push_back(0);
	numberList.push_back(1);
	CPPUNIT_ASSERT(numberList.size() == 2);
	CPPUNIT_ASSERT(numberList[1] == 1);
	numberList.insert(1, 4);
	CPPUNIT_ASSERT(numberList.size() == 3);
	CPPUNIT_ASSERT(numberList[1] == 4);
	cout << "End Insert test." << endl << endl;
}

void TestLinkedList::testPopBack()
{
	numberList.clear();
	cout << "Start PopBack test." << endl;
	numberList.push_back(0);
	numberList.push_back(1);
	CPPUNIT_ASSERT(numberList.size() == 2);
	numberList.pop_back();
	CPPUNIT_ASSERT(numberList.size() == 1);
	CPPUNIT_ASSERT(numberList[0] == 0);
	cout << "End PopBack test." << endl << endl;
}
void TestLinkedList::testIndex()
{
	numberList.clear();
	cout << "Start Index test." << endl;
	numberList.push_back(0);
	numberList.push_back(1);
	CPPUNIT_ASSERT(numberList[1] == 1);
	cout << "End Index test." << endl << endl;
}
void TestLinkedList::testCopyConstructor()
{
	numberList.clear();
	cout << "Start Copy Constructor test." << endl;
	numberList.push_back(1);
	numberList.push_back(2);
	numberList.push_back(3);
	numberList.push_back(4);
	LinkedList<int> copyList = numberList;
	numberList.removeIndex(1);
	CPPUNIT_ASSERT(numberList.size() == 3);
	CPPUNIT_ASSERT(copyList.size() == 4);
	copyList.removeIndex(2);
	CPPUNIT_ASSERT(copyList.size() == 3);
	CPPUNIT_ASSERT(copyList[0] == 1);
	cout << "End Copy Constructor test." << endl << endl;
}
void TestLinkedList::testAssignment()
{
	numberList.clear();
	numberListTwo.clear();
	cout << "Start Assignment test." << endl;
	numberList.push_back(0);
	numberList.push_back(1);
	numberListTwo = numberList;
	CPPUNIT_ASSERT(numberListTwo.size()==2);
	cout << "End Assignment test." << endl << endl;

}
void TestLinkedList::testEquality()
{
	numberList.clear();
	numberListTwo.clear();
	cout << "Start Equality test." << endl;
	 numberList.push_back(0);
	 numberList.push_back(1);
	 numberListTwo.push_back(0);
	 numberListTwo.push_back(1);
	 CPPUNIT_ASSERT(numberList == numberListTwo);
	cout << "End Equality test." << endl << endl;
}

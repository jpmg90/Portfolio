/*
 * TestLinkedList.h 
 */

#ifndef TESTLINKEDLIST_H_
#define TESTLINKEDLIST_H_
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "LinkedList.h"

class TestLinkedList: public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE (TestLinkedList);
	// TODO Repeat one of the following lines for each of your test methods
    CPPUNIT_TEST (testPushBack);
    CPPUNIT_TEST (testClear);
    CPPUNIT_TEST (testRemoveIndex);
    CPPUNIT_TEST (testRemoveNodeWithData);
    CPPUNIT_TEST (testInsert);
    CPPUNIT_TEST (testPopBack);
    CPPUNIT_TEST (testIndex);
    CPPUNIT_TEST (testCopyConstructor);
    CPPUNIT_TEST (testAssignment);
    CPPUNIT_TEST (testEquality);
    CPPUNIT_TEST_SUITE_END ();
public:
    void setUp(void);
    void tearDown(void);
protected:
	void testPushBack();
	void testClear();
	void testRemoveIndex();
	void testRemoveNodeWithData();
	void testInsert();
	void testPopBack();
	void testIndex();
	void testCopyConstructor();
	void testAssignment();
	void testEquality();
private:
	LinkedList<int> numberList;
	LinkedList<int> numberListTwo;
};

#endif /* TESTLINKEDLIST_H_ */

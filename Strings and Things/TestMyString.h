/*
 * TestMyString.h
 */

#ifndef TESTMYSTRING_H_
#define TESTMYSTRING_H_
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "MyString.h"

class TestMyString: public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE(TestMyString);
	// TODO Repeat one of the following lines for each of your test methods
    CPPUNIT_TEST(testMyStringConstructor);
    CPPUNIT_TEST(testCharConstructor);
    CPPUNIT_TEST(testStringConstructor);
    CPPUNIT_TEST(testConcatenate);
    CPPUNIT_TEST(testStreamInsertion);
    CPPUNIT_TEST_SUITE_END ();
public:
    void setUp(void);
    void tearDown(void);
protected:
	// TODO Define your test methods here
    void testMyStringConstructor();
    void testCharConstructor();
    void testStringConstructor();
    void testConcatenate();
    void testStreamInsertion();
private:
	// TODO Define any instance variables your tests will use here
};

#endif /* TESTMYSTRING_H_ */

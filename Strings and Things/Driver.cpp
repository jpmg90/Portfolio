/*
 * Driver.cpp
 */

#include "MyString.h"
#include <cppunit/ui/text/TestRunner.h>
#include "StandardIncludes.h"
#include "TestMyString.h"

bool doAllTestsFunction()
{
    CppUnit::TextUi::TestRunner runner;
    runner.addTest(TestMyString::suite());
    return runner.run();
}

int main()
{
    if (doAllTestsFunction())
    {
    	// runApplication();
    }
    return 0;
}

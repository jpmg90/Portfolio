#include "LinkedList.h"
#include "StandardIncludes.h"
#include <cppunit/ui/text/TestRunner.h>
#include "TestLinkedList.h"

bool doAllTestsFunction()
{
	CppUnit::TextUi::TestRunner runner;
	runner.addTest(TestLinkedList::suite());
	return runner.run();
}
int main()
{
	cout << "Running All Tests!" << endl;
	if(doAllTestsFunction())
	{
		//runApplicaiton();
	}
	return 0;
}


/*
 * Driver.cpp
 * Lab 5 Parallel, Main Process divides Data to each thread
 *  Created on: Jul 14, 2011
 *      Author: John Grabanski
 */

#include <Windows.h>
#include <iostream>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <algorithm>

using std::vector;
using std::cout;
using std::cin;
using std::endl;
using std::sort;

//constants
const int MAX_THREADS = 4;

//Prototypes
void askForSize();
void convertToCorispondingValues();
vector<int> generateRandomNumbers();
void runTest(unsigned int threadCount, vector<int> randomDataSet);
void splitDataIntoBuckets(int threadCount, vector<int>* bucketPointers[],
		vector<int> randomDataSet);
DWORD WINAPI workerThread(LPVOID lpParam);
vector<int> assembleSortedDataSet(vector<int>* bucketPointers[],
		int threadCount);
bool verifySort(vector<int> sortedDataSet);

//Variables
int sizeOfN;
vector<int>* bucketPointers[MAX_THREADS];

int main()
{
	//get user input
	askForSize();

	while (sizeOfN != -1)
	{
		convertToCorispondingValues();
		if (sizeOfN != 0)
		{
			//generate random numbers and put them into dataSet.
			vector<int> randomDataSet = generateRandomNumbers();

			//run tests with 1 to MAX_THREADS number of threads
			for (int index = 1; index <= MAX_THREADS; index++)
			{
				cout << "Running with: " << index << " Thread(s)." << endl;

				runTest(index, randomDataSet);
			}
		}
		//get user input
		askForSize();
	}
	cout << "END OF PROGRAM!" << endl;

	return 0;
}

//functions!
void askForSize()
{
	sizeOfN = 0; //1024, 4096, 65536, and 16777216
	//Ask for file size
	cout << "What size of N would you like?" << endl;
	cout << "Enter 1 for: 1024" << endl;
	cout << "Enter 2 for: 4096" << endl;
	cout << "Enter 3 for: 65536" << endl;
	cout << "Enter 4 for: 16777216" << endl;
	cout << "Enter '-1' to quit" << endl;
	cin >> sizeOfN;
	cout << "_________________________________________________" << endl << endl;
	convertToCorispondingValues();
}

void convertToCorispondingValues()
{
	//change sizeOfN to correct size
	if (sizeOfN == 1 || sizeOfN == 1024)
		sizeOfN = 1024;
	else if (sizeOfN == 2 || sizeOfN == 4096)
		sizeOfN = 4096;
	else if (sizeOfN == 3 || sizeOfN == 65536)
		sizeOfN = 65536;
	else if (sizeOfN == 4 || sizeOfN == 16777216)
		sizeOfN = 16777216;
	else
	{
		cout << "You did not enter a Valid number!\n";
		sizeOfN = 0;
	}
}

vector<int> generateRandomNumbers()
{
	//generate numbers
	cout << "**Generating Random Numbers between 0 and ";
	cout << sizeOfN << "**" << endl;
	srand(time(NULL));
	vector<int> dataSet(sizeOfN);
	for (int index = 0; index < sizeOfN; index++)
	{
		unsigned int randomNumber;
		randomNumber = ((rand() << 15) + rand()) % sizeOfN;
		dataSet[index] = randomNumber;
	}
	return dataSet;
}

void runTest(unsigned int threadCount, vector<int> randomDataSet)
{
	HANDLE threadHandles[threadCount];
	DWORD threadID[threadCount];
	splitDataIntoBuckets(threadCount, bucketPointers, randomDataSet);
	//start parallel code
	clock_t startTime, endTime;
	startTime = clock();
	//create thread loop
	for (unsigned int index = 0; index < threadCount; index++)
	{
		//create threads
		cout << "Creating Thread: " << index;
		cout << " Thread ID = " << threadID[index] << endl;
		threadHandles[index] = CreateThread(NULL, 0, workerThread,
				bucketPointers[index], 0, &threadID[index]);
		if (threadHandles[index] == NULL)
		{
			cout << "CreatedThread #" << index << " Borked.\n";
			ExitProcess(3);
		}
	}

	//wait until all threads have terminated
	WaitForMultipleObjects(threadCount, threadHandles, TRUE, INFINITE);

	vector<int> sortedData = assembleSortedDataSet(bucketPointers, threadCount);

	//close threads
	for (int index = 0; index < MAX_THREADS; index++)
	{
		CloseHandle(threadHandles[index]);
	}
	//stop the clock
	endTime = clock() - startTime;
	double time = (double) endTime / ((double) CLOCKS_PER_SEC);

	//Check and see if Data is sorted
	if (verifySort(sortedData) == true)
		cout << "Data is sorted properly!" << endl;
	else
		cout << "Data is NOT sorted properly. :(" << endl;

	//Display threadCount and completion time
	cout << "Tested with: " << threadCount << " number of thread(s)." << endl;
	cout << "Test completed in: " << time << " seconds!" << endl;
	cout << "_________________________________________________" << endl << endl;
}

void splitDataIntoBuckets(int threadCount, vector<int>* bucketPointers[],
		vector<int> randomDataSet)
{
	cout << "Splitting Data...." << endl;
	//determine the ranges of each bucket
	int bucketSize = (sizeOfN / threadCount);
	int bucketIndex;
	//create a vector inside of dataSetPoints for each thread
	for (int index = 0; index < threadCount; index++)
	{
		bucketPointers[index] = new vector<int> ();
		cout << "Thread [" << index << "] will recieve numbers raning from ";
		cout << bucketSize * index << " to " << bucketSize * (index + 1)
				<< endl;
	}

	//give each bucket their data
	for (unsigned int index = 0; index < randomDataSet.size(); ++index)
	{
		int data = randomDataSet[index];
		bucketIndex = data / bucketSize;
		if (bucketIndex < threadCount)
			bucketPointers[bucketIndex]->push_back(data);
		else
			bucketPointers[bucketIndex - 1]->push_back(data);
	}
}

DWORD WINAPI workerThread(LPVOID lpParam)
{
	//create holders for data
	vector<int>* bucketData = (vector<int>*) (lpParam);

	//sort data
	sort(bucketData->begin(), bucketData->end());

	return 0;
}

vector<int> assembleSortedDataSet(vector<int>* bucketPointers[],
		int threadCount)
{
	vector<int> sortedData(sizeOfN);
	int masterIndex = 0;
	for (int bucketIndex = 0; bucketIndex < threadCount; ++bucketIndex)
	{
		for (unsigned int index = 0; index
				< bucketPointers[bucketIndex]->size(); ++index)
		{
			sortedData[masterIndex] = bucketPointers[bucketIndex]->at(index);
			masterIndex++;
		}
	}
	return sortedData;
}

bool verifySort(vector<int> sortedData)
{
	for (unsigned int index = 1; index < sortedData.size(); ++index)
	{
		if (sortedData[index] < sortedData[index - 1])
			return false;
	}
	return true;
}

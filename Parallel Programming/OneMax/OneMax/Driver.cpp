/*
 * Driver.cpp
 *
 *  Created on: Aug 13, 2011
 *      Author: John Grabanski
 *      Sequential Implementation
 *      Thead Implementatatoin uses threadMethods
 */

#include <Windows.h>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <vector>

using std::ifstream;
using std::vector;
using std::string;
using std::cout;
using std::cin;
using std::endl;

//Constants
const unsigned int MAX_POPULATION = 100000; // 100 Thousand
const int SIZE_OF_GENE_SEQUENCE = 100;//subject to change.
const int MAX_GENERATIONS = 5;
//Thread Constant
const int MAX_THREADS = 2;

//Prototypes
void initializeGeneration();
void displayGeneticSequence();
void displaySelectedList();
void checkFitness();
void selectMostFit();
void produceNextGeneration();

//class
class individual
{
private:
	int fitnessLevel;
public:
	int geneticSequence[SIZE_OF_GENE_SEQUENCE];
	int getFitness() const
	{
		return fitnessLevel;
	}
	void setFitness(int fitness)
	{
		fitnessLevel = fitness;
	}
	inline bool operator<(const individual& individualB) const
	{
		return getFitness() < individualB.getFitness();
	}

};

//ThreadFunctions
void runTest(unsigned int threadCount);
DWORD WINAPI workerThread(LPVOID lpParam);
void threadCheckFitness(vector<individual>* threadGeneration);
vector<individual>* threadSelectMostFit(vector<individual>* threadGeneration,
		int threadCount);
vector<individual>* threadProduceNextGeneration(vector<individual> allSelected,
		int threadCount, int threadID);

//variables
vector<individual> generation;
vector<individual> selectedIndividuals;
//ThreadVariables
vector<individual>* threadSelectedIndividuals[MAX_THREADS];
vector<individual>* threadGeneration[MAX_THREADS];
HANDLE mutex;
int mutexCounter = 0;
int numThreads;

int main()
{

	mutex = CreateMutex(NULL, FALSE, NULL);

	//initialize generation
	initializeGeneration();

	//run tests with 1 to MAX_THREADS number of threads
	for (int index = 1; index <= MAX_THREADS; ++index)
	{
		cout << "Running with: " << index << " Thread(s)," << endl;
		//run program
		runTest(index);
	}

	//Display Maximum index
	//Finds the maximum element Index in fitness Ranks (the most fit)
	cout << "Checking Last Generation..." << endl;
	checkFitness();
	sort(generation.begin(), generation.end());
	cout << "The most fit individual's gene sequence: ";
	for (int index = 0; index < SIZE_OF_GENE_SEQUENCE; index++)
	{
		cout << generation.back().geneticSequence[index] << ", ";
	}
	cout << "\n Most fit Individual's Fitness Level:";
	cout << generation.back().getFitness() << endl;

	cout << "The least fit individual's gene sequence: ";
	for (int index = 0; index < SIZE_OF_GENE_SEQUENCE; index++)
	{
		cout << generation.front().geneticSequence[index] << ", ";
	}
	cout << "\n least fit Individual's Fitness Level:";
	cout << generation.front().getFitness() << endl;

	cout << "END OF PROGRAM!" << endl;
	return 0;
}

void initializeGeneration()
{
	cout << "Initializing Generation...." << endl;
	individual thisIndividual;
	srand(time(NULL));
	for (unsigned int popIndex = 0; popIndex < MAX_POPULATION; popIndex++)
	{
		for (int index = 0; index < SIZE_OF_GENE_SEQUENCE; index++)
		{
			thisIndividual.geneticSequence[index] = rand() % 2; //random number between 0 and 1
		}
		generation.push_back(thisIndividual);
	}
	cout << "Initialization Complete!" << endl;
}

void runTest(unsigned int threadCount)
{
	numThreads = threadCount;
	HANDLE threadHandles[threadCount];
	DWORD threadID[threadCount];
	//start parallel code
	clock_t startTime, endTime;
	startTime = clock();

	for (unsigned int index = 0; index < threadCount; ++index)
	{
		//create threads
		cout << "Creating Thread: " << index << endl;
		threadID[index] = index;

		threadHandles[index] = CreateThread(NULL, 0, workerThread, &generation,
				0, &threadID[index]);
		if (threadHandles[index] == NULL)
		{
			cout << "CreatedThread #" << index << " Broken.\n";
			ExitProcess(3);
		}
	}
	WaitForMultipleObjects(threadCount, threadHandles, TRUE, INFINITE);

	//close threads
	for (int index = 0; index < MAX_THREADS; index++)
	{
		CloseHandle(threadHandles[index]);
	}
	//stop the clock
	endTime = clock() - startTime;
	double time = (double) endTime / ((double) CLOCKS_PER_SEC);

	//Display threadCount and completion time
	//cout << "Tested with: " << threadCount << " number of thread(s)." << endl;
	cout << "Test completed in: " << time << " seconds!" << endl;
	cout << "___________________________________________" << endl << endl;

}

DWORD WINAPI workerThread(LPVOID lpParam)
{
	int threadID;
	int threadCount = numThreads;
	vector<individual>* thisGeneration = (vector<individual>*) (lpParam);

	WaitForSingleObject(mutex, INFINITE);
	threadID = mutexCounter;
	mutexCounter++;
	ReleaseMutex(mutex);
	threadSelectedIndividuals[threadID] = new vector<individual> ();
	//split generation into threadCount parts
	threadGeneration[threadID] = new vector<individual> ();
	int generationRange = (MAX_POPULATION / threadCount);
	unsigned int starting = threadID * generationRange;
	unsigned int stopping = (threadID + 1) * generationRange;
	for (unsigned int index = starting; index < stopping; index++)
	{
		individual individual = thisGeneration->at(index);
		threadGeneration[threadID]->push_back(individual);
	}

	//start loop
	for (int index = 0; index < MAX_GENERATIONS; index++)
	{
		//display Generation
		cout << "Generation #" << index << " Beginning on thread:";
		cout << threadID << endl;

		//clear Selected
		threadSelectedIndividuals[threadID]->clear();

		//fitness function
		threadCheckFitness(threadGeneration[threadID]);

		// this selection should only produce (1/threadCount)*.01 (a piece of 1%)
		//selection!
		threadSelectedIndividuals[threadID] = threadSelectMostFit(
				threadGeneration[threadID], threadCount);

		//clear generation
		threadGeneration[threadID]->clear();

		//TODO: Barrier

		vector<individual> allSelectedIndividuals;
		for (int threadIndex = 0; threadIndex < threadCount; threadIndex++)
		{
			for (unsigned int index = 0; index
					< threadSelectedIndividuals[threadIndex]->size(); ++index)
			{
				allSelectedIndividuals.push_back(
						threadSelectedIndividuals[threadIndex]->at(index));
			}
		}

		//Crossover/Breeding, also fills next generation
		threadGeneration[threadID] = threadProduceNextGeneration(
				allSelectedIndividuals, threadCount, threadID);

		//TODO: SEND GENERATION TO ALL THEREADS
		//end generation
		cout << "Next Thread Generation's Size "
				<< threadGeneration[threadID]->size() << endl;
		cout << "End Of " << index << " Generation." << endl;
		cout << "___________________________________________\n";
		//end loop
	}

	return 0;
}

void threadCheckFitness(vector<individual>* threadGeneration)
{
	cout << "Running Fitness Function...." << endl;
	int oneCount;
	for (unsigned int popIndex = 0; popIndex < threadGeneration->size(); ++popIndex)
	{
		oneCount = 0;
		for (int index = 0; index < SIZE_OF_GENE_SEQUENCE; ++index)
		{
			if (threadGeneration->at(popIndex).geneticSequence[index] == 1)
			{
				oneCount++;
			}
		}
		threadGeneration->at(popIndex).setFitness(oneCount);
	}
	cout << "Fitness Function Complete!" << endl;
}

vector<individual>* threadSelectMostFit(vector<individual>* threadGeneration,
		int threadCount)
{
	vector<individual>* selected = new vector<individual> ();
	cout << "Begin Selection...." << endl;
	unsigned int numberOfSelected = .001 * (MAX_POPULATION / threadCount); // 1% of total pop will be able to breed
	sort(threadGeneration->begin(), threadGeneration->end());
	for (unsigned int index = 0; index < numberOfSelected; index++)
	{
		selected->push_back(threadGeneration->back());
		threadGeneration->pop_back();
	}
	cout << "Selection Complete!" << endl;
	return selected;
}
vector<individual>* threadProduceNextGeneration(vector<individual> allSelected,
		int threadCount, int theradID)
{
	cout << "Producing Next Generation..." << endl;
	vector<individual>* nextGeneration = new vector<individual> ();
	int crossoverIndex = 0;
	individual child;
	individual childTwo;
	srand(time(NULL));
	//TODO limit generation based on threadID
	while (nextGeneration->size() < (MAX_POPULATION / threadCount))
	{
		for (unsigned int father = 0; father < allSelected.size(); ++father)
		{
			for (unsigned int mother = 0; mother < allSelected.size(); ++mother)
			{
				crossoverIndex = rand() % SIZE_OF_GENE_SEQUENCE;
				for (int index = 0; index < SIZE_OF_GENE_SEQUENCE; index++)
				{
					if (index < crossoverIndex)
					{
						child.geneticSequence[index]
								= allSelected.at(father).geneticSequence[index];
						childTwo.geneticSequence[index]
								= allSelected.at(mother).geneticSequence[index];
					}
					else
					{
						child.geneticSequence[index]
								= allSelected.at(mother).geneticSequence[index];
						childTwo.geneticSequence[index]
								= allSelected.at(father).geneticSequence[index];
					}
					//random chance to mutate child
					if (rand() % SIZE_OF_GENE_SEQUENCE == 1)
					{
						if (child.geneticSequence[index] == 0)
							child.geneticSequence[index] = 1;
						else
							child.geneticSequence[index] = 0;
					}
					//random chance to mutate childTwo
					if (rand() % SIZE_OF_GENE_SEQUENCE == 1)
					{
						if (childTwo.geneticSequence[index] == 0)
							childTwo.geneticSequence[index] = 1;
						else
							childTwo.geneticSequence[index] = 0;
					}

				}
				if (nextGeneration->size() < (MAX_POPULATION / threadCount))
				{
					nextGeneration->push_back(child);
					nextGeneration->push_back(childTwo);
				}
				else
				{
					cout << "Production of Next Generation Complete!" << endl;
					return nextGeneration;
				}
			}
		}
	}
	cout << "Production of Next Generation Complete!" << endl;
	return nextGeneration;
}

/* PARALLEL METHODS ABOVE THIS POINT (includes main and Initialization method)
 *
 * ================================
 *
 * SEQUENTIAL METHODS UNDER THIS POINT
 */
void checkFitness()
{
	cout << "Running Fitness Function...." << endl;
	int oneCount;
	for (unsigned int popIndex = 0; popIndex < MAX_POPULATION; ++popIndex)
	{
		oneCount = 0;
		for (int index = 0; index < SIZE_OF_GENE_SEQUENCE; ++index)
		{
			if (generation.at(popIndex).geneticSequence[index] == 1)
			{
				oneCount++;
			}
		}
		generation.at(popIndex).setFitness(oneCount);
	}
	cout << "Fitness Function Complete!" << endl;
}
void selectMostFit()
{
	cout << "Begin Selection...." << endl;
	unsigned int numberOfSelected = .001 * MAX_POPULATION; // 1% of total pop will be able to breed
	sort(generation.begin(), generation.end());
	for (unsigned int index = 0; index < numberOfSelected; index++)
	{
		selectedIndividuals.push_back(generation.back());
		generation.pop_back();
	}
	cout << "Selection Complete!" << endl;
}

void produceNextGeneration()
{
	cout << "Producing Next Generation..." << endl;
	int crossoverIndex = 0;
	individual child;
	individual childTwo;
	srand(time(NULL));
	while (generation.size() < MAX_POPULATION)
	{
		for (unsigned int father = 0; father < selectedIndividuals.size(); ++father)
		{
			for (unsigned int mother = 0; mother < selectedIndividuals.size(); ++mother)
			{
				crossoverIndex = rand() % SIZE_OF_GENE_SEQUENCE;
				for (int index = 0; index < SIZE_OF_GENE_SEQUENCE; index++)
				{
					if (index < crossoverIndex)
					{
						child.geneticSequence[index]
								= selectedIndividuals[father].geneticSequence[index];
						childTwo.geneticSequence[index]
								= selectedIndividuals[mother].geneticSequence[index];
					}
					else
					{
						child.geneticSequence[index]
								= selectedIndividuals[mother].geneticSequence[index];
						childTwo.geneticSequence[index]
								= selectedIndividuals[father].geneticSequence[index];
					}
					//random chance to mutate child
					if (rand() % SIZE_OF_GENE_SEQUENCE == 1)
					{
						if (child.geneticSequence[index] == 0)
							child.geneticSequence[index] = 1;
						else
							child.geneticSequence[index] = 0;
					}
					//random chance to mutate childTwo
					if (rand() % SIZE_OF_GENE_SEQUENCE == 1)
					{
						if (childTwo.geneticSequence[index] == 0)
							childTwo.geneticSequence[index] = 1;
						else
							childTwo.geneticSequence[index] = 0;
					}
				}
				if (generation.size() < MAX_POPULATION)
				{
					generation.push_back(child);
					generation.push_back(childTwo);
				}
				else
				{
					cout << "Production of Next Generation Complete!" << endl;
					return;
				}
			}
		}
	}
	cout << "Production of Next Generation Complete!" << endl;
}

void displayGeneticSequence()
{
	cout << "\nHow many Individuals would you like to display?" << endl;
	int number;
	cin >> number;
	cout << "Displaying Genetic Sequences...." << endl;
	//test display 1st 10 people and their genetic sequence
	for (int popIndex = 0; popIndex < number; popIndex++)
	{
		cout << "\nIndividual #: " << popIndex << endl;
		for (int index = 0; index < SIZE_OF_GENE_SEQUENCE; index++)
		{
			cout << generation.at(popIndex).geneticSequence[index] << ", ";
		}
		cout << "\n--Rank: " << generation[popIndex].getFitness() << endl;
	}
	cout << "Display Complete!" << endl;

}

void displaySelectedList()
{
	cout << "Displaying Selected Individuals..." << endl;
	for (unsigned int popIndex = 0; popIndex < selectedIndividuals.size(); popIndex++)
	{
		cout << "\nIndividual #: " << popIndex << endl;
		for (int index = 0; index < SIZE_OF_GENE_SEQUENCE; index++)
		{
			cout << selectedIndividuals.at(popIndex).geneticSequence[index]
					<< ", ";
		}
	}
	cout << "Display Complete!" << endl;

}

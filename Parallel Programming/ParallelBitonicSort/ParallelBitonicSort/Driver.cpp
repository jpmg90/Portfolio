// Parallel Bitonic Sort
// John Grabanski
// Use -> log(n.0)/log(2.0) -For log2(n.0)

// Include Statements
#include <mpi.h>
#include <stdio.h>
#include <iostream>
#include <cmath>
#include <time.h>
#include <vector>
#include <algorithm>

// std using statements
using std::cout;
using std::cin;
using std::endl;
using std::vector;

// Prototypes
vector<int>* GenerateRandomNumbers(int sizeOfN);
bool isBitSet(int number, int bitIndex);
int FlipBit(int number, int bitIndex);
vector<int>* CompareLow(int myid, int index, vector<int>* localData);
vector<int>* CompareHigh(int myid, int index, vector<int>* localData);

int main(int argc, char* argv[])
{
	cout << "Hello Bitonic Sort World\n";

	// Variables
	int myid;
	int numberOfProcesses;
	char name[256];
	int resultLenght;
	int sizeOfN;
	vector<int>* randomDataSet;
	int* randomDataArray;
	vector<int>* localData;
	int* localDataArray;


	// MPI Initialization
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numberOfProcesses);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);

	// Root Processes
	if(myid == 0)
	{
		cout << "Bitonic Sort running on " << numberOfProcesses << " processes" << endl;

		// Get size of N
		cout << "Please input Desired size of dataset." << endl;
		cout << "Enter 16 for 16 Million." << endl;
		cout << "Enter 32 for 32 Million." << endl;		
		cout << "Enter 64 for 64 Million." << endl;
		cout << "Enter 128 for 128 Million." << endl;
		cin >> sizeOfN;

		// TODO: check input for invalid numbers 

		randomDataSet = GenerateRandomNumbers(sizeOfN);
		
		// Copying data into the array.
		randomDataArray = new int [sizeOfN];
		for(int index = 0; index < randomDataSet->size(); index++)
		{
			randomDataArray[index] = randomDataSet->at(index);
		}
	}
	// Scatter data to all processes
	MPI_Scatter((void *)randomDataArray, (sizeOfN/numberOfProcesses), MPI_INT, (void *)localDataArray, (sizeOfN/numberOfProcesses), MPI_INT, 0,  MPI_COMM_WORLD);
	
	// Collect Garbage
	delete [] randomDataArray;

	// Wait for Root Process to finish Scattering data
	MPI_Barrier(MPI_COMM_WORLD);

	// Copying data into the vector.
	for(int index = 0; index < (sizeOfN/numberOfProcesses); index++)
	{
		localData->push_back(localDataArray[index]);
	}

	// Start timer
	clock_t startTime, endTime;
	startTime = clock();
	
	cout << "From process " << myid << "/" << numberOfProcesses << endl;
	cout << "Bitionic Sort beginning itterations from processes " << name << endl;

	// Calculate Max number of itterations
	int maxItterations = log((double)numberOfProcesses);

	// sort the local Data
	sort(localData->begin(), localData->end());

	// Start Itterations
	for(int itterationIndex = 1; itterationIndex < maxItterations; itterationIndex++)
	{
		int windowID = (myid >> itterationIndex);

		for(int index = itterationIndex-1; index >= 0; index--)
		{
			if(windowID%2 == 0 && isBitSet(myid, index) == false || 
				windowID%2 != 0 && isBitSet(myid, index) == true)
			{
				localData = CompareLow(myid, index, localData); 
			}
			else
			{
				localData = CompareHigh(myid, index, localData);
			}
		}
	}
	// Stop the clock
	endTime = clock() - startTime;
	double time = (double) endTime / ((double) CLOCKS_PER_SEC);

	// Finish MPI calls
	MPI_Finalize();

	return 0;
}

// FUNCTIONS
vector<int>* GenerateRandomNumbers(int sizeOfN)
{
	// Variables
	vector<int>* randomData = new vector<int>();
	int randomNumber;

	// Random number seed
	srand(time(NULL));

	// Generate sizeOfN
	while(randomData->size() <= sizeOfN)
	{
		randomNumber = rand() % 1000000;
		randomData->push_back(randomNumber);
	}

	return randomData;
}

bool isBitSet(int number, int bitIndex)
{
	int mask = pow(2.0, bitIndex); // TODO: make sure pow works

	return (number&mask);
}

int FlipBit(int number, int bitIndex)
{
	int mask = pow(2.0, bitIndex); // TODO: again make sure pow works 

	if(isBitSet(number, bitIndex))
		return (number - mask);
	else
		return (number + mask);
}

vector<int>* CompareLow(int myid, int index, vector<int>* localData)
{
	vector<int>* sortedData = new vector<int>;
	int * remoteDataArray;

	int * localDataArray = new int [localData->size()];
	for(int index = 0; index < localData->size(); index++)
	{
		localDataArray[index] = localData->at(index);
	}

	int communicateWith = FlipBit(myid, index);

	MPI_Status status;
	MPI_Recv((void*)remoteDataArray, localData->size(), MPI_INT, communicateWith, 0, MPI_COMM_WORLD, &status); // TODO: use MPI_Recv syntax and be sure if i need 'remoteData ='
	MPI_Send((void*)localDataArray, localData->size(), MPI_INT, communicateWith, 0, MPI_COMM_WORLD); // TODO: use MPI_Send syntax 
	
	//TODO: Put data into 1 vector, sort and then take bottom half
	for(int index = 0; index < (localData->size()*2); index++)
	{
		sortedData->push_back(localDataArray[index]);
		sortedData->push_back(remoteDataArray[index]);
	}
	// sort Data
	sort(sortedData->begin(), sortedData->end());

	// take top half
	for( int index = 0; index < (sortedData->size()/2); index++)
	{
		localData->at(index) = sortedData->at(+index);
	}

	return localData;
}

vector<int>* CompareHigh(int myid, int index, vector<int>* localData)
{
	vector<int>* sortedData = new vector<int>;
	int * remoteDataArray;

	int * localDataArray = new int [localData->size()];
	for(int index = 0; index < localData->size(); index++)
	{
		localDataArray[index] = localData->at(index);
	}

	int communicateWith = FlipBit(myid, index);
	MPI_Status status;
	MPI_Send((void*)localDataArray, localData->size(), MPI_INT, communicateWith, 0, MPI_COMM_WORLD); // TODO: use MPI_Send syntax 
	MPI_Recv((void*)remoteDataArray, localData->size(), MPI_INT, communicateWith, 0, MPI_COMM_WORLD, &status); // TODO: use MPI_Recv syntax and be sure if i need 'remoteData ='
	
	for(int index = 0; index < (localData->size()*2); index++)
	{
		sortedData->push_back(localDataArray[index]);
		sortedData->push_back(remoteDataArray[index]);
	}
	// sort Data
	sort(sortedData->begin(), sortedData->end());

	// take top half
	for( int index = 0; index < (sortedData->size()/2); index++)
	{
		localData->at(index) = sortedData->at((sortedData->size()/2)+index);
	}

	return localData;
}
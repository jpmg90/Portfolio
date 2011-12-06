#pragma once
#include <cmath>
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

class BitonicSorter
{
public:
	BitonicSorter(void);
	~BitonicSorter(void);
private: 
	vector<int> initialData;
	vector<int> localData;
	vector<int> remoteData;

};


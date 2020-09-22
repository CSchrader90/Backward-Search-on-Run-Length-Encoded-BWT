#ifndef INDEX_IO
#define INDEX_IO

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
class indexes {
public:
	void VectorToFile(vector<unsigned long int> index_entry, fstream& out_file);
	vector<unsigned long int> FileToVector(fstream& in_file, unsigned long int offset);
	bool find_or_create_file(string filename);
};

#endif
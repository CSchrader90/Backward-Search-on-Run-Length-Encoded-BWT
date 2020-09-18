#include <fstream>
#include <vector>

using namespace std;
#define ALPHABET_SIZE 256


class indexes {
public:
	void VectorToFile(vector<unsigned long int> index_entry, fstream& out_file);
	vector<unsigned long int> FileToVector(fstream& in_file, unsigned long int offset);
};

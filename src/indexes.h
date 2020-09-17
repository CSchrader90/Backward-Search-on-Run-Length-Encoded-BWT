#include <fstream>
#include <vector>

using namespace std;
#define ALPHABET_SIZE 256


class indexes {
public:
	void ArrayToFile(vector<unsigned long int> index_entry, fstream& out_file);
	vector<unsigned long int> FileToArray(fstream& in_file, unsigned long int offset);
};

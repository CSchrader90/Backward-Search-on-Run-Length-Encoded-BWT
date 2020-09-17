#include <vector>
#include <fstream>
#include "indexes.h"


void indexes::ArrayToFile(vector<unsigned long int> index_entry, fstream& out_file){

	for (auto val : index_entry) {
        out_file.write(reinterpret_cast<const char *>(&val), sizeof(unsigned long int));
    }

}

vector<unsigned long int> indexes::FileToArray(fstream& in_file, unsigned long int offset){

	unsigned long int in;
	in_file.seekg(offset, in_file.beg);
	vector<unsigned long int> datavec;

   	for(int i = 0; i < ALPHABET_SIZE; i++){
        in_file.read(reinterpret_cast<char *>(&in), sizeof(unsigned long int));
        datavec.push_back(in);
    }

    return datavec;
}
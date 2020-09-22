#include <vector>
#include <fstream>
#include "indexes.h"
#include "constants.h"

void indexes::VectorToFile(vector<unsigned long int> index_entry, fstream& out_file){

	for (auto val : index_entry) {
        out_file.write(reinterpret_cast<const char *>(&val), sizeof(unsigned long int));
    }

}

vector<unsigned long int> indexes::FileToVector(fstream& in_file, unsigned long int offset){

	unsigned long int in;
	in_file.seekg(offset, in_file.beg);
	vector<unsigned long int> datavec;

   	for(int i = 0; i < ALPHABET_SIZE; i++){
        in_file.read(reinterpret_cast<char *>(&in), sizeof(unsigned long int));
        datavec.push_back(in);
    }

    return datavec;
}

//return true if file was found 
bool indexes::find_or_create_file(string filename){

    fstream FILE;
    FILE.open(filename);

    if(FILE){
        cout << "Found file: " << filename << "\n";
        FILE.close();
        return true;
    } else {
        fstream FILE(filename, fstream::out | fstream::in | fstream::trunc);
        FILE.close();
        cout << "File created: " << filename << "\n";
        return false;   
    }
}
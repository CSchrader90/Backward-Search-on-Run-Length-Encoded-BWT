#include <fstream>
#include <iostream>
#include "s.h"

fstream count_file;
fstream rank_file;
string index_dir;

s::s(string filename){

	string rank_file_name = index_dir + filename + ".rank";
	string count_file_name = index_dir + filename + ".count";

	if(!find_or_create_file(rank_file_name)){
		create_rank_file(FILE_DIR + filename + ".s", rank_file_name);
	}
	if(!find_or_create_file(count_file_name)){
		create_count_file(FILE_DIR + filename + ".s", count_file_name);
	}
	
}

unsigned int s::count(char c, unsigned int index){

	unsigned int total;

	return total;
}

unsigned int s::rank(char c, unsigned int index) {

}


//return true if file was found 
bool s::find_or_create_file(string filename){

	ifstream FILE;
	FILE.open(filename);

	if(FILE){
		cout << filename << " found" << "\n";
		return true;
	} else {
		ofstream FILE { filename };
		FILE.close();
		cout << "file created: " << filename << "\n";
		return false;	
	}
}

void s::create_rank_file(string s_file_name, string rank_file_name){

}

void s::create_count_file(string s_file_name, string count_file_name){
	unsigned int count[ALPHABET_SIZE] = { 0 };
	ifstream IN_FILE;
	IN_FILE.open(s_file_name, ios::in);
	count_file.open(count_file_name, ios::out);

	char in_char;

	while(IN_FILE.get(in_char)){
		count[in_char]++;
		cout << in_char << endl;
	}
	IN_FILE.close();

	unsigned int cum_tot = 0; //cumulative total
	unsigned int temp;
	for(int i = 0; i < ALPHABET_SIZE; i ++) {
		if(count[i] > 0 ){
			temp = count[i];
			count[i] = cum_tot;
			cum_tot += temp;
		} else {
			count[i] = cum_tot;
		}
		count_file << count[i] << ",";
	}
}

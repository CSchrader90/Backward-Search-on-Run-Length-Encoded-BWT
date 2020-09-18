#include <fstream>
#include <iostream>
#include "s.h"

fstream s_file;
fstream count_file;
fstream rank_file;
string index_dir;
vector<unsigned long int>count_vector;

s::s(string filename){

	string rank_file_name = index_dir + filename + ".rank";
	string count_file_name = index_dir + filename + ".count";
	string s_file_name = FILE_DIR + filename + ".s";

	s_file.open(s_file_name, fstream::in);

	if(!find_or_create_file(rank_file_name)){
		fill_rank_file(s_file, rank_file_name);
	}
	if(!find_or_create_file(count_file_name)){
		fill_count_file(s_file, count_file_name);
	}

	count_file.open(count_file_name, fstream::in);
	count_vector = FileToVector(count_file, 0);

	rank_file.open(rank_file_name, fstream::in);


}

unsigned long int s::count(char c){
	return count_vector[c];
}

unsigned long int s::rank(char c, unsigned int index) {

	unsigned long int index_offset = index/RANK_SAVE_INTERVAL;
	vector<unsigned long int> index_vec;
	index_vec = FileToVector(rank_file, index_offset*ALPHABET_SIZE*sizeof(unsigned long int));
	unsigned long int total = index_vec[c];
 
	unsigned long int cur_read = index - index%RANK_SAVE_INTERVAL + 1; 
	char in_char;
	s_file.clear();
	s_file.seekg(cur_read);

	while(cur_read <= index){

		s_file.get(in_char);

		if(in_char == c){
			total++;
		}
		cur_read++;
	}

	return total;
}


//return true if file was found 
bool s::find_or_create_file(string filename){

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

void s::fill_rank_file(fstream& s_file, string rank_file_name){

	rank_file.open(rank_file_name, fstream::out | fstream::in | fstream::app);
	
	vector<unsigned long int> cur_rank(ALPHABET_SIZE, 0);
	s_file.clear();
	s_file.seekg(0);
	char cur_char;
	unsigned long int cur_idx;
	while(s_file.get(cur_char)){
		cur_rank[cur_char]++;
		if(cur_idx%RANK_SAVE_INTERVAL == 0){
			VectorToFile(cur_rank, rank_file);
		}
		cur_idx++;
	}
	rank_file.close();
}

void s::fill_count_file(fstream& s_file, string count_file_name){

	count_file.open(count_file_name, fstream::out | fstream::in);

	char in_char;
	vector<unsigned long int> count_vector(ALPHABET_SIZE, 0);

	s_file.clear();
	s_file.seekg(0);
	while(s_file.get(in_char)){
		count_vector[in_char]++;
	}

	unsigned int cum_tot = 0; //cumulative total
	unsigned int temp;
	for(int i = 0; i < ALPHABET_SIZE; i ++) {
		if(count_vector[i] > 0 ){
			temp = count_vector[i];
			count_vector[i] = cum_tot;
			cum_tot += temp;
		} else {
			count_vector[i] = cum_tot;
		}
	}

	VectorToFile(count_vector, count_file);
	count_file.close();
}
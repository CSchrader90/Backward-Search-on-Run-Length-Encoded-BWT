#include <fstream>
#include <iostream>
#include "s.h"
#include "constants.h"

s::s(string filename){

	string s_rank_file_name = INDEX_DIR + filename + "_s" ".rank";
	string s_count_file_name = INDEX_DIR + filename + ".count";
	string s_file_name = FILE_DIR + filename + ".s";

	s_file.open(s_file_name, fstream::in);

	if(!find_or_create_file(s_rank_file_name))
		fill_s_rank_file(s_file, s_rank_file_name);
	
	if(!find_or_create_file(s_count_file_name))
		fill_s_count_file(s_file, s_count_file_name);
	

	s_count_file.open(s_count_file_name, fstream::in);
	count_vector = FileToVector(s_count_file, 0);

	s_rank_file.open(s_rank_file_name, fstream::in);

}
		
s::~s(){
	s_count_file.close();
	s_rank_file.close();
	s_file.close();
}

unsigned long int s::count(char c){
	return count_vector[c];
}

unsigned long int s::rank(char c, unsigned int index) {

	unsigned long int index_offset = index/S_RANK_SAVE_INTERVAL;
	vector<unsigned long int> index_vec;
	index_vec = FileToVector(s_rank_file, index_offset*ALPHABET_SIZE*sizeof(unsigned long int));
	unsigned long int total = index_vec[c];
 
	unsigned long int cur_read = index - index%S_RANK_SAVE_INTERVAL + 1; 
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

bool s::char_at_idx(char check_char, unsigned long int idx){
	char found_char;
	s_file.clear();
	s_file.seekg(idx, s_file.beg);
	s_file.get(found_char);

	if(found_char == check_char)
		return true;
	else 
		return false;
}

void s::fill_s_rank_file(fstream& s_file, string s_rank_file_name){

	s_rank_file.open(s_rank_file_name, fstream::out | fstream::in | fstream::app);
	
	vector<unsigned long int> cur_rank(ALPHABET_SIZE, 0);
	s_file.clear();
	s_file.seekg(0);
	char cur_char;
	unsigned long int cur_idx;
	while(s_file.get(cur_char)){
		cur_rank[cur_char]++;
		if(cur_idx%S_RANK_SAVE_INTERVAL == 0){
			VectorToFile(cur_rank, s_rank_file);
		}
		cur_idx++;
	}
	s_rank_file.close();
}

void s::fill_s_count_file(fstream& s_file, string s_count_file_name){

	s_count_file.open(s_count_file_name, fstream::out | fstream::in);

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

	VectorToFile(count_vector, s_count_file);
	s_count_file.close();
}
#include <string>
#include "b.h"
#include "constants.h"

b::b(string filename, string extension){
	string b_rank_file_name = INDEX_DIR + filename + "_" + extension + ".rank";
	string b_file_name = FILE_DIR + filename + "."  + extension;

	b_file.open(b_file_name, fstream::in);

	if(!find_or_create_file(b_rank_file_name))
		fill_b_rank_file(b_file, b_rank_file_name);

	b_rank_file.open(b_rank_file_name, fstream::in);

}

b::~b(){
	b_file.close();
	b_rank_file.close();
}

unsigned long int b::rank(unsigned long int index){
	b_rank_file.clear();
	b_file.clear();

	unsigned long int rank_file_idx = index/BYTE_SIZE;
	unsigned long int remainder;
	if(rank_file_idx)
		remainder = index%(rank_file_idx*BYTE_SIZE) + 1;
	else
		remainder = index + 1;

	unsigned long int cur_tot;
	b_rank_file.seekg(rank_file_idx*sizeof(unsigned long int), b_rank_file.beg);
	b_rank_file.read(reinterpret_cast<char *>(&cur_tot), sizeof(unsigned long int));

	//Find the remainder of set bits
	char in_byte;
	b_file.seekg(rank_file_idx, b_file.beg);
	b_file.get(in_byte);
	for(int i = (BYTE_SIZE - remainder); i < BYTE_SIZE; i++){
		cur_tot += ((unsigned char)in_byte >> i) & 1;
	}

	return cur_tot;
}

unsigned long int b::select(unsigned long int index){

	//perform a binary search on b_rank_file
	b_rank_file.clear();
	b_rank_file.seekg(0, b_rank_file.end);
	unsigned int num_entries = b_rank_file.tellg()/sizeof(unsigned long int) - 1;

	return bin_select(0, num_entries, index);
}

//Helper function using a binary search over the rank index
unsigned long int b::bin_select(unsigned long int l, unsigned long int r, unsigned long int index){

	char in_byte;

	if(r == l + 1){

		unsigned long int rem;
		unsigned long int tot_read = l*B_RANK_SAVE_INTERVAL*BYTE_SIZE; //total bits checked
		unsigned long int tot_set; // total set bits
		b_rank_file.seekg(l*sizeof(unsigned long int));
		b_rank_file.get(in_byte);
		tot_set = (unsigned long int)in_byte;

		b_file.clear();
		b_file.seekg(l*B_RANK_SAVE_INTERVAL, b_file.beg);

		int byte_idx;
		while(tot_set < index){
			b_file.get(in_byte);
			byte_idx = 0;
			while(tot_set < index && byte_idx <= BYTE_SIZE){
				byte_idx++;
				tot_read++;
				tot_set += ((unsigned char)in_byte >> (BYTE_SIZE - byte_idx) & 1);
			}
		}
		return tot_read - 1;
	} 

	unsigned int m = (r - l)/2;
	b_rank_file.seekg(m*sizeof(unsigned long int));
	b_rank_file.get(in_byte);

	if((unsigned long int)in_byte > index){
		r = m;
	} else {
		l = m;
	}
	return bin_select(l, r, index);
}

void b::fill_b_rank_file(fstream& b_file, string b_rank_file_name){

	b_file.clear();
	b_rank_file.open(b_rank_file_name, fstream::in | fstream::out | fstream::app);

	char in_byte;
	unsigned long int cur_tot = 0;
	unsigned long int cur_idx = 0;

	b_rank_file.write(reinterpret_cast<const char *>(&cur_tot), sizeof(unsigned long int));
	while(b_file.get(in_byte)){
		cur_tot += COUNT_BITS_LOOKUP[(unsigned char)in_byte];
		if(cur_idx%B_RANK_SAVE_INTERVAL == 0){
			b_rank_file.write(reinterpret_cast<const char *>(&cur_tot), sizeof(unsigned long int));
		}
		cur_idx++;
	}
	b_rank_file.close();
}
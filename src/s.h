#include <fstream>
#include <string>
#include "indexes.h"

#define INDEX_DIR "./../indexes/"
#define FILE_DIR "./../files/"

#define RANK_SAVE_INTERVAL 4

using namespace std;
class s : public indexes {
	fstream count_file;
	fstream rank_file;
	string index_dir = INDEX_DIR;

	bool find_or_create_file(string filename);
	void fill_rank_file(fstream& s_file, string rank_file_name);
	void fill_count_file(fstream& s_file, string count_file_name);

	public:
		s(string filename);
		unsigned long int count(char c);
		unsigned long int rank(char c, unsigned int index);
};
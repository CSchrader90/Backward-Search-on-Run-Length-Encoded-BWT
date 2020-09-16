#include <fstream>
#include <string>

#define INDEX_DIR "./../indexes/"
#define FILE_DIR "./../files/"
#define ALPHABET_SIZE 256

using namespace std;
class s {
	fstream count_file;
	fstream rank_file;
	string index_dir = INDEX_DIR;

	bool find_or_create_file(string filename);
	void create_rank_file(string s_file_name, string rank_file_name);
	void create_count_file(string s_file_name, string count_file_name);

	public:
		s(string filename);
		unsigned int count(char c, unsigned int index);
		unsigned int rank(char c, unsigned int index);
};
#include <fstream>
#include <string>
#include "indexes.h"
#include "constants.h"

using namespace std;
class s : public indexes {
	fstream s_file;
	fstream s_count_file;
	fstream s_rank_file;

	vector<unsigned long int>count_vector;

	void fill_s_rank_file(fstream& s_file, string s_rank_file_name);
	void fill_s_count_file(fstream& s_file, string s_count_file_name);

	public:
		s(string filename);
		~s();
		unsigned long int count(char c);
		unsigned long int rank(char c, unsigned int index);
};
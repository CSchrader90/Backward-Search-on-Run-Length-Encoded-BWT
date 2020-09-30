#include <iostream>
#include <string>
#include <cassert>
#include "s.h"
#include "b.h"

using namespace std;

int main(int argc, char *argv[]){

	assert(argc >= 2); //update this assertion

	string text_name(argv[1]);
	string b_extension = "b";
	string bb_extension = "bb";

	s s_obj{ text_name };
	b b_obj{ text_name, b_extension };
	b bb_obj{ text_name, bb_extension };

	string search_string(argv[2]);

	//Initialisation
	char cur_char = search_string[search_string.size() - 1];
	unsigned long int First = bb_obj.select(s_obj.count(cur_char) + 1);
	unsigned long int Last  = bb_obj.select(s_obj.count(cur_char + 1) + 1) - 1;

	for(string::iterator it = search_string.end() - 2; it != search_string.begin() - 1; --it) {

		//Update First
		if(s_obj.char_at_idx(*it, b_obj.rank(First - 1) - 1))
			First = bb_obj.select(s_obj.count(*it) + s_obj.rank(*it, b_obj.rank(First - 1) -1)) + First - b_obj.select(b_obj.rank(First - 1));
		else 
			First = bb_obj.select(s_obj.count(*it) + 1 + s_obj.rank(*it, b_obj.rank(First - 1) - 1));

		//Update Last
		if(s_obj.char_at_idx(*it, b_obj.rank(Last) - 1))
			Last = bb_obj.select(s_obj.count(*it) + s_obj.rank(*it, b_obj.rank(Last) - 1)) + Last - b_obj.select(b_obj.rank(Last));
		else
			Last = bb_obj.select(s_obj.count(*it) + 1 + s_obj.rank(*it, b_obj.rank(Last) - 1)) - 1;
	}

	if(Last < First )
		cout << "No matching strings found" << endl;
	else
		cout << Last - First + 1 << " match(es) found" << endl;
}
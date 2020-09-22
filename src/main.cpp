#include <iostream>
#include <string>
#include <cassert>
#include "s.h"
#include "b.h"


using namespace std;

int main(int argc, char *argv[]){

	assert(argc >= 2); //udpate this assertion

	string text_name(argv[1]);
	string b_extension = "b";
	string bb_extension = "bb";

	s s_obj{ text_name };
	b b_obj{ text_name, b_extension };
	b bb_obj{ text_name, bb_extension };

	string search_string(argv[2]);

	//Initialisation
	unsigned long int First = bb_obj.select(s_obj.count(argv[2][0]) + 1);
	unsigned long int Last  = bb_obj.select(s_obj.count(argv[2][0] + 1) + 1) - 1;

	cout << "First = " << First << endl;
	cout << "Last = " << Last << endl;


}
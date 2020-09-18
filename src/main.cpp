#include <iostream>
#include <string>
#include <cassert>
#include "s.h"


using namespace std;

int main(int argc, char *argv[]){

	assert(argc >= 2); //udpate this assertion

	string text_name(argv[1]);

	s s_obj{ text_name };

}
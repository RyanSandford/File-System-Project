/*
Ryan Sandford, CS3307 Assignment 1, October 2 2019
myrm acts as the rm command in linux, removes a file given a file name passed as an arguement
*/

#include "file_manager.h"

using namespace std;


int main (int argc, char * argv[]) {
	string str;

	if (argc == 1){
		cout << "No arguements given" <<endl;
	}

	//Remove all files given
	for (int i = 1; i < argc; i++){
		str = argv[i];
		file_manager manager = file_manager(str);
		if (manager.my_remove() != 0){
			cout << "Error " << manager.get_err_string() << ". Could not remove file, Error number is: " << manager.get_err_int() << endl;
		}
	}
	return 0;
}

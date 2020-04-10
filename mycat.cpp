/*
Ryan Sandford, CS3307 Assignment 1, October 2 2019
mycat recreates the cat command standard in linux, prints the content of one or more files passed as arguements to standard output
*/
#include "file_manager.h"

using namespace std;


int main (int argc, char * argv[]) {
        string str;
        if (argc == 1){
                cout << "No arguements given" <<endl;
        }

	//handle multiple arguements
        for (int i = 1; i < argc; i++){
                str = argv[i];
                file_manager manager = file_manager(str);

                //print an error message to standard output if the file is a directory
		if (manager.get_type() == "directory"){
			cout<< "Error can not cat a directory" << endl;
			exit(0);
		}

		//dump the file contents to standard output
		manager.dump(cout);

		//Note that when calling mycat.cpp on multiple files, any error message printed could get
		//buried in between files being outputed to the console
		if (manager.get_err_int() != 0) {
			cout << "Error " << manager.get_err_string() << endl;
		}
        }
        return 0;
}


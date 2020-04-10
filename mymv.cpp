/*
Ryan Sandford, CS3307 Assignment 1, October 2 2019
mymv acts as mv, takes two file names as parameters and renames/moves the source file to the destination
*/

#include "file_manager.h"

using namespace std;


int main (int argc, char * argv[]) {
        string source;
        string dest;

        if (argc < 3){
                cout << "Not enough arguements" << endl;
        }
        else if (argc > 3){
                cout << "Too many arguements given" << endl;
        }
        else {
                source = argv[1];
                dest = argv[2];
                file_manager source_file = file_manager(source);
		source_file.my_rename(dest);

		//the source and destination are on different file systems, my_rename will throw an EXDEV Error
		//dump the source file to the destination and delete the source instead.
                //This works for regular files
		if (source_file.get_err_int() == EXDEV){
			ofstream dest_file;
			dest_file.open(dest);
			source_file.dump(dest_file);
			source_file.my_remove();
			dest_file.close();
		}
                else if (source_file.get_err_int() != 0){
                        cout << "Error " << source_file.get_err_string() << endl;
                }
        }

        return 0;
}


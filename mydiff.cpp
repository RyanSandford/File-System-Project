/*
Ryan Sandford, October 2 2019
compares to files and prints a message containing the results
*/

#include "file_manager.h"

using namespace std;


int main (int argc, char * argv[]) {
        string name1;
        string name2;
	int status;

        if (argc < 3){
                cout << "Not enough arguements" << endl;
        }
        else if (argc > 3){
                cout << "Too many arguements given" << endl;
        }
        else {
                name1 = argv[1];
                name2 = argv[2];
                file_manager file1 = file_manager(name1);
                file_manager file2 = file_manager(name2);

		//Compare the files
                status = file1.my_compare(file2);
		if (file1.get_err_int() != 0){
			cout<< "Error " << file1.get_err_string() << endl;
		}
		else if (status == 0){
			cout << "Success files are the same " << endl;
		}
		else{
			cout << "Files are different " << endl;
		}
        }

        return 0;
}



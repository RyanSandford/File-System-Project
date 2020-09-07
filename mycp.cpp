/*
Ryan Sandford, October 2 2019
mycp acts as the cp command standard to linux, copies a source file to a destination file
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
		//prepare the source and destination files
		source = argv[1];
		dest = argv[2];
		file_manager source_file = file_manager(source);
		ofstream dest_file;
		dest_file.open(dest);

		//dump the contents of the source file to a destination file
		source_file.dump(dest_file);
		if (source_file.get_err_int() != 0){
			cout << "Error " << source_file.get_err_string() << endl;
		}

		dest_file.close();
	}

        return 0;
}


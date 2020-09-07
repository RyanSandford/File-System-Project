/*
Ryan Sandford, October 2 2019
myls acts as the ls command displaying all files in a directory passed as a parameter
*/

#include "file_manager.h"

using namespace std;


int main (int argc, char * argv[]) {
	char buf[PATH_MAX];
        getcwd(buf,sizeof(buf));
	string cwd = buf;
	cwd = "./";

	
	if (argc > 1){

                //-l is an arguement, proceed with long ls
        	if (string(argv[1]) == "-l"){
                	if (argc > 2){

				//long ls on specified directories
				for (int j = 2; j < argc; j++){
                                	string str = argv[j];
                                	file_manager manager = file_manager(str);

					if (manager.get_err_int() != 0){
						cout << "Error: " << manager.get_err_string() << endl;
					}

					//list the directory's children; they're names and permissions
                                	cout << manager.get_name() << "'s children : "  << endl;
                                	vector<file_manager> vec = manager.get_children();
                                	for (int i = 0; i < vec.size(); ++i){
                                        	cout << vec[i].get_permissions() << " " << vec[i].get_owner_name() << " " << vec[i].get_group_name() << " " << vec[i].get_name() <<endl;

                                	}

                       		 }

			}

			else {
				//long ls on current directory
				file_manager manager = file_manager(cwd);

				if (manager.get_err_int() != 0){
                                       cout << "Error: " << manager.get_err_string() << endl;
                                }

				//list the current working directory's children; they're names and permissions
                		cout << manager.get_name() << "'s children : " << endl;
                		vector<file_manager> vec = manager.get_children();
                		for (int i = 0; i < vec.size(); ++i){
                        		cout << vec[i].get_permissions() << " " << vec[i].get_owner_name() << " " << vec[i].get_group_name() << " " << vec[i].get_name()<<endl;
                		}

			}
		}

		//-l is not an arguement, proceed with short ls on given directories
        	else {
                	// short ls with arguements given
			for (int j = 1; j < argc; j++){
				string str = argv[j];
				file_manager manager = file_manager(str);

				if (manager.get_err_int() != 0){
                                	cout << "Error: " << manager.get_err_string() << endl;
                                }

				//list the names of the directory's children
				cout << manager.get_name() << "'s children : " << endl;
		                vector<file_manager> vec = manager.get_children();
                		for (int i = 0; i < vec.size(); ++i){
                       			cout << vec[i].get_name() << endl;
                		}

			}
		}
        }

	//-l is not an arguement, proceed with short ls on current working directory
	else{
		//short ls in current directory
		file_manager manager = file_manager(cwd);

		if (manager.get_err_int() != 0){
                	cout << "Error: " << manager.get_err_string() << endl;
                }

		//list the names of the current working directory's children
		cout << manager.get_name() << "'s children : " << endl;
		vector<file_manager> vec = manager.get_children();
		for (int i = 0; i < vec.size(); ++i){
			cout << vec[i].get_name() << endl;
		}
	}

        return 0;
}


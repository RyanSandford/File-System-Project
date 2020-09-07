/*
Ryan Sandford, October 2 2019
acts as the stat command does, prints information about a given file_manager object passed as a parameter
*/

#include "file_manager.h"

using namespace std;

//children and error number were excluded from the output of mystat since children can be obtained through myls
//and error number isn't an inherint property of a file, just information added to the constructor to help the project
int main (int argc, char * argv[]) {
        string fileName;

        if (argc != 2){
                cout << "Invalid number of arguements" << endl;
        }
        else {
        	fileName = argv[1];
		file_manager file = file_manager(fileName);

		//print file_manager attributes to standard output
		if (file.get_err_int() == 0) {
			cout << "Name: " << file.get_name() << endl;
			cout << "Type: " << file.get_type() << endl;
			cout << "File Size: " << file.get_file_size() << endl;
			cout << "Owner ID: " << file.get_ownerID() << endl;
			cout << "Owner Name " << file.get_owner_name() << endl;
			cout << "Group ID: " << file.get_groupID() << endl;
			cout << "Group Name: " << file.get_group_name() << endl;
			cout << "Permissions: " << file.get_permissions() << endl;
			cout << "Access Time: " << file.get_access_time() << endl;
			cout << "Modification Time: " << file.get_mod_time() << endl;
			cout << "Status Change Time: " << file.get_sc_time() << endl;
			cout << "Block Size: " << file.get_block_size() << endl;
		}
		else{
			cout << "Error " << file.get_err_string()<< endl;
		}
        }

        return 0;
}


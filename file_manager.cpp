/*
Ryan Sandford, CS3307 Assignment 1,
October 2, 2019
This file initializes a file manager class, defining a constuctor, destructor,
 member functions, and various getter and setter methods
This class is used to store relavent information about a given individual file
*/
#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <errno.h>
#include <vector>
#include <dirent.h>
#include <string.h>
#include "file_manager.h"

using namespace std;

	/*
	Default Constructor, no parameters or return value
	intitializes all strings to empty strings and all ints to zero
	*/
	file_manager::file_manager(){
		name = "";
                type = "";
                file_size = 0;
                ownerID = 0;
                owner_name = "";
                groupID = 0;
                group_name = "";
                permissions = "";
                access_time = "";
                mod_time = "";
                sc_time = "";
                block_size = 0;
                error_num = 0;
	}

	/*
	Constuctor, recieves the name of a file as a parameter, no return value
	extracts relavent information from the stat function called on the filename
	if the file name is invalid the error number is set appropriately and all other values
	are intitialized as they are in the default constructor
	*/
        file_manager::file_manager(string fileName){
            struct stat st;

	    //check if stat() worked correctly
            //and initialize attributes
            if (stat(fileName.c_str(),&st) != 0){
                name = "";
                type = "";
                file_size = 0;
                ownerID = 0;
                owner_name = "";
                groupID = 0;
                group_name = "";
                permissions = "";
                access_time = "";
                mod_time = "";
                sc_time = "";
                block_size = 0;
                error_num = ENOENT;
            }

            else{

                name = fileName;

		//initialize file type
                type = "";
                if (S_ISREG(st.st_mode)) {
                    type = "regular file";
                };
                if (S_ISDIR(st.st_mode)) {
                    type = "directory";
                };
                if (S_ISCHR(st.st_mode)) {
                    type = "character device";
                };
                if (S_ISBLK(st.st_mode)) {
                    type = "block device";
                };
                if (S_ISFIFO(st.st_mode)) {
                    type = "FIFO";
                };
                if (S_ISLNK(st.st_mode)) {
                    type = "symbolic link";
                };
                if (S_ISSOCK(st.st_mode)) {
                    type = "socket";
                };


                file_size = st.st_size;
                ownerID = st.st_uid;
                owner_name = getpwuid(ownerID)->pw_name;
                groupID = st.st_gid;
                group_name = getgrgid(groupID)->gr_name;

                //start with no permissions (empty string), concatenate corresponding letter in order to format permissions
		permissions = "";

		//owner permissions
                if (st.st_mode & S_IRUSR)
                    {permissions = permissions + "r";}
                else
                    {permissions = permissions + "-";}
                if (st.st_mode & S_IWUSR)
                    {permissions = permissions + "w";}
                else {permissions = permissions + "-";}
                if (st.st_mode & S_IXUSR)
                    {permissions = permissions + "x";}
                else {permissions = permissions + "-";}

                //group permissions
                if (st.st_mode & S_IRGRP)
                    {permissions = permissions + "r";}
                else {permissions = permissions + "-";}
                if (st.st_mode & S_IWGRP)
                    {permissions = permissions + "w";}
                else {permissions = permissions + "-";}
                if (st.st_mode & S_IXGRP)
                    {permissions = permissions + "x";}
                else {permissions = permissions + "-";}

                //other permissions
                if (st.st_mode & S_IROTH)
                    {permissions = permissions + "r";}
                else {permissions = permissions + "-";}
                if (st.st_mode & S_IWOTH)
                    {permissions = permissions + "w";}
                else {permissions = permissions + "-";}
                if (st.st_mode & S_IXOTH)
                    {permissions = permissions + "x";}
                else {permissions = permissions + "-";}

		//initialize time attributes and block size
                access_time =to_string(st.st_atim.tv_nsec);
                mod_time = to_string(st.st_mtim.tv_nsec);
                sc_time = to_string(st.st_ctim.tv_nsec);
                block_size = st.st_blksize;



		if (type == "directory"){
			expand(children);
		}

		//set error_num to zero on every successful operation
                error_num = 0;

            };

        };

        /*Destructor, no parameters or return value, deletes object and clears memory since c++
	does not have a garbage collector
	*/
        file_manager::~file_manager() {
        };

	/*dump, takes an ostream as a parameter, checks if the file stored in this file_manager object is a regular file, handles it accordingly
	reads block_size characters at a time from the file contained in the file_manager object and writes into the given file stream,
        until all characters are read.
	Uses gcount() to check if the file has less characters then the block-size
	*/
        void file_manager::dump(ostream &file){
            if (type.compare("regular file") != 0) {
                error_num = ENOTSUP;
            }
            else{
                ifstream myfile;
                myfile.open(name);

                char memblock[block_size];
		myfile.read(memblock, block_size);

		//check if the file size is bigger then the block_size
		if (block_size <= myfile.gcount()){
			//read and write block_size characters
			while  (block_size <= myfile.gcount()){
				myfile.read(memblock, block_size);
                		file.write(memblock, block_size);
			}
			myfile.read(memblock, myfile.gcount());
		}

		//write the remaining gcount() characters into the filestream
                file.write(memblock, myfile.gcount());
                myfile.close();
                error_num = 0;
            };
        };

	/*
	my_rename, takes in a string to become the files new name as a parameter, invokes the built in rename function to rename the file,
	reurns the error number
	*/
        int  file_manager::my_rename(string new_name){
		if (rename(name.c_str(), new_name.c_str()) != 0){
			error_num = errno;
		}
		else{
	   		name = new_name;
			error_num = 0;
		};
		return error_num;
        };

	/*
	my_remove(), doesn't take any parameters, invokes the built in unlink function to remove the file contained in the file_manager object,
	returns the error number
	*/
	int file_manager::my_remove(){
		if(unlink(name.c_str()) != 0){
			error_num = errno;
		}
		else{
			error_num = 0;
		}
		return error_num;
	};

	/*
	my_compare, takes a file_manager object as a parameter, reads and compares the contents of the two file_manager objects in intervals
	of block_size characters.  Uses gcount() to determine if the files contain less characters then block_size
	returns -1 if the files are not the same, 0 if the files are the same.
	Sets the error number if an error occurs
	*/
	int file_manager::my_compare(file_manager foo){
		ifstream myfile;
		ifstream ofile;
		char file_content1[block_size];
		char file_content2[block_size];

		myfile.open(name);
		ofile.open(foo.name);

		if (myfile.fail()){
			error_num = ENOENT;
		}

		else if (ofile.fail()){
			error_num = ENOENT;
		}

		else{
			//check if the files are different sizes
			if (file_size != foo.file_size){
				return -1;
			}
			//checks if the files are different types
			if ( type != foo.type){
				return -1;
			}

			ofile.read(file_content2, block_size);
			myfile.read(file_content1, block_size);

			//read files in by block_size if the files are bigger then block_size
			if (block_size <= myfile.gcount()){

                        	while  (block_size <= myfile.gcount()){
					//check if contents are the same
                                	if (memcmp(file_content1, file_content2, block_size) != 0){
                                        	return -1;
                                	}
					ofile.read(file_content2, block_size);
					myfile.read(file_content1, block_size);
                        	}
                        	myfile.read(file_content1, myfile.gcount());
				ofile.read(file_content2, myfile.gcount());
               		}

			//file content is the same
			if (memcmp(file_content1, file_content2, myfile.gcount()) == 0){
                                return 0;
	                }
			//file content is different
        	        else {
                        	return -1;
                        }

			error_num = 0;
		}
		myfile.close();
		ofile.close();
	};

	/*expand, takes a vector of file_managers as a parameter, uses built in functions opendir, readdir, closedir to extract children
	pushes children into vector, returns the error number
	*/
	int file_manager::expand(vector<file_manager> &vec){

		struct dirent * entry;
		string path_name;
		string local_name;
		DIR *dirp;
		if ( type != "directory") {
                	error_num = ENOTSUP;
                	cout << "Error ENOTSUP "<< error_num << " Operation not supported, file: " << name << " is not a directory file" << endl;
            	}
		else {

			if((dirp = opendir(name.c_str())) != NULL){

				// for some reason it reads out "." and ".." before reading any actual files, these two lines clear the dots
				entry = readdir(dirp);
				entry = readdir(dirp);
				while ((entry = readdir(dirp)) != NULL){

					local_name = string (entry->d_name);
					path_name = name + "/" +  local_name;
					file_manager foo = file_manager(path_name);
					vec.push_back(foo);
				}
				closedir(dirp);
				error_num = 0;
			}
			else{
				error_num = ENOENT;
			}


		};
		return error_num;
	};

	/*
	get_name, no parameters, getter method, returns name
	*/
	string file_manager::get_name() {
		return name;
	};

	/*
        get_type, no parameters, getter method, returns type
        */
	string file_manager::get_type() {
		return type;
	};

	/*
        get_file_size, no parameters, getter method, returns file_size
        */
	int file_manager::get_file_size() {
		return file_size;
	};

	/*
        get_ownerID, no parameters, getter method, returns ownerID
        */
	int file_manager::get_ownerID() {
		return ownerID;
	};

	/*
        get_owner_name, no parameters, getter method, returns owner_name
        */
	string file_manager::get_owner_name() {
		return owner_name;
	};

	/*
        get_groupID, no parameters, getter method, returns groupID
        */
	int file_manager::get_groupID() {
		return groupID;
	};

	/*
        get_group_name, no parameters, getter method, returns group_name
        */
	string file_manager::get_group_name() {
		return group_name;
	};

	/*
        get_permissions, no parameters, getter method, returns permissions
        */
	string file_manager::get_permissions() {
		return permissions;
	};

	/*
        get_access_time, no parameters, getter method, returns access_time
        */
	string file_manager::get_access_time() {
		return access_time;
	};

	/*
        get_mod_time, no parameters, getter method, returns mod_time
        */
	string file_manager::get_mod_time() {
		return mod_time;
	};

	/*
        get_sc_time, no parameters, getter method, returns sc_time
        */
	string file_manager::get_sc_time() {
		return sc_time;
	};

	/*
        get_block_size, no parameters, getter method, returns block_size
        */
	int file_manager::get_block_size() {
		return block_size;
	};

	/*
	get_children, no parameters, getter method, returns a vector of file_managers containing the child files
	*/
	vector<file_manager> file_manager::get_children(){
		return children;
	};

	/*
        get_err_int, no parameters, getter method, returns the error number as an int
        */
	int file_manager::get_err_int() {
		return error_num;
	};

	/*
        get_err_string, no parameters, getter method, returns the error number as a string
        */
	string file_manager::get_err_string() {
		return strerror(error_num);
	};

	/*
        set_name, takes a string to be the new name, setter method, returns nothing
        */
	void file_manager::set_name(string new_name){
		name = new_name;
	};


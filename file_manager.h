/*
Ryan sandford, October 2 2019,
Header file for file manager class
*/
#ifndef guard
#define guard
#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <errno.h>
#include <vector>
#include <dirent.h>
#include <string.h>

class file_manager
{
	private:
		std::string name;
		std::string type;
		int file_size;
		int ownerID;
		std::string owner_name;
		int groupID;
		std::string group_name;
		std::string permissions;

		std::string access_time;
		std::string mod_time;
		std::string sc_time;
		int block_size;
		std::vector<file_manager> children;
		int error_num;

	public:
		file_manager();
		file_manager(std::string fileName);
		~file_manager();
		void dump(std::ostream &file);
		int my_rename(std::string new_name);
		int my_remove();
		int my_compare(file_manager foo);
		int expand(std::vector<file_manager>  &vec);
		std::string get_name();
		std::string get_type();
		int get_file_size();
		int get_ownerID();
		std::string get_owner_name();
		int get_groupID();
		std::string get_group_name();
		std::string get_permissions();
		std::string get_access_time();
		std::string get_mod_time();
		std::string get_sc_time();
		std::vector<file_manager> get_children();
		int get_block_size();
		int get_err_int();
		std::string get_err_string();
		void set_name(std::string new_name);
};
#endif

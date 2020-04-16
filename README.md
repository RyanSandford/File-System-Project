# File System Project
This repository contains several files which implement a file system. This goal of this project was
to become familiar with C++ and the Raspberry Pi Desktop. The class file_manager implements the 
functionality of a file/directory. Additionally several files which behave as stripped linux 
commands are included to manipulate file_manager objects.

The class file_manager.cpp contains:
- The name of the file
- The type of the file
- The size of the file
- The owner of the file
- The group of the file
- The permissions for the file
- The Acces time of the file
- The modification time of the file
- The status change time of the file
- The block size of the file
- A vector of children for the file (if it is a directory)
- An error number if an operation is unsuccesful

as attributes as well as the following member functions:
- Dump
- Rename
- Remove
- Compare 
- Expand
to assist with the implementation of the stripped linux-commands.

The files mymv.cpp, mycp.cpp, myls.cpp, mycat.cpp, myrm.cpp, mydiff.cpp, mystat.cpp work as stripped
versions of the respective linux commands mv, cp, ls, cat, rm, diff, stat. Each of which use the member functions
in the file_manager class to perform its intended purpose. Descriptions of the non-trivial member functions invoked by
the stripped linux commands can be found below.


__Dump:__ This function will take a file stream as a parameter and dump the contents of the named file to that file stream.
This can be used to copy the file, display its contents to the terminal, and so on. The block size of the file is used
to determine the amount of data to be read from the file and written to the file stream at a time.
This function can only be used on regular files; attempts to do this on other types of files will have an error returned,
with the object's internal error number set.

__Rename:__ This changes the name of the file from its existing name to the new name provided as a parameter to this function.
In addition to changing the corresponding attribute of the file object in question, this will change the name of the file 
on disk using the rename() system function. This function sets the object's internal error number if the operation could
not be completed. Note that this function may allow files to be moved from one directory to another,
but will not likely allow files to be moved from one filesystem to another.

__Remove:__ This removes the file from the file system, reseting the attributes of the file object in question by using
the unlink() system function. This function sets the object's internal error number if the operation could
not be completed.

__Compare:__ This function takes a file object as a parameter and will compare the contents of the file
object this function was invoked upon to this other file object. Block size is used to determine the 
amount of data to be compared at a time. This function will print the results of the comparison to
standard output. This function sets the object's internal error number if the operation could
not be completed.

__Expand:__ This function operates on directories only and is used to fill in the children of the file object that this function
was invoked upon. It does so by obtaining a listing of the directory in question and creating a new file object for each
file found in the directory, adding these new objects to the collection of children.  This function sets the object's internal
error number if the operation could not be completed. Moreover, if this function is called on a regular file the error number
will be set to ENOTSUP.

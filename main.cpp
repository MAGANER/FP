/*
	FFP - File Folder Processor.

	-key=<value>

	-w is key, representing where files are stored.
	-p is predicat, where value is name.ext
		it can contain * and it means anything
	-c is command to delete after they are moved to special folder
	-f is a name of new folder
*/
#include"WhatToinclude.h"
#include"Common.h"

#if COPY == 1
#include"Copy.h"
using namespace Copy;
#define INCLUDE_COUNTER (INCLUDE_COUNTER + 1)
#endif

int main(int argc, char** argv)
{
	#if INCLUDE_COUNTER == 0
	cout << "can not run programm, cos it's compiled of no module!";
	exit(-1);
	#endif 

	setlocale(LC_ALL, "rus");

	string destination;
	string new_folder;
	string predicat;

	bool clear = false;
	
	for (int i = 1; i < argc; ++i)
	{
		auto arg = Common::parse_argument(string(argv[i]));
		switch (arg.first)
		{
		case 'w':destination = arg.second;   break;
		case 'c':clear       = true;         break;
		case 'f':new_folder  = arg.second;   break;
		case 'p':predicat    = arg.second;   break;
		}
	}
	if (destination.empty())
		Common::kill_app("no folder, where to go!");
	if (new_folder.empty())
		Common::kill_app("no folder to move files!");
	if (predicat.empty())
		Common::kill_app("no predicat!");

	#if COPY == 1
	Copy::copy(destination, new_folder, predicat, clear);
	#endif

	return 0;
}

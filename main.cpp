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
#include"GlobalArgProcessor.h"

#if COPY == 1
#include"Copy.h"
using namespace Copy;
#define INCLUDE_COUNTER (INCLUDE_COUNTER + 1)
#endif

vector<string> erase_global_arguments(int  argc, char** argv);
int main(int argc, char** argv)
{
#if INCLUDE_COUNTER == 0
	cout << "can not run programm, cos it's compiled of no module!";
	exit(-1);
#endif 

	setlocale(LC_ALL, "rus");
	if (argc == 1)
	{
		cout << "not enough arguments!";
		exit(-1);
	}
	

	GlobArgProc::Type operation_type = GlobArgProc::Type::Undefined;
	if (GlobArgProc::is_correct(argc, argv))
		operation_type = GlobArgProc::get_arg_type(argv[1]);
	else
	{
		cout << "such global argument: " << argv[1] << " doesn't exist!";
		exit(-1);
	}

	
	vector<string> arguments = erase_global_arguments(argc, argv);

#if COPY == 1
	if (operation_type == GlobArgProc::Type::Copy) Copy::run(arguments);
#endif

	return 0;
}
vector<string> erase_global_arguments(int  argc, char** argv)
{
	vector<string> arguments;

	for (int i = 2; i < argc - 1; ++i) arguments.push_back(string(argv[i]));

	auto last_one = string(argv[argc - 1]);
	arguments.push_back(Common::get_substr(last_one, 0, last_one.size() - 1));

	return arguments;
}
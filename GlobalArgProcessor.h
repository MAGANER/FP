/*
	this application is combinations of 
	the different ones. Also all of them 
	use console line arguments and to 
	separate different arguments and 
	to call specific programm they are
	global arguments.
*/
#pragma once
#include <string.h>
namespace GlobalArgProcessor
{
	enum class Type
	{
		Copy,
		Undefined
	};
	bool is_correct(int argc, char** argv);
	Type get_arg_type(char* first_argument);
};
namespace GlobArgProc = GlobalArgProcessor;
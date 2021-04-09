#include"GlobalArgProcessor.h"

bool GlobalArgProcessor::is_correct(int argc,char** argv)
{
	const int ARGS_NUMBER = 1;
	const char* args[1] = { "C[\0" };

	char* first= argv[1];
	char* last = argv[argc - 1];
	
	bool exist = false;
	for (int i = 0; i < ARGS_NUMBER; ++i)
		if (strcmp(args[i],first) == 0)exist = true;

	int last_arg_size = strlen(last);
	char last_ch = last[last_arg_size - 1];
	
	return exist && last_ch == ']';
}
GlobalArgProcessor::Type GlobalArgProcessor::get_arg_type(char* first_argument)
{
	if (strcmp(first_argument, "C[\0") == 0) return GlobalArgProcessor::Type::Copy;
	else return GlobalArgProcessor::Type::Undefined;
}
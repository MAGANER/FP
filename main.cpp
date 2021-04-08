/*
	FFP - File Folder Processor.

	-key=<value>

	-w is key, representing where files are stored.
	-p is predicat, where value is name.ext
		it can contain * and it means anything
	-c is command to delete after they are moved to special folder
	-f is a name of new folder
*/
#include"Copy.h"

using namespace Copy;
int main(int argc, char** argv)
{
	setlocale(LC_ALL, "rus");

	string destination;
	string new_folder;
	string predicat;

	bool clear = false;
	
	for (int i = 1; i < argc; ++i)
	{
		auto arg = parse_argument(string(argv[i]));
		switch (arg.first)
		{
		case 'w':destination = arg.second;   break;
		case 'c':clear       = true;         break;
		case 'f':new_folder  = arg.second;   break;
		case 'p':predicat    = arg.second;   break;
		}
	}
	if (destination.empty())
		kill_app("no folder, where to go!");
	if (new_folder.empty())
		kill_app("no folder to move files!");
	if (predicat.empty())
		kill_app("no predicat!");

	Copy::copy(destination, new_folder, predicat, clear);

	return 0;
}

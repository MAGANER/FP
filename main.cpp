/*
	FFP - File Folder Processor.

	-key=<value>

	-w is key, representing where files are stored.
	-p is predicat, where value is name.ext
		it can contain * and it means anything
	-c is command to delete after they are moved to special folder
	-f is a name of new folder
	-u unite folder tree into the one folder
	-h is help
*/
#include<filesystem>
#include<utility>
#include<string>
#include<iostream>
using namespace std;


void kill_app(string err);
pair<char, string> parse_argument(string arg);
int main(int argc, char** argv)
{

	string destination;
	string new_folder;
	bool clear = false;
	bool unite = false;
	for (int i = 1; i < argc; ++i)
	{
		auto arg = parse_argument(string(argv[i]));
		switch (arg.first)
		{
		case 'w':destination = arg.second; break;
		case 'c':clear = true; break;
		case 'f':new_folder = arg.second; break;
		case 'u':unite = true; break;
		case 'h':break;
		}
	}
	return 0;
}
pair<char, string> parse_argument(string arg)
{
	string  keys= "-w-p-c-f-u-h";
	if (arg.size() < 4) kill_app("argument is too short!");
	if (keys.find(arg.substr(0, 2)) == string::npos)
		kill_app("no such key:" + arg.substr(0, 2));
	if (arg.find('=') == string::npos)
		kill_app("incorrect argument:" + arg);

	char key = arg[1];
	string val = arg.substr(3, arg.size() - 4);
	return make_pair(key, val);
}
void kill_app(string err)
{
	cout << err;
	exit(-1);
}
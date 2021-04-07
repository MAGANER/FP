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
bool does_match_with_predicat(string predicat, string value);
string get_substr(string str, int begin, int end);
int main(int argc, char** argv)
{
	setlocale(LC_ALL, "rus");

	string destination;
	string new_folder;
	string predicat;

	bool clear = false;
	bool unite = false;
	
	for (int i = 1; i < argc; ++i)
	{
		auto arg = parse_argument(string(argv[i]));
		switch (arg.first)
		{
		case 'w':destination = arg.second;   break;
		case 'c':clear       = true;         break;
		case 'f':new_folder  = arg.second;   break;
		case 'u':unite       = true;         break;
		case 'p':predicat    = arg.second;   break;
		}
	}
	if (destination.empty())
		kill_app("no folder, where to go!");
	if (new_folder.empty())
		kill_app("no folder to move files!");
	if (predicat.empty())
		kill_app("no predicat!");


	filesystem::path directory_to_use = filesystem::path(destination);
	filesystem::path new_directory = filesystem::path(new_folder);
	new_directory = directory_to_use / new_directory;

	filesystem::create_directory(new_directory);
	if (!filesystem::exists(directory_to_use))
		kill_app("directory " + destination + " doesn't exist!");

	for (auto& f : filesystem::directory_iterator(directory_to_use))
	{
		if (f.path() != new_directory)
		{
			try
			{
				if(does_match_with_predicat(predicat,f.path().string()))
					copy(f,directory_to_use/new_directory,filesystem::copy_options::overwrite_existing);
			}
			catch (filesystem::filesystem_error& e)
			{
				cout << "can not copy file! " << e.what() << endl;
			}
			if (clear)filesystem::remove(f);
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
	if (arg.find('=') == string::npos && arg[1] != 'h')
		kill_app("incorrect argument:" + arg);

	char key = arg[1];
	string val = get_substr(arg,3,arg.size());
	return make_pair(key, val);
}
void kill_app(string err)
{
	cout << err;
	exit(-1);
}
bool does_match_with_predicat(string predicat, string value)
{
	if      (predicat == "*") return true;
	else if (predicat.find('*') == string::npos)
	{
		if (predicat == value) return true;
	}
	else
	{
		auto match = [](string predicat, string value)
		{
			string::size_type star_point = predicat.find('*');

			//match left and right parts of predicat
			string left = get_substr(predicat, 0, star_point);
			string right = get_substr(predicat, star_point + 1, predicat.size());

			string left_to_check = get_substr(value, 0, left.size());
			string right_to_check(value, value.size() - right.size(), value.size());
			bool left_eq = left == left_to_check;
			bool right_eq = right == right_to_check;
			return left_eq && right_eq;
		};

		if (predicat.find('.') == string::npos && value.find('.') == string::npos)
		{
			int star_number = count(predicat.begin(), predicat.end(), '*');
			if (star_number > 1)kill_app("incorrect predicat!");

			return match(predicat, value);
		}
		else if (predicat.find('.') != string::npos && value.find('.') != string::npos)
		{
			int star_number = count(predicat.begin(), predicat.end(), '*');
			if (star_number > 2)kill_app("incorrect predicat!");

			int point_position = predicat.find('.');
			string left_pred = get_substr(predicat, 0, point_position);
			string right_pred = get_substr(predicat, point_position + 1, predicat.size());

			int val_point_pos = value.find('.');
			string left_val = get_substr(value, 0, val_point_pos);
			string right_val = get_substr(value, val_point_pos + 1, value.size());

			return match(left_pred, left_val) && match(right_pred, right_val);
		}
		else cout<<"predicat and value should have the same number of points `.`!"<<endl
				 <<value+" won't be processed!"<<endl;
	}

	return false;
}
string get_substr(string str, int begin, int end)
{
	if (begin > end) return "";
	if (begin < 0) return "";

	string new_str;
	for (int i = begin; i < end; ++i)
		new_str += str[i];
	return new_str;
}
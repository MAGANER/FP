#include"Copy.h"
void Copy::inner::copy(const string& destination,
					   const string& new_folder,
					   const string& predicat,
					   bool clear)
{
	filesystem::path directory_to_use = filesystem::path(destination);
	filesystem::path new_directory = filesystem::path(new_folder);

	if (new_directory.is_relative())
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
				bool matched = does_match_with_predicat(predicat, f.path().string());
				bool can_be_copied = matched && f.is_regular_file();
				if (can_be_copied)
					copy(f, directory_to_use / new_directory, filesystem::copy_options::overwrite_existing);
				if (clear && can_be_copied)
					try
				{
					filesystem::remove(f);
				}
				catch (filesystem::filesystem_error& e)
				{
					cout << "can not remove file! " << e.what() << endl;
				}
			}
			catch (filesystem::filesystem_error& e)
			{
				cout << "can not copy file! " << e.what() << endl;
			}

		}
	}
}
void Copy::run(const vector<string>& arguments)
{
	using namespace Copy::inner;

	string destination;
	string new_folder;
	string predicat;
	bool clear = false;

	map<char, string> options = Common::parse_arguments(arguments,
														keys,
														KEYS_SIZE,
														special_keys,
														SPEC_KEY_SIZE);
	for (auto& option : options)
	{
		switch (option.first)
		{
		case 'w':destination = option.second;   break;
		case 'c':clear = true;			break;
		case 'f':new_folder = option.second;   break;
		case 'p':predicat = option.second;   break;
		}
	}
	if (destination.empty())
		Common::kill_app("no folder, where to go!");
	if (new_folder.empty())
		Common::kill_app("no folder to move files!");
	if (predicat.empty())
		Common::kill_app("no predicat!");



	copy(destination, new_folder, predicat, clear);
}
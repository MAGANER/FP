#include"Copy.h"

void Copy::copy(const string& destination,
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
#include"Find.h"

void Find::run(const vector<string>& arguments)
{
	using namespace Find::inner;

	string top;
	string predicat;

	map<char, string> options = Common::parse_arguments(arguments,
														keys,
														KEYS_SIZE,
														special_keys,
														SPEC_KEYS_SIZE);

	for (auto& op : options)
	{
		switch (op.first)
		{
		case 't':top      = op.second; break;
		case 'p':predicat = op.second; break;
		}
	}

	if (top.empty()) kill_app("no top directory passed!");
	if (predicat.empty()) kill_app("no predicat!");

	find(top, predicat);
}
void Find::inner::find(const string& top, const string& predicat)
{
	namespace fs = std::filesystem;

	fs::path top_dir = { top };
	if (!fs::is_directory(top_dir)) kill_app(top + " must be directory!");
	for (auto& p : fs::recursive_directory_iterator(top_dir))
	{
		string path = p.path().string();
		if (does_match_with_predicat(predicat, path))
		{
			cout << "found:" << p.path().u8string() << endl;
		}
	}

}
#include"Find.h"

void Find::run(const vector<string>& arguments)
{
	using namespace Find::inner;

	string top;
	string predicat;
	bool recursivly = false;

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
		case 'r':recursivly = true;    break;
		}
	}

	if (top.empty()) kill_app("no top directory passed!");
	if (predicat.empty()) kill_app("no predicat!");

	find(top, predicat,recursivly);
}
void Find::inner::find(const string& top, const string& predicat, bool recursivly)
{
	namespace fs = std::filesystem;

	fs::path top_dir = { top };
	if (!fs::is_directory(top_dir)) kill_app(top + " must be directory!");


	auto process = [&](const string& p) 
	{
		if (does_match_with_predicat(predicat, p))
		{
			cout << "found:" << p << endl;
		}
	};

	if (recursivly)
		for (auto& p : fs::recursive_directory_iterator(top_dir))
			process(p.path().string());
	else
		for (auto& p : fs::directory_iterator(top_dir))
			process(p.path().string());

}
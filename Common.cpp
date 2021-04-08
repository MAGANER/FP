#include"Common.h"
pair<char, string> Common::parse_argument(string arg)
{
	bool special_key = arg != "-c";

	if (arg.size() < 4 && special_key) Common::kill_app("argument is too short!");

	string  keys = "-w-p-c-f";
	if (keys.find(arg.substr(0, 2)) == string::npos)
		Common::kill_app("no such key:" + arg.substr(0, 2));
	if (arg.find('=') == string::npos && special_key)
		Common::kill_app("incorrect argument:" + arg);

	char key = arg[1];
	string val = Common::get_substr(arg, 3, arg.size());
	return make_pair(key, val);
}
void Common::kill_app(string err)
{
	cout << err;
	exit(-1);
}
bool Common::does_match_with_predicat(string predicat, string value)
{
	if (predicat == "*") return true;
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
		else cout << "predicat and value should have the same number of points `.`!" << endl
			<< value + " won't be processed!" << endl;
	}

	return false;
}
string Common::get_substr(string str, int begin, int end)
{
	if (begin > end) return "";
	if (begin < 0) return "";

	string new_str;
	for (int i = begin; i < end; ++i)
		new_str += str[i];
	return new_str;
}
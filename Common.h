#pragma once
#include<string>
#include<utility>
#include<iostream>
#include<map>
#include<vector>

using namespace std;
namespace Common
{
	void kill_app(string err);
	bool does_match_with_predicat(const string& predicat, const string& value);
	string get_substr(string str, int begin, int end);

	map<char, string> parse_arguments(const vector<string>& args, 
									  const string* keys,
									  int keys_size,
								      const string* special_keys,
									  int spec_keys_size);
	namespace inner
	{
		pair<char, string> parse_argument(const string& arg,
										  const string* keys,
										  int keys_size,
										  const string* special_keys,
										  int spec_keys_size);
		
		bool match(const string& predicat, const string& value);
	};
};

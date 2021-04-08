#pragma once
#include<string>
#include<utility>
#include<iostream>

using namespace std;
namespace Common
{
	void kill_app(string err);
	pair<char, string> parse_argument(string arg);
	bool does_match_with_predicat(string predicat, string value);
	string get_substr(string str, int begin, int end);
};
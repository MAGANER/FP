#pragma once
#include"Common.h"
#include<filesystem>

namespace Find
{
	void run(const vector<string>& arguments);

	namespace inner
	{
		const int KEYS_SIZE = 2;
		const string keys[KEYS_SIZE] = { "-t", "-p" };

		const int SPEC_KEYS_SIZE = 1;
		const string special_keys[SPEC_KEYS_SIZE] = {};

		void find(const string& top,
				  const string& predicat);

		using namespace Common;
	};

};

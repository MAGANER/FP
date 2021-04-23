#pragma once
#include"Common.h"
#include<filesystem>
namespace Copy
{
	
	void run(const vector<string>& arguments);

	namespace inner
	{

		const int KEYS_SIZE = 3;
		const string keys[KEYS_SIZE] = { "-w","-p","-f" };

		const int SPEC_KEY_SIZE = 2;
		const string special_keys[SPEC_KEY_SIZE] = { "-c", "-r" };

		using namespace Common;
		void copy(const string& destination,
				  const string& new_folder,
				  const string& predicat,
				  bool clear,
				  bool recursivly);
	};
};
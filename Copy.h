#pragma once
#include"Common.h"
#include<filesystem>
namespace Copy
{
	using namespace Common;
	void copy(const string& destination,
			  const string& new_folder,
			  const string& predicat,
			  bool clear);
};
#pragma once

#ifndef __DIRECTORY_READER_H__
#define __DIRECTORY_READER_H__

#include <string>
#include <iostream>
#include <filesystem>
#include <vector>

#include "DllDataStructure.h"

class DirectoryReader
{
private:
	// make default constructor private.
	DirectoryReader() {};

	std::vector<DllDataStructure*> dll_file_list;
public:
	explicit DirectoryReader(std::string& dir_path);
	~DirectoryReader();

	std::vector<DllDataStructure*> GetListOfDlls() const;
};

#endif // !__DIRECTORY_READER_H__
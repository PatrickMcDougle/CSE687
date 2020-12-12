#pragma once

#ifndef __DIRECTORY_READER_H__
#define __DIRECTORY_READER_H__

#include <string>
#include <iostream>
#include <filesystem>
#include <vector>

#include "DllDataStructure.h"

using std::string;
using std::vector;

/// <summary>
/// This class will read from the directory and pull out all the DLL file information that it can find.
/// </summary>
class DirectoryReader
{
private:
	DirectoryReader() = delete;
	DirectoryReader(DirectoryReader&) = delete;
	DirectoryReader(DirectoryReader&&) = delete;

	// an array of dll data structures with the dll info.
	vector<DllDataStructure*> dll_file_list;
public:
	/// <summary>
	/// This is the main constructor.  When the constructor is called the folder is immediately serached.
	/// </summary>
	/// <param name="dir_path">This is a string to the directory where the dll(s) are located.</param>
	explicit DirectoryReader(const string& dir_path);

	~DirectoryReader();

	/// <summary>
	/// This method is a way for other classes to get access to the dll list.
	/// </summary>
	/// <returns>Returns an array (vector) of dll data structures that were found.</returns>
	vector<DllDataStructure*> GetListOfDlls() const;
};

#endif // !__DIRECTORY_READER_H__
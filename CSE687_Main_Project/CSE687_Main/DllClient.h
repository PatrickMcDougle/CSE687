#pragma once
#ifndef __DLL_CLIENT_H__
#define __DLL_CLIENT_H__

#include <string>
#include <wtypes.h>
#include <vector>

#include "DllDataStructure.h"
#include "DirectoryReader.h"

using std::vector;
using std::string;

typedef string* (*funcListOfFunctions)(void);
typedef size_t(*funcNumberOfTests)(void);

/// <summary>
/// This class is in charge of loading up the dlls and pulling the tests out.
/// </summary>
class DllClient
{
private:
	vector<DllDataStructure*> dll_data_list;
	bool do_something_ = false;

	void GetDllsFunctionList(DllDataStructure* dll_data_struct);

	DllClient(DllClient&) = delete;
	DllClient(DllClient&&) = delete;

public:
	/// <summary>
	/// The default Constructor
	/// </summary>
	DllClient() {	};
	~DllClient();

	/// <summary>
	/// This method will go through all the dlls found in the directory and
	/// start loading in all the functions found in the dlls.
	/// </summary>
	/// <param name="dir_path">The path to where the dll(s) are located.</param>
	void LoadDll(const string& dir_path);

	/// <summary>
	/// This method returns the data structure list of the dll(s) that it found.
	/// </summary>
	/// <returns></returns>
	vector<DllDataStructure*> GetDataList() const { return dll_data_list; };
};

#endif // !__DLL_CLIENT_H__
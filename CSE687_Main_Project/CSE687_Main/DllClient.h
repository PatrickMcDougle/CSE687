#pragma once
#ifndef __DLL_CLIENT_H__
#define __DLL_CLIENT_H__

#include <string>
#include <wtypes.h>
#include <vector>

#include "DllDataStructure.h"
#include "DirectoryReader.h"

typedef bool (*funcTestbool)(void);

typedef std::string* (*funcListOfFunctions)(void);
typedef size_t(*funcNumberOfTests)(void);

class DllClient
{
private:
	std::vector<DllDataStructure*> dll_data_list;
	bool do_something_ = false;

	void GetDllsFunctionList(DllDataStructure* dll_data_struct);
public:
	DllClient() {	};
	~DllClient();

	void LoadDll(std::string& dir_path);
};

#endif // !__DLL_CLIENT_H__
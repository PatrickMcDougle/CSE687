#pragma once

#ifndef __DLL_DATA_STRUCTURE_H__
#define __DLL_DATA_STRUCTURE_H__

#include <string>
#include <wtypes.h>

struct DllDataStructure
{
	HINSTANCE dll_instance = nullptr;
	size_t number_of_functions = 0;
	std::string* function_list_array = nullptr;

	std::string dll_path;
	std::string dll_name;

	DllDataStructure() {}

	// copy constructor.
	DllDataStructure(const DllDataStructure& copy) :
		dll_instance(copy.dll_instance),
		number_of_functions(copy.number_of_functions),
		dll_path(copy.dll_path),
		dll_name(copy.dll_name) {
		function_list_array = new std::string[number_of_functions];
		for (size_t i = 0; i < number_of_functions; i++)
		{
			function_list_array[i] = copy.function_list_array[i];
		}
	}
};

#endif // !__DLL_DATA_STRUCTURE_H__
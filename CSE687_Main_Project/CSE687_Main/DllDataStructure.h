#pragma once

#ifndef __DLL_DATA_STRUCTURE_H__
#define __DLL_DATA_STRUCTURE_H__

#include <string>
#include <wtypes.h>

using std::string;

/// <summary>
/// This structure is holding onto information about the DLL that was
/// dynamicly read in.
/// </summary>
struct DllDataStructure
{
	/// <summary>
	/// a pointer to the dynamic dll.
	/// </summary>
	HINSTANCE dll_instance = nullptr;

	/// <summary>
	/// Is the number of functions in this dll that needs to be tested.
	/// </summary>
	size_t number_of_functions = 0;

	/// <summary>
	/// Is an array of all the function names in the dll that need to be tested.
	/// </summary>
	string* function_list_array = nullptr;

	/// <summary>
	/// Is the path to the dll file.
	/// </summary>
	string dll_path;

	/// <summary>
	/// Is the name of the dll file.
	/// </summary>
	string dll_name;

	/// <summary>
	/// Default Construct.
	/// </summary>
	DllDataStructure() {}

	/// <summary>
	/// Copy Constructor
	/// </summary>
	/// <param name="copy">The stuct that we want to copy from.</param>
	DllDataStructure(const DllDataStructure& copy) :
		dll_instance(copy.dll_instance),
		number_of_functions(copy.number_of_functions),
		dll_path(copy.dll_path),
		dll_name(copy.dll_name) {
		function_list_array = new string[number_of_functions];
		for (size_t i = 0; i < number_of_functions; i++)
		{
			function_list_array[i] = copy.function_list_array[i];
		}
	}
};

#endif // !__DLL_DATA_STRUCTURE_H__
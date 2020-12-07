#include "DllClient.h"

void DllClient::GetDllsFunctionList(DllDataStructure* dll_data_struct)
{
	HINSTANCE hDLL;
	funcListOfFunctions list_of_functions;
	funcNumberOfTests number_of_tests;

	std::wstring w_name(dll_data_struct->dll_name.begin(), dll_data_struct->dll_name.end());

	const wchar_t* libName = w_name.c_str();

	hDLL = LoadLibraryEx(libName, NULL, NULL);   // Handle to DLL

	if (hDLL != NULL) {
		list_of_functions = (funcListOfFunctions)GetProcAddress(hDLL, "ListOfFunctions");
		number_of_tests = (funcNumberOfTests)GetProcAddress(hDLL, "NumberOfTests");

		if (list_of_functions == NULL) {
			// function list not found so return.
			return;
		}

		if (number_of_tests == NULL) {
			// number of tests not found so return.
			return;
		}

		dll_data_struct->dll_instance = hDLL;
		dll_data_struct->function_list_array = list_of_functions();
		dll_data_struct->number_of_functions = number_of_tests();

		dll_data_list.push_back(dll_data_struct);
	}
}

DllClient::~DllClient()
{
	for (DllDataStructure* data : dll_data_list) {
		//delete data->function_list_array;
		FreeLibrary(data->dll_instance);
	}

	dll_data_list.clear();
}

void DllClient::LoadDll(std::string& dir_path)
{
	DirectoryReader dir_read(dir_path);

	for (auto dll_info : dir_read.GetListOfDlls()) {
		auto copy_info = new DllDataStructure(*dll_info);

		GetDllsFunctionList(copy_info);
	}
}
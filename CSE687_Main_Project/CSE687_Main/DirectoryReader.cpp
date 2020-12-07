#include "DirectoryReader.h"

DirectoryReader::DirectoryReader(std::string& dir_path)
{
	if (std::filesystem::exists(dir_path) && std::filesystem::is_directory(dir_path)) {
		for (const auto& entry : std::filesystem::directory_iterator(dir_path)) {
			std::filesystem::path p = entry.path();
			std::filesystem::path e = p.extension();

			if (std::filesystem::is_regular_file(entry) && e == ".dll") {
				auto data_struct = new DllDataStructure();
				data_struct->dll_path = p.string();
				data_struct->dll_name = p.stem().string();
				dll_file_list.push_back(data_struct);
			}
		}
	}
}

DirectoryReader::~DirectoryReader()
{
	dll_file_list.clear();
}

std::vector<DllDataStructure*> DirectoryReader::GetListOfDlls() const
{
	return dll_file_list;
}
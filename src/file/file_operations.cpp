#include "file/file_operations.h"

#include <windows.h>  
#include <cstring>

#include <Strsafe.h>

namespace limo_file
{
	void traverse_by_path(const std::string& i_dir_path, void* i_data,
		const traverse_callback_t& i_item_callback,
		const update_data_callback_t& i_data_callback)
	{
		WIN32_FIND_DATA find_file_data;

		// find out file info of current dif path
		auto dir_spec = i_dir_path + "\\*";
		const auto h_find = FindFirstFile(dir_spec.c_str(), &find_file_data);

		// callback when step into folder
		if (i_data_callback != nullptr)
			i_data_callback(find_file_data, true, i_data);

		if (h_find != INVALID_HANDLE_VALUE)
		{
			// traverse the files under current folder
			while (FindNextFile(h_find, &find_file_data) != 0)
			{
				const auto is_folder = (find_file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
				const auto is_curr_folder = strcmp(find_file_data.cFileName, ".") == 0;
				const auto is_prev_folder = strcmp(find_file_data.cFileName, "..") == 0;

				if (!is_curr_folder && !is_prev_folder)
				{
					// callback when meet a file/folder node
					if (i_item_callback != nullptr)
						i_item_callback(find_file_data, i_data);

					if (is_folder)
					{
						// step into sub folder
						const auto dir_add = i_dir_path + "\\" + find_file_data.cFileName;
						traverse_by_path(dir_add, i_data, i_item_callback, i_data_callback);
					}
				}
			}
		}
		FindClose(h_find);

		// callback when step out of folder
		if (i_data_callback != nullptr)
			i_data_callback(find_file_data, false, i_data);
	}

}

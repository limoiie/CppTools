#pragma once

#include <string>
#include <functional>
#include <windows.h>  

namespace limo_file
{
	/**
	* \brief The parameters of callback are: 1. current file node name; 2. flag indicates if
	* current node is a folder or not and; 3. the data which is used to store some info in each
	* iteration.
	*/
	using traverse_callback_t = std::function<void(WIN32_FIND_DATA&, void*)>;

	/**
	* \brief The parameters of callback are: 1. current file node name; 2. step into or step
	* out of folder; 3. the data which is going to be updated.
	*/
	using update_data_callback_t = std::function<void(WIN32_FIND_DATA&, bool, void*)>;

	/**
	* \brief
	* \param i_dir_path Dir path which we want to traverse through.
	* \param i_data User data which will be updated when step into or step out of folder and be
	* used when meet a file node.
	* \param i_item_callback Callback when meet a file node.
	* \param i_data_callback Callback when step into or step out of folder.
	*/
	void traverse_by_path(const std::string& i_dir_path, void* i_data,
		const traverse_callback_t& i_item_callback = nullptr,
		const update_data_callback_t& i_data_callback = nullptr);

}

#include <iostream>
#include <ctime>

#include <windows.h>

#include "file/file_operations.h"

using namespace std;

int main() 
{
	const auto start_time = time(nullptr);

	const auto cb_print = [](WIN32_FIND_DATA& file_data, void*)
	{
		cout << file_data.cFileName << endl;
	};

	limo_file::traverse_by_path("C://", nullptr, cb_print);
	limo_file::traverse_by_path("D://", nullptr, cb_print);
	limo_file::traverse_by_path("E://", nullptr, cb_print);
	limo_file::traverse_by_path("F://", nullptr, cb_print);

	cout << "COST: " << (time(nullptr) - start_time) << endl;

	system("PAUSE");
	return 0;
}
#include "library.hpp"
#include <iostream>

int main() {

	std::cout << "Start of program" << std::endl;

	typedef int(*myfunc)(void);

	JLib::Library MyLibrary("test_dll");
	myfunc MyFunctionExport = MyLibrary.GetExport<myfunc>("MyExportedFunction");

	std::cout << "function returns " << MyFunctionExport() << std::endl;

	while (true) {}

	return 0;
}
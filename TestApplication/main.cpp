#include "library.hpp"
#include <iostream>

class xyz {
public:
	virtual void call(std::string msg) = 0;
};

int main() {

	std::cout << "Start of program" << std::endl;

	typedef int(*myfunc)(void);

	JLib::DLL::Library MyLibrary("test_dll");
	myfunc MyFunctionExport = MyLibrary.getSymbol<myfunc>("MyExportedFunction");

	std::cout << "function returns " << MyFunctionExport() << std::endl;

	xyz* myClassExport = MyLibrary.getSymbol<xyz*>("plugin_export");
	myClassExport->call("hello world from the other side");

	while (true) {}

	return 0;
}
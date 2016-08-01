#include <library.hpp>
#include <string>
#include <iostream>

EXPORT_API int MyExportedFunction(void) {
	return 42*10;
}

class xyz {
public:
	virtual void call(std::string msg) = 0;
};

class xyz_ext : public xyz {
public:
	void call(std::string msg) {
		std::cout << msg << std::endl;
	}

};

EXPORT_API_ALIAS(xyz_ext, plugin_export);

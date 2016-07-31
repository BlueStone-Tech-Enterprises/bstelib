#include "library.hpp"

#ifdef _WIN32
wchar_t * JLib::_WINDOWS_wchar_t(const char* normal) {

	size_t insize = strlen(normal);
	size_t outSize;

	wchar_t *wcstr = new wchar_t[strlen(normal) + 1];
	mbstowcs_s(&outSize, wcstr, insize + 1, normal, insize);

	return wcstr;
}
#endif

JLib::Library::Library(std::string File) {

#ifdef _WIN32
	File += ".dll";
#elif defined __unix__
	File += ".so";
#elif defined __APPLE__
	File += ".dylib";
#endif

#ifdef _WIN32
	wchar_t *wcstr = JLib::_WINDOWS_wchar_t(File.c_str());
	this->Module = JLIB_LIBRARY_OPEN(wcstr);
	delete[] wcstr;
#else
	this->Module = JLIB_LIBRARY_OPEN(File.c_str());
#endif

	if (this->Module == NULL) {
		throw std::exception("Could not load library");
	}
}

JLib::library_export JLib::Library::GetExportRaw(std::string export_name) {

	if (this->Module != NULL) {

		JLib::library_export Export = JLIB_LIBRARY_REQS(this->Module, export_name.c_str());
		if (Export == NULL) {
			throw std::exception( "Could not load export" );
		}
		else {
			return Export;
		}

	}
	return (JLib::library_export)nullptr;
}

JLib::Library::~Library() {
	JLIB_LIBRARY_CLOSE(this->Module);
}

#pragma once

#define EXPORT_API extern "C" __declspec(dllexport)

#ifdef _WIN32
#include <windows.h>
#define JLIB_LIBRARY_OPEN LoadLibrary
#define JLIB_LIBRARY_REQS(x,y) GetProcAddress(x, (LPSTR) y )
#define JLIB_LIBRARY_CLOSE FreeLibrary
#else
#include <dlfcn.h>
#define JLIB_LIBRARY_OPEN(x) dlopen(x, RTLD_LAZY)
#define JLIB_LIBRARY_REQS dlsym
#define JLIB_LIBRARY_CLOSE dlclose
#endif

#ifdef __APPLE__
#define JLIB_LIBRARY_OPEN(x) dlopen(x, RTLD_LAZY)
#endif

#include <string>
#include <exception>

namespace JLib {

#ifdef _WIN32
	typedef HMODULE library_handle;
	typedef FARPROC library_export;
#else
	typedef void* library_handle;
	typedef void* library_export;
#endif

#ifdef _WIN32
	wchar_t * _WINDOWS_wchar_t(const char* normal);
#endif

	class Library {
	public:
		Library(std::string File);
		library_export GetExportRaw(std::string export_name);

		template<typename functype>
		functype GetExport(std::string export_name) {
			return (functype)GetExportRaw(export_name);
		}

		~Library();

	private:
		library_handle Module;
	};



} // namespace JLib
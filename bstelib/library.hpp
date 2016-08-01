#pragma once

#ifdef _WIN32
#include <windows.h>
#define JLIB_LIBRARY_OPEN LoadLibrary
#define JLIB_LIBRARY_REQS(x,y) GetProcAddress(x, (LPSTR) y )
#define JLIB_LIBRARY_CLOSE FreeLibrary
#define EXPORT_INTERNAL __declspec(dllexport)
#else
#include <dlfcn.h>
#define JLIB_LIBRARY_OPEN(x) dlopen(x, RTLD_LAZY)
#define JLIB_LIBRARY_REQS dlsym
#define JLIB_LIBRARY_CLOSE dlclose
#define EXPORT_INTERNAL
#endif

#define EXPORT_API extern "C" EXPORT_INTERNAL
#define EXPORT_API_ALIAS(x,y) EXPORT_API x y; x y

#include <string>
#include <exception>

namespace JLib {

	namespace DLL {
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

		enum Options {
			None,
			AddDecoration
		};

		class Library {
		public:
			Library(std::string File);
			Library(std::string File, Options opt);

			bool hasSymbol(std::string export_name);
			library_export getSymbolRaw(std::string export_name);

			template<typename functype>
			functype getSymbol(std::string export_name) {
				return (functype)getSymbolRaw(export_name);
			}

			~Library();

		private:
			library_handle Module;
		};

	} // namespace DLL

} // namespace JLib
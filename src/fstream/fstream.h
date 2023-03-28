#pragma once

#include <fstream>
#include <string>

namespace vlr {
	class fstream : public std::fstream {
		public:
		// Constructors
#ifdef _WIN32
		// Windows implementation
		fstream(const char* file,
			ios_base::openmode _Mode = ios_base::in | ios_base::out,
			int _Prot = ios_base::_Default_open_prot
		) : fstream(std::string(file), _Mode, _Default_open_prot) {}
		fstream(
			const std::string& file,
			ios_base::openmode _Mode = ios_base::in | ios_base::out,
			int _Prot = ios_base::_Default_open_prot
		) : std::fstream(file, _Mode, _Prot) {}
#else
		// TODO: Linux implementation

#endif
		// Operators
		// fstream& operator=(std::fstream&& other);

		private:

	};
} // namespace vlr
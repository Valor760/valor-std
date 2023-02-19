#pragma once

#include <string>


namespace vlr {
	class string : public std::string {
		public:
			// Call base class constructors
			string() : std::string() {}
			string(std::string&& other) : std::string(other) {}
			string(std::string& other) : std::string(other) {}
			string(const char* s) : std::string(s) {}

			// Helper functions
			string& getInstance();

			// Replace functions
			// TODO: make a doc and export to api
			string& replace(const std::string& what, const std::string& with, const size_t& n = 1);
	};
} // namespace vlr
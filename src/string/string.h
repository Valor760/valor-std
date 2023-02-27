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
			string* getInstance();

			// Replace functions
			// TODO: make a doc and export to api
			string& replace(const std::string& what, const std::string& with, const size_t& n = 1);

			// to_lower functions
			string& to_lower();

			// contains functions (will be standard in C++23)
			bool contains(const std::string& str);
			bool contains(const char& ch);
	};
} // namespace vlr
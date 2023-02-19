#include "string.h"

#include <stdexcept>


namespace vlr {
	string& string::replace(const std::string& what, const std::string& with, const size_t& n) {
		if(n < 1) {
			throw std::runtime_error("Number of replacements (n) cannot be less than 1!");
		}

		size_t count = 0;
		size_t pos = 0;
		while(count < n) {
			pos = this->find(what, pos);
			if(pos == this->npos) break;

			std::string::replace(pos, what.length(), with);
			count++;
		}
		return *this;
	}

	string& string::replace(const char& what, const std::string& with, const size_t& n) {
		return replace(std::string(&what), with, n);
	}
	string& string::replace(const std::string& what, const char& with, const size_t& n) {
		return replace(what, std::string(&with), n);
	}
	string& string::replace(const char& what, const char& with, const size_t& n) {
		return replace(std::string(&what), std::string(&with), n);
	}
} // namespace vlr
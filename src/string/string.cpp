#include "string.h"

#include <stdexcept>
#include <algorithm>


namespace vlr {
	// std::string doesn't have a constructor for char, so only str-str overload
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
			pos += with.length();
		}
		return *this;
	}

	string* string::getInstance() {
		return this;
	}

	string& string::to_lower() {
		std::transform(this->begin(), this->end(), this->begin(), [](unsigned char c) { return tolower(c); } );
		return *this;
	}

	bool string::contains(const std::string& str) {
		if(this->find(str) == this->npos) {
			return false;
		}
		return true;
	}

	bool string::contains(const char& ch) {
		if(this->find(ch) == this->npos) {
			return false;
		}
		return true;
	}
} // namespace vlr
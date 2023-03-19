#include "xml.h"

#include <fstream>


namespace vlr {

void trim_str(std::string& str) {
	const std::string chars_to_remove = " \n\r\t";

	// Trim from the left
	str.erase(0, str.find_first_not_of(chars_to_remove));

	// Trim from right
	str.erase(str.find_last_not_of(chars_to_remove) + 1);
}

XMLNode* XMLParser::getRoot() {
	if(m_RootNode == nullptr) {
		try {
			parseXML();
		} catch(std::exception& e) {
			return nullptr;
		}
	}
	return m_RootNode.get();
}

void XMLParser::parseXML() {
	if(m_FilePath.empty()) {
		throw std::runtime_error("No filepath provided!");
	}

	std::fstream file(m_FilePath);
	if(!file.is_open()) {
		throw std::runtime_error("Failed to open file -> " + m_FilePath);
	}

	// Actual parsing
	std::string line = "";
	std::vector<std::string> parsed_nodes = {};
	while(std::getline(file, line)) {
		trim_str(line);
		// It is possible, that xml is not formated, so each node is not on it's line
		// So, we need to parse each character
		for(size_t i = 0; i < line.length(); i++) {

			// Parse open tag
			if(line[i] == '<') {

				// Find closing tag
				size_t close_tag_pos = line.find_first_of('>', i);
				if(line.substr(i, close_tag_pos - i).find('<') != std::string::npos || close_tag_pos == std::string::npos) {
					throw std::runtime_error("ERROR: No closing bracket found between " + std::to_string(i) + " and " + std::to_string(close_tag_pos));
				}

				// Check for xml prolog
				if(line[i + 1] == '?' && line[close_tag_pos - 1] == '?') {
					// TODO: Decide whether use std::wstring or std::string based on prolog
					i = close_tag_pos;
				}

				if(line[i + 1] == '/') {
					std::string end_tag = line.substr(i + 1, close_tag_pos - i);
					trim_str(end_tag);

					// XML has strict hierarchy, so the last parsed open tag
					// should correspond to the first close tag
					if(end_tag == parsed_nodes.back()) {
						parsed_nodes.pop_back();
						i = close_tag_pos;
					}
					else {
						throw std::runtime_error("ERROR: last parsed tag doesn't correspond to the close tag: " + end_tag);
					}
				}
			}
		}
	}
}

} // namespace vlr
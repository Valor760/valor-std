#include "xml.h"

#include <fstream>


namespace vlr {

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
	while(std::getline(file, line)) {
		// It is possible, that xml is not formated, so each node is not on it's line
		// So, we need to parse each character
		for(size_t i = 0; i < line.length(); i++) {

			// Parse open tag
			if(line[i] == '<') {

				// Find closing tag
				size_t close_tag_pos = line.find_first_of('>', i);

				// Check for xml prolog
				if(line[i + 1] == '?') {
					
				}
			}
		}
	}

}

} // namespace vlr
#include "xml.h"

#include <fstream>
#include <iostream>


namespace vlr {

void trim_str(std::string& str, const std::string& chars_to_remove = " \n\r\t") {
	// Trim from the left
	str.erase(0, str.find_first_not_of(chars_to_remove));

	// Trim from right
	str.erase(str.find_last_not_of(chars_to_remove) + 1);
}

std::unordered_map<std::string, std::string> split_attributes(std::string str) {
	std::unordered_map<std::string, std::string> attribute_map = {};

	for(size_t pos = 0; pos < str.length(); pos++) {
		size_t eq_sign_pos = str.find('=', pos);

		if(eq_sign_pos == std::string::npos) {
			// throw std::runtime_error("ERROR: No '=' found and string hasn't ended!");
			break;
		}

		std::string attr = str.substr(pos, eq_sign_pos - pos - 1);
		trim_str(attr);

		size_t value_start_pos = str.find('\"', eq_sign_pos);
		size_t value_end_pos   = str.find('\"', value_start_pos + 1);
		std::string value      = str.substr(value_start_pos, value_end_pos - value_start_pos - 1);
		
		attribute_map[attr] = value;

		pos = value_end_pos;
	}

	return attribute_map;
}

// std::unordered_map<std::string, std::string> parse_attributes(std::string str) {
// 	std::unordered_map<std::string, std::string> attributes = {};

// 	auto split_tokens = split_str(str, "=");
// 	if(split_tokens.size() % 2 != 0) {
// 		throw std::runtime_error("ERROR: Wrong number of attributes(should be even)");
// 	}

// 	for(int i = 0; i < split_tokens.size(); i += 2) {
// 		std::string key = split_tokens[i];
// 		std::string value = split_tokens[i + 1];

// 		if(attributes.contains(key)) {
// 			throw std::runtime_error("ERROR: Attribute " + key + " already present in tag!");
// 		}

// 		trim_str(key);
// 		// Double trim value. First to remove any spaces, then to remove ""
// 		trim_str(value);
// 		trim_str(value, "\"");

// 		attributes[key] = value;
// 	}

// 	return attributes;
// }

XMLNode* XMLParser::getRoot() {
	if(m_RootNode == nullptr) {
		parseXML();
		// try {
		// 	parseXML();
		// } catch(std::exception& e) {
		// 	std::cout << e.what() << "\n";
		// 	return nullptr;
		// }
	}
	return m_RootNode;
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
	// std::vector<std::unique_ptr<XMLNode>> parsed_nodes = {};
	std::vector<XMLNode*> parsed_nodes = {};
	/*
		FIXME: XML format allows for opening/closing bracket to be on different lines.
		Eventually, I will come up to the method of reading the whole file into one line
		of string, which will be parsed
	*/
	while(std::getline(file, line)) {
		trim_str(line);
		// It is possible, that xml is not formated, so each node is not on it's line
		// So, we need to parse each character
		for(size_t i = 0; i < line.length(); i++) {
			
			// FIXME: Add xml comments handling
			// Parse open tag
			if(line[i] == '<') {
				// Increment i to get rid of +-1 in parsing of next character
				i++;

				// Find closing bracket
				size_t close_tag_pos = line.find_first_of('>', i);
				if(line.substr(i, close_tag_pos - i).find('<') != std::string::npos || close_tag_pos == std::string::npos) {
					throw std::runtime_error("ERROR: No closing bracket found between " + std::to_string(i) + " and " + std::to_string(close_tag_pos));
				}

				// Check for xml prolog
				if(line[i] == '?' && line[close_tag_pos - 1] == '?') {
					// TODO: Decide whether use std::wstring or std::string based on prolog
					i = close_tag_pos;
				}
				// Closing tag
				else if(line[i] == '/') {
					i++;
					std::string end_tag = line.substr(i, close_tag_pos - i);
					trim_str(end_tag);

					// XML has strict hierarchy, so the last parsed open tag
					// should correspond to the first close tag
					if(end_tag == parsed_nodes.back()->m_NodeName) {
						parsed_nodes.pop_back();
						i = close_tag_pos;
					}
					else {
						throw std::runtime_error("ERROR: last parsed tag doesn't correspond to the closing tag: " + end_tag);
					}
				}
				// If none of the above then it is an opening tag
				else {
					std::string tag_str = line.substr(i, close_tag_pos - i);
					// FIXME: Is it necessary to trim?
					trim_str(tag_str);
					// FIXME: It splits 'another="data 2"' into two parts. Need to handle carefully
					auto tokens = split_str(tag_str, " ");

					// No tags for current node
					if(!tokens.empty()) {
						// First token is node name
						XMLNode* node = new XMLNode(tokens[0]);
						if(m_RootNode == nullptr) {
							m_RootNode = node;
							parsed_nodes.push_back(m_RootNode);
						}
						else {
							parsed_nodes.back()->addChild(node);
							parsed_nodes.push_back(node);
						}

						for(int i = 1; i < tokens.size(); i++) {
							auto attribute_map = parse_attributes(tokens[i]);
							for(auto [key, val] : attribute_map) {
								parsed_nodes.back()->addAttribute(key, val);
							}
						}
					}
					i = close_tag_pos;
				}
			}
			else {
				size_t new_tag_pos = line.find('<', i);
				std::string data = line.substr(i, new_tag_pos - i - 1);
				parsed_nodes.back()->m_Data += data;
				i += data.length();
			}
		}
	}
}

/*
*
*	XMLNode Stuff
*
*/

void XMLNode::addChild(XMLNode* child) {
	m_Children.emplace_back(child);
}

void XMLNode::addAttribute(const std::string& key, const std::string& value) {
	if(m_NodeAttributes.contains(key)) {
		throw std::runtime_error("ERROR: Attribute " + key + " already present in tag!");
	}
	m_NodeAttributes[key] = value;
}

XMLNode* XMLNode::getChild(const std::string& child_name) {
	if(this == nullptr) {
		return nullptr;
	}

	for(auto child : m_Children) {
		if(child->m_NodeName == child_name) {
			return child;
		}
	}
	return nullptr;
}

std::string XMLNode::getData() {
	return m_Data;
}

} // namespace vlr
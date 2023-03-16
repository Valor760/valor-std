#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>


namespace vlr {

// TODO: Move node class to cpp file as it is not required to be in public API
class XMLNode {
	private:
		XMLNode(const std::string& name) : m_NodeName(name) {}

		void addChild(const XMLNode& child);
		XMLNode& getChild(const std::string& child_name);
		void addAttribute(const std::string& attribute, const std::string& value);


	private:
		const std::string m_NodeName;
		std::string m_Data = "";
		std::vector<XMLNode> m_Children = {};
		std::unordered_map<std::string, std::string> m_NodeAttributes = {};

		friend class XMLParser;
};

class XMLParser {
	public:
		XMLParser(const std::string& filepath) : m_FilePath(filepath) {}

		XMLNode* getRoot();


	private:
		void parseXML();


	private:
		const std::string m_FilePath;
		std::unique_ptr<XMLNode> m_RootNode = nullptr;
};

} // namespace vlr
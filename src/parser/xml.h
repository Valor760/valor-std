#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>


namespace vlr {

// TODO: Move node class to cpp file as it is not required to be in public API
class XMLNode {
	public:
		XMLNode(const std::string& name) : m_NodeName(name) {}

		std::string getData();
		std::shared_ptr<XMLNode> getChild(const std::string& child_name);


	private:
		void addChild(std::shared_ptr<XMLNode> child);
		void addAttribute(const std::string& , const std::string& value);


	private:
		const std::string m_NodeName;
		std::string m_Data = "";
		std::unordered_map<std::string, std::string> m_NodeAttributes = {};
		std::vector<std::shared_ptr<XMLNode>> m_Children = {};

		friend class XMLParser;
};

class XMLParser {
	public:
		XMLParser(const std::string& filepath) : m_FilePath(filepath) {}

		std::shared_ptr<XMLNode> getRoot();


	private:
		void parseXML();


	private:
		const std::string m_FilePath;
		std::shared_ptr<XMLNode> m_RootNode = nullptr;
};

} // namespace vlr
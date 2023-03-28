#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>


namespace vlr {

// TODO: Move node class to cpp file as it is not required to be in public API
class XMLNode {
	public:
		std::string getData();
		XMLNode* getChild(const std::string& child_name);


	private:
		XMLNode(const std::string& name) : m_NodeName(name) {}
		~XMLNode() {
			for(auto child : m_Children) {
				delete child;
				child = nullptr;
			}
		}

		void addChild(XMLNode* child);
		void addAttribute(const std::string& , const std::string& value);


	private:
		const std::string m_NodeName;
		std::string m_Data = "";
		std::unordered_map<std::string, std::string> m_NodeAttributes = {};
		std::vector<XMLNode*> m_Children = {};

		friend class XMLParser;
};

class XMLParser {
	public:
		XMLParser(const std::string& filepath) : m_FilePath(filepath) {}
		~XMLParser() {
			delete m_RootNode;
			m_RootNode = nullptr;
		}

		XMLNode* getRoot();


	private:
		void parseXML();


	private:
		const std::string m_FilePath;
		XMLNode* m_RootNode = nullptr;
};

} // namespace vlr
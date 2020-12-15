
#include <string>
#include "pugixml/pugixml.hpp"

typedef pugi::xml_document XMLDoc;
typedef pugi::xml_node XMLNode;
typedef pugi::xml_attribute XMLAttr;
typedef pugi::xml_parse_result XMLResult;

#include <iostream>
#include <string>

using namespace std;

//write xml file
int WriteTestXmlFile()
{
	XMLDoc doc;
	XMLNode node_dec = doc.prepend_child(pugi::node_declaration); //xml声明
	node_dec.append_attribute("version").set_value("1.0");
	node_dec.append_attribute("encoding").set_value("utf-8");

	doc.append_child(pugi::node_comment).set_value("这是一条评论");

	XMLNode node = doc.append_child("system_parameter");
	
	XMLNode device_node = node.append_child("device");
	device_node.append_attribute("Policy").set_value("UserControlled");
	device_node.text().set(L"windows 10");

	XMLNode ip_node = node.append_child("ip");
	ip_node.text().set("192.168.0.1");


	/*
	这里需要注意的是，ip节点的内容是一个pcdata类型的节点，这个节点的内容才是ip字符串，所以这里用text()来读写IP节点内容。
	如果要用.value()方法得到ip字符串的话，需要这样用：
	std::wstring ip = ip_node.first_child().value();
	ip_node.first_child().set_value(L"192.168.0.1");

	另外，node.text().set()方法也不错，提供了常用的数据类型写入XML的重载方法：

	// Set text (returns false if object is empty or there is not enough memory)
	bool set(const char_t* rhs);

	// Set text with type conversion (numbers are converted to strings, boolean is converted to "true"/"false")
	bool set(int rhs);
	bool set(unsigned int rhs);
	bool set(long rhs);
	bool set(unsigned long rhs);
	bool set(double rhs);
	bool set(float rhs);
	bool set(bool rhs);

#ifdef PUGIXML_HAS_LONG_LONG
	bool set(long long rhs);
	bool set(unsigned long long rhs);
#endif

	而node.text().as_xxx()方法可以按需要直接从XML文件中读取出指定类型的数据\\

	实际上node.text()返回的是xml_text对象实例，上面的set()和as_xxx()是由xml_text实现的。

	如果IP节点有属性的话，可以遍历属性：
	for (pugi::xml_attribute attr : node.attributes())
	{
		std::cout << " " << attr.name() << "=" << attr.value();
	}
	*/

	doc.save_file("D:\\temp\\pugiTest1.xml");

	return 0;
}

template<typename T>
bool create_attr_node(XMLNode& node, const pugi::char_t* pAttrName, const T& attrVal)
{
	XMLAttr attr = node.append_attribute(pAttrName);
	return (attr && attr.set_value(attrVal));
}

// read xml file
int ReadTestXmlFile()
{
	XMLDoc doc;
	//声明
	if (!doc.load_file("D:\\temp\\pugiTest1.xml", pugi::parse_default, pugi::encoding_utf8))
		return false;

	XMLNode nodeRoot = doc.child("system_parameter");
	XMLNode node1 = nodeRoot.child("device");

	cout << "system_parameter: " << node1.text().get() << endl;

	std::string str = node1.attribute("Policy").value();
	cout << "Policy: " << str << endl;

	node1 = nodeRoot.child("ip");
	str = node1.text().get();
	cout << "IP: " << str << endl;

	return 0;
}

void ReadBookXmlFile()
{
	XMLDoc doc;
	XMLResult result = doc.load_file("D:\\temp\\Book.xml");

	if(!result)
	{
		return ;
	}

	cout << "Load result: " << result.description() << endl;

	XMLNode book = doc.child("catalog").child("book");
	while (book)
	{
		cout << "Book id: " << book.attribute("id").value() << endl;
		cout << "Book edition: " << book.attribute("edition").value() << endl;
		
		for (XMLNode node = book.first_child(); node; node = node.next_sibling())
		{
			cout << "Node Name: " << node.name() << endl;

			XMLAttr attr = node.first_attribute();
			while (attr)
			{
				wcout << attr.name() << ": " << attr.value() << "; ";

				attr = attr.next_attribute();
			}
			cout << endl;

			cout << "Text: " << node.text().as_string() << endl;

			std::string text("");
			for (pugi::xml_node child : node.children())
			{
				if (child.type() == pugi::node_pcdata)
				{
					text += child.value();
				}
			}
			cout << "Text: " << text << endl;
		}
		book = book.next_sibling();
	}
}


void test1()
{
	pugi::xml_document doc;
	
	auto declarationNode = doc.append_child(pugi::node_declaration);
	declarationNode.append_attribute("version") = "1.0";
	declarationNode.append_attribute("encoding") = "ISO-8859-1";
	declarationNode.append_attribute("standalone") = "yes";

	// add node with some name
	pugi::xml_node node = doc.append_child("node");

	// add description node with text child
	pugi::xml_node descr = node.append_child("description");
	descr.append_child(pugi::node_pcdata).set_value("Simple node");

	pugi::xml_node demo = node.append_child("hello");
	demo.append_child(pugi::node_pcdata).set_value("world");

	//insert child param after description
	pugi::xml_node param = node.insert_child_after("param", descr);

	// add attributes to param node
	param.append_attribute("name") = "version";
	param.append_attribute("value") = 1.1;
	param.append_attribute("type") = "float";
	
	doc.print(cout);
	
#if 0
    std::stringstream ss;
    doc->print(ss, "  ");
    std::string str = ss.str();
#endif

#if 0
	Remove child nodes
	You can simply remove all child nodes of a given parent node by specifying the child name:

    // "remove_child" only removes the first found child
    // the return value signals if a child was found
    // removing all childs with a given name:
    while(someParentNode.remove_child("AnOtherNode"));

	When iterating through child nodes you can selectively decide to remove a child:

    for (pugi::xml_node child = someParentNode.first_child(); child; )
    {
        // Get next child node before possibly deleting current child
        pugi::xml_node next = child.next_sibling();
        // Check wether child node shall be deleted
        if (std::string(child.name()) != "AnOtherNode")
        {
            child.parent().remove_child(child);
        }
        child = next;
    }
#endif
}

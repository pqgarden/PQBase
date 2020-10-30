#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <unordered_map>

#include "nlohmann/json.hpp"
using json = nlohmann::json;

using namespace std;

/*
��������д��һ���ṹ��Person���ŵ��������ռ�magic�
Ȼ������������ռ��ﶨ��������������json��ִ��ת��ʱ�͵���������������
д���ǹ̶��ģ�����д���ɡ�ע��from_json��Ҫ��get������[]��
*/

namespace magic {
	struct Person {
		string name;
		int age;
	};

	void to_json(json& j, const Person& p) {
		j = json{ {"Name", p.name }, {"Age", p.age} };
	}

	void from_json(const json& j, Person& p) {
		p.name = j.at("Name").get<string>();
		p.age = j.at("Age").get<int>();
	}
}

class ComplexOne
{
private:
	vector<string> _vecStrs;
	unordered_map<string, magic::Person> _hashNameIndex;
public:
	void AddStr(string str) {
		_vecStrs.push_back(str);
	}
	void AddPair(string strkey, magic::Person p) {
		_hashNameIndex[strkey] = p;
	}

	//��Ԫ, ֮����������Ԫ����Ϊת����Ҫֱ�Ӳ�����Ա������
	friend void to_json(json& j, const ComplexOne& c);
	friend void from_json(const json& j, ComplexOne& c);
};

/*
����������Ԫ��ʵ�֡�
һ�㶼�����ӣ����ṹ����ͬ�ȹ�ģ�ġ�������Ϊjson�Ȿ���ṩ�˴�stlת��json�ķ���������ֱ�ӵ��á�
���ﻹ�漰�����Զ���ṹ��Person��ת������Ϊ�����ṩ��ת����������������Ҳ����ֱ��д����ʼ���б�ȷʵ�Ǻ��á�
*/
void to_json(json& j, const ComplexOne& c)
{
	j = json{{"VecStrs", c._vecStrs}, {"HashNameIndex", c._hashNameIndex}};
}

void from_json(const json& j, ComplexOne& c)
{
	c._vecStrs = j.at("VecStrs").get<vector<string>>();
	c._hashNameIndex = j.at("HashNameIndex").get<unordered_map<string, magic::Person>>();
}

int main()
{
	json myjson;

	//������ͨ��member, key/value��
	myjson["pi"] = 3.14;
	myjson["pass"] = true;
	myjson["region"] = string("Asia");
	myjson["nope"] = nullptr;

	//����һ������
	myjson["vector"] = { 1,2,3 };
	myjson["1st"]["2nd"] = string("object inside");
	myjson["1st"]["3rd"] = 121.3;
	myjson["moreobj"] = { {"obj1", "hello"}, {"obj2", "world"} };

	cout << myjson << endl;	//�Ǹ�ʽ�����json
	cout << setw(4) << myjson << endl; //��ʽ�����json��������setw
	

	//��ȡ����
	//��ʽһ, find������
	auto objJson = myjson.find("region");
	if (objJson != myjson.end())
	{
		auto s = objJson.value();

		cout << "region: " << s << endl;
	}
	
	try
	{
		//��ʽ��, at
		bool pass = myjson.at("pass"); //�����ڻ��� out_of_range�쳣
		cout << "pass: " << pass << endl;

		//��ʽ��, []
		vector<int> v = myjson["vector"]; //�����ڻ��� type_error �쳣
		cout << "vector size: " << v.size() << endl;
	}
	catch (const std::exception& e )
	{
		cout <<  e.what() << endl;
	}

	int n = myjson["1st"]["3rd"];
	double d = myjson["1st"]["3rd"]; //������ʾָ��value������

	cout << "1st-3rd int: " << n << endl;
	cout << "1st-3rd double: " << d << endl;

	//More
	//support STL
	//1.����װ��nάvector
	vector<vector<int>> form;
	form.push_back(vector<int>({1,2,3,4,5}));
	form.push_back(vector<int>({6,7,8,9,10}));

	myjson["2D"] = form;

	auto formR = myjson["2D"].get<vector<vector<int>>>();

	//������json�����һ��2ά���ݣ�Ҳ����һ�������Ƿǳ�������

	//2.֧���Զ���ṹ��
	magic::Person p = {"Peter", 18};
	json j = p;
	cout << j << endl;

	myjson["Magic"] = p;

	auto re = myjson["Magic"].get<magic::Person>();

	cout << "Magic::Person: " << re.name << " " << re.age << endl;

	//3.֧���Զ�����
	ComplexOne one;
	one.AddStr("first");
	one.AddStr("second");
	one.AddPair("who", {"Bob", 19});
	one.AddPair("whom", {"Peter", 20});

	myjson["CanThisWork?"] = one;

	cout << setw(4) << myjson << endl;

	auto rOne = myjson["CanThisWork?"].get<ComplexOne>();

	rOne.AddStr("third");
	rOne.AddPair("whose", {"Tom", 25});

	return 0;
}


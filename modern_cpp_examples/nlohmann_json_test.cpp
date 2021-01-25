#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <unordered_map>

#include "nlohmann/json.hpp"
using json = nlohmann::json;

using namespace std;


/*
I don’t know who is the king of kings.
But I do know nlohmann::json is the data-structure of data-structures
此数据结构一出，简直是惊天地泣鬼神，有如下的好处：
现代风格，代码简洁；
万能型数据结构（装载任何类型的数据，包括自定义数据）；
蕴含OO思想，可以作为OO数据库使用；
*/

/*
这里我们写了一个结构体Person，放到了命名空间magic里，
然后在这个命名空间里定义了两个函数，json在执行转换时就调用这两个函数。
写法是固定的，照着写即可。注意from_json里要用get而不是[]。
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

	//友元, 之所以声明友元是因为转化需要直接操作成员变量。
	friend void to_json(json& j, const ComplexOne& c);
	friend void from_json(const json& j, ComplexOne& c);
};

/*
接下来是友元的实现。
一点都不复杂，跟结构体是同等规模的。这是因为json库本身提供了从stl转到json的方法，可以直接调用。
这里还涉及到了自定义结构体Person的转化，因为我们提供了转化方法，所以这里也可以直接写。初始化列表确实是好用。
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



enum class category { order, cash_carry };
struct Product {
public:
	Product() : id(), price(), name(), cat() {}
	std::string id;
	double price;
	std::string name;
	category cat;
};

NLOHMANN_JSON_SERIALIZE_ENUM(category, { {category::order, "order"}, {category::cash_carry, "cc"} })
inline void to_json(nlohmann::json& j, const Product& p) {
	j = nlohmann::json{ {"id", p.id},
			   {"price", p.price},
			   {"name", p.name},
			   {"category", p.cat} };
}
inline void from_json(const nlohmann::json& j, Product& p) {
	j.at("name").get_to(p.name);
	j.at("id").get_to(p.id);
	j.at("price").get_to(p.price);
	j.at("category").get_to(p.cat);
}

int main()
{
	json myjson;

	//加入普通的member, key/value对
	myjson["pi"] = 3.14;
	myjson["pass"] = true;
	myjson["region"] = string("Asia");
	myjson["nope"] = nullptr;

	//复杂一点的情况
	myjson["vector"] = { 1,2,3 };
	myjson["1st"]["2nd"] = string("object inside");
	myjson["1st"]["3rd"] = 121.3;
	myjson["moreobj"] = { {"obj1", "hello"}, {"obj2", "world"} };

	cout << myjson << endl;	//非格式化输出json
	cout << setw(4) << myjson << endl; //格式化输出json，重载了setw
	

	//获取数据
	//方式一, find迭代器
	auto objJson = myjson.find("region");
	if (objJson != myjson.end())
	{
		auto s = objJson.value();

		cout << "region: " << s << endl;
	}
	
	try
	{
		//方式二, at
		bool pass = myjson.at("pass"); //不存在会抛 out_of_range异常
		cout << "pass: " << pass << endl;

		//方式三, []
		vector<int> v = myjson["vector"]; //不存在会抛 type_error 异常
		cout << "vector size: " << v.size() << endl;
	}
	catch (const std::exception& e )
	{
		cout <<  e.what() << endl;
	}

	int n = myjson["1st"]["3rd"];
	double d = myjson["1st"]["3rd"]; //可以显示指定value的类型

	cout << "1st-3rd int: " << n << endl;
	cout << "1st-3rd double: " << d << endl;

	//More
	//support STL
	//1.可以装载n维vector
	vector<vector<int>> form;
	form.push_back(vector<int>({1,2,3,4,5}));
	form.push_back(vector<int>({6,7,8,9,10}));

	myjson["2D"] = form;

	auto formR = myjson["2D"].get<vector<vector<int>>>();

	//我们往json里放了一个2维数据，也就是一个表，这是非常常见的

	//2.支持自定义结构体
	magic::Person p = {"Peter", 18};
	json j = p;
	cout << j << endl;

	myjson["Magic"] = p;

	auto re = myjson["Magic"].get<magic::Person>();

	cout << "Magic::Person: " << re.name << " " << re.age << endl;

	//3.支持自定义类
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



#if 0
	Product p;
	p.id = "0xff";
	p.price = 22.4;
	p.name = "Product 1";
	p.cat = category::cash_carry;
	
	Json product;
	product["products"] = p;
	std::cout << product.dump() << std::setw(4) << std::endl;

	Json j = Json::parse(R"({"products":{"category":"cc","id":"0xff","name":"Product 1","price":22.4}})");
	Product p1 = j["products"].get<Product>();
	std::cout << "id: " << p1.id << std::endl;
	std::cout << "price: " << p1.price << std::endl;
	std::cout << "name: " << p1.name << std::endl;
#endif
	
	return 0;
}


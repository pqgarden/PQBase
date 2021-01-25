特殊模式字符

|符号 |用途|
| ---- | ---- |
|. 			|任意字符|
|\d			|0-9的数字|
|\w			|A~Z,a~z,0~9,_的任意一个|
|\s			|空格、制表符、换页符等空白字符的任意一个|
|\D,\W,\S	|对应小写字母取反|



字符类

|符号 |用途|
| ---- | ---- |
|[ab12]			|匹配4个字符任意一个|
|[^ab12]		|匹配4个字符之外的任意一个|
|[a-z]			|匹配a~z的任意一个|
|[^a-zA-Z0-9_]	|匹配a-z,A-Z,0-9,_之外的任意一个|


量词

|符号 |用途|
| ---- | ---- |
|`*`			|0到无限次|
|`+`			|1到无限次|
|`?`			|0到1次|
|{int}		|int次|
|{int,}		|int到无限次|
|{min,max}	|大于等于min次，小于等于max次|
|`|`			|表示或的关系|

字符位置

|符号 |用途|
| ---- | ---- |
|^	|行开始|
|$	|行结束|
|\b	|非字符边界|
|\B	|字符边界|

字符位置只是对匹配到的边界做额外的限制，
“done, do, dog”如果用do去匹配，会找到3个，如果用`do\b`去匹配，则只有一个。

反向引用

|符号 |用途|
| ---- | ---- |
|(subpattern)	|创造反向引用|
|(?:subpattern)	|不创造反向引用|

将子表达式匹配到的内容，保存到内存中一个以数字编号的组里
`([ab])\1`会匹配到aa或者bb

转义符号
以下这些字符是特殊字符，如果需要匹配原字符，需要加转义符号
` ^ $ ( ) . * + ? { } [ ] | `
例如，为了匹配`?`，对应的正则表达式是`\?`
但是, 注意，在C++字符串中，\本身是个转义符号，需要用两个`\`代表原有的`\`，正确代码如下所示:

```c++
std::string s ("?");
std::regex e ("\\?");
if(std::regex_match (s,e)) {...}
std::string s2 ("\\");
std::regex e2 ("\\\\");
if(std::regex_match (s2,e2)) {...}
```

常用函数
用于正则表达式匹配的几个函数

`regex_match`:检查字符串与正则表达式是否匹配，返回值是`bool`
`regex_match`例子
```c++
// g++ -std=c++11 main.cpp
#include <iostream>
#include <string>
#include <regex>
int main(int argc, char* argv[])
{
    std::string s ("subject");
    std::regex e ("(.*)(sub)(.*)");
    if (std::regex_match (s,e))
        std::cout << "string matched\n";
}
```

`regex_search`:搜索字符串中匹配的部分。smatch的第一个字符串是匹配到的结果，后面的是()引用的内容。
`regex_search`例子
```c++
#include <iostream>
#include <string>
#include <regex>
int main ()
{
    std::string s ("subject submarine subsequence");
    std::smatch m;
    std::regex e ("\\b(sub)([^ ]*)");//begin by "sub"
    std::cout << "matches and submatches :" << std::endl;
    while (std::regex_search (s,m,e)) {
        for (auto x:m) {
			std::cout << x << " " << std::endl;
		}
        s = m.suffix().str();
    }
    return 0;
}

`regex_replace`:替换字符串中的一部分。
`regex_replace`例子
```c++
#include <iostream>
#include <string>
#include <regex>
int main ()
{
    std::string s ("there is a subsequence in the string\n");
    std::regex e ("\\b(sub)([^ ]*)");//begin by "sub"
    std::cout << std::regex_replace (s,e,"sub-$2");
    return 0;
}
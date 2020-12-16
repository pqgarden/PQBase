### `C++` u8

考虑一个问题，如何获得utf8的字符串？

```c++
#include <boost/locale.hpp>
#include <string>
int main() 
{
    std::string gbk_str = "你好";
    std::string utf8 = boost::locale::conv::to_utf<char>(gbk_str, "GBK");
}
```

在windows环境下的vs20xx中，"你好" 存储在gbk_str中的编码格式是GB2312。所以需要一个转换操作，才能得到utf8字符串。

`C++17`到来后，出现了u8

`std::string utf8 = u8"你好";`

这里注意的一个问题是：数据，和处理数据的程序的一致性。

把字符串送到控制台显示，想要不得到乱码，必须符合控制台当前选择的字符集。

把字符串送到数据库（例如mysql），想要不报错，也必须符合数据库字段中选择的字符集。

对于程序源文件，想要让开发工具正常显示程序文本中的字符，也必须是源文件存储的字符与开发工具当前选定的字符集一致。

`std::wstring str = L"你好";`
str在内存中将以UTF16编码存在，占用3个short的空间。如何在windows下输出到控制台？

```c++
std::wstring str = L"你好";
std::wcout.imbue(std::locale(""));
std::wcout << str << std::endl;
```



必须先让`wcout`切换到当前默认的`locale`，因为当前的操作系统是中文，所以`wcout`知道了应该把国际UNICODE码转为中国本地的GB2312码。

把str通过MySQL API接口发送到数据库，必须先转换成utf8编码。

看来，这些过程还是比较麻烦的。如果现在按照`utf8 everywhere`的思想，让各个子系统全部`utf8`化，这样可以减少很多不必要的错误。

大趋势就是`utf8`化。
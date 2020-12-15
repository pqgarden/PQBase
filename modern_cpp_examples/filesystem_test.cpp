#include <iostream>

#include <filesystem>
namespace fs = std::filesystem;

using namespace std;

int main() 
{
	fs::path str("C:\\Windows");

	//必须先检测目录是否存在才能使用文件入口.
	if (!fs::exists(str))
		return 1;

	//文件入口
	fs::directory_entry entry(str);		

	//这里用了C++11的强枚举类型
	if (entry.status().type() == fs::file_type::directory)	
		cout << "该路径是一个目录" << endl;

	//文件入口容器
	fs::directory_iterator list(str);	
	
	for (auto& it : list)
	{
		//通过文件入口（it）获取path对象，再得到path对象的文件名，将之输出
		cout << it.path().filename() << endl;
	}

	//system("pause");
	return 0;
}

/*
path ：对字符串（路径）进行一些处理，这也是文件系统的基石。
directory_entry ：类如其名，文件入口，这个类才真正接触文件。
directory_iterator ：获取文件系统目录中文件的迭代器容器，其元素为 directory_entry对象（可用于遍历目录）
file_status 类：用于获取和修改文件（或目录）的属性

void copy(const path& from, const path& to) ：目录复制

path absolute(const path& pval, const path& base = current_path()) ：获取相对于base的绝对路径

bool create_directory(const path& pval) ：当目录不存在时创建目录

bool create_directories(const path& pval) ：形如/a/b/c这样的，如果都不存在，创建目录结构

bool exists(const path& pval) ：用于判断path是否存在

uintmax_t file_size(const path& pval) ：返回目录的大小

file_time_type last_write_time(const path& pval) ：返回目录最后修改日期的file_time_type对象

bool remove(const path& pval) ：删除目录

uintmax_t remove_all(const path& pval) ：递归删除目录下所有文件，返回被成功删除的文件个数

void rename(const path& from, const path& to) ：移动文件或者重命名
*/
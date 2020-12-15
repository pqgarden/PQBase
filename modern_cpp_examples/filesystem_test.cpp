#include <iostream>

#include <filesystem>
namespace fs = std::filesystem;

using namespace std;

int main() 
{
	fs::path str("C:\\Windows");

	//�����ȼ��Ŀ¼�Ƿ���ڲ���ʹ���ļ����.
	if (!fs::exists(str))
		return 1;

	//�ļ����
	fs::directory_entry entry(str);		

	//��������C++11��ǿö������
	if (entry.status().type() == fs::file_type::directory)	
		cout << "��·����һ��Ŀ¼" << endl;

	//�ļ��������
	fs::directory_iterator list(str);	
	
	for (auto& it : list)
	{
		//ͨ���ļ���ڣ�it����ȡpath�����ٵõ�path������ļ�������֮���
		cout << it.path().filename() << endl;
	}

	//system("pause");
	return 0;
}

/*
path �����ַ�����·��������һЩ������Ҳ���ļ�ϵͳ�Ļ�ʯ��
directory_entry �������������ļ���ڣ������������Ӵ��ļ���
directory_iterator ����ȡ�ļ�ϵͳĿ¼���ļ��ĵ�������������Ԫ��Ϊ directory_entry���󣨿����ڱ���Ŀ¼��
file_status �ࣺ���ڻ�ȡ���޸��ļ�����Ŀ¼��������

void copy(const path& from, const path& to) ��Ŀ¼����

path absolute(const path& pval, const path& base = current_path()) ����ȡ�����base�ľ���·��

bool create_directory(const path& pval) ����Ŀ¼������ʱ����Ŀ¼

bool create_directories(const path& pval) ������/a/b/c�����ģ�����������ڣ�����Ŀ¼�ṹ

bool exists(const path& pval) �������ж�path�Ƿ����

uintmax_t file_size(const path& pval) ������Ŀ¼�Ĵ�С

file_time_type last_write_time(const path& pval) ������Ŀ¼����޸����ڵ�file_time_type����

bool remove(const path& pval) ��ɾ��Ŀ¼

uintmax_t remove_all(const path& pval) ���ݹ�ɾ��Ŀ¼�������ļ������ر��ɹ�ɾ�����ļ�����

void rename(const path& from, const path& to) ���ƶ��ļ�����������
*/
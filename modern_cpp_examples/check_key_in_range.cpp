template <typename T>
void func(T t)
{
	std::cout << t << std::endl;
}

template<typename T, typename... Args>
void func(T t, Args... args) // recursive variadic function
{
	std::cout << t << std::endl;
	func(args...);
}

template <class T>
void func2(std::initializer_list<T> list)
{
	for (auto elem : list)
	{
		std::cout << elem << std::endl;
	}
}

template <typename T>
bool CheckKeyInRange(const std::string& key, T t)
{
	cout << "Value: " << t << endl;
	return key == t;
}

template<typename T, typename ... Args>
bool CheckKeyInRange(const std::string& key, T t, Args ... args)
{
	if (key != t)
	{
		return CheckKeyInRange(key, args...);
	}
	cout << "Value: " << t <<endl;
	return true;
}


int main()
{
	//std::wcout.imbue(std::locale(""));

	bool a = CheckKeyInRange("5", "1", "3", "5", "7");
	bool b = CheckKeyInRange("5", "1", "3", "9", "7");

	cout << "result: " <<  (a ? "true" : "false") << endl;
	cout << "result: " <<  (b ? "true" : "false") << endl;
	
	return 0;
}
#include <iostream>
using namespace std;

//递归终止函数
void print()
{
   cout << "empty" << endl;
}

//展开函数
template <class T, class... Args>
void print(T head, Args... rest)
{
   cout << "parameter " << head << endl;
   print(rest...);
}


T sum(T first)
{
   return first;
}

template <class T, class... Types>
T sum (T first, Types... rest)
{
    return first + sum<T>(rest...);
}

int main()
{
   print(1,2,3,4);
   
   sum(1,2,3,4,5);
   
   return 0;
}


#include <iostream>
#include <string>

//https://stackoverflow.com/questions/3911536/utf-8-unicode-whats-with-0xc0-and-0x80
int strlen_utf8(const char* s)
{
    int i = 0;
    int j = 0;
    while (s[i])
    {
        if ((s[i] & 0xc0) != 0x80) {
            j++;
        }
            
        i++;
    }
    return j;
}

int main()
{
    std::string ss = u8"你好";
    std::cout << "len: " << strlen_utf8(ss.c_str()) << std::endl;
    return 0;
}
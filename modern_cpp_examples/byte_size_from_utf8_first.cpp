/*
utf-8 变长字节的算法
utf8 不比gb2312 ,后者是两个字节表示一个汉字 ， 而utf8是变长的。那么在utf8中多少个字节才是表示一个汉字呢？！
     在看wesnoth（很不错的回合制游戏）的源码时，特意注意到这一点。找到了分享之：
*/

int byte_size_from_utf8_first(unsigned char ch)
{
    int count = -1;
  
    if ((ch & 0x80) == 0x00)
        //这是用来兼容ASSIC的。也就是说一个标准的ASSIC文件就是UTF-8文件
        count = 1;
    else if ((ch & 0xE0) == 0xC0)
         //0xE0是11100000
         //0xC0是11000000
         //是说前面3个bit 是110 ，那当前的字符和后面的一个字符组成一个汉字
        count = 2;
    else if ((ch & 0xF0) == 0xE0)
         //0xF0是11110000
         //0xE0是11100000
         //是说前面4个bit 是1110 ，那当前的字符和后面的两个字符组成一个汉字
        count = 3;
    else if ((ch & 0xF8) == 0xF0)
        count = 4;
    else if ((ch & 0xFC) == 0xF8)
        count = 5;
    else if ((ch & 0xFE) == 0xFC)
        count = 6;
    else
        throw invalid_utf8_exception(); // Stop on invalid characters
 
    return count;
}

// https://stackoverflow.com/questions/3911536/utf-8-unicode-whats-with-0xc0-and-0x80
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
    std::cout << "len: " << strlen_utf8(ss.c_str()) << std::endl; //输出， len: 2
    return 0;
}

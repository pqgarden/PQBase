#include "pch.h"

#include <string>
#include <fstream>

#include "md5.h"

using namespace PQBase;

TEST(MD5Test, HandleStringInput)
{
	MD5 md5("");
	EXPECT_STRCASEEQ("d41d8cd98f00b204e9800998ecf8427e", md5.toString().c_str());

	md5.update("a");
	EXPECT_STRCASEEQ("0cc175b9c0f1b6a831c399e269772661", md5.toString().c_str());

	//md5 "abc"
	md5.update("bc");
	EXPECT_STRCASEEQ("900150983cd24fb0d6963f7d28e17f72", md5.toString().c_str());

	//md5 "abcdefghijklmnopqrstuvwxyz"
	md5.update("defghijklmnopqrstuvwxyz");
	EXPECT_STRCASEEQ("c3fcd3d76192e4007dfb496cca67e13b", md5.toString().c_str());

	md5.reset();
	md5.update("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");
	EXPECT_STRCASEEQ("d174ab98d277d9f5a5611c2c9f419d9f", md5.toString().c_str());

	md5.reset();
	md5.update("message digest");
	EXPECT_STRCASEEQ("F96B697D7CB7938D525A2F31AAF161D0", md5.toString().c_str());
	 
	md5.reset();
	md5.update(u8"°¡°¡");
	EXPECT_STRCASEEQ("263E11147890EE5FE7297F6878C37F8B", md5.toString().c_str());

#if 0
	md5.reset();
	std::ifstream in("md5_test.txt", std::ios::binary);
	if (in)
	{
		md5.update(in);
		EXPECT_STRCASEEQ("900150983CD24FB0D6963F7D28E17F72", md5.toString().c_str());
	}
#endif


	EXPECT_TRUE(true);
}
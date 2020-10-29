#ifndef MD5_H
#define MD5_H

#include <string>
#include <fstream>

using std::string;
using std::ifstream;

/* Type define*/
typedef unsigned int uint32;
typedef unsigned int size_type; // must be 32bit

namespace PQBase{
	/* MD5 declaration.*/
	class MD5
	{
	public:
		MD5();
		MD5(const void* input, size_type length);
		MD5(const string& str);
		MD5(ifstream& in);

		void update(const void* input, size_type length);
		void update(const string& str);
		void update(ifstream& in);

		const unsigned char* digest();
		string toString();
		void reset();

	private:
		void update(const unsigned char* input, size_type length);
		void final();
		void transform(const unsigned char block[64]);
		void encode(const uint32* input, unsigned char* output, size_type length);
		void decode(const unsigned char* input, uint32* output, size_type length);
		string bytesToHexString(const unsigned char* input, size_type length);

		/* class uncopyable*/
		MD5(const MD5&) = delete;
		MD5& operator=(const MD5&) = delete;

	private:
		uint32 _state[4];	/* state (ABCD)*/
		uint32 _count[2];	/* number of bits, modulo 2^64 (low-order word first)*/
		unsigned char _buffer[64];	/* input buffer*/
		unsigned char _digest[16];	/* message digest*/
		bool _finished;		/* calculate finished ?*/

		static const unsigned char PADDING[64];	/* padding for calculate*/
		static const char HEX[16];
		enum { BUFFER_SIZE = 1024 };
	};
} //namespace

#endif /*MD5_H*/

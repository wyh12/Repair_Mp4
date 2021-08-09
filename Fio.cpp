#include "Fio.h"

File::File(std::string& file) throw(std::string):
	fp(nullptr)
{
	errno_t err = fopen_s(&fp, file.c_str(), "ab+");
	if (err != NULL) {
		throw("error open\n");
	}
	fseek(fp, 0, SEEK_END);
	fileSize = ftell(fp);
	fseek(fp, 0, SEEK_SET);
}

File::~File()
{
	close();
}

size_t File::read_short()
{
	char val[2] = {};
	read(val, 2);
		
	return (val[0] << 8) + val[1];
}

uint32_t File::read_int()
{
	uint32_t value = 0;
	size_t n =  fread(&value, sizeof(value), 1, fp) ;

	const uint8_t* p = reinterpret_cast<const uint8_t*>(&value);
	return ((uint32_t(p[0]) << 24) | (uint32_t(p[1]) << 16) | (uint32_t(p[2]) << 8) | uint32_t(p[3]));
}

int64_t File::read_int64()
{
	uint64_t value = 0;
	size_t n = fread(&value, sizeof(value), 1, fp);
	
	const uint8_t* p = reinterpret_cast<const uint8_t*>(&value);
	return ((uint64_t(p[0]) << 56) | (uint64_t(p[1]) << 48) | (uint64_t(p[2]) << 40) | (uint64_t(p[3]) << 32)
		| (uint64_t(p[4]) << 24) | (uint64_t(p[5]) << 16) | (uint64_t(p[6]) << 8) | uint64_t(p[7]));
}

size_t File::read(char* data, size_t length)
{
	return fread_s(data, length, 1, length, fp);
}

int File::IsEnd()
{
	// 没有使用feof，feof在指针达到文件尾再读取一次才能触发。
	return fileSize <= ftell(fp);
}






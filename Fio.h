#pragma once
#include <cstdio>
#include <string>
class File
{
public:
	File(std::string& file) throw(std::string);
	~File();
	//  read 
	size_t		read_short();
	uint32_t		read_int();
	int64_t		read_int64();
	size_t	read(char* data, size_t length);
	

	// write



	// close
	inline void close() {
		if (fp) 
			fclose(fp);	
	}

	// 限制文件小于4G
	inline int64_t Pos() {
		return ftell(fp);
	}

	// seek
	int64_t Seek(int64_t offset) {
		if (offset <= fileSize - ftell(fp)) {
			return fseek(fp, offset, SEEK_CUR);
		}
		return -1;
	}

	// end
	int IsEnd();


private:
	FILE*		fp;
	int64_t		fileSize;
};
#pragma once
#include <iostream>

#include "Fio.h"
typedef struct SampleTable {
	uint64_t	offset;   // 文件中位置
	uint64_t	size;	// sample 大小
	bool		keyFrame;
	uint32_t	delta;   // sample	持续时长
};

class Track
{
public:
	Track(File& fp);
};


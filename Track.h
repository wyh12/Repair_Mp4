#pragma once
#include <iostream>

#include "Fio.h"
typedef struct SampleTable {
	uint64_t	offset;   // �ļ���λ��
	uint64_t	size;	// sample ��С
	bool		keyFrame;
	uint32_t	delta;   // sample	����ʱ��
};

class Track
{
public:
	Track(File& fp);
};


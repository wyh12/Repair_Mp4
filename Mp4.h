#pragma once
#include "Atom.h"
class Mp4
{
public:
	Mp4(std::string filePath);
	int Open(std::string filePath);
protected:
private:
	std::vector<Atom*>  atomSet;
	File*  fp;
};


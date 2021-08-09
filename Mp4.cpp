#include "Mp4.h"
#include <iostream>

Mp4::Mp4(std::string filePath) :
	fp(nullptr)
{
	if (Open(filePath) < 0) {
		throw("error open");
	}
}

int Mp4::Open(std::string filePath)
{
	if (fp)
		return 0;

	try {
		fp = new File(filePath);
		do {
			Atom* atom = new Atom();
			atom->Parser(*fp);
			atomSet.push_back(atom);
		} while (!fp->IsEnd());
	}
	catch (std::string& err) {
		std::cerr << err << std::endl;
		return -1;
	}

	return 0;
}

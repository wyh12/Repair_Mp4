#include "Atom.h"
#include <iostream>

int Atom::ParseHeader(File& file)
{
	start = file.Pos();
	content_start = start + 8;
	atom_size = file.read_int();
	if (atom_size < 0) {
		return -1;
	}

	file.read(boxType, 4);
	// large size
	if (atom_size == 0) {
		atom_size = file.read_int64();
		content_start += 8;
		BoxSize16 = true;
	}
	return 0;
}

bool Atom::IsPartentBox(const char* name)
{
	auto pair = boxMap.find(name);
	if (pair == boxMap.end()) {
		std::cout << "error find " << name << std::endl;
		return false;
	}
	return   know_atom[pair->second].type == ATOMTYPE::PARENT_ATOM;
}

Atom* Atom::FindAtomName(std::string& boxName) const
{
	for (auto iter : childAtom) {
		
		if (strcmp(iter->boxType, boxName.c_str()) == 0) {
			return iter;
		}

		Atom* box = iter->FindAtomName(boxName);
		if (box)
			return box;
	}

	return nullptr;
}



Atom::~Atom()
{
	for (auto var : childAtom)
	{
		delete(var);
	}
	childAtom.clear();
}

int Atom::Parser(File& file)
{
	if (ParseHeader(file) < 0)
		return -1;

	
	std::cout << "file end " << file.IsEnd() << " pos " << file.Pos() << " type " << boxType << std::endl;
	size_t ret = 0;
	if (IsPartentBox(boxType) && strcmp(boxType, "udta") != 0) {
		while (file.Pos() < start + atom_size) {
			Atom* atom = new Atom;
			atom->Parser(file);
			childAtom.push_back(atom);
		}
	}
	else {
		int64_t readSize = (BoxSize16 ? atom_size - 16 : atom_size - 8);
		// mdat 数据太大，不做存储  // udat 暂时也跳过
		if (strcmp(boxType, "mdat") == 0 || strcmp(boxType, "udta") == 0) {
			ret = file.Seek(readSize);
		}
		else {
			content_data = new char[readSize];
			ret = file.read(content_data, readSize);
		}
	}
	
	return 0;
}


Atom::Atom(uint64_t _start, uint64_t _content_start, uint64_t _atom_size) :
	start(_start),
	content_start(_content_start),
	atom_size(_atom_size),
	content_data(nullptr),
	BoxSize16(false)
{
	memset(boxType,0,5);
	
	for (int i(0); i < 30; i++) {
		boxMap.insert(std::make_pair(know_atom[i].atom_name, i));
	}
}


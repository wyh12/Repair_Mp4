#pragma once
#include <string>
#include <vector>
#include <map>
#include "Fio.h"
extern "C" {
#include <stdio.h>
}

enum class ATOMTYPE :std::uint32_t {
	PARENT_ATOM = 0, //container atom
	SIMPLE_PARENT_ATOM = 1,
	DUAL_STATE_ATOM = 2, //acts as both parent (contains other atoms) & child (carries data)
	CHILD_ATOM = 3, //atom that does NOT contain any children
	UNKNOWN_ATOM_TYPE = 4
};

typedef struct ATOM_BODY {
	const char* atom_name;
	const char* atom_partent[5];
	ATOMTYPE	type;
};



const ATOM_BODY know_atom[] = {
	{"ftyp",{"file_level"},ATOMTYPE::CHILD_ATOM},
	{"free",{"file_level"},ATOMTYPE::CHILD_ATOM},
	{"mdat",{"file_level"},ATOMTYPE::CHILD_ATOM},
	{"moov",{"file_level"},ATOMTYPE::PARENT_ATOM},
	{"mvhd",{"moov"},ATOMTYPE::CHILD_ATOM},
	{"trak",{"moov"},ATOMTYPE::PARENT_ATOM},
	{"tkhd",{"trak"},ATOMTYPE::CHILD_ATOM},
	{"edts",{"trak"},ATOMTYPE::PARENT_ATOM},
	{"elst",{"edts"},ATOMTYPE::CHILD_ATOM},
	{"mdia",{"trak"},ATOMTYPE::PARENT_ATOM},
	{"mdhd",{"mdia"},ATOMTYPE::CHILD_ATOM},
	{"hdlr",{"mdia"},ATOMTYPE::CHILD_ATOM},
	{"minf",{"mdia"},ATOMTYPE::PARENT_ATOM},
	{"vmhd",{"minf"},ATOMTYPE::CHILD_ATOM},
	{"dinf",{"minf"},ATOMTYPE::PARENT_ATOM},
	{"dref",{"dinf"},ATOMTYPE::CHILD_ATOM},
	{"url",{"dref"},ATOMTYPE::CHILD_ATOM},
	{"stbl",{"minf"},ATOMTYPE::PARENT_ATOM},
	{"stsd",{"stbl"},ATOMTYPE::DUAL_STATE_ATOM},
	{"avc1",{"stsd"},ATOMTYPE::DUAL_STATE_ATOM},
	{"avcC",{"avc1"},ATOMTYPE::CHILD_ATOM},
	{"stts",{"stbl"},ATOMTYPE::CHILD_ATOM},
	{"stss",{"stbl"},ATOMTYPE::CHILD_ATOM},
	{"stsc",{"stbl"},ATOMTYPE::CHILD_ATOM},
	{"stsz",{"stbl"},ATOMTYPE::CHILD_ATOM},
	{"stco",{"stbl"},ATOMTYPE::CHILD_ATOM},
	{"udta",{"moov"},ATOMTYPE::PARENT_ATOM},
	{"meta",{"udat"},ATOMTYPE::DUAL_STATE_ATOM},
	{"hdlr",{"meta"},ATOMTYPE::CHILD_ATOM},
	{"ilst",{"meta"},ATOMTYPE::PARENT_ATOM}
};

class Atom
{
public:
	Atom():Atom(0,0,0){}
	~Atom();
	int Parser(File& file);
protected:
	Atom(uint64_t _start, uint64_t _content_start, uint64_t _atom_size);

	// box文件头读取解析
	int ParseHeader(File& file);
	
	bool IsPartentBox(const char* name);

	Atom* FindAtomName(std::string& boxName) const;
private:
	// 数据域
	uint64_t	start;
	uint64_t	content_start;
	int64_t		atom_size;			//当前box大小 
	char		boxType[5];
	char*		content_data;		//存储当前box的数据
	bool		BoxSize16;
	std::vector<Atom*>		childAtom;
	std::map<std::string, int>	boxMap;
};


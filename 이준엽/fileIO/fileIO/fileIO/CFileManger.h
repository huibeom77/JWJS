#pragma once
#include <fstream>
#include <list>
#include "pch.h"

struct WORD_INFO
{
	string name;
	int count;
};

class CFileManger
{
private:
	ifstream* readFile; 
	list< WORD_INFO*> wordInfo;
public:
	CFileManger();
	~CFileManger();
	int GetCountWordByText(const string text);
	int GetWordByOneLineText(const string text);
	int Run();
	int fileOpen(const char* filePath);
	int TextSortByWord();
	void streamReset();
	void CollectDataByText(string text);
};



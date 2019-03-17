#include "pch.h"
#include "CFileManger.h"




CFileManger::CFileManger()
{

}


CFileManger::~CFileManger()
{
	readFile->close();
}




int CFileManger::Run()
{
#define TotalFileCount 10
	int currentFileCount = 1;
	const char** File;
	const char* currentFile;
	File = new const char*[currentFileCount];
	File[0] = "../test.txt";
	

	while (1)
	{
		cout << "파일을 선택해주세요" << endl;
		for (int i = 0; i < currentFileCount; ++i)
			cout << i + 1 << " :" << File[i] << " " << endl;
		int iChoice = 0;
		cin >> iChoice;
		if (iChoice <= currentFileCount && iChoice > 0)
			fileOpen(File[iChoice - 1]);
		else
			cout << " 다시 입력해주세요" << endl;
	}

	return 1;
}

struct LISTnumber_sort
{
	bool operator() (WORD_INFO*  first, WORD_INFO* second) const
	{
		
		if (first->count < second->count)
			return true;
		else
			return false; 

	}
};

struct LISTname_sort
{
	bool operator() (WORD_INFO*  first, WORD_INFO* second) const
	{

		if (first->name < second->name)
			return true;
		else
			return false;

	}
};




int CFileManger::fileOpen(const char* filePath)
{
	system("cls");
	readFile = new ifstream;
	readFile->open(filePath);

	char cText[1000];
	int iTotalWordCount = 0;
	if (!readFile->fail())
	{
		cout << "파일 로드 성공" << endl;
		while (!readFile->eof())
		{
			string sText;
			readFile->getline(cText, 1000);
			
			cout << cText << endl;	
		}
		
		TextSortByWord();

		return 1;
	}
	else
	{
		cout << "파일 로드 실패... 경로를 확인해 주세요" << endl;
		return 0;
	}
}
enum sortBase
{
	_Name = 1,
	_Count,
};
int CFileManger::TextSortByWord()
{
	int iChoice;
	cout << endl << endl;
	cout << "로드한 파일의 단어를 어떠한 방법으로 정렬하시겠습니까?" << endl;
	cout << "1. 가나다 정렬   2. 갯수 정렬" << endl;
	cin >> iChoice;


	streamReset();

	cout << "정렬 중 입니다...." << endl;

	char cText[1000];
	
	while (!readFile->eof())
	{
		string sText;
		readFile->getline(cText, 1000);
		sText = cText;
		GetWordByOneLineText(sText);
	}
	switch (iChoice)
	{
	case _Name:
		wordInfo.sort(LISTname_sort());
		break;
	case _Count:
		wordInfo.sort(LISTnumber_sort());
		break;
	}
	
	system("cls");
	for (list<WORD_INFO*>::iterator iter = wordInfo.begin(); iter != wordInfo.end(); ++iter)
	{
		cout << " " << (*iter)->count << " : " << '\t';
		cout << (*iter)->name << endl;
	}
	return 0;
}

void CFileManger::streamReset()
{
	readFile->clear();
	readFile->seekg(0L, ios::beg);
}


void CFileManger::CollectDataByText(const string text)
{

	bool bExist = false;
	
	for (list<WORD_INFO*>::iterator iter = wordInfo.begin(); iter != wordInfo.end(); ++iter)
	{
		if ((*iter)->name == text)
		{
			(*iter)->count++;
			bExist = true;
		}
	}
	if (!bExist)
	{
		WORD_INFO* info = new WORD_INFO;
		info->name = text;
		info->count = 1;
		wordInfo.push_back(info);
	}
}

int CFileManger::GetCountWordByText(string text)
{
	int iBuffer = 0;
	int Word = 0;

	if (text[0] != ' ' && text[0] != NULL)		
		Word++;

	while (1)
	{

		if (text[iBuffer] == NULL)
			break;
		if (text[iBuffer] == ' ')				    
			if (text[iBuffer + 1] != NULL && text[iBuffer + 1] != ' ')
				Word++;	
		iBuffer++;
	}
	iBuffer = 0;

	
	return Word;
}

int CFileManger::GetWordByOneLineText(const string text)
{
	int iBuffer = 0;
	string sWord;
	bool bSignOfCorrection = false;
	bool bNextSignOfCorrection = false;

	

	while (1)
	{
		if (text[iBuffer] == NULL)
			break;

		bSignOfCorrection = false;
		bNextSignOfCorrection = false;
		if (text[iBuffer] == ' ' ||
			text[iBuffer] == '.' ||
			text[iBuffer] == '"' ||
			text[iBuffer] == ',' ||
			text[iBuffer] == '!' ||
			text[iBuffer] == '?' ||
			text[iBuffer] == '\''||
			text[iBuffer] == '~' ||
			text[iBuffer] == '…'||
			text[iBuffer] == '，'||
			text[iBuffer] == '·'||
			text[iBuffer] == '！')
			bSignOfCorrection = true;
		else 
			sWord.push_back(text[iBuffer]);
			
		if (text[iBuffer + 1] == ' ' ||
			text[iBuffer + 1] == '.' ||
			text[iBuffer + 1] == '"' ||
			text[iBuffer + 1] == ',' ||
			text[iBuffer + 1] == '!' ||
			text[iBuffer + 1] == '?' ||
			text[iBuffer + 1] == '\''||
			text[iBuffer + 1] == '~' ||
			text[iBuffer + 1] == '…'||
			text[iBuffer + 1] == '，'||
			text[iBuffer + 1] == '·'||
			text[iBuffer + 1] == '！')
			bNextSignOfCorrection = true;

		if (bSignOfCorrection)
			sWord.erase();
		else if (bNextSignOfCorrection || text[iBuffer + 1] == NULL)
				CollectDataByText(sWord);
		

		iBuffer++;
		
		
	}


	return 0;
}

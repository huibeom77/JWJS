

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int GetWordByText(string text);
int fileManage();
int fileOpen(const char* filePath);
void systemPause();

int main()
{
	fileManage();
	systemPause();
	return 0;
}

int fileManage()
{
	if (fileOpen("../test.txt"))
		return 1;
	else
		return 0;
}

int fileOpen(const char* filePath)
{
	ifstream readFile(filePath);

	char cText[1000];
	int iTotalWordCount = 0;
	if (!readFile.fail())
	{
		cout << "파일 로드 성공" << endl;
		while (!readFile.eof())
		{
			string sText;

			readFile.getline(cText, 1000);
			cout << cText << endl;
			sText = cText;
			iTotalWordCount += GetWordByText(sText);
		}
		cout << "단어의 총 갯수 :" << iTotalWordCount << endl;
		return 1;
	}
	else
		cout << "파일 로드 실패... 경로를 확인해 주세요" << endl;
		return 0;


	readFile.close();
}

int GetWordByText(string text)
{
	int iBuffer = 0;
	int Word = 0;

	if (text[0] != ' ' && text[0] != NULL)		//  텍스트의 첫번째 글자가 존재할때
		Word++;

	while (1)
	{
		if (text[iBuffer] == NULL)
			break;
		if (text[iBuffer] == ' ')				    // 띄어쓰기인 경우 다음 글씨가 있을경우 단어 체크
			if (text[iBuffer + 1] != NULL && text[iBuffer + 1] != ' ')
				Word++;

		iBuffer++;
	}
	return Word;
}
void systemPause()
{
	getchar();
}

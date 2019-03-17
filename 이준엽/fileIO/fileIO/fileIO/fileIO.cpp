
#include "pch.h"
#include "CFileManger.h"

using namespace std;

void systemPause();

int main()
{
	CFileManger* fileManager = new CFileManger;
	fileManager->Run();
	delete fileManager;

	systemPause();
	return 0;
}


void systemPause()
{
	getchar();
}

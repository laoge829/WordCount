#include "Test.h"
#include"stdafx.h"
#include"WordCount.h"
#include"word.h"
int main(int argc, char* argv[]) {

	/*getwordCount("C:\\Users\\zhao xiao qin\\Desktop\\程序文件\\软件质量与测试\\WordCount\\Debug\\text.txt");
	printword();
	getchar();*/
	/*char* g[] = { "WordCount.exe", "-l" ,"C:\\Users\\zhao xiao qin\\Desktop\\程序文件\\软件质量与测试\\WordCount\\Debug\\text.txt" };
	Test(3, g);*/
	Test(argc, argv);
	getchar();
	return 0;
}
//
// Created by SilverCV on 2018/9/19.
//
#include "WordCount.h"
#include"word.h"

wordlist list;
char *result = "result.txt";          //定义输入文件名
int flag = 0;                          //表示写入result的模式
int ret[2] = { 0 };
void WordCount(int argc, char* argv[])
{
	list = createlist();//创建单词列表
	char* fileName;
	if (argc <= 1) {
		Help();
		exit(0);
	}
	GetOptions(argc, argv);
	fileName = argv[ret[1]];
	switch (ret[0])
	{
	case 1:
		ReadChar(fileName);
		break;
	case 3:
		ReadWord(fileName);
		break;
	case 5:
		Readlines(fileName);
		break;
	case 4: {
		ReadChar(fileName);
		flag = 1;
		ReadWord(fileName);
		break;
	}
	case 6: {
		ReadChar(fileName);
		flag = 1;
		Readlines(fileName);
		break;
	}
	case 8: {
		ReadWord(fileName);
		flag = 1;
		Readlines(fileName);
		break;
	}
	case 9: {
		CharWordLine(fileName);
		break;
	}
	default:
		Help();
		break;
	}
}
int *GetOptions(int argc, char* argv[])
{
	/* 返回0代表参数有错
	 *  1 表示读取字母
	 * 3 表示读取单词
	 *  5 表示读取行数
	 *  它们的和代表所要的功能
	 */

	char* params;
	for (int i = 0; i < argc; i++)
	{
		params = argv[i];
		if (strcmp("-c", params) == 0)
		{
			ret[0] += 1;
		}
		else if (strcmp("-w", params) == 0)
		{
			ret[0] += 3;
		}
		else if (strcmp("-l", params) == 0)
		{
			ret[0] += 5;
		}
		//启动图形界面，则退出命令行结口

	}
	if (argc > 3) {
		params = argv[argc - 2];
		if (strcmp("-o", params) == 0 && argv[argc - 1] != NULL) {
			result = argv[argc - 1];
			ret[1] = argc - 3;
		}
		else
		{
			ret[1] = argc - 1;
		}
	}
	else {
		ret[1] = argc - 1;
	}
	//处理 -o之前缺少输入文件
	return  ret;
}
void WriteToFile(char* fileName, int count[], int Csize, char* feature)
{
	/*fileName 表示读取的文件
	 * count 表示记录的个数
	 * Csize 表示记录数组的大小
	 * feature表示记录的内容 单词或者字母或者行数
	 * flag 表示只写，还是追加模式,0 表示只写，1表示追加
	 */
	char *mode = '\0';
	if (flag == 1)
	{
		mode = "a+";
	}
	else
	{
		mode = "w+";
	}
	int index = 0; //记录字符数
	for (int i = 0; i < Csize; i++)
	{
		if (count[i] != 0)
		{
			index += count[i];     //计算总的单词个数
		}
	}
	FILE *fp = NULL;
	fp = fopen(result, mode); //将结果写入文件
	if (fp == NULL)
	{
		printf("Failed when writing the count to file\n");
		exit(-1);
	}
	fprintf(fp, "%s,%s %d\n", fileName, feature, index); //写入文件

	if (list.count > 0)
	{
		for (int i = 0; i < list.count; i++)
		{
			fprintf(fp, "%s:%d\n", list.list[i].wordstring, list.list[i].count); //写入文件
		}
	}
	fclose(fp);
}
void print(char* fileName, int count[], int Csize, char* feature)
{
	int index = 0; //记录字符数
	for (int i = 0; i < Csize; i++)
	{
		if (count[i] != 0)
		{
			index += count[i];     //计算总的单词个数
		}
	}
	printf("%s %s:%d\n", fileName, feature, index); //打印输出
}
void *ReadChar(char* fileName)
{
	char* feature = "字符数: ";
	char buf;
	//int count[1] = {0}; //用来储存字母出现过的次数
	int sum = 0;
	FILE* fp = fopen(fileName, "r");
	if (fp == NULL)
	{
		printf("Fail to open the file!\n");
		Help();
		exit(-1);
	}
	while (!feof(fp))
	{
		buf = fgetc(fp);
		sum++;
	}
	fclose(fp);
	int count[1] = { sum };
	WriteToFile(fileName, count, 1, feature);
	print(fileName, count, 1, feature);
}
void *ReadWord(char* fileName)
{
	/*在记录单词个数 的时候，
	* 我们通过统计逗号和空格的个数
	* 然后通过计算得到单词的个数
	 * 假设每个单词的长度不超过256字母
	*/
	/*char* feature = "单词数: ";
	getwordCount(fileName);//得到各单词总数

	int sum = list.count;
	int count[1] = {sum};
	WriteToFile(fileName,count,1,feature);
	print(fileName, count, N, feature);
	return NULL;*/
	/*在记录单词个数 的时候，
	* 我们通过统计逗号和空格的个数
	* 然后通过计算得到单词的个数
	* 假设每个单词的长度不超过256字母
	*/
	char *feature = "单词数:";
	getwordCount(fileName);
	printword();
	int sum = 0;
	for (int i = 0; i < list.count; i++)
		sum += list.list[i].count;//计算总量
	int count[1] = { sum };
	WriteToFile(fileName, count, 1, feature);
	return NULL;
}
void *Readlines(char* fileName)
{
	char buf = '\0';
	char* feature = "行数: ";
	FILE* fp = NULL;
	fp = fopen(fileName, "r");
	if (fp == NULL)
	{
		printf("Fail to open the file!\n");
		Help();
		exit(-1);
	}
	int space[1] = { 0 }; //记录行数
	while (!feof(fp))
	{
		buf = fgetc(fp);
		if (buf == 10)  //换行符的ASCII码为10 只要找出所有的换行符就好
		{
			space[0] ++;
		}
	}
	space[0] ++; //在最后一个行中会把换行符设置为其他字符，随意需要加1
	WriteToFile(fileName, space, 1, feature);
	print(fileName, space, 1, feature);
	//关闭文件
	fclose(fp);
}
void Help()
{
	printf("wc.exe [parameter] [input_file_name] [-o] [output_file_name]\n");
	printf("Useage Options:\n");
	printf("    -c   Read the letters in the file\n");
	printf("    -w   Read the words in the file\n");
	printf("    -l   Read the number of rows in a file\n");
	printf("    -o   The Name of output file\n");
	printf("The -o must be at the back of input file. And the back of -o has an output File!\n");

}
void* CharWordLine(char* fileName)
{
	ReadChar(fileName);
	flag = 1;
	ReadWord(fileName);
	Readlines(fileName);

	return NULL;
}
#define n 100
void getwordCount(char *filename)//得到各单词的个数统计
{
	char data[100];//假设每行最多100个字符
	FILE* fp = NULL;
	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		printf("Fail to open the file!\n");
		Help();
		getchar();
		exit(-1);
	}
	while (!feof(fp))
	{
		fscanf(fp, "%s", &data);
		char str[n];
		for (int i = 0; i < n; i++)
		{
			str[i] = '\0';
		}
		int len = 0;
		for (int i = 0; i < strlen(data); i++)
		{
			char c = data[i];
			if (!issplitchar(c))//若不为单词分隔符
			{
				str[len] = c;

				len++;
			}
			else//若为单词分隔符且指针不超过字符长度
			{
				if (len > 0)
				{
					additem(&list, str);//添加
				}

				for (int i = 0; i < n; i++)
				{
					str[i] = '\0';
				}
				len = 0;
			}
		}
		if (len > 0)
		{
			additem(&list, str);//添加
		}
	}
	fclose(fp);

}
bool issplitchar(char c)//判断是否为分隔符
{
	char split[] = { '，',',','.','?','~','!','。',' ','"','—','-','(',')',':','=','\n','/' };//分隔符集合
	int len = 17;
	bool flag = false;
	for (int i = 0; i < len; i++)
	{
		if (split[i] == c || isdigit(c))
		{
			flag = true;
			break;
		}
	}
	return flag;
}
void printword()
{
	int sum = 0;
	for (int i = 0; i < list.count; i++)
		sum += list.list[i].count;//计算总量
	printf("单词种类数：%d\n", list.count);
	printf("单词总量：%d\n", sum);
	printf("各单词数量:\n");
	for (int i = 0; i < list.count; i++)
	{
		printf("%s:%d\n", list.list[i].wordstring, list.list[i].count);
	}
}
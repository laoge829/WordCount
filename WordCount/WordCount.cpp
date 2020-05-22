//
// Created by SilverCV on 2018/9/19.
//
#include "WordCount.h"
#include"word.h"

wordlist list;
char *result = "result.txt";          //���������ļ���
int flag = 0;                          //��ʾд��result��ģʽ
int ret[2] = { 0 };
void WordCount(int argc, char* argv[])
{
	list = createlist();//���������б�
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
	/* ����0���������д�
	 *  1 ��ʾ��ȡ��ĸ
	 * 3 ��ʾ��ȡ����
	 *  5 ��ʾ��ȡ����
	 *  ���ǵĺʹ�����Ҫ�Ĺ���
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
		//����ͼ�ν��棬���˳������н��

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
	//���� -o֮ǰȱ�������ļ�
	return  ret;
}
void WriteToFile(char* fileName, int count[], int Csize, char* feature)
{
	/*fileName ��ʾ��ȡ���ļ�
	 * count ��ʾ��¼�ĸ���
	 * Csize ��ʾ��¼����Ĵ�С
	 * feature��ʾ��¼������ ���ʻ�����ĸ��������
	 * flag ��ʾֻд������׷��ģʽ,0 ��ʾֻд��1��ʾ׷��
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
	int index = 0; //��¼�ַ���
	for (int i = 0; i < Csize; i++)
	{
		if (count[i] != 0)
		{
			index += count[i];     //�����ܵĵ��ʸ���
		}
	}
	FILE *fp = NULL;
	fp = fopen(result, mode); //�����д���ļ�
	if (fp == NULL)
	{
		printf("Failed when writing the count to file\n");
		exit(-1);
	}
	fprintf(fp, "%s,%s %d\n", fileName, feature, index); //д���ļ�

	if (list.count > 0)
	{
		for (int i = 0; i < list.count; i++)
		{
			fprintf(fp, "%s:%d\n", list.list[i].wordstring, list.list[i].count); //д���ļ�
		}
	}
	fclose(fp);
}
void print(char* fileName, int count[], int Csize, char* feature)
{
	int index = 0; //��¼�ַ���
	for (int i = 0; i < Csize; i++)
	{
		if (count[i] != 0)
		{
			index += count[i];     //�����ܵĵ��ʸ���
		}
	}
	printf("%s %s:%d\n", fileName, feature, index); //��ӡ���
}
void *ReadChar(char* fileName)
{
	char* feature = "�ַ���: ";
	char buf;
	//int count[1] = {0}; //����������ĸ���ֹ��Ĵ���
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
	/*�ڼ�¼���ʸ��� ��ʱ��
	* ����ͨ��ͳ�ƶ��źͿո�ĸ���
	* Ȼ��ͨ������õ����ʵĸ���
	 * ����ÿ�����ʵĳ��Ȳ�����256��ĸ
	*/
	/*char* feature = "������: ";
	getwordCount(fileName);//�õ�����������

	int sum = list.count;
	int count[1] = {sum};
	WriteToFile(fileName,count,1,feature);
	print(fileName, count, N, feature);
	return NULL;*/
	/*�ڼ�¼���ʸ��� ��ʱ��
	* ����ͨ��ͳ�ƶ��źͿո�ĸ���
	* Ȼ��ͨ������õ����ʵĸ���
	* ����ÿ�����ʵĳ��Ȳ�����256��ĸ
	*/
	char *feature = "������:";
	getwordCount(fileName);
	printword();
	int sum = 0;
	for (int i = 0; i < list.count; i++)
		sum += list.list[i].count;//��������
	int count[1] = { sum };
	WriteToFile(fileName, count, 1, feature);
	return NULL;
}
void *Readlines(char* fileName)
{
	char buf = '\0';
	char* feature = "����: ";
	FILE* fp = NULL;
	fp = fopen(fileName, "r");
	if (fp == NULL)
	{
		printf("Fail to open the file!\n");
		Help();
		exit(-1);
	}
	int space[1] = { 0 }; //��¼����
	while (!feof(fp))
	{
		buf = fgetc(fp);
		if (buf == 10)  //���з���ASCII��Ϊ10 ֻҪ�ҳ����еĻ��з��ͺ�
		{
			space[0] ++;
		}
	}
	space[0] ++; //�����һ�����л�ѻ��з�����Ϊ�����ַ���������Ҫ��1
	WriteToFile(fileName, space, 1, feature);
	print(fileName, space, 1, feature);
	//�ر��ļ�
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
void getwordCount(char *filename)//�õ������ʵĸ���ͳ��
{
	char data[100];//����ÿ�����100���ַ�
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
			if (!issplitchar(c))//����Ϊ���ʷָ���
			{
				str[len] = c;

				len++;
			}
			else//��Ϊ���ʷָ�����ָ�벻�����ַ�����
			{
				if (len > 0)
				{
					additem(&list, str);//����
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
			additem(&list, str);//����
		}
	}
	fclose(fp);

}
bool issplitchar(char c)//�ж��Ƿ�Ϊ�ָ���
{
	char split[] = { '��',',','.','?','~','!','��',' ','"','��','-','(',')',':','=','\n','/' };//�ָ�������
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
		sum += list.list[i].count;//��������
	printf("������������%d\n", list.count);
	printf("����������%d\n", sum);
	printf("����������:\n");
	for (int i = 0; i < list.count; i++)
	{
		printf("%s:%d\n", list.list[i].wordstring, list.list[i].count);
	}
}
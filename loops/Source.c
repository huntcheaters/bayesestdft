#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>


//int main(void)
{
	int i=1, s=0;
	
	while (i <= 1000)
	{
		s = s + i;
		i++;
	}

	printf("%s%d\n", "i: ", i);
	printf("%s%d\n", "1+2+...+1000: ", s);

	return 0;
}

	//float s1=0, s2=0, s3=0;

	//printf("%s\n", "下方以 成绩1,成绩2,成绩3回车 的格式输入学生成绩");
	//scanf("%f,%f,%f", &s1, &s2, &s3);

	//printf("%s%f\n", "平均分： ", (s1 + s2 + s3) / 3);


	//int i = 0, s = 0, 表达式1, 表达式2, 表达式3, 语句;

	//for (表达式1; 表达式2; 表达式3)
	//	语句;

	//for (表达式1; 表达式2; 表达式3)
	//{
	//	语句;
	//	
	//	语句;
	//}


////	int i = 0, s = 0;
////	for (i = 1; i <= 1000; i++)
////		s = s + i;
//
//
//
//	return 0;
//}
{

	while (表达式1)
		语句;


	while (表达式1)
	{
		语句;
		语句;
	}

}
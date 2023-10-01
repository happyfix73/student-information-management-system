#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "stuscore.h"

void InitLinkList(LList *L)
{
	(*L) = (LinkListNode *)malloc(sizeof(LinkListNode));
	(*L)->next = NULL;
}


void ui(void)
{
	printf("*******************************\n");
	printf("*** 学 生 成 绩 管 理 系 统 ***\n");
	printf("***   1. 输入学生成绩\t*******\n");
	printf("***   2. 增加学生成绩\t*******\n");
	printf("***   3. 学生信息排序\t*******\n");
	printf("***   4. 查找学生成绩\t*******\n");
	printf("***   5. 删除学生成绩\t*******\n");
	printf("***   6. 显示学生成绩\t*******\n");
	printf("***   7. 安全退出系统\t*******\n");
	printf("*******************************\n");
}

void InputStuScore(void)
{
	fp = fopen("stus.dat", "rb"); 
	if (fp == NULL)
	{
		printf("数据文件无法打开！\n");
		exit(-1);
	}
	while (!feof(fp))
	{
		SNode buf; //创建一个学生信息的结构体
		int ret = fread(&buf, sizeof(SNode), 1, fp);
		if (ret)
		{
			LinkListNode *n = (LinkListNode *)malloc(sizeof(LinkListNode));
			n->data = buf;
			n->next = NULL;
			n->next = STUS->next;
			STUS->next = n;
		}
	}
	fclose(fp);
}

void AddStuScore(void)
{
	SNode s;

	
	printf("请输入学号(格式9301XXXX）：");
	scanf("%d", &s.snum);
	LinkListNode *t = _SearchStuSnum(s.snum);
	if (t != NULL)
	{
		printf("学号已存在\n");
		return;
	}
	printf("请输入学生姓名：");
	scanf("%s", s.name);

	printf("请输入数学成绩：");
	scanf("%f", &s.shuxue);

	printf("请输入英语成绩：");
	scanf("%f", &s.yingyu);

	printf("请输入语文成绩：");
	scanf("%f", &s.yuwen);

	//将该学生保存到学生链表中
	/*printf("学号：%d\t姓名：%s\t数学：%5.2f\t英语：%5.2f\t语文：%5.2f\n\n",
		s.snum, s.name, s.suxue, s.yingyu, s.yuwen);*/

	LinkListNode *n = (LinkListNode *)malloc(sizeof(LinkListNode)); //在堆区创建一个结点
	n->data = s;
	n->next = NULL;

	//将当前学生信息结点加入到链表中
	n->next = STUS->next;
	STUS->next = n;
	fp = fopen("stus.dat", "ab");
	if (fp == NULL)
	{
		printf("文件打开失败\n");
		exit(-1);
	}
	//将学生信息保存到文件中
	fwrite(&s, sizeof(SNode), 1, fp);
	fclose(fp);
}

void StuScoreSort(void)
{
	LinkListNode *p = STUS->next;
	LinkListNode *q = STUS->next;
	while (p != NULL)
	{
		q = p->next;
		while (q!=NULL)
		{
			if (p->data.snum > q->data.snum)
			{
				SNode t = p->data;
				p->data = q->data;
				q->data = t;
			}
			q = q->next;
		}
		p = p->next;
	}
}
LinkListNode *_SearchStuSnum(int snum)
{
	LinkListNode *t = STUS->next;
	while (t != NULL && snum != t->data.snum)
	{
		t = t->next;
	}
	return t;
}

void SearchStuScore(void)
{
	int snum;
	printf("请输入学号(格式9301XXXX）\n");
	scanf("%d", &snum);
	LinkListNode *t = _SearchStuSnum(snum);
	if (t != NULL)
	{
		SNode s = t->data;
		printf("学号：%d\t姓名：%s\t数学：%5.2f\t英语：%5.2f\t语文：%5.2f\n\n",
			s.snum, s.name, s.shuxue, s.yingyu, s.yuwen);
	}
	else
	{
		printf("\n没有该学号\n");
	}
}

void DelStuScore(void)
{
	int snum;
	printf("请输入学号(格式9301XXXX）");
	scanf("%d", &snum);
	LinkListNode *pt = STUS; 
	LinkListNode *t = STUS->next;
	while (t != NULL && snum != t->data.snum)
	{
		pt = pt->next;
		t = t->next;
	}
	if (t == NULL)
	{
		printf("没有找到学号\n");
	}
	else
	{
		pt->next = t->next;
		fp = fopen("stus.dat", "wb");
		if (fp == NULL)
		{
			printf("数据文件打开失败\n");
			exit(-1);
		}
		t = STUS->next;
		while (t!=NULL)
		{
			SNode s = t->data;
			fwrite(&s, sizeof(SNode), 1, fp);
			t = t->next;
		}
		fclose(fp);
	}
}

void DispStuScore(void)
{
	LinkListNode *t = STUS->next;//创建临时变量，指当前要操作的结点
	while (t != NULL)
	{
		SNode s = t->data;

		printf("学号：%d\t姓名：%s\t数学：%5.2f\t英语：%5.2f\t语文：%5.2f\n",
			s.snum, s.name, s.shuxue, s.yingyu, s.yuwen);

		printf("--------------------------------------------------------\n");

		t = t->next;
	}
}

int Init(void)
{
	COUNT = 93100001; //学号的初始值
	InitLinkList(&STUS); //初始化链表
	InputStuScore(); //加载学生信息
	return 0; //表示初始化正常
}

int main()
{
	//程序初始化
	if (Init() == -1)
	{
		return -1;
	}
	int input;
	while (1)
	{
		ui();
		printf("请选择：");
		scanf("%d", &input);

		switch (input)
		{
		case 1:
			printf("已加载，无需输出\n");
			break;
		case 2:
			AddStuScore();
			break;
		case 3:
			StuScoreSort();
			break;
		case 4:
			SearchStuScore();
			break;
		case 5:
			DelStuScore();
			break;
		case 6:
			DispStuScore();
			break;
		case 7:
			fclose(fp);
			printf("欢迎再次使用系统！\n");
			return 0;
		default:
			printf("输入有误！\n");
			break;
		}
	}

	return 0;
}
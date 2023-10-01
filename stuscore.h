#pragma once
typedef struct STUSCORE
{
	int snum;
	char name[10];
	float yuwen;
	float shuxue;
	float yingyu;

}SNode,*sllist;
typedef struct linklist
{
	SNode data;
	struct linklist *next;
	
}LinkListNode,*LList;
//int COUNT = 93100001;
unsigned int COUNT;
LList STUS;//创建保存所有学生信息的链表
FILE *fp;//保存学生信息文件
void InitLinkList(LList *l);
void InputStuScore(void);
void AddStuScore(void);
void StuScoreSort(void);
LinkListNode *_SearchStuSnum(int snum);
void SearchStuScore(void);
void DelStuScore(void);
void DispStuScore(void);
int Init(void);
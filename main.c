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
	printf("*** ѧ �� �� �� �� �� ϵ ͳ ***\n");
	printf("***   1. ����ѧ���ɼ�\t*******\n");
	printf("***   2. ����ѧ���ɼ�\t*******\n");
	printf("***   3. ѧ����Ϣ����\t*******\n");
	printf("***   4. ����ѧ���ɼ�\t*******\n");
	printf("***   5. ɾ��ѧ���ɼ�\t*******\n");
	printf("***   6. ��ʾѧ���ɼ�\t*******\n");
	printf("***   7. ��ȫ�˳�ϵͳ\t*******\n");
	printf("*******************************\n");
}

void InputStuScore(void)
{
	fp = fopen("stus.dat", "rb"); 
	if (fp == NULL)
	{
		printf("�����ļ��޷��򿪣�\n");
		exit(-1);
	}
	while (!feof(fp))
	{
		SNode buf; //����һ��ѧ����Ϣ�Ľṹ��
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

	
	printf("������ѧ��(��ʽ9301XXXX����");
	scanf("%d", &s.snum);
	LinkListNode *t = _SearchStuSnum(s.snum);
	if (t != NULL)
	{
		printf("ѧ���Ѵ���\n");
		return;
	}
	printf("������ѧ��������");
	scanf("%s", s.name);

	printf("��������ѧ�ɼ���");
	scanf("%f", &s.shuxue);

	printf("������Ӣ��ɼ���");
	scanf("%f", &s.yingyu);

	printf("���������ĳɼ���");
	scanf("%f", &s.yuwen);

	//����ѧ�����浽ѧ��������
	/*printf("ѧ�ţ�%d\t������%s\t��ѧ��%5.2f\tӢ�%5.2f\t���ģ�%5.2f\n\n",
		s.snum, s.name, s.suxue, s.yingyu, s.yuwen);*/

	LinkListNode *n = (LinkListNode *)malloc(sizeof(LinkListNode)); //�ڶ�������һ�����
	n->data = s;
	n->next = NULL;

	//����ǰѧ����Ϣ�����뵽������
	n->next = STUS->next;
	STUS->next = n;
	fp = fopen("stus.dat", "ab");
	if (fp == NULL)
	{
		printf("�ļ���ʧ��\n");
		exit(-1);
	}
	//��ѧ����Ϣ���浽�ļ���
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
	printf("������ѧ��(��ʽ9301XXXX��\n");
	scanf("%d", &snum);
	LinkListNode *t = _SearchStuSnum(snum);
	if (t != NULL)
	{
		SNode s = t->data;
		printf("ѧ�ţ�%d\t������%s\t��ѧ��%5.2f\tӢ�%5.2f\t���ģ�%5.2f\n\n",
			s.snum, s.name, s.shuxue, s.yingyu, s.yuwen);
	}
	else
	{
		printf("\nû�и�ѧ��\n");
	}
}

void DelStuScore(void)
{
	int snum;
	printf("������ѧ��(��ʽ9301XXXX��");
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
		printf("û���ҵ�ѧ��\n");
	}
	else
	{
		pt->next = t->next;
		fp = fopen("stus.dat", "wb");
		if (fp == NULL)
		{
			printf("�����ļ���ʧ��\n");
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
	LinkListNode *t = STUS->next;//������ʱ������ָ��ǰҪ�����Ľ��
	while (t != NULL)
	{
		SNode s = t->data;

		printf("ѧ�ţ�%d\t������%s\t��ѧ��%5.2f\tӢ�%5.2f\t���ģ�%5.2f\n",
			s.snum, s.name, s.shuxue, s.yingyu, s.yuwen);

		printf("--------------------------------------------------------\n");

		t = t->next;
	}
}

int Init(void)
{
	COUNT = 93100001; //ѧ�ŵĳ�ʼֵ
	InitLinkList(&STUS); //��ʼ������
	InputStuScore(); //����ѧ����Ϣ
	return 0; //��ʾ��ʼ������
}

int main()
{
	//�����ʼ��
	if (Init() == -1)
	{
		return -1;
	}
	int input;
	while (1)
	{
		ui();
		printf("��ѡ��");
		scanf("%d", &input);

		switch (input)
		{
		case 1:
			printf("�Ѽ��أ��������\n");
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
			printf("��ӭ�ٴ�ʹ��ϵͳ��\n");
			return 0;
		default:
			printf("��������\n");
			break;
		}
	}

	return 0;
}
#pragma once
/*
�ļ�����CriticlPath.h
������ �ؼ�·��
ʱ�䣺2019.1.7
*/

#include"AdjacencyList.h"
#include"Stack.h"
//#include<stdio.h>
#define OK 1
#define ERROR 0
#define Status int
#define MAX 93376
int ve[MAX_VERTEX_NUM];		//���������緢��ʱ������
int vl[MAX_VERTEX_NUM];		//��������ٷ���ʱ������


Status FindInDegree(ALGraph G, int indegree[MAX_VERTEX_NUM])
{
	int i = 0;
	ArcNode *p = NULL;	//����ָ��
	for (i = 0; i < MAX_VERTEX_NUM; i++)	//��ʼ�����������������緢��ʱ������
	{
		indegree[i] = 0;
		ve[i] = 0;
	}
		
	for (i = 0; i < G.vexnum; i++)	//������������
	{
		p = G.vretices[i].firstarc;
		while (p != NULL)
		{
			indegree[p->adjvex]++;
			p = p->nextarc;
		}

	}//for_i

}

_Bool TopologicalSort(ALGraph G,SqStack *T)
{
	//������G�����ڽӱ�洢���������ʱ������緢��ʱ��ve
	//TΪ�������򶥵�ջ
	// ��G�޻�·�������G�����һ���������в�����OK�����򷵻�ERROR
	int i, count, k;
	int indegree[MAX_VERTEX_NUM];	//�������������
	SqStack S;		//���Ϊ���ջ
	ArcNode *p = NULL;
	InitStack(&S);
	FindInDegree(G, indegree);	//�Ը����������
	for (i = 0; i < G.vexnum; i++)
	{
		if (!indegree[i]) Push(&S, i);
	}
	count = 0;
	while (!StackEmpty(&S))		//���������ve
	{
		Pop(&S, &i);
		Push(T, i);	//i�Ŷ�����Tջ
		count++;
		for (p = G.vretices[i].firstarc; p; p = p->nextarc)	//��i�Ŷ����ÿ���ڽӵ����ȼ�һ
		{
			k = p->adjvex;		//j�Ŷ���ÿ���ڽӵ���ȼ�һ
			if (!(--indegree[k])) Push(&S, k);	//�����Ϊ�㣬��ջ
			if (ve[i] + p->weight > ve[k]) ve[k] = ve[i] + p->weight;
		}
	}//while
	if (count < G.vexnum)	return ERROR;
	else return OK;

}


Status CriticalPath(ALGraph G)
{
	//Status TopologicalSort(ALGraph G, SqStack *T);
	//GΪ�����������G�ĸ���ؼ��
	SqStack T;
	int i, j, k, t, dut, ee, el;
	int time=0;	//ʱ��
	ArcNode *p = NULL;
	ArcNode *q = NULL;
	InitStack(&T);
	//TopologicalSort(G, &T);
	if (!TopologicalSort(G, &T)) return ERROR;
	for (i = 0; i< G.vexnum; i++)		//��ʼ����ٷ���ʱ������
	{
		vl[i] = MAX;
	}
	vl[G.vexnum-1] = ve[G.vexnum-1];
	while (!StackEmpty(&T))		//������������vl
	{
		Pop(&T, &j);
		p = G.vretices[j].firstarc;
		while(p!=NULL)
		{
			k = p->adjvex;
			dut = p->weight;
			if (vl[k] - dut < vl[j]) vl[j] = vl[k] - dut;
			p = p->nextarc;
		}
	}
	printf("�ؼ����");
	for (j = 0; j < G.arcnum; j++)	//��ؼ����ʱ������Ϊ0
	{
		for (p = G.vretices[j].firstarc; p; p = p->nextarc)
		{
			k = p->adjvex;
			dut = p->weight;
			ee = ve[j];
			el = vl[k] - dut;
			if (ee == el) printf("%c ", *(p->info));
		}
	}
	printf("\n�ؼ�·����\n");
	t = 1;
	while (t > 0)	//��������ؼ�·��
	{
		time = 0;	//��ʼ��ʱ��
		for (j = 0;j != G.vexnum-1;j = q->adjvex)	//��ؼ�·�����Լ�ʱ��
		{
			for (p = G.vretices[j].firstarc, q = p,i = 0; p!=NULL; p = p->nextarc)
			{
				k = p->adjvex;
				dut = p->weight;
				ee = ve[j];
				el = vl[k] - dut;
				if (ee == el)
				{
					if (i == 0)
					{
						q = p;
						time = time + p->weight;
						printf("%c ", *(p->info));
						//p->weight = 0;
						
						i++;

					}
					else
					{
						t++;
						q->weight = 0;
						//j = q->adjvex;	//��һ�����ҵĶ���
					}
				}
			}
		}
		t--;
		printf("\n��ɹؼ������ʱ�䣺%d\n", time);

	}
	
		
}

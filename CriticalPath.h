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
#define Status _Bool
int ve[MAX_VERTEX_NUM];		//���������緢��ʱ������
int vl[MAX_VERTEX_NUM];		//��������ٷ���ʱ������


void FindInDegree(ALGraph G, int indegree[MAX_VERTEX_NUM])
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


_Bool CriticalPath(ALGraph G)
{
	_Bool TopologicalSort(ALGraph G, SqStack *T);
	//GΪ�����������G�ĸ���ؼ��
	SqStack T;
	int i, j, k, dut, ee, el;
	char tag;
	ArcNode *p = NULL;
	InitStack(&T);
	TopologicalSort(G, &T);
	//if (!TopologicalSort(G, &T)) return ERROR;
	for (i = 0; i< G.vexnum; i++)		//��ʼ����ٷ���ʱ������
	{
		vl[i] = ve[i];
	}
	while (!StackEmpty(&T))		//������������vl
	{
		for (Pop(&T, &j), p = G.vretices[j].firstarc; p; p = p->nextarc)
		{
			k = p->adjvex;
			dut = p->weight;
			if (vl[k] - dut < vl[j]) vl[j] = vl[k] - dut;
		}
		for (j = 0; j < G.arcnum; j++)	//ʱ������Ϊ0
		{
			for (p = G.vretices[j].firstarc; p; p = p->nextarc)
			{
				k = p->adjvex;
				dut = p->weight;
				ee = ve[j];
				el = vl[k] - dut;
				tag = (ee == el) ? '*' : ' ';
				printf("%c %c %d %d %d %c\n", G.vretices[j].data, G.vretices[k].data, dut, ee, el, tag);
			}
		}

	}



}

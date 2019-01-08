#pragma once
/*
文件名：CriticlPath.h
描述： 关键路径
时间：2019.1.7
*/

#include"AdjacencyList.h"
#include"Stack.h"
//#include<stdio.h>
#define OK 1
#define ERROR 0
#define Status int
#define MAX 93376
int ve[MAX_VERTEX_NUM];		//各顶点最早发生时间数组
int vl[MAX_VERTEX_NUM];		//各顶点最迟发生时间数组


Status FindInDegree(ALGraph G, int indegree[MAX_VERTEX_NUM])
{
	int i = 0;
	ArcNode *p = NULL;	//遍历指针
	for (i = 0; i < MAX_VERTEX_NUM; i++)	//初始化入度数组各顶点最早发生时间数组
	{
		indegree[i] = 0;
		ve[i] = 0;
	}
		
	for (i = 0; i < G.vexnum; i++)	//计算各顶点入度
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
	//有向网G采用邻接表存储，求各顶点时间的最早发生时间ve
	//T为拓扑排序顶点栈
	// 若G无回路，则输出G顶点的一个拓扑序列并返回OK，否则返回ERROR
	int i, count, k;
	int indegree[MAX_VERTEX_NUM];	//各顶点入度数组
	SqStack S;		//入度为零的栈
	ArcNode *p = NULL;
	InitStack(&S);
	FindInDegree(G, indegree);	//对各顶点求入度
	for (i = 0; i < G.vexnum; i++)
	{
		if (!indegree[i]) Push(&S, i);
	}
	count = 0;
	while (!StackEmpty(&S))		//求出各顶点ve
	{
		Pop(&S, &i);
		Push(T, i);	//i号顶点入T栈
		count++;
		for (p = G.vretices[i].firstarc; p; p = p->nextarc)	//对i号顶点的每个邻接点的入度减一
		{
			k = p->adjvex;		//j号顶点每个邻接点入度减一
			if (!(--indegree[k])) Push(&S, k);	//若入度为零，入栈
			if (ve[i] + p->weight > ve[k]) ve[k] = ve[i] + p->weight;
		}
	}//while
	if (count < G.vexnum)	return ERROR;
	else return OK;

}


Status CriticalPath(ALGraph G)
{
	//Status TopologicalSort(ALGraph G, SqStack *T);
	//G为有向网，输出G的各项关键活动
	SqStack T;
	int i, j, k, t, dut, ee, el;
	int time=0;	//时间
	ArcNode *p = NULL;
	ArcNode *q = NULL;
	InitStack(&T);
	//TopologicalSort(G, &T);
	if (!TopologicalSort(G, &T)) return ERROR;
	for (i = 0; i< G.vexnum; i++)		//初始化最迟发生时间数组
	{
		vl[i] = MAX;
	}
	vl[G.vexnum-1] = ve[G.vexnum-1];
	while (!StackEmpty(&T))		//按拓扑序列求vl
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
	printf("关键活动：");
	for (j = 0; j < G.arcnum; j++)	//求关键活动，时间余量为0
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
	printf("\n关键路径：\n");
	t = 1;
	while (t > 0)	//输出多条关键路径
	{
		time = 0;	//初始化时间
		for (j = 0;j != G.vexnum-1;j = q->adjvex)	//求关键路径，以及时间
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
						//j = q->adjvex;	//下一个该找的顶点
					}
				}
			}
		}
		t--;
		printf("\n完成关键活动所需时间：%d\n", time);

	}
	
		
}

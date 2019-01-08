/*
文件名：AdjacencyList.h
描述：图的链式存储结构，邻接表
时间：2018.11.24
2018.12.26修改
2018.1.6修改
	解决邻接表first.next指向非null问题
*/
#pragma once

#include<stdio.h>
#include<stdlib.h>

/*-----------------图的邻接链表存储表示------------------*/
#define MAX_VERTEX_NUM	20		//最大定点数
#define InfoType char	//该弧相关信息类型
#define VertexType char		//顶点类型
typedef struct ArcNode {
	//邻接表结点类型定义
	int adjvex;		//该弧所指向的顶点的位置
	struct ArcNode *nextarc;		//指向下一条弧的指针
	InfoType *info;		//该弧相关信息的指针
	int weight;		//权值
}ArcNode;

typedef struct VNode {
	//图顶点类型定义
	VertexType data;	//顶点信息
	ArcNode	*firstarc;	//指向第一条依附该顶点的弧的指针
}VNode, AdjList[MAX_VERTEX_NUM];

typedef struct {
	//图类型定义
	AdjList vretices;	//邻接表
	int vexnum, arcnum;		//图的当前顶点数和弧数
	int kind;		//图的种类
}ALGraph;

VertexType what(ALGraph G, VertexType adj)
{
	int i = 0;
	for (i = 0; i < G.vexnum; i++)
	{
		if (G.vretices[i].data == adj) return i;
	}
	return '#';

}

void CreateDG(ALGraph *G)	//邻接表构建有向图G
{
	ArcNode *p = NULL;
	ArcNode *q = NULL;
	int i, j, wei;
	VertexType temp_adj = '0';
	InfoType temp_info;
	printf("输入图的顶点数，弧数");
	scanf("%d %d", &G->vexnum, &G->arcnum);
	for (i = 0; i < G->vexnum; i++)		//输入顶点值及初始化邻接表指针
	{
		printf("输入第%d个顶点：", i + 1);
		scanf(" %c", &(G->vretices[i].data));
		G->vretices[i].firstarc = NULL;		//初始化指针，杜绝野指针
	}
	for (i = 0; i < G->vexnum; i++)
	{
		for (j = 0;; j++)	//输入的弧尾为1时表示该顶点的弧已输入完
		{
			printf("输入顶点%c的第%d条弧的弧尾，弧信息，以及权值", G->vretices[i].data, j + 1);
			scanf(" %c %c %d", &temp_adj, &temp_info,&wei);
			if (temp_adj == '#')
			{
				temp_adj = '0';
				if (j == 0)
				{
					G->vretices[i].firstarc = NULL;
				}
				else
				{
					p->nextarc = NULL;
					//emp = &p;
					//free(p);
					p = NULL;
				}
				break;
			}
			else
			{
				temp_adj = what(*G, temp_adj);
				if (j == 0)
				{
					G->vretices[i].firstarc = (ArcNode *)malloc(sizeof(ArcNode));	//给邻接表的第i个头结点开辟第一个表结点

					G->vretices[i].firstarc->info = (InfoType *)malloc(sizeof(InfoType));	//给邻接表的第i个头结点的第一个表结点的info指针开辟空间
					//G->vretices[i].firstarc->nextarc = (ArcNode *)malloc(sizeof(ArcNode));	//给下一个指向开辟空间
					p = G->vretices[i].firstarc;
					p->adjvex = temp_adj;
					p->weight = wei;
					*(p->info) = temp_info;
				}
				else
				{
					
					p->nextarc = (ArcNode *)malloc(sizeof(ArcNode));
					p = p->nextarc;
					p->info = (InfoType *)malloc(sizeof(InfoType));
					p->adjvex = temp_adj;
					p->weight = wei;
					*(p->info) = temp_info;
				}

				//p = p->nextarc;
			}
		}//for_j

	}//for_i
	//printf("创建成功\n");
}//CreateDG


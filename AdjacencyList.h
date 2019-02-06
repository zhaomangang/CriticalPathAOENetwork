/*
�ļ�����AdjacencyList.h
������ͼ����ʽ�洢�ṹ���ڽӱ�
ʱ�䣺2018.11.24
2018.12.26�޸�
2018.1.6�޸�
	����ڽӱ�first.nextָ���null����
*/

#include<string.h>
#include<stdio.h>
#include<stdlib.h>


/*-----------------ͼ���ڽ�����洢��ʾ------------------*/
#define MAX_VERTEX_NUM	20		//��󶨵���
#define InfoType char	//�û������Ϣ����
#define VertexType char*		//��������
typedef struct ArcNode {
	//�ڽӱ������Ͷ���
	int adjvex;		//�û���ָ��Ķ����λ��
	struct ArcNode *nextarc;		//ָ����һ������ָ��
	InfoType *info;		//�û������Ϣ��ָ��
	int weight;		//Ȩֵ
}ArcNode;

typedef struct VNode {
	//ͼ�������Ͷ���
	char data[20];	//������Ϣ
	ArcNode	*firstarc;	//ָ���һ�������ö���Ļ���ָ��
}VNode, AdjList[MAX_VERTEX_NUM];

typedef struct {
	//ͼ���Ͷ���
	AdjList vretices;	//�ڽӱ�
	int vexnum, arcnum;		//ͼ�ĵ�ǰ�������ͻ���
	int kind;		//ͼ������
}ALGraph;

int what(ALGraph G, char adj[20])
{
	int i = 0;
	for (i = 0; i < G.vexnum; i++)
	{
		if (!strcmp(G.vretices[i].data,adj)) return i;
	}
	return -1;

}

void CreateDG(ALGraph *G)	//�ڽӱ�������ͼG
{
	ArcNode *p = NULL;
	ArcNode *q = NULL;
	int i, j, wei;
	char temp_adj[20] = "0";
	InfoType temp_info;
	printf("����ͼ�Ķ�����������");
	scanf("%d %d", &G->vexnum, &G->arcnum);
	for (i = 0; i < G->vexnum; i++)		//���붥��ֵ����ʼ���ڽӱ�ָ��
	{
		printf("�����%d�����㣺", i + 1);
		scanf("%s", &G->vretices[i].data);
		G->vretices[i].firstarc = NULL;		//��ʼ��ָ�룬�ž�Ұָ��
	}
	for (i = 0; i < G->vexnum; i++)
	{
		for (j = 0;; j++)	//����Ļ�βΪ1ʱ��ʾ�ö���Ļ���������
		{
			printf("���붥��%s�ĵ�%d�����Ļ�β������Ϣ���Լ�Ȩֵ", G->vretices[i].data, j + 1);
			scanf("%s %c %d", &temp_adj, &temp_info, &wei);
			//scanf(" %c %c %d", &temp_adj, &temp_info,&wei);
			if (!strcmp(temp_adj,"#"))
			{
				*temp_adj = "0";
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
				
				if (j == 0)
				{
					G->vretices[i].firstarc = (ArcNode *)malloc(sizeof(ArcNode));	//���ڽӱ�ĵ�i��ͷ��㿪�ٵ�һ������

					G->vretices[i].firstarc->info = (InfoType *)malloc(sizeof(InfoType));	//���ڽӱ�ĵ�i��ͷ���ĵ�һ�������infoָ�뿪�ٿռ�
					//G->vretices[i].firstarc->nextarc = (ArcNode *)malloc(sizeof(ArcNode));	//����һ��ָ�򿪱ٿռ�
					p = G->vretices[i].firstarc;
					p->adjvex = what(*G, temp_adj);
					p->weight = wei;
					*(p->info) = temp_info;
				}
				else
				{
					p->nextarc = (ArcNode *)malloc(sizeof(ArcNode));
					p = p->nextarc;
					p->info = (InfoType *)malloc(sizeof(InfoType));
					p->adjvex = what(*G, temp_adj);
					p->weight = wei;
					*(p->info) = temp_info;
				}

				//p = p->nextarc;
			}
		}//for_j

	}//for_i
	//printf("�����ɹ�\n");
}//CreateDG


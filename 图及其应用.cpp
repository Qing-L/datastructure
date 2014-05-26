#include <stdio.h>
#include <stdlib.h>
#include <stack>
using namespace std;
#define INFINITY INT_MAX  
#define MAX_VERTEX_NUM 20

/******    ͼ���ڽӾ���洢��ʾ    ******/

//DN-������,UDN-������
typedef enum {DN=0,UDN=1}Graphkind;
typedef struct ArcCell
{
	int adj;//��Ȩͼ����0,1��ʾ���ڷ񣻶Դ�Ȩͼ����ΪȨֵ������Ϊint�ͣ�
}AreCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef struct
{
	char vexs[MAX_VERTEX_NUM];//��������Ϊchar����
	AdjMatrix arcs; //�ڽӾ���
	int vexnum, arcnum;//vexnum��ʾ��ǰ�Ķ�����,arcnum��ʾ����
	Graphkind kind;  //ͼ�������־
}MGraph;

/****   ͼ���ڽӱ�洢��ʾ   ****/
typedef struct ArcNode
{
	int adjvex; //�û���ָ��Ķ����λ��
	struct ArcNode *nextarc; //ָ����һ������ָ��
	int w;//Ȩֵ
}ArcNode;
typedef struct VNode
{
	char data; //������Ϣ
	ArcNode *firstarc; //ָ���һ�������õ�Ļ���ָ��
}VNode, AdjList[MAX_VERTEX_NUM];
typedef struct
{
	AdjList vertices;
	int vexnum, arcnum; //ͼ�ĵ�ǰ�������ͻ���
	int kind;  //ͼ�������־
}ALGraph;

int LocateVex_juzhen(MGraph G, char v)
{
	for (int i = 0; i < G.vexnum; i++)
	{
		if (G.vexs[i] == v) return i;
	}
}
int LocateVex_biao(ALGraph G, char v)
{
	for (int i = 0; i < G.vexnum; i++)
	{
		if (G.vertices[i].data == v) return i;
	}
}

/****   �ڽӾ���   ****/

int CreateUDN_juzhen(MGraph &G)
{
	//�������飨�ڽӾ��󣩱�ʾ��������������G
	char v1, v2;//һ��������������������
	int w;//�ߵ�Ȩֵ
	int i, j;

	scanf_s("%d%d", &G.vexnum, &G.arcnum);
	getchar();
	for (i = 0; i < G.vexnum; i++)
	{
		scanf_s("%c", &G.vexs[i]);//���춥������
	}
	for (i = 0; i < G.vexnum; i++)
	{
		for (j = 0; j < G.vexnum; j++)
		{
			G.arcs[i][j] = { INFINITY };//��ʼ���ڽӾ���
		}
	}
	for (int k = 0; k < G.arcnum; k++)
	{
		getchar();
		scanf_s("%c", &v1);
		getchar();
		scanf_s("%c", &v2);
		getchar();
		scanf_s("%d", &w);
		i = LocateVex_juzhen(G, v1);
		j = LocateVex_juzhen(G, v2);
		G.arcs[i][j].adj = w;
		G.arcs[j][i] = G.arcs[i][j];
	}
	return 1;
}
int CreateDN_juzhen(MGraph &G)
{
	//�������飨�ڽӾ��󣩱�ʾ��������������G
	char v1, v2;//һ��������������������
	int w;//�ߵ�Ȩֵ
	int i, j;

	scanf_s("%d%d", &G.vexnum, &G.arcnum);
	getchar();
	for (i = 0; i < G.vexnum; i++)
	{
		scanf_s("%c", &G.vexs[i]);//���춥������
	}
	for (i = 0; i < G.vexnum; i++)
	{
		for (j = 0; j < G.vexnum; j++)
		{
			G.arcs[i][j] = { INFINITY };//��ʼ���ڽӾ���
		}
	}
	for (int k = 0; k < G.arcnum; k++)
	{
		getchar();
		scanf_s("%c", &v1);
		getchar();
		scanf_s("%c", &v2);
		getchar();
		scanf_s("%d", &w);
		i = LocateVex_juzhen(G, v1);
		j = LocateVex_juzhen(G, v2);
		G.arcs[i][j].adj = w;
	}
	return 1;
}
int CreateGraph_juzhen(MGraph &G)
{
	scanf_s("%d", &G.kind);
	switch (G.kind)
	{
	case DN:return CreateDN_juzhen(G); //����������G
	case UDN:return CreateUDN_juzhen(G); //����������G
	default:return 0;
	}
}

/*****   �ڽӱ�    ******/

int CreateUDN_biao(ALGraph &G)
{
	//�������飨�ڽӱ���ʾ��������������G
	char v1, v2;//һ��������������������
	int w;//�ߵ�Ȩֵ
	int i, j;

	scanf_s("%d%d", &G.vexnum, &G.arcnum);
	getchar();
	for (i = 0; i < G.vexnum; i++)
	{
		scanf_s("%c", &G.vertices[i].data);//���춥������
		G.vertices[i].firstarc = NULL;
	}
	for (int k = 0; k < G.arcnum; k++)
	{
		getchar();
		scanf_s("%c", &v1);
		getchar();
		scanf_s("%c", &v2);
		getchar();
		scanf_s("%d", &w);
		i = LocateVex_biao(G, v1);
		j = LocateVex_biao(G, v2);

		//����ͼ���ڽӱ�Ҫ�����ӵ������߶�Ӧ�Ľڵ��������
		if (G.vertices[i].firstarc == NULL)
		{
			G.vertices[i].firstarc = (ArcNode*)malloc(sizeof(ArcNode));
			G.vertices[i].firstarc->adjvex = j;
			G.vertices[i].firstarc->nextarc = NULL;
			G.vertices[i].firstarc->w = w;
		}
		else
		{
			ArcNode* p = G.vertices[i].firstarc;
			ArcNode* q;
			while (p->nextarc != NULL)
				p = p->nextarc;
			q = (ArcNode*)malloc(sizeof(ArcNode));
			q->adjvex = j;
			q->nextarc = NULL;
			q->w = w;
			p->nextarc = q;
		}
		if (G.vertices[j].firstarc == NULL)
		{
			G.vertices[j].firstarc = (ArcNode*)malloc(sizeof(ArcNode));
			G.vertices[j].firstarc->adjvex =i;
			G.vertices[j].firstarc->nextarc = NULL;
			G.vertices[j].firstarc->w = w;
		}
		else
		{
			ArcNode* p = G.vertices[j].firstarc;
			ArcNode* q;
			while (p->nextarc != NULL)
				p = p->nextarc;
			q = (ArcNode*)malloc(sizeof(ArcNode));
			q->adjvex = i;
			q->nextarc = NULL;
			q->w = w;
			p->nextarc = q;
		}
	}
	return 1;
}
int CreateDN_biao(ALGraph &G)
{
	//�������飨�ڽӱ���ʾ��������������G
	char v1, v2;//һ��������������������
	int w;//�ߵ�Ȩֵ
	int i, j;
	scanf_s("%d%d", &G.vexnum, &G.arcnum);
	getchar();
	for (i = 0; i < G.vexnum; i++)
	{
		scanf_s("%c", &G.vertices[i].data);//���춥������
		G.vertices[i].firstarc = NULL;
	}
	for (int k = 0; k < G.arcnum; k++)
	{
		getchar();
		scanf_s("%c", &v1);
		getchar();
		scanf_s("%c", &v2);
		getchar();
		scanf_s("%d", &w);
		i = LocateVex_biao(G, v1);
		j = LocateVex_biao(G, v2);
		if (G.vertices[i].firstarc == NULL)
		{
			G.vertices[i].firstarc = (ArcNode*)malloc(sizeof(ArcNode));
			G.vertices[i].firstarc->adjvex = j;
			G.vertices[i].firstarc->nextarc = NULL;
			G.vertices[i].firstarc->w = w;
		}
		else
		{
			ArcNode* p = G.vertices[i].firstarc;
			ArcNode* q;
			while (p->nextarc != NULL)
				p = p->nextarc;
			q = (ArcNode*)malloc(sizeof(ArcNode));
			q->adjvex = j;
			q->nextarc = NULL;
			q->w = w;
			p->nextarc = q;
		}
	}
	return 1;
}
int CreateGraph_biao(ALGraph &G)
{
	scanf_s("%d", &G.kind);
	switch (G.kind)
	{
	case DN:return CreateDN_biao(G); //����������G
	case UDN:return CreateUDN_biao(G); //����������G
	default:return 0;
	}
}

/********  �ؼ�·��  *******/
int vl[MAX_VERTEX_NUM];
int ve[MAX_VERTEX_NUM];
void FindInDegree(ALGraph G, int *indegree)
{
	for (int j = 0; j < G.vexnum; j++)
	{
		indegree[j] = 0;//��ʼ��
	}
	for (int i = 0; i < G.vexnum; i++)
	{
		ArcNode* p = G.vertices[i].firstarc;
		while (p != NULL)
		{
			indegree[p->adjvex]++;
			p = p->nextarc;
		}
	}
}
int TopologicalOrder(ALGraph G, stack<int> &T)
{
	int indegree[MAX_VERTEX_NUM];
	int i,j,k;
	stack<int> S;
	ArcNode* p;

	FindInDegree(G, indegree); //�Ը����������
	
	for (i = 0; i < G.vexnum; i++)
	{
		if (indegree[i] == 0)  S.push(i);//�����Ϊ0�Ķ�����Sջ
	}
	int count = 0;
	for (i = 0; i < G.vexnum; i++)  ve[i] = 0;

	while (!S.empty())
	{
		j = S.top();S.pop();
		T.push(j);++count;//j�Ŷ����Sջ����Tջ��������
		for (p = G.vertices[j].firstarc; p; p = p->nextarc)
		{
			k = p->adjvex; //��j�Ŷ����ÿ���ڽӵ����ȼ�1
			if (--indegree[k] == 0) S.push(k);//�����Ϊ0������Sջ
			if ((ve[j] + p->w) > ve[k]) ve[k] = ve[j] + p->w;
		}//for
	}//while
	if (count < G.vexnum)  return 0;
	else return 1;
}
int CriticalPath(ALGraph G)
{
	stack<int> T;
	int i,j,k,dut;
	ArcNode *p;

	int ee, el;
	char tag;

	if (!TopologicalOrder(G, T)) return 0;
	for (i = 0; i < G.vexnum; i++) vl[i] = ve[i];
	while (!T.empty())
	{
		for (j = T.top(), T.pop(), p = G.vertices[j].firstarc; p; p = p->nextarc)
		{
			k = p->adjvex;
			dut = p->w;
			if (vl[k] - dut < vl[j]) vl[j] = vl[k] - dut;
		}//for
	}//while
	printf("��� �ص� Ȩֵ ���翪ʼʱ�� ��ٿ�ʼʱ�� �ؼ����ʶ\n");
	for (j = 0; j < G.vexnum; j++)
	{
		for (p = G.vertices[j].firstarc; p; p = p->nextarc)
		{
			k = p->adjvex;
			dut = p->w;
			ee = ve[j];
			el = vl[k] - dut;
			tag = (ee == el) ? '*' : ' ';
			printf("%c   %c       %d        %d          %d          %c\n", 
				G.vertices[j].data, G.vertices[k].data, dut, ee, el, tag);//����ؼ��
		}//for
	}//for
}//CriticalPath

/****   ������ʾ    ****/

void ShowGraph_juzhen(MGraph &G)
{
	for (int i = 0; i < G.vexnum; i++)
	{
		for (int j = 0; j < G.vexnum; j++)
		{
			if (G.arcs[i][j].adj == INFINITY)  printf("�� ");
			else printf("%d ", G.arcs[i][j]);
		}
		printf("\n");
	}
}
void ShowGraph_biao(ALGraph &G)
{
	for (int i = 0; i < G.vexnum; i++)
	{
		printf("%d:%c -> ", i, G.vertices[i].data);
		ArcNode *p = G.vertices[i].firstarc;
		while (p != NULL)
		{
				printf("%d,w=%d ->", p->adjvex, p->w);
				p = p->nextarc;		
		}
		printf("NULL\n");
	}
}

/*****    ������    ****/
void show()
{
	printf("1��ͼ���ڽӾ���\n");
	printf("2��ͼ���ڽӱ�\n");
	printf("3���ؼ�·��\n");
	printf("4���˳�\n");
}
int main()
{
	int i;
	char r;
	MGraph G;
	ALGraph G1;

	show();
	scanf_s("%d", &i);
	while (i != 4)
	{
		switch (i)
		{
		case 1:
			system("cls");
			CreateGraph_juzhen(G);
			ShowGraph_juzhen(G);
			printf("�������������\n");
			getchar();
			scanf_s("%c", &r);			
			system("cls");
			show();
			break;
		case 2:
			system("cls");
			CreateGraph_biao(G1);
			ShowGraph_biao(G1);
			printf("�������������\n");
			getchar();
			scanf_s("%c", &r);
			system("cls");
			show();
			break;
		case 3:
			system("cls");
			CreateGraph_biao(G1);
			printf("�ڽӱ����£�\n");
			ShowGraph_biao(G1);
			printf("��Ӧ�Ĺؼ��Ϊ:\n");
			CriticalPath(G1);
			printf("�������������\n");
			getchar();
			scanf_s("%c", &r);
			system("cls");
			show();
			break;
		}
		scanf_s("%d", &i);
	}	
	system("pause");
	return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <stack>
using namespace std;
#define INFINITY INT_MAX  
#define MAX_VERTEX_NUM 20

/******    图的邻接矩阵存储表示    ******/

//DN-有向网,UDN-无向网
typedef enum {DN=0,UDN=1}Graphkind;
typedef struct ArcCell
{
	int adj;//无权图，用0,1表示相邻否；对带权图，则为权值（本例为int型）
}AreCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef struct
{
	char vexs[MAX_VERTEX_NUM];//顶点向量为char类型
	AdjMatrix arcs; //邻接矩阵
	int vexnum, arcnum;//vexnum表示当前的顶点数,arcnum表示弧数
	Graphkind kind;  //图的种类标志
}MGraph;

/****   图的邻接表存储表示   ****/
typedef struct ArcNode
{
	int adjvex; //该弧所指向的顶点的位置
	struct ArcNode *nextarc; //指向下一条弧的指针
	int w;//权值
}ArcNode;
typedef struct VNode
{
	char data; //顶点信息
	ArcNode *firstarc; //指向第一条依附该点的弧的指针
}VNode, AdjList[MAX_VERTEX_NUM];
typedef struct
{
	AdjList vertices;
	int vexnum, arcnum; //图的当前顶点数和弧数
	int kind;  //图的种类标志
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

/****   邻接矩阵   ****/

int CreateUDN_juzhen(MGraph &G)
{
	//采用数组（邻接矩阵）表示法，构造无向网G
	char v1, v2;//一条边所依附的两个顶点
	int w;//边的权值
	int i, j;

	scanf_s("%d%d", &G.vexnum, &G.arcnum);
	getchar();
	for (i = 0; i < G.vexnum; i++)
	{
		scanf_s("%c", &G.vexs[i]);//构造顶点向量
	}
	for (i = 0; i < G.vexnum; i++)
	{
		for (j = 0; j < G.vexnum; j++)
		{
			G.arcs[i][j] = { INFINITY };//初始化邻接矩阵
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
	//采用数组（邻接矩阵）表示法，构造有向网G
	char v1, v2;//一条边所依附的两个顶点
	int w;//边的权值
	int i, j;

	scanf_s("%d%d", &G.vexnum, &G.arcnum);
	getchar();
	for (i = 0; i < G.vexnum; i++)
	{
		scanf_s("%c", &G.vexs[i]);//构造顶点向量
	}
	for (i = 0; i < G.vexnum; i++)
	{
		for (j = 0; j < G.vexnum; j++)
		{
			G.arcs[i][j] = { INFINITY };//初始化邻接矩阵
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
	case DN:return CreateDN_juzhen(G); //构造有向网G
	case UDN:return CreateUDN_juzhen(G); //构造无向网G
	default:return 0;
	}
}

/*****   邻接表    ******/

int CreateUDN_biao(ALGraph &G)
{
	//采用数组（邻接表）表示法，构造无向网G
	char v1, v2;//一条边所依附的两个顶点
	int w;//边的权值
	int i, j;

	scanf_s("%d%d", &G.vexnum, &G.arcnum);
	getchar();
	for (i = 0; i < G.vexnum; i++)
	{
		scanf_s("%c", &G.vertices[i].data);//构造顶点向量
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

		//无向图的邻接表要将弧加到弧两边对应的节点的链表中
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
	//采用数组（邻接表）表示法，构造有向网G
	char v1, v2;//一条边所依附的两个顶点
	int w;//边的权值
	int i, j;
	scanf_s("%d%d", &G.vexnum, &G.arcnum);
	getchar();
	for (i = 0; i < G.vexnum; i++)
	{
		scanf_s("%c", &G.vertices[i].data);//构造顶点向量
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
	case DN:return CreateDN_biao(G); //构造有向网G
	case UDN:return CreateUDN_biao(G); //构造无向网G
	default:return 0;
	}
}

/********  关键路径  *******/
int vl[MAX_VERTEX_NUM];
int ve[MAX_VERTEX_NUM];
void FindInDegree(ALGraph G, int *indegree)
{
	for (int j = 0; j < G.vexnum; j++)
	{
		indegree[j] = 0;//初始化
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

	FindInDegree(G, indegree); //对个顶点求入度
	
	for (i = 0; i < G.vexnum; i++)
	{
		if (indegree[i] == 0)  S.push(i);//将入度为0的顶点入S栈
	}
	int count = 0;
	for (i = 0; i < G.vexnum; i++)  ve[i] = 0;

	while (!S.empty())
	{
		j = S.top();S.pop();
		T.push(j);++count;//j号顶点出S栈，入T栈，并计数
		for (p = G.vertices[j].firstarc; p; p = p->nextarc)
		{
			k = p->adjvex; //对j号顶点的每个邻接点的入度减1
			if (--indegree[k] == 0) S.push(k);//若入度为0，则入S栈
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
	printf("起点 重点 权值 最早开始时间 最迟开始时间 关键活动标识\n");
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
				G.vertices[j].data, G.vertices[k].data, dut, ee, el, tag);//输出关键活动
		}//for
	}//for
}//CriticalPath

/****   矩阵显示    ****/

void ShowGraph_juzhen(MGraph &G)
{
	for (int i = 0; i < G.vexnum; i++)
	{
		for (int j = 0; j < G.vexnum; j++)
		{
			if (G.arcs[i][j].adj == INFINITY)  printf("∞ ");
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

/*****    主函数    ****/
void show()
{
	printf("1、图的邻接矩阵\n");
	printf("2、图的邻接表\n");
	printf("3、关键路径\n");
	printf("4、退出\n");
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
			printf("输入任意键返回\n");
			getchar();
			scanf_s("%c", &r);			
			system("cls");
			show();
			break;
		case 2:
			system("cls");
			CreateGraph_biao(G1);
			ShowGraph_biao(G1);
			printf("输入任意键返回\n");
			getchar();
			scanf_s("%c", &r);
			system("cls");
			show();
			break;
		case 3:
			system("cls");
			CreateGraph_biao(G1);
			printf("邻接表如下：\n");
			ShowGraph_biao(G1);
			printf("对应的关键活动为:\n");
			CriticalPath(G1);
			printf("输入任意键返回\n");
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
#include"CriticalPath.h"
int main()
{
	ALGraph G;
	//maxa();
	CreateDG(&G);
	if (!CriticalPath(G)) printf("��ͼΪ�л�ͼ\n");
//	CriticalPath(G);
	//maxa(G);
	return 0;
}
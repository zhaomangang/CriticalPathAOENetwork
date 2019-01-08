#include"CriticalPath.h"
int main()
{
	ALGraph G;
	//maxa();
	CreateDG(&G);
	if (!CriticalPath(G)) printf("该图为有环图\n");
//	CriticalPath(G);
	//maxa(G);
	return 0;
}
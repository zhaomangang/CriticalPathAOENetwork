#include"CriticalPath.h"
int main()
{
	ALGraph G;
	//maxa();
	CreateDG(&G);
	CriticalPath(G);
	//maxa(G);
	return 0;
}
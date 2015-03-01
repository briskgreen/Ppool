#include "ppool_errno.h"

void perror(const char *msg)
{
	if(!msg)
		printf("%s\n",pstrerr(ppool_errno));
	else
		printf("%s : %s\n",pstrerr(ppool_errno));
}

char *pstrerr(int errno)
{
	switch(errno)
	{
		default:
			return "未知错误!";
	}
}

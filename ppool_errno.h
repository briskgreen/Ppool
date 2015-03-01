#ifndef _PPOOL_ERRNO_H
#define _PPOOL_ERRNO_H

#include <stdio.h>
#include <string.h>

int ppool_errno=0; //错误代码变量

#define PE_OK 0
#define PE_POOL_NO_MEM -1

//打印错误信息
void perror(const char *msg);

//根据错误代码代码打印错误信息
char *pstrerr(int errno);

#endif

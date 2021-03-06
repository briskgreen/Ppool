#ifndef _PPOOL_QUEUE_H
#define _PPOOL_QUEUE_H

#include "ppool_errno.h"
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef void (*ppool_work)(void *);

typedef struct ppool_node
{
	int priority; //优先级
	ppool_work task; //任务
	void *arg; //参数

	struct ppool_node *next;
}pool_node;

//任务列表头指针
typedef struct
{
	int len; //任务数量
	pool_node *head; //列表头指针
}pool_w;

pool_w *ppool_queue_init(void);
//初始化一个任务列表

pool_node *ppool_queue_new(ppool_work task,void *arg,int priority);
/* 创建一个节点
 * task为新任务
 * arg为任务参数
 * priority为该任务优先级
 */

void ppool_queue_add(pool_w *head,pool_node *node);
// 添加一个任务

pool_node *ppool_queue_get_task(pool_w *head);
//获取一个任务

void ppool_queue_cleanup(pool_w *head);
//清理任务列表

void ppool_queue_destroy(pool_w *head);
//销毁任务列表

#endif

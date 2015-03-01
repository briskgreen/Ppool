#ifndef _PPOOL_H
#define _PPOOL_H

#include <pthread.h>
#include "ppool_queue.h"

typedef char pbool;

#define PTRUE 1
#define PFALSE 0

typedef struct
{
	int pool_max_num; //线程池最大线程数量
	pool_w *head; //线程头
	pthread_t *id; //线程id

	pthread_mutex_t ppool_lock;
	pthread_cond_t ppool_cond;
}pool_t;

//任务数据结构
typedef struct
{
	int priority; //优先级
	ppool_work task; //任务
	void *arg; //参数
}pool_task;

//初始化一个线程池
pool_t *ppool_init(int pool_max_num);

//向线程池中添加一个任务
pbool ppool_add(pool_t *pool,pool_task *task);

//销毁一个线程池
void ppool_destroy(pool_t *pool);

#endif

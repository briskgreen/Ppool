#ifndef _PPOOL_H
#define _PPOOL_H

#include <pthread.h>
#include "ppool_queue.h"

enum PPOOL_STATUS{start,stop};

typedef char pbool;

#define PTRUE 1
#define PFALSE 0

typedef struct
{
	PPOOL_STATUS status; //当前线程池的状态
	int pool_max_num; //线程池最大线程数量
	int task_num; //当前任务数
	int work_num; //当前运行的数量
	pool_w *head; //线程头
	pthread_t *id; //线程id

	pthread_mutex_t ppool_lock;
	pthread_mutex_t ppool_mux;
	pthread_cond_t ppool_con;
}pool_t;

//初始化一个线程池
pool_t *ppool_init(int pool_max_num);

//向线程池中添加一个任务
pbool ppool_taskadd(pool_t *pool,pool_w *task);

//销毁一个线程池
void ppool_destroy(pool_t *pool);

#endif

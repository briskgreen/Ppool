#ifndef _PPOOL_H
#define _PPOOL_H

#include <pthread.h>
#include "ppool_queue.h"

enum PPOOL_STATUS{start,stop};

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

#endif

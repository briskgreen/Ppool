#include "ppool.h"

//线程池执行任务函数
void ppool_run(pool_t *pool);

pool_t *ppool_init(int pool_max_num)
{
	pool_t *pool;
	pool_w *head;
	int i;

	pool=malloc(sizeof(pool_t));
	if(!pool)
	{
		ppool_errno=PE_POOL_NO_MEM;
		return NULL;
	}

	head=ppool_queue_init();
	if(!head)
	{
		free(pool);
		return NULL;
	}

	pool->pool_max_num=pool_max_num;
	pool->head=head;
	pool->id=malloc(sizeof(pthread_t)*pool_max_num);
	if(!pool->id)
	{
		ppool_errno=PE_THREAD_NO_MEM;
		free(head);
		free(pool);
		return NULL;
	}

	pthread_mutex_init(&pool->ppool_lock);
	pthread_cond_init(&pool->ppool_cond,NULL);

	for(i=0;i < pool_max_num;++i)
	{
		pthread_create(&pool->id[i],NULL,(void *)ppool_run,pool);
		pthread_detach(pool->id[i]);
	}

	return pool;
}

pbool ppool_add(pool_t *pool,pool_task *task)
{
	pool_node *node;

	node=ppool_queue_new(task->task,task->arg,task->priority);
	if(!node)
		return PFALSE;

	pthread_mutex_lock(&pool->ppool_lock);
	ppool_queue_add(pool->head,node);
	pthread_mutex_unlock(&pool->ppool_lock);

	return PTRUE;
}

void ppool_destroy(pool_t *pool)
{
	int i;

	ppool_queue_destroy(pool->head);

	for(i=0;i < pool->pool_max_num;++i)
		pthread_cancel(pool->id[i]);
	free(pool->id);

	pthread_mutex_destroy(&pool->ppool_mux);
	pthread_mutex_destroy(&pool->ppool_lock);
	pthread_cond_destroy(&pool->ppool_con);

	free(pool);
}

void ppool_run(pool *pool)
{
}

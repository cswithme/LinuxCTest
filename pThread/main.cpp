/*
 * main.cpp
 * 在使用pthread_xxx功能时，需要链接libpthread.so
 *	Thread func Test
 */

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <unistd.h>

#include <pthread.h>


#include "apue.h"

void cleanupFunc(void *arg)
{
	printf("cleanup: %s\n", (char *)arg);
}

void *thr_fn1(void *arg)
{
	printf("thread 1 start\n");
	pthread_cleanup_push(cleanupFunc, (void *)"thread 1 first handler");
	pthread_cleanup_push(cleanupFunc, (void *)"thread 1 second handler");
	printf("thread 1 push complete\n");

	if (arg)	return((void *)1); //arg 不为null 总是执行此处

	puts("blabla!\n"); //arg 已经在上方return,词句不会执行

	//pthread_cleanup_push、pthread_cleanup_pop必须成对出现
	pthread_cleanup_pop(0);
	pthread_cleanup_pop(0);

	return((void *)1);
}

void *thr_fn2(void *arg)
{
	printf("thread 2 start\n");
	pthread_cleanup_push(cleanupFunc, (void *)"thread 2 first handler");
	pthread_cleanup_push(cleanupFunc, (void *)"thread 2 second handler");
	printf("thread 2 push complete\n");

	//xxx 只有调用pthread_exit时,pthread_cleanup_push才起作用
	if (arg)	pthread_exit((void *)2);	//arg 不为null 总是执行此处

	puts("blabla!\n");	//arg 已经在上方return,词句不会执行

	//pthread_cleanup_push、pthread_cleanup_pop必须成对出现
	pthread_cleanup_pop(0);
	pthread_cleanup_pop(0);
	pthread_exit((void *)2);
	return 0;
}

int main(void)
{
	int			err;
	pthread_t	tid1, tid2;
	void		*tret;

	//xxx pthread_create中的attr可不指定
	err = pthread_create(&tid1, NULL, thr_fn1, (void *)1);
	if (err != 0)
		err_exit(err, "can't create thread 1");

	sleep(1);
	//xxx 通过属性设置线程为可分离pthread_attr_setdetachstate，也可调用pthread_detach(pthread_t tid);
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);

	err = pthread_create(&tid2, &attr, thr_fn2, (void *)1);
	if (err != 0)
		err_exit(err, "can't create thread 2");

	err = pthread_join(tid1, &tret);
	if (err != 0)
		err_exit(err, "can't join with thread 1");
	printf("thread 1 exit code %ld\n", (long)tret);

	//xxx 设置线程pthread_detach后，不可再调用pthread_join
//	err = pthread_join(tid2, &tret);
//	if (err != 0)
//		err_exit(err, "can't join with thread 2");
//	printf("thread 2 exit code %ld\n", (long)tret);

	sleep(2);

	exit(0);
}

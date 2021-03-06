/*
 * PthreadBarrierTest.cpp
 *	线程执行到pthread_barrier_wait 处阻塞，直到pthread_barrier_wait的数量达到init时指定的数目为止
 *
 *  Created on: 2017-9-23
 *      Author: root
 */

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <unistd.h>
#include <pthread.h> //pthread_barrier

pthread_barrier_t pb;

void *threadFunc(void *arg)
{
	struct timespec tsBegin;
	unsigned int uiParm = *(unsigned int *)arg;
	usleep(uiParm * 400 * 1000); //不同的线程，运行至pthread_barrier_wait的时间不同
	int iRet = pthread_barrier_wait(&pb);
	if(iRet == PTHREAD_BARRIER_SERIAL_THREAD)
		printf("thread num%d, is the last one\n",uiParm);

	clock_gettime(CLOCK_REALTIME, &tsBegin);
	printf("thread %d start at tv_sec[%ld], tv_usec[%ld](ns), pid = %u\n",
			uiParm, tsBegin.tv_sec, tsBegin.tv_nsec, (unsigned int)pthread_self());

	printf("Thread num%d will exit!\n", uiParm);
	return((void *)1);
}



void PthreadBarrierTest()
{
	const int ciThreadCnt = 4;
	pthread_t tid[ciThreadCnt];
	pthread_barrier_init(&pb, NULL, ciThreadCnt+1);

	unsigned int uiSleepArry[4] = {1,2,3,4};

	for(int i=0; i<ciThreadCnt; ++i)
	{
		int err = pthread_create(&tid[i], NULL, threadFunc, (void *)&uiSleepArry[i]);
//		int err = pthread_create(&tid[i], NULL, threadFunc, (void *)&i); //此处不可用i，等到线程访问时，i的值已经变了
		if (err != 0)
		{
			printf("can't create thread Num: %d\n", i);
			return;
		}
	}
	puts("wait thread creat!");
	int iRet = pthread_barrier_wait(&pb);
	if(iRet == PTHREAD_BARRIER_SERIAL_THREAD)
		printf("Main thread is the last one\n");
	puts(" thread creat finish!");

	for(int i=0; i<ciThreadCnt; ++i)
		pthread_join(tid[i],NULL);

	pthread_barrier_destroy(&pb);
}

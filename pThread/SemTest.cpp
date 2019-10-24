/*
 * SemTest.cpp
 *
 *  Created on: 2018-8-30
 *      Author: root
 */

#include <semaphore.h>

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include "slepubfunc.h"

sem_t m_CmdResponseSem;


void *thread_fn(void *arg)
{
	printf("thread started...\n");

//	usleep(200);

	sem_wait(&m_CmdResponseSem);
	printf("get m_CmdResponseSem\n");

	printf("thread exit...\n");
	return(0);
}

void semTest()
{
	bool bRet = true;
	memset(&m_CmdResponseSem, 0, sizeof(m_CmdResponseSem));

	pthread_t tid;
	if(pthread_create(&tid, NULL, thread_fn, 0) != 0)
		puts("pthread_create fail!");

	usleep(1200);


	if(0 != sem_init(&m_CmdResponseSem, 0, 0))
	{
		printf("[%s][%s][%d]sem_init m_CmdResponseSem fail. errno=%d\n", __FILE__ , __FUNCTION__, __LINE__, errno);
		bRet = false;
	}

	usleep(2000 * 1000);
	puts("sem_post begin!");
//	sem_post(&m_CmdResponseSem);
	puts("sem_post end!");

	sem_destroy(&m_CmdResponseSem);
}


void *thread_fn2(void *arg)
{
	printf("thread started...\n");

//	usleep(200);

	sem_wait_i(&m_CmdResponseSem, 65000);
	printf("get m_CmdResponseSem\n");

	printf("thread exit...\n");
	return(0);
}

void semTest2()
{

	bool bRet = true;
	memset(&m_CmdResponseSem, 0, sizeof(m_CmdResponseSem));

	pthread_t tid;
	if(pthread_create(&tid, NULL, thread_fn2, 0) != 0)
		puts("pthread_create fail!");

	usleep(1200);


	if(0 != sem_init(&m_CmdResponseSem, 0, 0))
	{
		printf("[%s][%s][%d]sem_init m_CmdResponseSem fail. errno=%d\n", __FILE__ , __FUNCTION__, __LINE__, errno);
		bRet = false;
	}

//	usleep(2000 * 1000);
	sleep(70);
//	puts("sem_post begin!");
//	sem_post(&m_CmdResponseSem);
//	puts("sem_post end!");

	sem_destroy(&m_CmdResponseSem);

}

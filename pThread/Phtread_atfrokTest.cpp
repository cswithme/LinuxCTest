#include <pthread.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

pthread_mutex_t lock1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock2 = PTHREAD_MUTEX_INITIALIZER;

void err_cont(int iErr, const char* szInfo)
{
	printf("err_cont:%s, iErr=%d\n", szInfo, iErr);
}

void err_exit(int iErr, const char* szInfo)
{
	printf("err_exit:%s, iErr=%d\n", szInfo, iErr);
	exit(-1);
}

//在父进程fork之前自动调用,用于将进程内所有的锁加锁
void prepare(void)
{
	int err;

	printf("preparing locks...\n");
	if ((err = pthread_mutex_lock(&lock1)) != 0)
		err_cont(err, "can't lock lock1 in prepare handler");
	if ((err = pthread_mutex_lock(&lock2)) != 0)
		err_cont(err, "can't lock lock2 in prepare handler");
}

//fork创建子进程后，返回父进程之前自动调用,用于释放prepare中获得的锁
void parent(void)
{
	int err;

	printf("parent unlocking locks...\n");
	if ((err = pthread_mutex_unlock(&lock1)) != 0)
		err_cont(err, "can't unlock lock1 in parent handler");
	if ((err = pthread_mutex_unlock(&lock2)) != 0)
		err_cont(err, "can't unlock lock2 in parent handler");
}

//fork创建子进程后，返回子进程之前自动调用,用于释放prepare中获得的锁
void child(void)
{
	int err;

	printf("child unlocking locks...\n");
	if ((err = pthread_mutex_unlock(&lock1)) != 0)
		err_cont(err, "can't unlock lock1 in child handler");
	if ((err = pthread_mutex_unlock(&lock2)) != 0)
		err_cont(err, "can't unlock lock2 in child handler");
}

//void *thr_fn(void *arg)
//{
//	printf("thread started...\n");
//	pause();
//	printf("thread exit!!!!\n");
//	return(0);
//}

void *thr_fn(void *arg)
{
	printf("thread started...\n");

	for(int i=0; i<5; ++i)
	{
		pthread_mutex_lock(&lock1);
		printf("tid=%lu, i=%d\n", pthread_self(), i);
		usleep(700 * 1000);
		pthread_mutex_unlock(&lock1);

		usleep(50 * 1000);
	}


	printf("thread exit...\n");
	return(0);
}

void Pthread_atforkTest()
{
	int			err;
	pid_t		pid;
	pthread_t	tid;

	if ((err = pthread_atfork(prepare, parent, child)) != 0)
		err_exit(err, "can't install fork handlers");
	if ((err = pthread_create(&tid, NULL, thr_fn, 0)) != 0)
		err_exit(err, "can't create thread");

	sleep(2);
	printf("parent about to fork...\n");

	if ((pid = fork()) < 0)
	{
		puts("fork error!");
		exit(-1);
	}
	else if (pid == 0)	/* child */
	{
		printf("child returned from fork\n");
		if(pthread_mutex_trylock(&lock1) == 0)
		{
			puts("try lock sucess!");
			pthread_mutex_unlock(&lock1);
		}
		else
			puts("try lock fail!");

	}
	else		/* parent */
		printf("parent returned from fork\n");

	pthread_join(tid, NULL);
	puts("test end!");
}

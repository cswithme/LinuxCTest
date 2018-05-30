/*
 * DeleteCalssWithThread.h
 *
 *  Created on: 2018-5-11
 *      Author: root
 */

#ifndef DELETECALSSWITHTHREAD_H_
#define DELETECALSSWITHTHREAD_H_

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <list>

class CClassWithThread
{
public:
	CClassWithThread();
	~CClassWithThread();
	void Init();

	void ShowCntValue();
private:
	static void * ThreadFunc(void *Parm);
	pthread_t	m_tid;
	int m_iCnt;
	std::list<int> m_listTest;
};

#endif /* DELETECALSSWITHTHREAD_H_ */

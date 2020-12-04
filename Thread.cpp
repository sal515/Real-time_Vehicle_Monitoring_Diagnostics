/*
 * Thread.cpp
 *
 *  Created on: Nov 14, 2020
 *      Author: Salman
 */

#include "Thread.h"
#include <iostream>
#include <cerrno>
#include <stdio.h>

#define DEBUG_PRINT 0

namespace realtime_vehicle_monitoring_diagnostics
{
	Thread::Thread()
	{
		if (DEBUG_PRINT)
		{
			std::cout << "Thread object created" << std::endl;
		}
	}

	Thread::~Thread()
	{
		/* TODO: Thread kill */
		// pthread_kill(this->thread, SIGKILL);
		if (DEBUG_PRINT)
		{
			std::cout << "Thread object destroyed" << std::endl;
		}
	}

	Thread::Thread(start_routine_t start_routine,
				   int sched_priority,
				   char *thread_name)
	{
		this->thread_name = thread_name;

		pthread_mutex_init(&this->thread_control.mutex, NULL);
		pthread_cond_init(&this->thread_control.condvar, NULL);

		pthread_attr_init(&this->attr);

		/* Set Joinable or Detached */
		// pthread_attr_setdetachstate(&this->attr, PTHREAD_CREATE_JOINABLE);
		pthread_attr_setdetachstate(&this->attr, PTHREAD_CREATE_DETACHED);

		if (pthread_attr_setinheritsched(&this->attr, PTHREAD_EXPLICIT_SCHED) != 0)
		{
			printf("ERROR: pthread_attr_setinheritsched() failed %d \n",
				   errno);
			return;
		}

		if (pthread_attr_setschedpolicy(&this->attr, SCHED_FIFO) != 0)
		{
			printf("ERROR: pthread_attr_setschedpolicy() failed %d\n",
				   errno);
			return;
		}

		/* Set priority */
		this->params.sched_priority = sched_priority;

		if (pthread_attr_setschedparam(&this->attr, &this->params) != 0)
		{
			printf("ERROR: pthread_attr_setschedparam() failed %d \n", errno);
			return;
		}

		/* Set start routine */
		this->start_routine = start_routine;

		if (pthread_create(&this->thread,
						   &this->attr,
						   this->start_routine,
						   this) != EOK)
		{
			printf("ERROR: Thread Creation failed\n");
			return;
		}

		// EAGAIN
		// EFAULT
		// EINVAL
		// EOK
	}

	void Thread::unblock()
	{
		pthread_mutex_unlock(&this->thread_control.mutex);
		if (DEBUG_PRINT)
		{
			printf("%s : Unlocked\n", this->thread_name);
		}
	}
	void Thread::block()
	{
		if (DEBUG_PRINT)
		{
			printf("%s : Condvar Wait Call\n", this->thread_name);
		}
		pthread_mutex_lock(&this->thread_control.mutex);
		pthread_cond_wait(&this->thread_control.condvar, &this->thread_control.mutex);
	}

	void Thread::signal()
	{
		if (DEBUG_PRINT)
		{
			printf("%s : Signalled\n", this->thread_name);
		}
		pthread_cond_signal(&this->thread_control.condvar);
	}

} // namespace realtime_vehicle_monitoring_diagnostics

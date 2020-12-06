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
#include <stdlib.h>
#include "Logger.h"

#define DEBUG_PRINT 0

namespace realtime_vehicle_monitoring_diagnostics
{
	Thread::Thread()
	{
		this->is_complete = 0;
		this->prio = 0;
		this->thread_name = "default";
		Logger::log_thread_details(this, "Default Thread was created\n");
	}

	Thread::~Thread()
	{
		this->is_complete = 1;
		this->prio = 0;

		/* TODO: Thread kill */
		pthread_kill(this->thread, SIGKILL);
		Logger::log_thread_details(this, "Terminated\n");
	}

	Thread::Thread(start_routine_t start_routine,
				   int sched_priority,
				   char *thread_name)
	{
		this->is_complete = 0;
		this->prio = 0;
		this->thread_name = thread_name;
		Logger::log_thread_details(this, "Created\n");

		pthread_mutex_init(&this->thread_control.mutex, NULL);
		pthread_mutex_init(&this->thread_control.completion_mutex, NULL);
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

	Thread::Thread(const Thread &thread)
	{
		this->thread = thread.thread;
		this->thread_name = thread.thread_name;
		this->attr = thread.attr;
		this->params = thread.params;
		this->start_routine = thread.start_routine;
		this->thread_control = thread.thread_control;
		this->is_complete = thread.is_complete;
	}

	void Thread::release_completion_mutex()
	{

		pthread_mutex_unlock(&this->thread_control.completion_mutex);
		if (DEBUG_PRINT)
		{
			printf("%s : release_completion_mutex\n", this->thread_name);
		}
	}

	int Thread::acquire_completion_mutex()
	{
		return pthread_mutex_lock(&this->thread_control.completion_mutex);
		if (DEBUG_PRINT)
		{
			printf("%s : acquire_completion_mutex \n", this->thread_name);
		}
	}

	void Thread::release_lock()
	{
		pthread_mutex_unlock(&this->thread_control.mutex);
		if (DEBUG_PRINT)
		{
			printf("%s : Release Lock\n", this->thread_name);
		}
	}

	int Thread::acquire_lock()
	{
		return pthread_mutex_lock(&this->thread_control.mutex);
		if (DEBUG_PRINT)
		{
			printf("%s : Acquire Lock\n", this->thread_name);
		}
	}

	void Thread::block()
	{
		if (DEBUG_PRINT)
		{
			printf("%s : Condvar Wait Call\n", this->thread_name);
		}
		this->acquire_lock();

		this->acquire_completion_mutex();
		this->is_complete = 0;
		this->release_completion_mutex();

		pthread_cond_wait(&this->thread_control.condvar, &this->thread_control.mutex);
	}

	void Thread::unblock()
	{
		this->acquire_completion_mutex();
		this->is_complete = 1;
		this->release_completion_mutex();

		this->release_lock();
	}

	void Thread::signal()
	{
		if (DEBUG_PRINT)
		{
			printf("%s : Signalled\n", this->thread_name);
		}
		pthread_cond_signal(&this->thread_control.condvar);
	}

	void Thread::update_priority(int prio)
	{
		this->prio = prio;
		// int pthread_setschedprio( pthread_t thread, int prio );
		if (pthread_setschedprio(this->thread, prio) != EOK)
		{
			printf("Thread Fatal Error: Couldn't change the priority of the Thread\n");
			/* TODO: Remove */
			exit(-1);
		}
	}

} // namespace realtime_vehicle_monitoring_diagnostics

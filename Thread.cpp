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

namespace realtime_vehicle_monitoring_diagnostics
{
	Thread::Thread()
	{
		// std::cout << "Thread object created" << std::endl;
		// create_thread();
	}

	Thread::~Thread()
	{
		// std::cout << "Thread object destroyed" << std::endl;
	}

	Thread::Thread(start_routine_t start_routine, int sched_priority, char *thread_name)
	{
		/* 
		pthread_create (NULL, NULL, new_thread, (void *) 123);
		 */

		pthread_attr_init(&this->attr);
		// pthread_attr_setdetachstate(&this->attr, PTHREAD_CREATE_JOINABLE);
		pthread_attr_setdetachstate(&this->attr, PTHREAD_CREATE_DETACHED);

		// pthread_attr_setinheritsched(&this->attr, PTHREAD_EXPLICIT_SCHED);
		if (pthread_attr_setinheritsched(&this->attr, PTHREAD_EXPLICIT_SCHED) != 0)
		{
			printf("ERROR: pthread_attr_setinheritsched() failed %d \n",
				   errno);
			return;
		}

		// pthread_attr_setschedpolicy(&this->attr, SCHED_FIFO);
		if (pthread_attr_setschedpolicy(&this->attr, SCHED_FIFO) != 0)
		{
			printf("ERROR: pthread_attr_setschedpolicy() failed %d\n",
				   errno);
			return;
		}

		/* set priority */
		// this->params.sched_priority = THREAD_IDLE_PRIORITY;
		this->params.sched_priority = sched_priority;

		// this->params.sched_ss_low_priority = MY_LOW_PRIORITY;
		// memcpy(&this->params.sched_ss_init_budget, &MY_INIT_BUDGET,
		// 	   sizeof(MY_INIT_BUDGET));
		// memcpy(&this->params.sched_ss_repl_period, &MY_REPL_PERIOD,
		// 	   sizeof(MY_REPL_PERIOD));
		// this->params.sched_ss_max_repl = MY_MAX_REPL;

		// ret = pthread_attr_setschedparam(&this->attr, &this->params);
		if (pthread_attr_setschedparam(&this->attr, &this->params) != 0)
		{
			printf("ERROR: pthread_attr_setschedparam() failed %d \n", errno);
			return;
		}

		this->start_routine = start_routine;

		// int ret;
		// ret = pthread_create(&this->thread,
		// 					 &this->attr,
		// 					 this->start_routine,
		// 					 NULL);

		if (pthread_create(&this->thread,
						   &this->attr,
						   this->start_routine,
						   thread_name) != EOK)
		{
			printf("ERROR: Thread Creation failed\n");
			return;
		}

		// pthread_join(this->thread, NULL);

		// EAGAIN
		// EFAULT
		// EINVAL
		// EOK
	}

	int Thread::destroy_thread(pthread_t thread)
	{
		// return pthread_abort(thread);

		// ESRCH
		// EOK
		// pthread_self()
	}

} // namespace realtime_vehicle_monitoring_diagnostics

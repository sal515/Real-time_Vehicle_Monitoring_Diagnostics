/*
 * Thread.cpp
 *
 *  Created on: Nov 14, 2020
 *      Author: Salman
 */

#include "Thread.h"
#include <iostream>

namespace realtime_vehicle_monitoring_diagnostics
{

	Thread::Thread()
	{
		std::cout << "Thread object created" << std::endl;
		// create_thread();
	}

	Thread::~Thread()
	{
		std::cout << "Thread object destroyed" << std::endl;
	}

	Thread::Thread(pthread_t thread, pthread_attr_t attr, start_routine_t start_routine, void *args)
	{
		// return pthread_create(&threadInfo.thread, &threadInfo.attr, threadInfo.start_routine, NULL);
		/* 
		pthread_create (NULL, NULL, new_thread, (void *) 123);
		 */

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

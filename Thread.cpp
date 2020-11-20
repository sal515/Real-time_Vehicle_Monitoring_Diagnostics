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
		// TODO Auto-generated constructor stub
		std::cout << "Thread object created" << std::endl;
		
		// create_thread();
	}

	Thread::~Thread()
	{
		// TODO Auto-generated destructor stub
		std::cout << "Thread object destroyed" << std::endl;
	}

	int Thread::create_thread(thread_info_t threadInfo)
	{
		return pthread_create(&threadInfo.thread, &threadInfo.attr, threadInfo.start_routine, NULL);

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
		return pthread_abort(thread);

		// ESRCH
		// EOK
		// pthread_self()
	}

} // namespace realtime_vehicle_monitoring_diagnostics

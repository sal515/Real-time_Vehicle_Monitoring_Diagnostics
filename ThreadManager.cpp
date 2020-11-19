/*
 * ThreadManager.cpp
 *
 *  Created on: Nov 14, 2020
 *      Author: Salman
 */

#include "ThreadManager.h"
#include <iostream>

namespace realtime_vehicle_monitoring_diagnostics
{

	ThreadManager::ThreadManager()
	{
		// TODO Auto-generated constructor stub
		std::cout << "ThreadManager object created" << std::endl;
	}

	ThreadManager::~ThreadManager()
	{
		// TODO Auto-generated destructor stub
		std::cout << "ThreadManager object destroyed" << std::endl;
	}

	int ThreadManager::create_thread(thread_info_t threadInfo)
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

	int ThreadManager::destroy_thread(pthread_t thread)
	{
		return pthread_abort(thread);

		// ESRCH
		// EOK
		// pthread_self()
	}

} // namespace realtime_vehicle_monitoring_diagnostics

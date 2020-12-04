/*
 * Thread.h
 *
 *  Created on: Nov 14, 2020
 *      Author: Salman
 */

#ifndef THREAD_H_
#define THREAD_H_

#include <pthread.h>

namespace realtime_vehicle_monitoring_diagnostics
{
#define THREAD_IDLE_PRIORITY (1)
#define THREAD_IDLE_PRIORITY (60)

	typedef void *(*start_routine_t)(void *);
	struct Thread_Control
	{
		// int data_ready = 0;
		pthread_mutex_t mutex;
		pthread_cond_t condvar;
	};

	class Thread
	{
	public:
		Thread();
		Thread(start_routine_t start_routine,
			   int sched_priority,
			   char *thread_name);
		virtual ~Thread();

		pthread_t thread;
		char *thread_name;

		// void *args;
		pthread_attr_t attr;
		struct sched_param params;
		start_routine_t start_routine;
		struct Thread_Control thread_control;

		void signal();
		void block();
		void unblock();

		int update_priority(int prio);
		// int pthread_setschedprio( pthread_t thread, int prio );
	};

} // namespace realtime_vehicle_monitoring_diagnostics

#endif /* THREAD_H_ */

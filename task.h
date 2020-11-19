/*
 * Task.h
 *
 *  Created on: Nov 14, 2020
 *      Author: Salman
 */

#ifndef TASK_H_
#define TASK_H_

#include <pthread.h>

namespace realtime_vehicle_monitoring_diagnostics
{
	typedef void *(*start_routine_t)(void *);

	enum TaskType
	{
		PERIODIC,
		APERIODIC,
		SPORADIC
	};

	struct thread_info_t
	{
		pthread_t thread;
		pthread_attr_t attr;
		start_routine_t start_routine;
		void *args;
	};

	class Task
	{
	public:
		Task();
		virtual ~Task();

		TaskType task_type;
		long executed_time;
		thread_info_t thread_info;
	};

} // namespace realtime_vehicle_monitoring_diagnostics

#endif /* TASK_H_ */

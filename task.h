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

	enum TaskType
	{
		PERIODIC,
		APERIODIC,
		SPORADIC
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

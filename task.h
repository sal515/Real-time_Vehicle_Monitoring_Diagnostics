/*
 * Task.h
 *
 *  Created on: Nov 14, 2020
 *      Author: Salman
 */

#ifndef TASK_H_
#define TASK_H_

#include "Thread.h"
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

		virtual void debug_print();

		TaskType task_type;
		long executed_time;
		Thread thread;
	};

} // namespace realtime_vehicle_monitoring_diagnostics

#endif /* TASK_H_ */

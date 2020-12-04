/*
 * Task.h
 *
 *  Created on: Nov 14, 2020
 *      Author: Salman
 */

#ifndef TASK_H_
#define TASK_H_

#include "Thread.h"

namespace realtime_vehicle_monitoring_diagnostics
{
	enum Priority
	{
		HIGH,
		MED,
		LOW

	};

	enum TaskType
	{
		PERIODIC,
		APERIODIC,
		SPORADIC
	};

	class Task
	{
	public:
		virtual void debug_print() = 0;

		char *task_name; // max length of task name
		// char task_name[100]; // max length of task name
		TaskType task_type;
		long last_start_time;
		long executed_time;
		long priority;
		Thread thread;
	};

} // namespace realtime_vehicle_monitoring_diagnostics

#endif /* TASK_H_ */

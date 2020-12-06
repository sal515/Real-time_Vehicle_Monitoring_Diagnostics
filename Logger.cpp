/*
 * Logger.cpp
 *
 *  Created on: Dec 5, 2020
 *      Author: Salman
 */

#include "Logger.h"
#include <stdio.h>

namespace realtime_vehicle_monitoring_diagnostics
{

	Logger::Logger()
	{
	}

	Logger::~Logger()
	{
	}

	void Logger::log_task_details(Task *task, char *event_string)
	{
		switch (task->task_type)
		{
		case PERIODIC:
		{
			PeriodicTask *task_periodic = static_cast<PeriodicTask *>(task);
			printf("%s -> Name: %s, Period: %u, Deadline: %u, Released Time: %u, Executed Time: %u, Processing Done: %u, Priority: %u\n",
				   event_string,
				   task_periodic->task_name,
				   task_periodic->period,
				   task_periodic->deadline,
				   task_periodic->released_time,
				   task_periodic->executed_time,
				   task_periodic->thread.is_complete,
				   task_periodic->thread.prio);
			break;
		}
		case APERIODIC:
		{
			break;
		}
		case SPORADIC:
		{
			break;
		}
		default:
		{
			break;
		}
		}
	}

	void Logger::log_thread_details(Thread *thread, char *event_string)
	{
		printf("%s -> Thread Name: %s, \n",
			   event_string,
			   thread->thread_name);
	}

} // namespace realtime_vehicle_monitoring_diagnostics

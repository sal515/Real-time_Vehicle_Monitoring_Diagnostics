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
		// TODO Auto-generated constructor stub
	}

	Logger::~Logger()
	{
		// TODO Auto-generated destructor stub
	}

	void Logger::log_task_details(Task *task)
	{
		switch (task->task_type)
		{
		case PERIODIC:
		{
			PeriodicTask *task_periodic = static_cast<PeriodicTask *>(task);
			printf("Task -> Name: %s, Period: %u, Deadline: %u, Executed Time: %u\n",
				   task_periodic->task_name,
				   task_periodic->period,
				   task_periodic->deadline,
				   task_periodic->executed_time);
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

} // namespace realtime_vehicle_monitoring_diagnostics

/*
 * PeriodicTask.cpp
 *
 *  Created on: Nov 16, 2020
 *      Author: Salman
 */

#include "PeriodicTask.h"
#include <iostream>
#include <string.h>
#include <stdio.h>
#include "Logger.h"
#include <cerrno>

#define LOG_COPY_CONSTRUCTOR 0
#define LOG_CREATED_TASK 0
// #define LOG_REMOVED_TASK 0
#define LOG_REMOVED_TASK 1
#define DEBUG_PRINT 0

namespace realtime_vehicle_monitoring_diagnostics
{

	PeriodicTask::PeriodicTask(long period,
							   long execution_time,
							   char task_name[],
							   start_routine_t routine,
							   long relative_deadline,
							   long phase)
	{

		this->phase = phase;
		this->period = period;
		this->execution_time = execution_time;
		this->relative_deadline = relative_deadline;
		if (relative_deadline == -1)
		{
			this->relative_deadline = this->period;
		}
		this->deadline = -1;

		this->task_name = task_name;
		this->task_type = PERIODIC;
		this->released_time = 0;
		this->executed_time = 0;
		this->routine = routine;
		if (LOG_CREATED_TASK)
		{
			Logger::log_task_details(this, "Created Periodic Task\n");
		}
	}

	PeriodicTask::~PeriodicTask()
	{
		// try
		// {
		// 	delete this->thread;
		// }
		// catch (std::exception &e)
		// {
		// 	printf("Error: %s\n", strerror(errno));
		// }
		/* TODO: Kill the thread if not killed */
		if (LOG_REMOVED_TASK)
		{
			Logger::log_task_details(this, "Removed Periodic Task Detailed:\n");
		}
	}

	PeriodicTask::PeriodicTask(const PeriodicTask &periodicTask)
	{
		this->phase = periodicTask.phase;
		this->period = periodicTask.period;
		this->execution_time = periodicTask.execution_time;
		this->relative_deadline = periodicTask.relative_deadline;
		this->deadline = periodicTask.deadline;

		this->task_name = periodicTask.task_name;
		this->task_type = periodicTask.task_type;
		this->released_time = periodicTask.released_time;
		this->executed_time = periodicTask.executed_time;
		this->routine = periodicTask.routine;

		if (LOG_COPY_CONSTRUCTOR)
		{
			Logger::log_task_details(this, "Copy Constructor Periodic Task\n");
		}
	}

} // namespace realtime_vehicle_monitoring_diagnostics

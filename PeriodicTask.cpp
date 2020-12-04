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

#define DEBUG_PRINT 0

namespace realtime_vehicle_monitoring_diagnostics
{

	PeriodicTask::PeriodicTask(long period, long execution_time, char task_name[], long relative_deadline, long phase)
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
		this->executed_time = 0;
		this->priority = LOW;
		/* TODO: Setup Thread Creation */
		// this->thread = null;
	}

	PeriodicTask::~PeriodicTask()
	{
		if (DEBUG_PRINT)
		{
			printf("PeriodicTask object destroyed\n");
		}
	}

	PeriodicTask::PeriodicTask(const PeriodicTask &periodicTask)
	{
		this->phase = periodicTask.phase;
		this->period = periodicTask.period;
		this->executed_time = periodicTask.executed_time;
		this->relative_deadline = periodicTask.relative_deadline;
		this->deadline = periodicTask.deadline;

		this->task_name = periodicTask.task_name;
		this->task_type = periodicTask.task_type;
		this->executed_time = periodicTask.executed_time;
		this->priority = LOW;
		/* TODO: Setup Thread Creation */
		//		this->thread = PeriodicTask.thread;
	}

	void PeriodicTask::debug_print()
	{
		printf("________________________________\n");
		printf("Periodic Task class debug print\n");
		printf("________________________________\n");

		printf("Phase is: %l \n", this->phase);
		printf("Period is: %l \n", this->period);
		printf("Execution_time is: %l \n", this->execution_time);
		printf("Executed_time is: %l \n", this->executed_time);
		printf("Task_type is: %l \n", this->task_type);
		printf("Relative_deadline is: %l \n", this->relative_deadline);
		printf("Deadline is: %l \n", this->deadline);
	}

} // namespace realtime_vehicle_monitoring_diagnostics

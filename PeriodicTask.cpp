/*
 * PeriodicTask.cpp
 *
 *  Created on: Nov 16, 2020
 *      Author: Salman
 */

#include "PeriodicTask.h"
#include <iostream>
#include <string.h>

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
			this->relative_deadline = period;
		}

		this->task_name = task_name;
		this->task_type = PERIODIC;
		this->executed_time = 0;
		// this->thread = null;
	}

	PeriodicTask::~PeriodicTask()
	{
		std::cout << "PeriodicTask object destroyed" << std::endl;
	}

	PeriodicTask::PeriodicTask(const PeriodicTask &periodicTask)
	{
		this->phase = periodicTask.phase;
		this->period = periodicTask.period;
		this->executed_time = periodicTask.executed_time;
		this->relative_deadline = periodicTask.relative_deadline;

		this->task_name = periodicTask.task_name;
		this->task_type = periodicTask.task_type;
		this->executed_time = periodicTask.executed_time;
//		this->thread = PeriodicTask.thread;
	}

	void PeriodicTask::debug_print()
	{
		std::cout << "________________________________" << std::endl;
		std::cout << "Periodic Task class debug print" << std::endl;
		std::cout << "________________________________" << std::endl;

		std::cout << "Phase is: " << this->phase << std::endl;
		std::cout << "Period is: " << this->period << std::endl;
		std::cout << "Execution_time is: " << this->execution_time << std::endl;
		std::cout << "Executed_time is: " << this->executed_time << std::endl;
		std::cout << "Task_type is: " << this->task_type << std::endl;
		std::cout << "Relative_deadline is: " << this->relative_deadline << std::endl;
	}

} // namespace realtime_vehicle_monitoring_diagnostics

/*
 * PeriodicTask.cpp
 *
 *  Created on: Nov 16, 2020
 *      Author: Salman
 */

#include "PeriodicTask.h"
#include <iostream>

namespace realtime_vehicle_monitoring_diagnostics
{

	// PeriodicTask::PeriodicTask():Task() {
	PeriodicTask::PeriodicTask()
	{
		// TODO Auto-generated constructor stub
		std::cout << "PeriodicTask object created" << std::endl;

		this->phase = -1;
		this->period = -1;
		this->execution_time = -1;
		this->relative_deadline = -1;

		this->executed_time = 0;
		this->task_type = PERIODIC;
	}

	PeriodicTask::PeriodicTask(long period, long execution_time, long relative_deadline, long phase)
	{
		this->phase = phase;
		this->period = period;
		this->execution_time = execution_time;
		this->relative_deadline = relative_deadline;

		this->executed_time = 0;
		this->task_type = PERIODIC;

		// this->last_started_time = 0;
		if (relative_deadline == -1)
		{
			this->relative_deadline = period;
		}
	}

	PeriodicTask::~PeriodicTask()
	{
		// TODO Auto-generated destructor stub
		std::cout << "PeriodicTask object destroyed" << std::endl;
	}

} // namespace realtime_vehicle_monitoring_diagnostics

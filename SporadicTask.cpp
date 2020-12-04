/*
 * SporadicTasks.cpp
 *
 *  Created on: Nov 29, 2020
 *      Author: Salman
 */

#include "SporadicTask.h"

namespace realtime_vehicle_monitoring_diagnostics
{

	SporadicTask::SporadicTask(long execution_time, char task_name[], long relative_deadline)
	{
		this->execution_time = execution_time;
		this->relative_deadline = relative_deadline;

		this->task_name = task_name;
		this->task_type = SPORADIC;
		this->executed_time = 0;
		this->priority = LOW;
		// this->thread = null;
	}

	SporadicTask::~SporadicTask()
	{
		// TODO Auto-generated destructor stub
	}

} // namespace realtime_vehicle_monitoring_diagnostics

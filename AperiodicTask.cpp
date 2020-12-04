/*
 * AperiodicTask.cpp
 *
 *  Created on: Nov 29, 2020
 *      Author: Salman
 */

#include "AperiodicTask.h"

namespace realtime_vehicle_monitoring_diagnostics
{

	AperiodicTask::AperiodicTask(long execution_time, char task_name[])
	{
		this->execution_time = execution_time;

		this->task_name = task_name;
		this->task_type = APERIODIC;
		this->executed_time = 0;
		this->priority = LOW;
		// this->thread = Null;
	}

	AperiodicTask::~AperiodicTask()
	{
	}

} // namespace realtime_vehicle_monitoring_diagnostics

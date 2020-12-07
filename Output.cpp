/*
 * Output.cpp
 *
 *  Created on: Dec 6, 2020
 *      Author: Salman
 */

#include "Output.h"

namespace realtime_vehicle_monitoring_diagnostics
{

	Output::Output(char *task_name, std::string value)
	{

		this->task_name = task_name;
		this->value = value;
	}

	Output::~Output()
	{
		// TODO Auto-generated destructor stub
	}

} // namespace realtime_vehicle_monitoring_diagnostics

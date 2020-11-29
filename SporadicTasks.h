/*
 * SporadicTasks.h
 *
 *  Created on: Nov 29, 2020
 *      Author: Salman
 */

#ifndef SPORADICTASKS_H_
#define SPORADICTASKS_H_
#include "Task.h"

namespace realtime_vehicle_monitoring_diagnostics
{

	class SporadicTasks : public realtime_vehicle_monitoring_diagnostics::Task
	{
	public:
		SporadicTasks();
		virtual ~SporadicTasks();
	};

} // namespace realtime_vehicle_monitoring_diagnostics

#endif /* SPORADICTASKS_H_ */

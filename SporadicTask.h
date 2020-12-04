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

	class SporadicTask : public realtime_vehicle_monitoring_diagnostics::Task
	{
	public:
		SporadicTask(long execution_time, char task_name[], long relative_deadline = -1);
		virtual ~SporadicTask();

		long execution_time;
		long relative_deadline;
	};

} // namespace realtime_vehicle_monitoring_diagnostics

#endif /* SPORADICTASKS_H_ */

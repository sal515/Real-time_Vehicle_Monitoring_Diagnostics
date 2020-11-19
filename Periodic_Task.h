/*
 * Periodic_Task.h
 *
 *  Created on: Nov 16, 2020
 *      Author: Salman
 */

#ifndef PERIODIC_TASK_H_
#define PERIODIC_TASK_H_

#include "task.h"

namespace realtime_vehicle_monitoring_diagnostics
{

	class Periodic_Task : public realtime_vehicle_monitoring_diagnostics::Task
	{
	public:
		Periodic_Task();
		Periodic_Task(long period, long execution_time, long relative_deadline = -1, long phase = 0);

		virtual ~Periodic_Task();

		long phase;
		long period;
		long execution_time;
		long relative_deadline;
	};

} // namespace realtime_vehicle_monitoring_diagnostics

#endif /* PERIODIC_TASK_H_ */

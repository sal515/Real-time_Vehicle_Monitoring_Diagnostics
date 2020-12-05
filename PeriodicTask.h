/*
 * PeriodicTask.h
 *
 *  Created on: Nov 16, 2020
 *      Author: Salman
 */

#ifndef PERIODIC_TASK_H_
#define PERIODIC_TASK_H_

#include "Task.h"

namespace realtime_vehicle_monitoring_diagnostics
{

	class PeriodicTask : public realtime_vehicle_monitoring_diagnostics::Task
	{
	public:
		PeriodicTask(long period,
					 long execution_time,
					 char task_name[],
					 start_routine_t routine,
					 long relative_deadline = -1,
					 long phase = 0);
		PeriodicTask(const PeriodicTask &periodicTask);
		virtual ~PeriodicTask();

		void debug_print();

		long phase;
		long period;
		long execution_time;
		long relative_deadline;
		long deadline;
	};

} // namespace realtime_vehicle_monitoring_diagnostics

#endif /* PERIODIC_TASK_H_ */

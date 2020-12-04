/*
 * AperiodicTask.h
 *
 *  Created on: Nov 29, 2020
 *      Author: Salman
 */

#ifndef APERIODICTASK_H_
#define APERIODICTASK_H_
#include "Task.h"

namespace realtime_vehicle_monitoring_diagnostics
{

	class AperiodicTask : public realtime_vehicle_monitoring_diagnostics::Task
	{
	public:
		AperiodicTask(long execution_time, char task_name[]);
		virtual ~AperiodicTask();

		long execution_time;
	};

} // namespace realtime_vehicle_monitoring_diagnostics

#endif /* APERIODICTASK_H_ */

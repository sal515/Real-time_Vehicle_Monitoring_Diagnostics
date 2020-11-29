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
		AperiodicTask();
		virtual ~AperiodicTask();
	};

} // namespace realtime_vehicle_monitoring_diagnostics

#endif /* APERIODICTASK_H_ */

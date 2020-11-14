/*
 * Task.h
 *
 *  Created on: Nov 14, 2020
 *      Author: Salman
 */

#ifndef TASK_H_
#define TASK_H_

namespace realtime_vehicle_monitoring_diagnostics
{
//	#include <bits/stdc++.h>
	enum  TaskType
	{
		PERIODIC,
		APERIODIC,
		SPORADIC
	};

	class Task
	{
	public:
		Task();
		virtual ~Task();

		int task_type;
	};

} // namespace realtime_vehicle_monitoring_diagnostics

#endif /* TASK_H_ */

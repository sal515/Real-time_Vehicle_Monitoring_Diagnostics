/*
 * task.h
 *
 *  Created on: Nov 14, 2020
 *      Author: Salman
 */

#ifndef TASK_H_
#define TASK_H_

namespace realtime_vehicle_monitoring_diagnostics
{

	enum class task_type
	{
		PERIODIC,
		APERIODIC,
		SPORADIC
	}

	class task
	{

	public:
		task();
		virtual ~task();

		task_type task_typ

	};

} // namespace realtime_vehicle_monitoring_diagnostics

#endif /* TASK_H_ */

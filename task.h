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
	enum TaskType
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

		// Task(long period, long execution_time, long relative_deadline = -1, long phase = 0);

		TaskType task_type;
		long executed_time;

		// long last_started_time;
		// void increment_executed_time_by(long time);
	};

} // namespace realtime_vehicle_monitoring_diagnostics

#endif /* TASK_H_ */

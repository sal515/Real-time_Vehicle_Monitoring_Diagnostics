/*
 * Logger.h
 *
 *  Created on: Dec 5, 2020
 *      Author: Salman
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include "task.h"
#include "PeriodicTask.h"
namespace realtime_vehicle_monitoring_diagnostics
{

	class Logger
	{
	public:
		Logger();
		virtual ~Logger();
		static void log_task_details(Task *task, char *event_string);
	};

} // namespace realtime_vehicle_monitoring_diagnostics

#endif /* LOGGER_H_ */

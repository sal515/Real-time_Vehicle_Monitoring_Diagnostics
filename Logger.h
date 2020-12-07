/*
 * Logger.h
 *
 *  Created on: Dec 5, 2020
 *      Author: Salman
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include <iostream>
#include <fstream>
#include <time.h>
#include <stdio.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "task.h"
#include "PeriodicTask.h"
#include "Thread.h"

namespace realtime_vehicle_monitoring_diagnostics
{

	class Logger
	{
	public:
		Logger();
		virtual ~Logger();
		static void log_task_details(Task *task, char *event_string);
		static void log_thread_details(Thread *thread, const char *event_string);

		static void create_open_log_file(int &fd);
		static void close_file(int &fd);
		static void write_to_file(int fd, const char *buffer, int size_of_buffer);

		static void create_open_log_file(std::ofstream &file);
		static void close_file(std::ofstream &file);
		static void write_to_file(std::ofstream &file, char *msg);
	};

} // namespace realtime_vehicle_monitoring_diagnostics

#endif /* LOGGER_H_ */

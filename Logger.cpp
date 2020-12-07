/*
 * Logger.cpp
 *
 *  Created on: Dec 5, 2020
 *      Author: Salman
 */

#include "Logger.h"
#include <stdio.h>

#define MAX_LOG_FILE_NAME_SIZE 300

namespace realtime_vehicle_monitoring_diagnostics
{
	void Logger::create_open_log_file(int &fd)
	{
		time_t raw_time_now = time(0);
		struct tm *time_info = localtime(&raw_time_now);
		char buffer[MAX_LOG_FILE_NAME_SIZE];
		strftime(buffer,
				 MAX_LOG_FILE_NAME_SIZE,
				 "Log_%Y-%m-%d_%H-%M-%S.txt",
				 time_info);

		fd = open(buffer,
				  O_WRONLY | O_CREAT | O_APPEND,
				  S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	}

	void Logger::create_open_log_file(std::ofstream &file)
	{
		time_t raw_time_now = time(0);
		struct tm *time_info = localtime(&raw_time_now);
		char buffer[MAX_LOG_FILE_NAME_SIZE];
		strftime(buffer,
				 MAX_LOG_FILE_NAME_SIZE,
				 "Log_%Y-%m-%d_%H-%M-%S.txt",
				 time_info);

		file.open(buffer);

		if (!file.is_open())
		{
			printf("Fatal Error in creating log file\n");
		}
	}

	void Logger::close_file(int &fd)
	{
		if (fd != -1)
		{
			close(fd);
		}
	}

	void Logger::close_file(std::ofstream &file)
	{
		file.close();
	}

	void Logger::write_to_file(std::ofstream &file, char *msg)
	{
		file << msg;
	}

	void Logger::write_to_file(int fd, const char *buffer, int size_of_buffer)
	{
		if (write(fd, buffer, size_of_buffer) != size_of_buffer)
		{
			printf("Error writing to the Log file\n");
		}
	}

	void Logger::log_task_details(Task *task, char *event_string)
	{
		switch (task->task_type)
		{
		case PERIODIC:
		{
			PeriodicTask *task_periodic = static_cast<PeriodicTask *>(task);
			printf("%s ---> Period: %u, Deadline: %u, Released Time: %u, Executed Time: %u, Name: %s\n",
				   event_string,
				   task_periodic->period,
				   task_periodic->deadline,
				   task_periodic->released_time,
				   task_periodic->executed_time,
				   task_periodic->task_name);

			// PeriodicTask *task_periodic = static_cast<PeriodicTask *>(task);
			// printf("%s -> Period: %u, Deadline: %u, Released Time: %u, Executed Time: %u, Processing Done: %u, Priority: %u, Name: %s\n",
			// 	   event_string,
			// 	   task_periodic->period,
			// 	   task_periodic->deadline,
			// 	   task_periodic->released_time,
			// 	   task_periodic->executed_time,
			// 	   task_periodic->thread.is_complete,
			// 	   task_periodic->thread.prio,
			// 	   task_periodic->task_name);
			break;
		}
		case APERIODIC:
		{
			break;
		}
		case SPORADIC:
		{
			break;
		}
		default:
		{
			break;
		}
		}
	}

	void Logger::log_thread_details(Thread *thread, const char *event_string)
	{
		printf("%s ---> Thread Name: %s, priority: %u, completed: %u \n",
			   event_string,
			   thread->thread_name,
			   thread->prio,
			   thread->is_complete);
	}

} // namespace realtime_vehicle_monitoring_diagnostics

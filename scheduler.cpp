/*
 * Scheduler.cpp
 *
 *  Created on: Nov 14, 2020
 *      Author: Salman
 */

#include "Scheduler.h"
#include <iostream>

#include <stdio.h>

#define DEBUG_PRINT 1

namespace realtime_vehicle_monitoring_diagnostics
{

	Scheduler::Scheduler()
	{
		std::cout << "Scheduler object created" << std::endl;
	}

	Scheduler::~Scheduler()
	{
		std::cout << "Scheduler object destroyed" << std::endl;
	}

	void Scheduler::add_periodic_task(PeriodicTask perodicTask, std::vector<PeriodicTask> *periodicTasks)
	{
		periodicTasks->push_back(perodicTask);
	}

	void Scheduler::release_periodic_tasks(unsigned timer_storage,
										   std::vector<PeriodicTask> *periodicTasks,
										   std::priority_queue<PeriodicTask *, std::vector<PeriodicTask *>, comparePeriodicTasks> *periodicReleasedQueue)
	{
		/* Release Periodic Tasks */
		int periodicTasksSize = periodicTasks->size();
		for (int i = 0; i < periodicTasksSize; i++)
		{
			if (timer_storage % periodicTasks->at(i).period == 0)
			{
				periodicReleasedQueue->push(new PeriodicTask(periodicTasks->at(i)));

				if (DEBUG_PRINT)
				{
					printf("Added task name is: %s\n", periodicTasks->at(i).task_name);
				}
			}
		}
		/* Release Aperiodic Tasks */

		/* Release Sporatic Tasks */
	}

	int Scheduler::get_running_queue_size(std::priority_queue<PeriodicTask *, std::vector<PeriodicTask *>, comparePeriodicTasks> *periodicReleasedQueue)
	{
		return periodicReleasedQueue->size();
	}

} // namespace realtime_vehicle_monitoring_diagnostics

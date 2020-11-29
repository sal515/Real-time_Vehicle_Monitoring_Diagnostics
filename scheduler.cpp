/*
 * Scheduler.cpp
 *
 *  Created on: Nov 14, 2020
 *      Author: Salman
 */

#include "Scheduler.h"
#include <iostream>

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

	void Scheduler::add_periodic_task(PeriodicTask perodicTask, std::vector<PeriodicTask> *perodicTasks)
	{
		perodicTasks->push_back(perodicTask);
	}

	void Scheduler::release_update(unsigned timer_storage,
								   std::vector<PeriodicTask> *perodicTasks,
								   std::priority_queue<PeriodicTask *, std::vector<PeriodicTask *>, comparePeriodicTasks> *runningQueue)
	{
		int periodicTasksSize = perodicTasks->size();
		for (int i = 0; i < periodicTasksSize; i++)
		{
			if (timer_storage % perodicTasks->at(i).period == 0)
			{
				runningQueue->push(new PeriodicTask(perodicTasks->at(i)));
			}
		}
	}

	int Scheduler::get_running_queue_size(std::priority_queue<PeriodicTask *, std::vector<PeriodicTask *>, comparePeriodicTasks> *runningQueue)
	{
		return runningQueue->size();
	}

} // namespace realtime_vehicle_monitoring_diagnostics

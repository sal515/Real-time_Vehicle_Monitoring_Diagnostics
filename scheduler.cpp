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
		// TODO Auto-generated constructor stub
		std::cout << "Scheduler object created" << std::endl;
	}

	Scheduler::~Scheduler()
	{
		// TODO Auto-generated destructor stub
		std::cout << "Scheduler object destroyed" << std::endl;
	}

	void Scheduler::add_periodic_task(PeriodicTask perodicTask, std::vector<PeriodicTask> *perodicTasks)
	{
		perodicTasks->push_back(perodicTask);
	}

	void Scheduler::release_update(unsigned timer_storage,
								   std::vector<PeriodicTask> *perodicTasks,
								   std::vector<Task *> *runningQueue)
	{
		int periodicTasksSize = perodicTasks->size();
		for (int i = 0; i < periodicTasksSize; i++)
		{
			if (timer_storage % perodicTasks->at(i).period == 0)
			{
				runningQueue->push_back(new PeriodicTask(perodicTasks->at(i)));
			}
		}
	}

	int Scheduler::get_running_queue_size(std::vector<Task *> *runningQueue)
	{
		return runningQueue->size();
	}

	int Scheduler::get_periodic_tasks_size(std::vector<PeriodicTask> *perodicTasks)
	{
		return perodicTasks->size();
	}

} // namespace realtime_vehicle_monitoring_diagnostics

/*
 * Scheduler.cpp
 *
 *  Created on: Nov 14, 2020
 *      Author: Salman
 */

#include "Scheduler.h"
#include <iostream>
#include <stdio.h>

#define DEBUG_PRINT 0

namespace realtime_vehicle_monitoring_diagnostics
{

	Scheduler::Scheduler()
	{
		if (DEBUG_PRINT)
		{
			printf("Scheduler object created\n");
		}
	}

	Scheduler::~Scheduler()
	{
		if (DEBUG_PRINT)
		{
			printf("Scheduler object destroyed\n");
		}
	}

	void Scheduler::add_periodic_task(PeriodicTask perodicTask)
	{
		this->periodicTasks.push_back(perodicTask);
	}

	void Scheduler::release_periodic_tasks(unsigned timer_storage)
	{
		/* Release Periodic Tasks */
		int periodicTasksSize = this->periodicTasks.size();
		for (int i = 0; i < periodicTasksSize; i++)
		{
			if (timer_storage % this->periodicTasks.at(i).period == 0)
			{
				PeriodicTask *temp = new PeriodicTask(this->periodicTasks.at(i));
				temp->deadline = timer_storage + temp->relative_deadline;
				this->periodicReleasedQueue.push(temp);

				if (DEBUG_PRINT)
				{
					printf("Added task name is: %s\n", this->periodicTasks.at(i).task_name);
				}
			}
		}
	}

	/* TODO: Release Aperiodic Tasks */
	/* TODO: Release Sporatic Tasks */

	void Scheduler::priority_update_periodic_tasks(unsigned timer_storage)
	{
		/* Update executed time */
		while (!this->runningQueue.empty())
		{
			Task *temp = this->runningQueue.front();

			switch (temp->task_type)
			{
			case PERIODIC:
				/* update executed time */
				temp->executed_time += timer_storage - temp->last_start_time;
				/* TODO: Update priority */
				/* add the task back to the periodicReleaseQueue */
				this->periodicReleasedQueue.push(static_cast<PeriodicTask *>(temp));
				this->runningQueue.pop();
				break;
			case APERIODIC:
				printf("WARNING: APERIODIC - NOT IMPLEMENTED");
				break;
			case SPORADIC:
				printf("WARNING: SPORADIC - NOT IMPLEMENTED");
				break;
			default:
				break;
			}
		}

		/* Pop tasks from priority queue and set highest priority */
	}

	int Scheduler::get_running_queue_size()
	{
		return this->periodicReleasedQueue.size();
	}

} // namespace realtime_vehicle_monitoring_diagnostics

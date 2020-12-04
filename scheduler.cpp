/*
 * Scheduler.cpp
 *
 *  Created on: Nov 14, 2020
 *      Author: Salman
 */

#include "Scheduler.h"
#include <iostream>
#include <stdio.h>

// #define DEBUG_PRINT 0
#define DEBUG_PRINT 1

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
				PeriodicTask *periodic_task = new PeriodicTask(this->periodicTasks.at(i));
				/* TODO: SORT PRIORITY QUEUE BY DEADLINE */
				periodic_task->deadline = timer_storage + periodic_task->relative_deadline;
				this->periodicReleasedQueue.push(periodic_task);

				if (DEBUG_PRINT)
				{
					printf("Added task name is: %s\n", this->periodicTasks.at(i).task_name);
				}
			}
		}
	}

	/* TODO: Release Aperiodic Tasks */
	/* TODO: Release Sporatic Tasks */

	void Scheduler::update_executed_priority(unsigned timer_storage)
	{
		std::queue<Task *> temp_running_queue;

		while (!this->runningQueue.empty())
		{
			Task *running_task = this->runningQueue.front();

			/* update executed time */
			/* TODO: FIXME IMP - How to set the last start time?? */
			running_task->executed_time += timer_storage - running_task->last_start_time;

			switch (running_task->task_type)
			{
			case PERIODIC:
			{ /* 
				Check if the task is complete 
				*/
				running_task->thread.acquire_completion_mutex();
				if (running_task->thread.is_complete)
				{
					/* Remove the completed task from running queue */
					this->runningQueue.pop();
					running_task->thread.release_completion_mutex();

					/* release memory */
					delete running_task;
					/* TODO: LOG: completion of task  */
					continue;
				}
				running_task->thread.release_completion_mutex();

				/* 
				If task is not complete and waiting 
				*/
				PeriodicTask *next_to_release_periodic_task = this->periodicReleasedQueue.top();
				PeriodicTask *current_running_task = static_cast<PeriodicTask *>(running_task);

				/* TODO: Check logic - check how deadline is calculated */
				if (current_running_task->deadline > next_to_release_periodic_task->deadline)
				{
					/* put current_running_task to wait */
					/* TODO: can it be Block or kill -> current_running_task? */
					// TODO: CHECK VERIFY ->
					current_running_task->thread.block();
					/* lower the priority of current_running_task*/
					current_running_task->thread.update_priority(THREAD_IDLE_PRIORITY);
					/* add the current_running_task back to the periodicReleaseQueue */
					this->periodicReleasedQueue.push(current_running_task);
					/* pop the current_running_task from the runningQueue */
					this->runningQueue.pop();
					/* increase the priority of next_to_release_periodic_task */
					next_to_release_periodic_task->thread.update_priority(THREAD_RUN_PRIORITY);
					/* add the next_to_release_periodic_task to the temp_running_queue */
					temp_running_queue.push(next_to_release_periodic_task);
				}

				/* add the task back to the periodicReleaseQueue */
				// this->periodicReleasedQueue.push(static_cast<PeriodicTask *>(running_task));
				/* TODO: Check if needs to be done? */
				// this->runningQueue.pop();
				/* TODO: Update priority based on EDF? */
				/* TODO: Update priority based on EDF? */
				break;
			}
			case APERIODIC:
			{
				printf("WARNING: APERIODIC - NOT IMPLEMENTED");
				break;
			}
			case SPORADIC:
			{
				printf("WARNING: SPORADIC - NOT IMPLEMENTED");
				break;
			}
			default:
			{
				break;
			}
			}
		}
		/* TODO: Add all the temporary running queued task to running queu */
	}

	int Scheduler::get_running_queue_size()
	{
		return this->periodicReleasedQueue.size();
	}

} // namespace realtime_vehicle_monitoring_diagnostics

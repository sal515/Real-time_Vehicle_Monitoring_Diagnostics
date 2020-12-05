/*
 * Scheduler.cpp
 *
 *  Created on: Nov 14, 2020
 *      Author: Salman
 */

#include "Scheduler.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#define DEBUG_PRINT 0
// #define DEBUG_PRINT 1

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
			if (timer_storage < this->periodicTasks.at(i).phase)
			{
				continue;
			}

			if ((timer_storage % this->periodicTasks.at(i).period == 0))
			{

				PeriodicTask *periodic_task = new PeriodicTask(this->periodicTasks.at(i));
				periodic_task->deadline = timer_storage + periodic_task->relative_deadline;
				this->periodicWaitingQueue.push(periodic_task);

				if (DEBUG_PRINT)
				{
					printf("Added task name is: %s\n", this->periodicTasks.at(i).task_name);
				}
			}
		}
	}

	/* FUTURE IMPLEMENTATION: Release Aperiodic Tasks */
	/* FUTURE IMPLEMENTATION: Release Sporatic Tasks */

	void Scheduler::update_executed_time(unsigned timer_storage)
	{
		int periodic_task_queue_size = this->periodicRunningQueue.size();
		std::priority_queue<PeriodicTask *, std::vector<PeriodicTask *>, Compare_Periodic_Task_by_LDF> tempRunningQueue;

		for (int i = 0; i < periodic_task_queue_size; i++)
		{
			PeriodicTask *current_running_task = this->periodicRunningQueue.top();

			/*
				Remove if the task is complete
			*/
			current_running_task->thread.acquire_completion_mutex();
			if (current_running_task->thread.is_complete)
			{
				/* Remove the completed task from running queue */
				this->periodicRunningQueue.pop();
				current_running_task->thread.release_completion_mutex();

				/* release memory */
				delete current_running_task;
				/* TODO: LOG: completion of task  */
				continue;
			}
			current_running_task->thread.release_completion_mutex();

			/*
				Not Complete, Update Executed time
			*/
			/* TODO: FIXME  -NUCLEAR- How to set the last start time?? */
			current_running_task->executed_time += timer_storage - current_running_task->last_start_time;
			tempRunningQueue.push(current_running_task);
			this->periodicRunningQueue.pop();
		}

		for (int i = 0; i < periodic_task_queue_size; i++)
		{
			periodicRunningQueue.push(tempRunningQueue.top());
			tempRunningQueue.pop();
		}
	}

	{

		/* ***NOTE: Current Implementation only handles Periodic Tasks*** */

		// int running_tasks_to_pop = 0;
		// bool found_equal_deadline_flag = 0;

		if (this->periodicRunningQueue.empty())
		{
			PeriodicTask *next_to_release_periodic_task = this->periodicWaitingQueue.top();
			this->periodicRunningQueue.push(next_to_release_periodic_task);
			this->periodicWaitingQueue.pop();

			bool done = 0;
			while (!done)
			{
				PeriodicTask *next_after_next_to_release_task = this->periodicWaitingQueue.top();

				/* no other same priority tasks */
				if (next_after_next_to_release_task->deadline > next_to_release_periodic_task->deadline)
				{
					done = 1;
					return;
				}
				else if (next_after_next_to_release_task->deadline == next_to_release_periodic_task->deadline)
				{
					this->periodicRunningQueue.push(next_after_next_to_release_task);
					this->periodicWaitingQueue.pop();
				}
				else if (next_after_next_to_release_task->deadline < next_to_release_periodic_task->deadline)
				{
					printf("FATAL ERROR: Error with Priority Queues");
					exit(-1);
				}
			}
		}

		int waiting_tasks_to_pop = 0;
		std::queue<PeriodicTask *> temp_periodic_running_queue;

		bool done = 0;
		while (!done)
		{
			PeriodicTask *current_running_task = this->periodicRunningQueue.top();
			PeriodicTask *next_to_release_periodic_task = this->periodicWaitingQueue.top();

			/* 
				No task to swap
			*/
			if (current_running_task->deadline < next_to_release_periodic_task->deadline)
			{
				return;
			}

			/*
				If task is not complete and waiting
			*/
			/* TODO: Check logic - check how deadline is calculated */
			if (current_running_task->deadline > next_to_release_periodic_task->deadline)
			{
				// TODO: CHECK VERIFY logic
				/* TODO: can it be Block or kill -> current_running_task? */
				/* Put Current_running_task to Wait */
				current_running_task->thread.block();
				/* Lower the Priority of Current_running_task*/
				current_running_task->thread.update_priority(THREAD_IDLE_PRIORITY);
				/* Add the Current_running_task Back to the Periodic_release_queue */
				this->periodicWaitingQueue.push(current_running_task);
				/* Pop the Current_running_task From the Runningqueue */
				this->periodicRunningQueue.pop();
				/* Increase the Priority of Next_to_release_periodic_task */
				next_to_release_periodic_task->thread.update_priority(THREAD_RUN_PRIORITY);
				/* Add the Next_to_release_periodic_task to the Temp_running_queue */
				temp_periodic_running_queue.push(next_to_release_periodic_task);
				/* Pop the waiting task From the periodicWaitingQueue */
				waiting_tasks_to_pop++;
			}

			/* TODO: Check logic - check how deadline is calculated */
			else if (current_running_task->deadline == next_to_release_periodic_task->deadline)
			{
				/* Increase the Priority of Next_to_release_periodic_task */
				next_to_release_periodic_task->thread.update_priority(THREAD_RUN_PRIORITY);
				/* Add the Next_to_release_periodic_task to the Temp_running_queue */
				temp_periodic_running_queue.push(next_to_release_periodic_task);
				/* Pop the waiting task From the periodicWaitingQueue */
				waiting_tasks_to_pop++;
				break;
			}

			/* TODO: Update priority based on EDF? */

			/* CLEAN: Static Casting  */
			// PeriodicTask *current_running_task = static_cast<PeriodicTask *>(current_running_task);
		}
		/* TODO: Add all the temporary running queued task to running queu */
		/* TODO: Pop all the tasks accoring to the counter */
		/* Pop the Current_running_task From the Runningqueue */
		// this->periodicRunningQueue.pop();
	}

	int Scheduler::get_running_queue_size()
	{
		return this->periodicWaitingQueue.size();
	}

} // namespace realtime_vehicle_monitoring_diagnostics

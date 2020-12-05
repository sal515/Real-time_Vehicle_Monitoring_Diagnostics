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
#include "Logger.h"

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
				periodic_task->released_time = timer_storage;
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
		// printf("Updating executed time at time %u\n", timer_storage);

		if (this->periodicRunningQueue.empty())
		{
			printf("No running task at %u\n", timer_storage);
			return;
		}

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

				/* TODO: LOG: completion of task  */
				Logger::log_task_details(current_running_task, "Completed Task");

				/* If the deadline was misseed */
				if (current_running_task->executed_time + current_running_task->released_time > current_running_task->deadline)
				{

					Logger::log_task_details(current_running_task, "?Log Deadline Missed?");
					// exit(-1);
				}

				/* release memory */
				delete current_running_task;
				continue;
			}
			current_running_task->thread.release_completion_mutex();

			/*
				Not Complete, Update Executed time
			*/
			/* Update executed time */
			current_running_task->executed_time = timer_storage - current_running_task->released_time;

			Logger::log_task_details(current_running_task, "Execution Time Updated");

			/* If the executed time is greater than the execution time */
			if (current_running_task->executed_time > current_running_task->execution_time)
			{
				tempRunningQueue.push(current_running_task);
				this->periodicRunningQueue.pop();

				Logger::log_task_details(current_running_task, "?Executed > Execution Time?");
				// exit(-1);
			}
			/* If the deadline was misseed */
			if (current_running_task->executed_time + current_running_task->released_time > current_running_task->deadline)
			{
				this->periodicRunningQueue.pop();

				Logger::log_task_details(current_running_task, "?Deadline Missed?");
				// exit(-1);
			}
		}

		for (int i = 0; i < periodic_task_queue_size; i++)
		{
			periodicRunningQueue.push(tempRunningQueue.top());
			tempRunningQueue.pop();
		}
	}

	void Scheduler::update_priority()
	{

		/* ***NOTE: Current Implementation only handles Periodic Tasks*** */

		/* 
			Running queue - empty 
		*/
		if (this->periodicRunningQueue.empty())
		{
			if (this->periodicWaitingQueue.empty())
			{
				return;
			}
			PeriodicTask *highest_prio_waiting_task = this->periodicWaitingQueue.top();
			this->periodicRunningQueue.push(highest_prio_waiting_task);
			this->periodicWaitingQueue.pop();

			/* Find task with same deadline as the first one pushed to the empty running queue  */
			bool done_flag = 0;
			while (!done_flag)
			{
				if (this->periodicWaitingQueue.empty())
				{
					return;
				}

				PeriodicTask *next_highest_prio_waiting_task = this->periodicWaitingQueue.top();

				/* no other same priority tasks */
				if (next_highest_prio_waiting_task->deadline > highest_prio_waiting_task->deadline)
				{
					done_flag = 1;
					return;
				}
				else if (next_highest_prio_waiting_task->deadline == highest_prio_waiting_task->deadline)
				{
					this->periodicRunningQueue.push(next_highest_prio_waiting_task);
					this->periodicWaitingQueue.pop();
				}
				else if (next_highest_prio_waiting_task->deadline < highest_prio_waiting_task->deadline)
				{
					printf("FATAL ERROR: Error with Priority Queues");
					exit(-1);
				}
			}
		}

		/* 
			Running queue is not empty 
		*/
		if (this->periodicWaitingQueue.empty())
		{
			/* nothing to swap */
			return;
		}
		PeriodicTask *highest_prio_waiting_task = this->periodicWaitingQueue.top();
		bool move_waiting_task_to_running_queue_flag = 0;
		bool done_flag = 0;
		while (!done_flag)
		{

			if (this->periodicRunningQueue.empty())
			{
				done_flag = 1;
				break;
			}
			PeriodicTask *lowest_prio_running_task = this->periodicRunningQueue.top();

			/* 
				No task to swap
			*/
			if (lowest_prio_running_task->deadline < highest_prio_waiting_task->deadline)
			{
				done_flag = 1;
				break;
			}

			/* 
				waiting task has higher priority 
			*/
			else if (lowest_prio_running_task->deadline > highest_prio_waiting_task->deadline)
			{
				/* TODO: can it be Block or kill -> lowest_prio_running_task? */
				/* Put lowest_prio_running_task to Wait */
				/* TODO: NUCLEAR !!Can I call this?  */
				// lowest_prio_running_task->thread.block();
				/* Lower the Priority of lowest_prio_running_task*/
				lowest_prio_running_task->thread.update_priority(THREAD_IDLE_PRIORITY);
				/* Add the lowest_prio_running_task Back to the Periodic_release_queue */
				this->periodicWaitingQueue.push(lowest_prio_running_task);
				/* Pop the lowest_prio_running_task From the Runningqueue */
				this->periodicRunningQueue.pop();

				move_waiting_task_to_running_queue_flag = 1;
			}

			/* 
				waiting task has equal priority 
			*/
			else if (lowest_prio_running_task->deadline == highest_prio_waiting_task->deadline)
			{
				move_waiting_task_to_running_queue_flag = 1;
				break;
			}
		}

		/* 
			Move waiting task to the Running queue
		*/
		if (move_waiting_task_to_running_queue_flag)
		{

			this->periodicRunningQueue.push(highest_prio_waiting_task);
			this->periodicWaitingQueue.pop();

			int waiting_queue_size = this->periodicWaitingQueue.size();
			for (int i = 0; i < waiting_queue_size; i++)
			{
				if (this->periodicWaitingQueue.top()->deadline > highest_prio_waiting_task->deadline)
				{
					return;
				}
				else if (this->periodicWaitingQueue.top()->deadline < highest_prio_waiting_task->deadline)
				{
					printf("FATAL ERROR: Issue with priority queue\n");
					exit(-1);
				}

				this->periodicRunningQueue.push(this->periodicWaitingQueue.top());
				this->periodicWaitingQueue.pop();
			}
		}
	}

	void Scheduler::run_tasks()
	{
		int periodic_task_queue_size = this->periodicRunningQueue.size();

		std::priority_queue<PeriodicTask *, std::vector<PeriodicTask *>, Compare_Periodic_Task_by_LDF> tempRunningQueue;

		for (int i = 0; i < periodic_task_queue_size; i++)
		{
			PeriodicTask *running_task = this->periodicRunningQueue.top();
			running_task->thread.signal();
			tempRunningQueue.push(running_task);
			this->periodicRunningQueue.pop();
		}

		for (int i = 0; i < periodic_task_queue_size; i++)
		{
			periodicRunningQueue.push(tempRunningQueue.top());
			tempRunningQueue.pop();
		}
	}

	int Scheduler::get_running_queue_size()
	{
		return this->periodicWaitingQueue.size();
	}

} // namespace realtime_vehicle_monitoring_diagnostics

/* CLEAN: Static Casting  */
// PeriodicTask *current_running_task = static_cast<PeriodicTask *>(current_running_task);
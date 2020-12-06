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
		printf("Scheduler object created\n");
	}

	Scheduler::~Scheduler()
	{
		printf("Scheduler object destroyed\n");
	}

	void Scheduler::add_periodic_task(PeriodicTask perodicTask)
	{
		Logger::log_task_details(&perodicTask, "Periodic Task created");
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

				Logger::log_task_details(periodic_task, "Task Released");

				if (DEBUG_PRINT)
				{
					printf("Added task name is: %s\n", this->periodicTasks.at(i).task_name);
				}
			}
		}
	}

	/* FUTURE IMPLEMENTATION: Release Aperiodic Tasks */
	/* FUTURE IMPLEMENTATION: Release Sporatic Tasks */

	void Scheduler::update_periodic_executed_time(unsigned timer_storage)
	{
		printf("Start of executed time updating, queue sizes are:\n");
		this->print_queue_sizes();

		if (this->periodicRunningQueue.empty())
		{
			printf("No running task.\n");
			this->print_queue_sizes();
			return;
		}

		std::priority_queue<PeriodicTask *, std::vector<PeriodicTask *>, Compare_Periodic_Task_by_LDF> tempRunningQueue;

		while (!this->periodicRunningQueue.empty())
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
				Logger::log_task_details(current_running_task, "Completed Task\n");
				this->print_queue_sizes();

				/* If the deadline was misseed */
				if (current_running_task->executed_time + current_running_task->released_time > current_running_task->deadline)
				{

					Logger::log_task_details(current_running_task, "?Log Deadline Missed?\n");
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

			Logger::log_task_details(current_running_task, "Execution Time Updated\n");

			/* If the executed time is greater than the execution time */
			if (current_running_task->executed_time > current_running_task->execution_time)
			{
				printf("!?WARNING::Executed > Execution Time?!\n");
				// exit(-1);
			}
			/* If the deadline was misseed */
			if ((current_running_task->executed_time + current_running_task->released_time) > current_running_task->deadline)
			{
				this->periodicRunningQueue.pop();
				printf("!?FATAL::Deadline Missed?!\n");
				// exit(-1);
				this->print_queue_sizes();
				delete current_running_task;
				continue;
			}

			tempRunningQueue.push(current_running_task);
			this->periodicRunningQueue.pop();
			this->print_queue_sizes();
		}

		while (!tempRunningQueue.empty())
		{
			periodicRunningQueue.push(tempRunningQueue.top());
			tempRunningQueue.pop();
		}

		printf("End of executed time updating, queue sizes are:\n");
		this->print_queue_sizes();
		printf("\n\n\n");
	}

	void Scheduler::update_periodic_priority()
	{
		printf("Start of priority updating, queue sizes are:\n");
		this->print_queue_sizes();

		/* ***NOTE: Current Implementation only handles Periodic Tasks*** */

		/* 
			Running queue - empty 
		*/
		if (this->periodicRunningQueue.empty())
		{
			if (this->periodicWaitingQueue.empty())
			{
				printf("Priority Updading: Running queue and Waiting queue was empty.\n\n\n");
				this->print_queue_sizes();
				return;
			}
			PeriodicTask *highest_prio_waiting_task = this->periodicWaitingQueue.top();
			this->periodicRunningQueue.push(highest_prio_waiting_task);
			this->periodicWaitingQueue.pop();

			Logger::log_task_details(highest_prio_waiting_task, "Priority Updading: Moving highest priority waiting task to running queue\n");
			this->print_queue_sizes();

			/* Find task with same deadline as the first one pushed to the empty running queue  */
			bool done_flag = 0;
			while (!done_flag)
			{
				if (this->periodicWaitingQueue.empty())
				{
					printf("Priority Updading: Only task in waiting queue was moved to running queue.\n\n\n");
					this->print_queue_sizes();
					return;
				}

				PeriodicTask *next_highest_prio_waiting_task = this->periodicWaitingQueue.top();

				/* no other same priority tasks */
				if (next_highest_prio_waiting_task->deadline > highest_prio_waiting_task->deadline)
				{
					printf("Priority Updading: Completed moving all eligible waiting task to running queue.\n\n\n");

					done_flag = 1;
					return;
				}
				else if (next_highest_prio_waiting_task->deadline == highest_prio_waiting_task->deadline)
				{

					this->periodicRunningQueue.push(next_highest_prio_waiting_task);
					this->periodicWaitingQueue.pop();

					Logger::log_task_details(next_highest_prio_waiting_task, "Priority Updading: Another task with same waiting priority has been moved to running queue\n");
					this->print_queue_sizes();
				}
				else if (next_highest_prio_waiting_task->deadline < highest_prio_waiting_task->deadline)
				{
					printf("Priority Updading: FATAL ERROR: Error with Priority Queues\n");
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
			printf("Priority Updading: Running queue is not empty, Waiting queue is empty. No tasks to swap.\n\n\n");
			return;
		}

		PeriodicTask *highest_prio_waiting_task = this->periodicWaitingQueue.top();

		Logger::log_task_details(highest_prio_waiting_task, "Priority Updading: Running queue is not empty, Looking at highest priority waiting task\n");

		bool move_waiting_task_to_running_queue_flag = 0;
		bool done_flag = 0;
		while (!done_flag)
		{

			if (this->periodicRunningQueue.empty())
			{
				printf("Priority Updading: All running tasks has lower priority than the highest priority waiting task, all running tasks has been moved to waiting queue.\n\n\n");

				done_flag = 1;
				break;
			}

			PeriodicTask *lowest_prio_running_task = this->periodicRunningQueue.top();
			Logger::log_task_details(lowest_prio_running_task, "Priority Updading: Comparing the current lowest priority running task with the highest priority waiting task\n");

			/* 
				No task to swap
			*/
			if (lowest_prio_running_task->deadline < highest_prio_waiting_task->deadline)
			{
				Logger::log_task_details(lowest_prio_running_task, "Priority Updading: Details of the lowest priority running task\n");
				Logger::log_task_details(highest_prio_waiting_task, "Priority Updading: Details of the highest priority waiting task\n");
				printf("Priority Updading: Priority(highest priority waiting task) < Priority(lowest priority running task), nothing more to swap.\n\n\n");

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

				Logger::log_task_details(lowest_prio_running_task, "Priority Updading: Details of the lowest priority running task\n");
				Logger::log_task_details(highest_prio_waiting_task, "Priority Updading: Details of the highest priority waiting task\n");
				printf("Priority Updading: Priority(highest priority waiting task) > Priority(lowest priority running task), moving lowest priority running task to waiting queue.\n");
				this->print_queue_sizes();
			}

			/* 
				waiting task has equal priority 
			*/
			else if (lowest_prio_running_task->deadline == highest_prio_waiting_task->deadline)
			{
				Logger::log_task_details(lowest_prio_running_task, "Priority Updading: Details of the lowest priority running task\n");
				Logger::log_task_details(highest_prio_waiting_task, "Priority Updading: Details of the highest priority waiting task\n");
				printf("Priority Updading: Priority(highest priority waiting task) == Priority(lowest priority running task), waiting task will be moved to running queue.\n\n\n");

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

			while (!this->periodicWaitingQueue.empty())
			{
				if (this->periodicWaitingQueue.top()->deadline > highest_prio_waiting_task->deadline)
				{
					printf("Priority Updading: Completed moving all eligible waiting task to running queue.\n\n\n");
					return;
				}
				else if (this->periodicWaitingQueue.top()->deadline < highest_prio_waiting_task->deadline)
				{
					printf("Priority Updading: FATAL ERROR: Issue with priority queue\n");
					exit(-1);
				}

				Logger::log_task_details(this->periodicWaitingQueue.top(), "Priority Updading: Moving waiting task to running queue\n");
				this->print_queue_sizes();

				this->periodicRunningQueue.push(this->periodicWaitingQueue.top());
				this->periodicWaitingQueue.pop();
			}
		}
	}

	void Scheduler::run_tasks()
	{

		std::priority_queue<PeriodicTask *, std::vector<PeriodicTask *>, Compare_Periodic_Task_by_LDF> tempRunningQueue;

		while (!this->periodicRunningQueue.empty())
		{
			PeriodicTask *running_task = this->periodicRunningQueue.top();
			running_task->thread.signal();

			Logger::log_task_details(running_task, "Signalling running task\n");

			tempRunningQueue.push(running_task);
			this->periodicRunningQueue.pop();
		}

		while (!tempRunningQueue.empty())
		{
			periodicRunningQueue.push(tempRunningQueue.top());
			tempRunningQueue.pop();
		}
	}

	int Scheduler::get_running_queue_size()
	{
		return this->periodicRunningQueue.size();
	}

	int Scheduler::get_waiting_queue_size()
	{
		return this->periodicWaitingQueue.size();
	}
	void Scheduler::print_queue_sizes()
	{
		printf("Running queue size: %u\n", this->get_running_queue_size());
		printf("Waiting queue size: %u\n", this->get_waiting_queue_size());
	}

} // namespace realtime_vehicle_monitoring_diagnostics

/* CLEAN: Static Casting  */
// PeriodicTask *current_running_task = static_cast<PeriodicTask *>(current_running_task);
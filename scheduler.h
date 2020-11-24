/*
 * Scheduler.h
 *
 *  Created on: Nov 14, 2020
 *      Author: Salman
 */

#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include <vector>
#include "PeriodicTask.h"

namespace realtime_vehicle_monitoring_diagnostics
{

	class Scheduler
	{
	private:
	public:
		/* TODO: Should be a priority Queue */
		// static std::vector<Task *> runningQueue;
		// static std::vector<PeriodicTask> periodicTasks;
		// static std::vector<Task> otherTasks;

		Scheduler(); // initializatin of a Scheduler
		virtual ~Scheduler();

		/* TODO: Figure out if we have queues with ascending sorting */
		// void init();
		void generate_tasks();
		// void create_a_task();
		void check_task_deadlines();
		void update_task_priority();

		static void add_periodic_task(PeriodicTask perodicTask, std::vector<PeriodicTask> *perodicTasks);
		static void remove_periodic_task();

		static void release_update(unsigned timer_storage, std::vector<PeriodicTask> *perodicTasks, std::vector<Task*> *runningQueue);

		static int get_running_queue_size(std::vector<Task*> *runningQueue);
		static int get_periodic_tasks_size(std::vector<PeriodicTask> *perodicTasks);
	};

} // namespace realtime_vehicle_monitoring_diagnostics

#endif /* SCHEDULER_H_ */

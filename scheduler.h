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
#include <queue>

namespace realtime_vehicle_monitoring_diagnostics
{
	struct comparePeriodicTasks
	{
		// This is the comparison function for the Priority Queue
		// bool operator()(Task *const t1, Task *const t2)
		// {
		// return static_cast<PeriodicTask *>(t1)->period > static_cast<PeriodicTask *>(t2)->period;
		// }

		bool operator()(PeriodicTask *const t1, PeriodicTask *const t2)
		{
			// return "true" if "p1" is ordered before "p2", for example:
			return t1->period > t2->period;
		}
	};

	class Scheduler
	{
	private:
		Scheduler(); // initializatin of a Scheduler
		virtual ~Scheduler();

	public:
		/* TODO: Should be a priority Queue */
		// static std::vector<Task *> runningQueue;
		// static std::vector<PeriodicTask> periodicTasks;
		// static std::vector<Task> otherTasks;

		/* TODO: Figure out if we have queues with ascending sorting */

		// void init();
		// void generate_tasks();
		// void create_a_task();

		// void check_task_deadlines();
		// void update_task_priority();

		// static void remove_periodic_task();
		static void add_periodic_task(PeriodicTask perodicTask,
									  std::vector<PeriodicTask> *perodicTasks);
		static void release_update(unsigned timer_storage,
								   std::vector<PeriodicTask> *perodicTasks,
								   std::priority_queue<PeriodicTask *, std::vector<PeriodicTask *>, comparePeriodicTasks> *runningQueue);
		static int get_running_queue_size(std::priority_queue<PeriodicTask *, std::vector<PeriodicTask *>, comparePeriodicTasks> *runningQueue);
		// static int get_periodic_tasks_size(std::vector<PeriodicTask> *perodicTasks);
	};

} // namespace realtime_vehicle_monitoring_diagnostics

#endif /* SCHEDULER_H_ */

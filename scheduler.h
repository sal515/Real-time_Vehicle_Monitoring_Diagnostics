/*
 * Scheduler.h
 *
 *  Created on: Nov 14, 2020
 *      Author: Salman
 */

#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include "PeriodicTask.h"
#include "SporadicTask.h"

#include <queue>
#include <vector>

namespace realtime_vehicle_monitoring_diagnostics
{

	struct Compare_Periodic_Task
	{
		bool operator()(PeriodicTask *const t1, PeriodicTask *const t2)
		{
			// return "true" if "p1" is ordered before "p2", for example:
			return t1->period > t2->period;
		}
	};

	struct Compare_Sporadic_Task
	{
		bool operator()(SporadicTask *const t1, SporadicTask *const t2)
		{
			// return "true" if "p1" is ordered before "p2", for example:
			return t1->relative_deadline > t2->relative_deadline;
		}
	};

	class Scheduler
	{
	private:
		std::vector<PeriodicTask> periodicTasks;

		std::priority_queue<PeriodicTask *, std::vector<PeriodicTask *>, Compare_Periodic_Task> periodicReleasedQueue;

	public:
		Scheduler(); // initializatin of a Scheduler
		virtual ~Scheduler();

		void release_periodic_tasks(unsigned timer_storage);
		void priority_update_periodic_tasks(unsigned timer_storage,
											std::priority_queue<PeriodicTask *, std::vector<PeriodicTask *>, Compare_Periodic_Task> *periodicReleasedQueue, std::queue<Task *> *runningQueue);

		void add_periodic_task(PeriodicTask perodicTask);
		int get_running_queue_size();
	};

} // namespace realtime_vehicle_monitoring_diagnostics

#endif /* SCHEDULER_H_ */

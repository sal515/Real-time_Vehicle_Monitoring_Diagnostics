/*
 * Scheduler.h
 *
 *  Created on: Nov 14, 2020
 *      Author: Salman
 */

#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include "PeriodicTask.h"

#include <queue>
#include <vector>

namespace realtime_vehicle_monitoring_diagnostics
{
	struct comparePeriodicTasks
	{
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
		static void add_periodic_task(PeriodicTask perodicTask,
									  std::vector<PeriodicTask> *periodicTasks);
		static void release(unsigned timer_storage,
							std::vector<PeriodicTask> *periodicTasks,
							std::priority_queue<PeriodicTask *, std::vector<PeriodicTask *>, comparePeriodicTasks> *runningQueue);
		static int get_running_queue_size(std::priority_queue<PeriodicTask *, std::vector<PeriodicTask *>, comparePeriodicTasks> *runningQueue);
	};

} // namespace realtime_vehicle_monitoring_diagnostics

#endif /* SCHEDULER_H_ */

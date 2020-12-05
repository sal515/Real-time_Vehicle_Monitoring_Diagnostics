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
	/* TODO: FIXME - NUCLEAR -> THE SORTING SHOULD BE BASED ON DEADLINE (EDF) NOT PERIOID  */

	/* EDF = Earliest_Deadline_First */
	struct Compare_Periodic_Task_by_EDF
	{
		bool operator()(PeriodicTask *const t1, PeriodicTask *const t2)
		{
			// return "true" if "p1" is ordered before "p2", for example:
			return t1->deadline > t2->deadline;
		}
	};

	/* LDF = Latest_Deadline_First */
	struct Compare_Periodic_Task_by_LDF
	{
		bool operator()(PeriodicTask *const t1, PeriodicTask *const t2)
		{
			// return "true" if "p1" is ordered before "p2", for example:
			return t1->deadline < t2->deadline;
		}
	};

	class Scheduler
	{

	private:
		std::vector<PeriodicTask> periodicTasks;

		std::priority_queue<PeriodicTask *, std::vector<PeriodicTask *>, Compare_Periodic_Task_by_EDF> periodicWaitingQueue;

		std::priority_queue<PeriodicTask *, std::vector<PeriodicTask *>, Compare_Periodic_Task_by_LDF> periodicRunningQueue;

	public:
		// TODO: Clean
		friend class Test;

		Scheduler(); // initializatin of a Scheduler
		virtual ~Scheduler();

		void release_periodic_tasks(unsigned timer_storage);
		void update_executed_priority(unsigned timer_storage);

		void add_periodic_task(PeriodicTask perodicTask);
		int get_running_queue_size();
	};

} // namespace realtime_vehicle_monitoring_diagnostics

#endif /* SCHEDULER_H_ */

/* FUTURE IMPLEMENTATION */
// struct Compare_Sporadic_Task
// {
// 	bool operator()(SporadicTask *const t1, SporadicTask *const t2)
// 	{
// 		// return "true" if "p1" is ordered before "p2", for example:
// 		return t1->relative_deadline > t2->relative_deadline;
// 	}
// };
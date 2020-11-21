/*
 * Scheduler.h
 *
 *  Created on: Nov 14, 2020
 *      Author: Salman
 */

#ifndef SCHEDULER_H_
#define SCHEDULER_H_

namespace realtime_vehicle_monitoring_diagnostics
{

	/* 
	producer_exec: pexec = x ms

	t1: full consumption
	task(10,pexec);
	t2: engine speed rpm
	task(500,pexec);
	t3: engine coolant temp
	task(2000,pexec);
	t4: current gear
	task(100,pexec);
	t5: transmission oil temp
	task(5000,pexec);
	t6: vehicle speed
	task(100,pexec);
	t7: acceleration speed longitudinal
	task(150,pexec);
	t8: indication of break switch
	task(100,pexec);
	
	 */

	class Scheduler
	{
	private:
	public:
		Scheduler(); // initializatin of a Scheduler
		virtual ~Scheduler();
		/* TODO: Figure out if we have queues with ascending sorting */
		// void init();
		void generate_tasks();
		// void create_a_task();
		void check_task_deadlines();
		void update_task_priority();
	};

} // namespace realtime_vehicle_monitoring_diagnostics

#endif /* SCHEDULER_H_ */

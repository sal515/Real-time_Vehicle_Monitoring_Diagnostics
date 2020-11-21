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

	p1: full consumption
	task(10,pexec);
	p2: engine speed rpm
	task(500,pexec);
	p3: engine coolant temp
	task(2000,pexec);
	p4: current gear
	task(100,pexec);
	p5: transmission oil temp
	task(5000,pexec);
	p6: vehicle speed
	task(100,pexec);
	p7: acceleration speed longitudinal
	task(150,pexec);
	p8: indication of break switch
	task(100,pexec);

	 */

	/* 
	consumer_exec : cexec = y ms

	c1: print func
	task(10,cexec);
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

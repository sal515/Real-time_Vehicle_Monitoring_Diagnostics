/*
 * Test.cpp
 *
 *  Created on: Dec 3, 2020
 *      Author: Salman
 */

#include "Test.h"

#include <stdio.h>
#include <unistd.h>
#include <iostream>

namespace realtime_vehicle_monitoring_diagnostics
{

	Test::Test()
	{
	}

	Test::~Test()
	{
	}

	void Test::test_thread(start_routine_t producer, start_routine_t consumer)
	{
		printf("Starting consumer/producer example...\n");
		Thread producer_thread1 = Thread(producer, 11, "P-P60");
		Thread consumer_thread = Thread(consumer, 10, "C-P10");

		sleep(5);
		printf("======5s======\n");
		printf("======First======\n");
		// pthread_cond_signal(&producer_condvar);
		producer_thread1.signal();
		sleep(5);
		printf("======5s======\n");
		consumer_thread.signal();
		// pthread_cond_signal(&consumer_condvar);
		sleep(5);
		printf("======5s======\n");

		sleep(5);
		printf("======5s======\n");
		sleep(5);
		printf("======5s======\n");

		printf("======Second======\n");
		producer_thread1.signal();
		// pthread_cond_signal(&producer_condvar);
		sleep(5);
		printf("======5s======\n");
		consumer_thread.signal();
		// pthread_cond_signal(&consumer_condvar);
		sleep(5);
		printf("======5s======\n");

		// while (1)
		// {
		// 	// infinite wait
		// }
	}

	void Test::test_priority_queues_EDF(Scheduler *scheduler)
	{
		// Scheduler scheduler = Scheduler();

		/* Priority Queue Test */
		// scheduler->periodicWaitingQueue.push(new PeriodicTask(500, 15, "p500,e15"));
		// scheduler->periodicWaitingQueue.push(new PeriodicTask(10, 5, "p10,e5"));
		// scheduler->periodicWaitingQueue.push(new PeriodicTask(2000, 25, "p2000,e25"));
		// scheduler->periodicWaitingQueue.push(new PeriodicTask(13, 900, "p13,e900"));

		std::cout << "periodicWaitingQueue Size: "
				  << scheduler->periodicWaitingQueue.size()
				  << std::endl;

		int periodicWaitingQueue_size = scheduler->periodicWaitingQueue.size();
		for (int i = 0; i < periodicWaitingQueue_size; i++)
		{
			PeriodicTask *t = scheduler->periodicWaitingQueue.top();
			scheduler->periodicWaitingQueue.pop();
			std::cout << "Task name: "
					  << t->task_name
					  << " Task period:"
					  << t->period
					  << " Task deadline:"
					  << t->deadline << std::endl;

			scheduler->periodicRunningQueue.push(t);
			// delete t;
		}

		std::cout << "periodicRunningQueue Size: "
				  << scheduler->periodicRunningQueue.size()
				  << std::endl;

		int periodicRunningQueue_size = scheduler->periodicRunningQueue.size();
		for (int i = 0; i < periodicRunningQueue_size; i++)
		{
			PeriodicTask *t = scheduler->periodicRunningQueue.top();
			scheduler->periodicRunningQueue.pop();
			std::cout << "Task name: "
					  << t->task_name
					  << " Task period:"
					  << t->period
					  << " Task deadline:"
					  << t->deadline << std::endl;
			delete t;
		}
	}

	// enum Task_Name
	// {
	// 	FUEL_CONSUMPTION,
	// 	ENGINE_SPEED_RPM,
	// 	ENGINE_COOLANT_TEMP,
	// 	CURRENT_GEAR,
	// 	TRANSMISSION_OIL_TEMP,
	// 	VEHICLE_SPEED,
	// 	ACCELERATION_SPEED_LONGITUDINAL,
	// 	INDICATION_BREAK_SWITCH
	// };

	// struct Task_Info
	// {
	// 	int fuel_consumption;
	// 	int engine_speed_rpm;
	// 	int engine_coolant_temp;
	// 	int current_gear;
	// 	int transmission_oil_temp;
	// 	int vehicle_speed;
	// 	int acceleration_speed_longitudinal;
	// 	int indication_break_switch;
	// };

	/* Classes test */
	// DatasetManager ds_manager_obj = DatasetManager();
	// Scheduler scheduler_obj = Scheduler();
	// //	Thread thread_manager_obj = Thread();
	// // Thread.create_thread();
	// Timer timer = Timer();
	// PeriodicTask periodic_task = PeriodicTask();
	// // Task task = Task();
	// // task.task_type = PERIODIC;
	/* Classes test */

} // namespace realtime_vehicle_monitoring_diagnostics

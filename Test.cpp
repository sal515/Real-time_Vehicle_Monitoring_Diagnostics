/*
 * Test.cpp
 *
 *  Created on: Dec 3, 2020
 *      Author: Salman
 */

#include "Test.h"

#include <stdio.h>
#include <unistd.h>

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

	/* Priority Queue Test */
	// periodicWaitingQueue.push(new PeriodicTask(500, 15));
	// periodicWaitingQueue.push(new PeriodicTask(10, 5));
	// periodicWaitingQueue.push(new PeriodicTask(2000, 25));
	// periodicWaitingQueue.push(new PeriodicTask(13, 900));

	// std::cout << "-----------Size:" << std::endl;
	// std::cout << "-----------Size:" << periodicWaitingQueue.size() << std::endl;

	// int size = periodicWaitingQueue.size();
	// for (int i = 0; i < size; i++)
	// {
	// 	PeriodicTask *t = periodicWaitingQueue.top();
	// 	periodicWaitingQueue.pop();
	// 	// std::cout << "task executed time" << t->executed_time << std::endl;
	// 	std::cout << "task executed time: " << t->period << std::endl;
	// 	delete t;
	// }
	// return 0;
	/* Priority Queue Test */

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

#include <cstdlib>
#include <iostream>

#include "Thread.h"
#include "Task.h"
#include "Timer.h"
#include "Scheduler.h"
#include "PeriodicTask.h"
#include "AperiodicTask.h"
#include "SporadicTask.h"
// #include "DatasetManager.h"

// /* TODO: TEST INCLUDES */
// #include <stdint.h>
#include <queue>
#include <atomic.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

using namespace realtime_vehicle_monitoring_diagnostics;

enum Task_Name
{
	FUEL_CONSUMPTION,
	ENGINE_SPEED_RPM,
	ENGINE_COOLANT_TEMP,
	CURRENT_GEAR,
	TRANSMISSION_OIL_TEMP,
	VEHICLE_SPEED,
	ACCELERATION_SPEED_LONGITUDINAL,
	INDICATION_BREAK_SWITCH
};

struct Task_Info
{
	int fuel_consumption;
	int engine_speed_rpm;
	int engine_coolant_temp;
	int current_gear;
	int transmission_oil_temp;
	int vehicle_speed;
	int acceleration_speed_longitudinal;
	int indication_break_switch;
};

// #define DEBUG_PRINT 0
#define DEBUG_PRINT 1

// #define RUN_TIME 30000
#define RUN_TIME 5000
// #define RUN_TIME 10

#define TIMER_1_MS_IN_NS (1000000)
#define TIMER_10_MS_IN_NS (10000000)
#define ONE_MILLION (1000000)

#define CONSUMER_EXECUTION_TIME (1)
#define PRODUCER_EXECUTION_TIME (1)

/* Timer */
/* Rotates in 4294967295 ~1.6months */
volatile unsigned timer_storage;
Scheduler scheduler = Scheduler();

/* Function prototypes */
void *consumer(void *args);
void *producer(void *args);
void build_periodic_tasks_list(Scheduler *scheduler);
void timer_timeout_handler(int sig_number);

int main(int argc, char *argv[])
{
	// printf("Starting consumer/producer example...\n");
	// Thread producer_thread1 = Thread(producer, 11, "P-P60");
	// Thread consumer_thread = Thread(consumer, 10, "C-P10");

	// sleep(5);
	// printf("======5s======\n");
	// printf("======First======\n");
	// // pthread_cond_signal(&producer_condvar);
	// producer_thread1.signal();
	// sleep(5);
	// printf("======5s======\n");
	// consumer_thread.signal();
	// // pthread_cond_signal(&consumer_condvar);
	// sleep(5);
	// printf("======5s======\n");

	// sleep(5);
	// printf("======5s======\n");
	// sleep(5);
	// printf("======5s======\n");

	// printf("======Second======\n");
	// producer_thread1.signal();
	// // pthread_cond_signal(&producer_condvar);
	// sleep(5);
	// printf("======5s======\n");
	// consumer_thread.signal();
	// // pthread_cond_signal(&consumer_condvar);
	// sleep(5);
	// printf("======5s======\n");

	// // while (1)
	// // {
	// // 	// infinite wait
	// // }
	// return 0;

	// Scheduler scheduler = Scheduler();

	int res;
	build_periodic_tasks_list(&scheduler);

	const int signal_type = SIGUSR1;
	signal(signal_type, timer_timeout_handler);

	Timer one_ms_timer = Timer(TIMER_1_MS_IN_NS,
							   "Task Release Timer",
							   signal_type);
	if (one_ms_timer.start() < 0)
	{
		printf("Failed to start perioidc timer - %s", one_ms_timer.timer_name);
		return -1;
	}

	while (1)
	{
		if (timer_storage >= RUN_TIME)
		{
			return 0;
		}
	}

	/* Priority Queue Test */
	// periodicReleasedQueue.push(new PeriodicTask(500, 15));
	// periodicReleasedQueue.push(new PeriodicTask(10, 5));
	// periodicReleasedQueue.push(new PeriodicTask(2000, 25));
	// periodicReleasedQueue.push(new PeriodicTask(13, 900));

	// std::cout << "-----------Size:" << std::endl;
	// std::cout << "-----------Size:" << periodicReleasedQueue.size() << std::endl;

	// int size = periodicReleasedQueue.size();
	// for (int i = 0; i < size; i++)
	// {
	// 	PeriodicTask *t = periodicReleasedQueue.top();
	// 	periodicReleasedQueue.pop();
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

	int pause = 0;
	return EXIT_SUCCESS;
}

void *consumer(void *args)
{
	printf("***Consumer Thread***\n");
	Thread *thread = (Thread *)(args);
	while (1)
	{
		thread->block();
		printf("Consumer: Data Processed\n");
		thread->unblock();
	}
}

void *producer(void *args)
{
	printf("***Producer Thread***\n");
	Thread *thread = (Thread *)(args);
	while (1)
	{
		thread->block();
		printf("Producer: Data Processed\n");
		thread->unblock();
	}
}

void build_periodic_tasks_list(Scheduler *scheduler)
{
	/* Initialize Given Periodic Tasks */
	scheduler->add_periodic_task(PeriodicTask(10,
											  PRODUCER_EXECUTION_TIME,
											  "fuel_consumption")); // total - 3000
	scheduler->add_periodic_task(PeriodicTask(500,
											  PRODUCER_EXECUTION_TIME,
											  "engine_speed_rpm")); // total - 60
	scheduler->add_periodic_task(PeriodicTask(2000,
											  PRODUCER_EXECUTION_TIME,
											  "engine_coolant_temp")); // total - 15
	scheduler->add_periodic_task(PeriodicTask(100,
											  PRODUCER_EXECUTION_TIME, "current_gear")); // total - 300
	scheduler->add_periodic_task(PeriodicTask(5000,
											  PRODUCER_EXECUTION_TIME,
											  "transmission_oil_temp")); // total - 6
	scheduler->add_periodic_task(PeriodicTask(100,
											  PRODUCER_EXECUTION_TIME,
											  "vehicle_speed")); // total - 300
	scheduler->add_periodic_task(PeriodicTask(150,
											  PRODUCER_EXECUTION_TIME,
											  "acceleration_speed_longitudinal")); // total - 200
	scheduler->add_periodic_task(PeriodicTask(100,
											  PRODUCER_EXECUTION_TIME,
											  "indication_break_switch")); // total - 300
}

/* Signal handler */
void timer_timeout_handler(int sig_number)
{
	/* Increment Timer Value */
	atomic_add(&timer_storage, TIMER_1_MS_IN_NS / ONE_MILLION);

	/* Release Periodic Tasks */
	scheduler.release_periodic_tasks(timer_storage);

	if (DEBUG_PRINT)
	{
		printf("At time t = : %u\n", timer_storage);
		printf("Number of Tasks: %u\n", scheduler.get_running_queue_size());
	}

	/* Update Priority */
	/* Update Running Queue */
	/* Update Update Execution Time */
	/* Update Run Tasks */
}
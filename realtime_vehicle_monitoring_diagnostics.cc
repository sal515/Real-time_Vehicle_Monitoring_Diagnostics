#include <cstdlib>
#include <iostream>

// #include "Thread.h"
// #include "DatasetManager.h"
#include "Task.h"
#include "Timer.h"
#include "Scheduler.h"
#include "PeriodicTask.h"
#include "AperiodicTask.h"
#include "SporadicTask.h"

// /* TODO: TEST INCLUDES */
// #include <vector>
// #include <stdint.h>
#include <queue>
#include <atomic.h>

// #include <sys/time.h>
// #include <stdint.h>
// #include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace realtime_vehicle_monitoring_diagnostics;

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

/* QUEUES */
std::vector<PeriodicTask> periodicTasks;

std::queue<Task *> runningQueue;

std::priority_queue<PeriodicTask *, std::vector<PeriodicTask *>, comparePeriodicTasks> periodicReleasedQueue;
std::queue<AperiodicTask> aperiodicReleasedQueue;
std::priority_queue<SporadicTask *, std::vector<SporadicTask *>, compareSporadicTasks> sporadicReleasedQueue;

/* Function prototypes */
void build_periodic_tasks_list();

/* Signal handler */
void timer_timeout_handler(int sig_number)
{
	/* Increment Timer Value */
	atomic_add(&timer_storage, TIMER_1_MS_IN_NS / ONE_MILLION);

	/* Release Periodic Tasks */
	Scheduler::release_periodic_tasks(timer_storage,
									  &periodicTasks,
									  &periodicReleasedQueue);

	if (DEBUG_PRINT)
	{

		printf("At time t = : %u\n", timer_storage);
		printf("Number of Tasks: %u\n", Scheduler::get_running_queue_size(&periodicReleasedQueue));
	}
}

int main(int argc, char *argv[])
{
	int res;

	build_periodic_tasks_list();

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
		if (timer_storage == RUN_TIME)
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

void build_periodic_tasks_list()
{
	/* Initialize Given Periodic Tasks */
	Scheduler::add_periodic_task(PeriodicTask(10, PRODUCER_EXECUTION_TIME, "fuel_consumption"), &periodicTasks);				 // total - 3000
	Scheduler::add_periodic_task(PeriodicTask(500, PRODUCER_EXECUTION_TIME, "engine_speed_rpm"), &periodicTasks);				 // total - 60
	Scheduler::add_periodic_task(PeriodicTask(2000, PRODUCER_EXECUTION_TIME, "engine_coolant_temp"), &periodicTasks);			 // total - 15
	Scheduler::add_periodic_task(PeriodicTask(100, PRODUCER_EXECUTION_TIME, "current_gear"), &periodicTasks);					 // total - 300
	Scheduler::add_periodic_task(PeriodicTask(5000, PRODUCER_EXECUTION_TIME, "transmission_oil_temp"), &periodicTasks);			 // total - 6
	Scheduler::add_periodic_task(PeriodicTask(100, PRODUCER_EXECUTION_TIME, "vehicle_speed"), &periodicTasks);					 // total - 300
	Scheduler::add_periodic_task(PeriodicTask(150, PRODUCER_EXECUTION_TIME, "acceleration_speed_longitudinal"), &periodicTasks); // total - 200
	Scheduler::add_periodic_task(PeriodicTask(100, PRODUCER_EXECUTION_TIME, "indication_break_switch"), &periodicTasks);		 // total - 300
}

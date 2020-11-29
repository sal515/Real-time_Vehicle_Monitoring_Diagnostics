#include <cstdlib>
#include <iostream>

// #include "Task.h"
// #include "Thread.h"
// #include "DatasetManager.h"
#include "Timer.h"
#include "Scheduler.h"
#include "PeriodicTask.h"

// /* TODO: TEST INCLUDES */
// #include <vector>
// #include <stdint.h>
#include <queue>
#include <atomic.h>

// #include <sys/time.h>
// #include <stdint.h>
// #include <time.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

using namespace realtime_vehicle_monitoring_diagnostics;

// #define DEBUG_PRINT 0
#define DEBUG_PRINT 1

// #define RUN_TIME 30000
#define RUN_TIME 5000

#define TIMER_1_MS_IN_NS (1000000)
#define TIMER_10_MS_IN_NS (10000000)
#define ONE_MILLION (1000000)

#define CONSUMER_EXECUTION_TIME (1)
#define PRODUCER_EXECUTION_TIME (1)

/* Rotates in 4294967295 ~1.6months */
volatile unsigned timer_storage;
std::vector<PeriodicTask> periodicTasks;
std::priority_queue<PeriodicTask *, std::vector<PeriodicTask *>, comparePeriodicTasks> periodicRunningQueue;

void task_release_handler(int sig_number)
{
	atomic_add(&timer_storage, TIMER_1_MS_IN_NS / ONE_MILLION);
	// atomic_add(&timer_storage, TIMER_10_MS_IN_NS / ONE_MILLION);
	Scheduler::release(timer_storage, &periodicTasks, &periodicRunningQueue);

	if (DEBUG_PRINT)
	{

		printf("At time t = : %u\n", timer_storage);
		printf("Number of Tasks: %u\n", Scheduler::get_running_queue_size(&periodicRunningQueue));
	}
}

int start_periodic_timer(int period_ns,
						 const int signal_type,
						 itimerspec *timer_spec,
						 sigevent *sigev,
						 timer_t *timer,
						 sigset_t *sigst,
						 char timer_name[])
{

	/* Timer timeout settings */
	timer_spec->it_value.tv_sec = 0;
	timer_spec->it_value.tv_nsec = period_ns;
	timer_spec->it_interval.tv_sec = 0;
	timer_spec->it_interval.tv_nsec = period_ns;

	/* add the signal to sig set */
	sigemptyset(sigst);			   // initialize a signal set
	sigaddset(sigst, signal_type); // add SIGALRM to the signal set
	// sigprocmask(SIG_BLOCK, &sigst, NULL); //block the signal

	/* set the signal event a timer expiration */
	memset(sigev, 0, sizeof(struct sigevent));
	sigev->sigev_notify = SIGEV_SIGNAL;
	sigev->sigev_signo = signal_type;

	/* create timer */
	if (timer_create(CLOCK_MONOTONIC, sigev, timer) < 0)
	{
		printf("%s - Creation Failed \n", timer_name);
		exit(-1);
	}

	/* activate the timer */
	return timer_settime(*timer, 0, timer_spec, NULL);
}

int main(int argc, char *argv[])
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

	int res;

	// const int signal = SIGALRM;
	const int signal_type = SIGUSR1;
	signal(signal_type, task_release_handler);

	timer_t timer;
	sigset_t sigst;
	struct sigevent sigev;
	struct itimerspec timer_spec;

	//set and activate a timer
	// res = start_periodic_timer(TIMER_10_MS_IN_NS,
	res = start_periodic_timer(TIMER_1_MS_IN_NS,
							   signal_type,
							   &timer_spec,
							   &sigev,
							   &timer,
							   &sigst,
							   "Task Release Timer");
	if (res < 0)
	{
		perror("Start periodic timer");
		return -1;
	}

	while (1)
	{
		if (timer_storage > RUN_TIME)
		{
			return 0;
		}
	}

	/* Priority Queue Test */
	// periodicRunningQueue.push(new PeriodicTask(500, 15));
	// periodicRunningQueue.push(new PeriodicTask(10, 5));
	// periodicRunningQueue.push(new PeriodicTask(2000, 25));
	// periodicRunningQueue.push(new PeriodicTask(13, 900));

	// std::cout << "-----------Size:" << std::endl;
	// std::cout << "-----------Size:" << periodicRunningQueue.size() << std::endl;

	// int size = periodicRunningQueue.size();
	// for (int i = 0; i < size; i++)
	// {
	// 	PeriodicTask *t = periodicRunningQueue.top();
	// 	periodicRunningQueue.pop();
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

#include <cstdlib>
#include <iostream>

#include "DatasetManager.h"
#include "Scheduler.h"
#include "Thread.h"
#include "Timer.h"
#include "Task.h"
#include "PeriodicTask.h"

/* TODO: TEST INCLUDES */
#include <vector>

#include <stdint.h>
#include <atomic.h>

#include <sys/time.h>
#include <signal.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

using namespace realtime_vehicle_monitoring_diagnostics;

#define TIMER_10_MS_IN_NS (10000000)
#define TIMER_1_MS_IN_NS (1000000)
#define ONE_MILLION (1000000)

#define CONSUMER_EXECUTION_TIME (1)
#define PRODUCER_EXECUTION_TIME (1)

/* Rotates in 4294967295 ~1.6months */
volatile unsigned timer_storage;

std::vector<PeriodicTask> periodicTasks;

// std::priority_queue<Task *, std::vector<Task *>, comparePeriodicTasks> periodicRunningQueue;

std::priority_queue<PeriodicTask *, std::vector<PeriodicTask *>, comparePeriodicTasks> periodicRunningQueue;

void task_release_handler(int sig_number)
{
	atomic_add(&timer_storage, TIMER_10_MS_IN_NS / ONE_MILLION);

	Scheduler::release_update(timer_storage, &periodicTasks, &periodicRunningQueue);

	printf("Number of Tasks: %u\n", Scheduler::get_running_queue_size(&periodicRunningQueue));
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

// static void task_body(void)
// {
// 	static int cycles = 0;
// 	static uint64_t start;
// 	uint64_t current;
// 	struct timespec tv;

// 	if (start == 0)
// 	{
// 		clock_gettime(CLOCK_MONOTONIC, &tv);
// 		start = tv.tv_sec * ONE_THOUSAND + tv.tv_nsec / ONE_MILLION;
// 	}

// 	clock_gettime(CLOCK_MONOTONIC, &tv);
// 	current = tv.tv_sec * ONE_THOUSAND + tv.tv_nsec / ONE_MILLION;

// 	if (cycles > 0)
// 	{
// 		fprintf(stderr, "Ave interval between instances: %f millisecons\n",
// 				(double)(current - start) / cycles);
// 	}

// 	cycles++;
// }

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

int main(int argc, char *argv[])
{
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

	/* Initialize Periodic Tasks for 30000s */
	Scheduler::add_periodic_task(PeriodicTask(10, PRODUCER_EXECUTION_TIME), &periodicTasks);   // 3000
	Scheduler::add_periodic_task(PeriodicTask(500, PRODUCER_EXECUTION_TIME), &periodicTasks);  // 60
	Scheduler::add_periodic_task(PeriodicTask(2000, PRODUCER_EXECUTION_TIME), &periodicTasks); // 15
	Scheduler::add_periodic_task(PeriodicTask(100, PRODUCER_EXECUTION_TIME), &periodicTasks);  // 300
	Scheduler::add_periodic_task(PeriodicTask(5000, PRODUCER_EXECUTION_TIME), &periodicTasks); // 6
	Scheduler::add_periodic_task(PeriodicTask(150, PRODUCER_EXECUTION_TIME), &periodicTasks);  // 200
	Scheduler::add_periodic_task(PeriodicTask(100, PRODUCER_EXECUTION_TIME), &periodicTasks);  // 300

	int res;

	// const int signal = SIGALRM;
	const int signal_type = SIGUSR1;
	signal(signal_type, task_release_handler);

	timer_t timer;
	sigset_t sigst;
	struct sigevent sigev;
	struct itimerspec timer_spec;

	//set and activate a timer
	res = start_periodic_timer(TIMER_10_MS_IN_NS,
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

	// struct itimerspec current_time;

	while (1)
	{
		if (timer_storage > 30000)
		// if (timer_storage > 10)
		{
			return 0;
		}
	}

	// // std::vector<PeriodicTask> taskQueue;
	// taskQueue.push_back(new PeriodicTask(10, 5));
	// taskQueue.push_back(new PeriodicTask(500, 15));
	// taskQueue.push_back(new PeriodicTask(2000, 25));

	// std::cout << "Size of Task Queue is : " << taskQueue.size() << std::endl;

	// int taskQueueSize = taskQueue.size();

	// for (int i = 0; i < taskQueueSize; i++)
	// {
	// 	/* Test Erase Periodic Tasks - Test Values */
	// 	Task *tempTask = taskQueue.front();
	// 	tempTask->debug_print();
	// 	taskQueue.erase(taskQueue.begin());
	// 	delete tempTask;
	// }

	int pause = 0;
	return EXIT_SUCCESS;
}

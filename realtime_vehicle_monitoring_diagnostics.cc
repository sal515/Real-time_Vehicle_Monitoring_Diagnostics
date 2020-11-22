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

#include <sys/time.h>
#include <signal.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

using namespace realtime_vehicle_monitoring_diagnostics;

#define ONE_THOUSAND 1000
#define ONE_MILLION 1000000
/* offset and period are in microsends. */
#define OFFSET 1000000
#define PERIOD 5000000

sigset_t sigst;

static void wait_next_activation(void)
{
	int dummy;
	/* suspend calling process until a signal is pending */
	sigwait(&sigst, &dummy);

	std::cout << " ----- Suspending Main Thread ----- " << std::endl;
}

int start_periodic_timer(uint64_t offset, int period)
{
	struct itimerspec timer_spec;
	struct sigevent sigev;
	timer_t timer;
	const int signal = SIGALRM;
	int res;

	/* set timer parameters */
	timer_spec.it_value.tv_sec = offset / ONE_MILLION;
	timer_spec.it_value.tv_nsec = (offset % ONE_MILLION) * ONE_THOUSAND;
	timer_spec.it_interval.tv_sec = period / ONE_MILLION;
	timer_spec.it_interval.tv_nsec = (period % ONE_MILLION) * ONE_THOUSAND;

	sigemptyset(&sigst);				  // initialize a signal set
	sigaddset(&sigst, signal);			  // add SIGALRM to the signal set
	sigprocmask(SIG_BLOCK, &sigst, NULL); //block the signal

	/* set the signal event a timer expiration */
	memset(&sigev, 0, sizeof(struct sigevent));
	sigev.sigev_notify = SIGEV_SIGNAL;
	sigev.sigev_signo = signal;

	/* create timer */
	res = timer_create(CLOCK_MONOTONIC, &sigev, &timer);

	if (res < 0)
	{
		perror("Timer Create");
		exit(-1);
	}

	/* activate the timer */
	return timer_settime(timer, 0, &timer_spec, NULL);
}

static void task_body(void)
{
	static int cycles = 0;
	static uint64_t start;
	uint64_t current;
	struct timespec tv;

	if (start == 0)
	{
		clock_gettime(CLOCK_MONOTONIC, &tv);
		start = tv.tv_sec * ONE_THOUSAND + tv.tv_nsec / ONE_MILLION;
	}

	clock_gettime(CLOCK_MONOTONIC, &tv);
	current = tv.tv_sec * ONE_THOUSAND + tv.tv_nsec / ONE_MILLION;

	if (cycles > 0)
	{
		fprintf(stderr, "Ave interval between instances: %f millisecons\n",
				(double)(current - start) / cycles);
	}

	cycles++;
}

int main(int argc, char *argv[])
{
	// DatasetManager ds_manager_obj = DatasetManager();
	// Scheduler scheduler_obj = Scheduler();
	// //	Thread thread_manager_obj = Thread();
	// // Thread.create_thread();
	// Timer timer = Timer();
	// PeriodicTask periodic_task = PeriodicTask();
	// // Task task = Task();
	// // task.task_type = PERIODIC;

	int res;

	//set and activate a timer
	res = start_periodic_timer(OFFSET, PERIOD);
	if (res < 0)
	{
		perror("Start periodic timer");
		return -1;
	}

	while (1)
	{
		wait_next_activation(); //wait for timer expiration

		// task_body(); //executes the task

		std::cout << " ----- Main Thread Resumed ----- " << std::endl;
	}

	return EXIT_SUCCESS;

	std::vector<Task *> taskQueue;
	// std::vector<PeriodicTask> taskQueue;
	taskQueue.push_back(new PeriodicTask(10, 5));
	taskQueue.push_back(new PeriodicTask(500, 15));
	taskQueue.push_back(new PeriodicTask(2000, 25));

	std::cout << "Size of Task Queue is : " << taskQueue.size() << std::endl;

	int taskQueueSize = taskQueue.size();

	for (int i = 0; i < taskQueueSize; i++)
	{
		/* Test Erase Periodic Tasks - Test Values */
		Task *tempTask = taskQueue.front();
		tempTask->debug_print();
		taskQueue.erase(taskQueue.begin());
		delete tempTask;
	}

	int pause = 0;
	return EXIT_SUCCESS;
}

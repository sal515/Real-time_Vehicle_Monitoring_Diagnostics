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

#define TIMER_10_MS (10000000)
#define ONE_MILLION (1000000)

/* Rotates in 4294967295 ~1.6months */
volatile unsigned timer_storage;

timer_t timer;
sigset_t sigst;
struct sigevent sigev;
struct itimerspec timer_spec;

void timer_usr1_handler(int sig_number)
{
	atomic_add(&timer_storage, TIMER_10_MS / ONE_MILLION);
	std::cout << "Signal was raised - "
			  << "Counter Val: " << timer_storage << " Size of unsigned " << sizeof(timer_storage) << std::endl;
}

int start_periodic_timer()
{
	signal(SIGUSR1, timer_usr1_handler);
	const int signal = SIGUSR1;
	// const int signal = SIGALRM;
	int res;

	/* 10ms timeout with 1ms interval  */
	timer_spec.it_value.tv_sec = 0;
	timer_spec.it_value.tv_nsec = TIMER_10_MS;
	timer_spec.it_interval.tv_sec = 0;
	timer_spec.it_interval.tv_nsec = TIMER_10_MS;

	/* add the sigusr1 to sig set */
	sigemptyset(&sigst);	   // initialize a signal set
	sigaddset(&sigst, signal); // add SIGALRM to the signal set
	// sigprocmask(SIG_BLOCK, &sigst, NULL); //block the signal

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
	res = start_periodic_timer();
	if (res < 0)
	{
		perror("Start periodic timer");
		return -1;
	}

	struct itimerspec current_time;

	while (1)
	{
	}

	// std::vector<Task *> taskQueue;
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

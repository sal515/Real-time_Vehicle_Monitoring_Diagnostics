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
#include <queue>

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

// This is the comparison function for the Priority Queue
struct compareTasksDeadline
{
	// bool operator()(Task* const &t1, Task* const &t2)
	bool operator()(Task *const t1, Task *const t2)
	{
		// return "true" if "p1" is ordered before "p2", for example:
		// return t1.executed_time > t2.executed_time;
		// return t1->executed_time > t2->executed_time;
		// return static_cast<PeriodicTask *>(t1)->period < static_cast<PeriodicTask *>(t2)->period;

		switch 

		return static_cast<PeriodicTask *>(t1)->period > static_cast<PeriodicTask *>(t2)->period;
	}
};

#define TIMER_10_MS_IN_NS (10000000)
#define ONE_MILLION (1000000)

#define CONSUMER_EXECUTION_TIME (1)
#define PRODUCER_EXECUTION_TIME (1)

/* Rotates in 4294967295 ~1.6months */
volatile unsigned timer_storage;

timer_t timer;
sigset_t sigst;
struct sigevent sigev;
struct itimerspec timer_spec;

/* TODO: Should be a priority Queue */
std::vector<Task *> runningQueue;
std::vector<PeriodicTask> periodicTasks;

// std::priority_queue<Task *, std::vector<Task *>, compareTasksDeadline> runningQueue_;
// std::priority_queue<Task, std::vector<Task>, compareTasksDeadline> runningQueue_;
std::priority_queue<PeriodicTask *, std::vector<PeriodicTask *>, compareTasksDeadline> runningQueue_;

void timer_usr1_handler(int sig_number)
{
	atomic_add(&timer_storage, TIMER_10_MS_IN_NS / ONE_MILLION);
	std::cout << "Signal was raised - "
			  << "Counter Val: " << timer_storage << " Size of unsigned " << sizeof(timer_storage) << std::endl;

	Scheduler::release_update(timer_storage, &periodicTasks, &runningQueue);

	std::cout << "Number of Tasks: " << Scheduler::get_running_queue_size(&runningQueue) << std::endl;
}

int start_periodic_timer(int period_ns)
{
	signal(SIGUSR1, timer_usr1_handler);
	const int signal = SIGUSR1;
	// const int signal = SIGALRM;
	int res;

	/* 10ms timeout with 1ms interval  */
	timer_spec.it_value.tv_sec = 0;
	timer_spec.it_value.tv_nsec = period_ns;
	timer_spec.it_interval.tv_sec = 0;
	timer_spec.it_interval.tv_nsec = period_ns;

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
		perror("Timer Create Failed\n");
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

	// runningQueue_.push(PeriodicTask(2000, 25));
	// runningQueue_.push(PeriodicTask(500, 15));
	// runningQueue_.push(PeriodicTask(10, 5));
	// runningQueue_.push(PeriodicTask(13, 900));

	runningQueue_.push(new PeriodicTask(500, 15));
	runningQueue_.push(new PeriodicTask(10, 5));
	runningQueue_.push(new PeriodicTask(2000, 25));
	runningQueue_.push(new PeriodicTask(13, 900));

	std::cout << "-----------Size:" << std::endl;
	std::cout << "-----------Size:" << runningQueue_.size() << std::endl;

	int size = runningQueue_.size();
	for (int i = 0; i < size; i++)
	{
		PeriodicTask *t = runningQueue_.top();
		runningQueue_.pop();
		// std::cout << "task executed time" << t->executed_time << std::endl;
		std::cout << "task executed time: " << t->period << std::endl;
		delete t;
	}
	// t = runningQueue_.pop();
	// std::cout << t.executed_time << std::endl;
	// t = runningQueue_.pop();
	// std::cout << t.executed_time << std::endl;
	// t = runningQueue_.pop();
	// std::cout << t.executed_time << std::endl;

	return 0;

	// DatasetManager ds_manager_obj = DatasetManager();
	// Scheduler scheduler_obj = Scheduler();
	// //	Thread thread_manager_obj = Thread();
	// // Thread.create_thread();
	// Timer timer = Timer();
	// PeriodicTask periodic_task = PeriodicTask();
	// // Task task = Task();
	// // task.task_type = PERIODIC;

	/* Initialize Periodic Tasks */
	Scheduler::add_periodic_task(PeriodicTask(10, PRODUCER_EXECUTION_TIME), &periodicTasks);
	Scheduler::add_periodic_task(PeriodicTask(500, PRODUCER_EXECUTION_TIME), &periodicTasks);
	// Scheduler::add_periodic_task(PeriodicTask(2000, PRODUCER_EXECUTION_TIME), &periodicTasks);
	// Scheduler::add_periodic_task(PeriodicTask(100, PRODUCER_EXECUTION_TIME), &periodicTasks);
	// Scheduler::add_periodic_task(PeriodicTask(5000, PRODUCER_EXECUTION_TIME), &periodicTasks);
	// Scheduler::add_periodic_task(PeriodicTask(150, PRODUCER_EXECUTION_TIME), &periodicTasks);
	// Scheduler::add_periodic_task(PeriodicTask(100, PRODUCER_EXECUTION_TIME), &periodicTasks);

	int res;

	//set and activate a timer
	res = start_periodic_timer(TIMER_10_MS_IN_NS);
	if (res < 0)
	{
		perror("Start periodic timer");
		return -1;
	}

	// struct itimerspec current_time;

	while (1)
	{
		if (timer_storage > 30000)
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

// volatile int data_ready = 0;

// void *consumer(void *arg)
// {

// 	printf("In consumer thread...\n");
// 	while (1)
// 	{
// 		pthread_sleepon_lock();
// 		while (!data_ready)
// 		{
// 			// WAIT
// 			pthread_sleepon_wait(&data_ready);
// 		}
// 		// process data
// 		// printf("test func %s -> %d\n", (char *)(arg), i++);
// 		printf("consumer:  %s \n", (char *)(arg));

// 		data_ready = 0;
// 		pthread_sleepon_unlock();
// 	}

// 	// int i = 0;
// 	// printf("test func %s\n", (char *)(arg));
// 	// while (1)
// 	// {
// 	// 	while (!data_ready)
// 	// 	{
// 	// 		// WAIT
// 	// 		pthread_sleepon_lock();
// 	// 	}
// 	// 	// process data
// 	// 	printf("test func %s -> %d\n", (char *)(arg), i++);

// 	// 	//		 sleep(5);
// 	// }
// 	//	pthread_exit();
// }

// void *producer(void *arg)
// {
// 	printf("In producer thread  %s \n", (char *)(arg));
// 	while (1)
// 	{
// 		sleep(1);
// 		// printf("producer:  got data from h/w\n");
// 		printf("producer:  %s \n", (char *)(arg));
// 		// wait for interrupt from hardware here...
// 		pthread_sleepon_lock();
// 		data_ready = 1;
// 		pthread_sleepon_signal(&data_ready);
// 		pthread_sleepon_unlock();
// 	}
// }

#include <cstdlib>
#include <iostream>

#include "Thread.h"
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
#include <unistd.h>

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

/* consumer and producer tasks */

// #include <stdio.h>
// #include <pthread.h>
// #include <unistd.h>

int data_ready = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condvar = PTHREAD_COND_INITIALIZER;

void *consumer(void *args)
{
	printf("In consumer thread...\n");
	while (1)
	{
		// while (!data_ready)
		// {
		sleep(1);

		pthread_mutex_lock(&mutex);
		pthread_cond_wait(&condvar, &mutex);
		// }
		// process data
		printf("consumer:  got data from producer\n");
		data_ready = 0;
		pthread_cond_signal(&condvar);
		pthread_mutex_unlock(&mutex);
	}
}

void *producer(void *args)
{
	printf("In producer thread...\n");
	while (1)
	{
		// get data from hardware
		// we'll simulate this with a sleep (1)
		// sleep(1);
		printf("producer:  got data from h/w\n");
		pthread_mutex_lock(&mutex);
		pthread_cond_wait(&condvar, &mutex);
		// while (data_ready)
		// {
		// }
		sleep(5);
		data_ready = 1;
		pthread_cond_signal(&condvar);
		pthread_mutex_unlock(&mutex);
	}
}

// main()
// {
// 	printf("Starting consumer/producer example...\n");

// 	// create the producer and consumer threads
// 	pthread_create(NULL, NULL, producer, NULL);
// 	pthread_create(NULL, NULL, consumer, NULL);

// 	// let the threads run for a bit
// 	sleep(10);
// 	pthread_cond_signal(&condvar);
// 	sleep(20);
// }

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
	printf("Starting consumer/producer example...\n");
	Thread producer_thread1 = Thread(producer, 11, "P-P60");
	Thread consumer_thread = Thread(consumer, 10, "C-P10");
	// Thread producer_thread2 = Thread(producer, 20, "P-P20");
	// Thread producer_thread3 = Thread(producer, 30, "P-P30");
	// Thread producer_thread4 = Thread(producer, 40, "P-P40");
	// Thread producer_thread5 = Thread(producer, 50, "P-P50");

	while (1)
	{
		// infinite wait
	}
	return 0;

	/* TODO: TESTING THREADS PRORITY */
	Thread t2 = Thread(consumer, 5, "T2-P5");
	Thread t3 = Thread(consumer, 50, "T3-P50");
	// Thread t1 = Thread(consumer, 1, "T1-P1");
	// Thread t4 = Thread(consumer, 254, "T4-P254");
	// pthread_join(t3.thread, NULL);
	return 0;
	/* TODO: TESTING THREADS PRORITY */

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

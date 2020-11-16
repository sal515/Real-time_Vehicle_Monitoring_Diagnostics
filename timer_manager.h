/*
 * Timer_Manager.h
 *
 *  Created on: Nov 14, 2020
 *      Author: Salman
 */

#ifndef TIMER_MANAGER_H_
#define TIMER_MANAGER_H_

namespace realtime_vehicle_monitoring_diagnostics
{

	class Timer_Manager
	{
	public:
		Timer_Manager(); // create a timer
		virtual ~Timer_Manager();

		// int create_timer();
		int start_timer();
		int stop_timer();
		void get_timer_value();
	};

} // namespace realtime_vehicle_monitoring_diagnostics

#endif /* TIMER_MANAGER_H_ */


/* Timer example */

// #include <stdlib.h>
// //#include <iostream>
// #include <unistd.h>
// #include <stdio.h>
// #include <pthread.h>
// #include <inttypes.h>
// #include <errno.h>
// #include <sys/neutrino.h>
// #include "csv_data.hpp"

// #include <sys/time.h>
// #include <signal.h>
// #include <time.h>
// #include <stdint.h>
// #include <string.h>

// #define ONE_THOUSAND 1000
// #define ONE_MILLION 1000000
// #define FIVE_MILLION 5000000
// /* offset and period are in microsends. */
// // #define OFFSET 1000000
// // #define PERIOD 5000000
// #define OFFSET (ONE_MILLION)
// #define PERIOD (FIVE_MILLION)

// #define SEC_NSEC 1000000000LL // 1 billion nanoseconds in a second

// struct task
// {
// 	int period;
// 	int executionTime;
// 	long currentTime;
// };

// sigset_t sigst;
// static void wait_next_activation(void)
// {
// 	int dummy;
// 	/* suspend calling process until a signal is pending */
// 	sigwait(&sigst, &dummy);
// }

// // int start_periodic_timer(uint64_t offset, int period)
// int start_periodic_timer(int period)
// {
// 	struct itimerspec timer_spec;
// 	struct sigevent sigev;
// 	timer_t timer;
// 	const int signal = SIGALRM;
// 	int res;

// 	/* set timer parameters */
// 	timer_spec.it_value.tv_sec = 0;
// 	timer_spec.it_value.tv_nsec = 1;
// 	timer_spec.it_interval.tv_sec = 0;
// 	timer_spec.it_interval.tv_nsec = ONE_MILLION;
// 	// timer_spec.it_value.tv_sec = offset / ONE_MILLION;
// 	// timer_spec.it_value.tv_nsec = (offset % ONE_MILLION) * ONE_THOUSAND;
// 	// timer_spec.it_interval.tv_sec = period / ONE_MILLION;
// 	// timer_spec.it_interval.tv_nsec = (period % ONE_MILLION) * ONE_THOUSAND;

// 	sigemptyset(&sigst);				  // initialize a signal set
// 	sigaddset(&sigst, signal);			  // add SIGALRM to the signal set
// 	sigprocmask(SIG_BLOCK, &sigst, NULL); //block the signal

// 	/* set the signal event a timer expiration */
// 	memset(&sigev, 0, sizeof(struct sigevent));
// 	sigev.sigev_notify = SIGEV_SIGNAL;
// 	sigev.sigev_signo = signal;

// 	/* create timer */
// 	res = timer_create(CLOCK_MONOTONIC, &sigev, &timer);

// 	if (res < 0)
// 	{
// 		perror("Timer Create");
// 		exit(-1);
// 	}

// 	/* activate the timer */
// 	return timer_settime(timer, 0, &timer_spec, NULL);
// }

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

// void *
// long_thread(void *notused)
// {
// 	printf("This thread runs for more than 10 seconds\n");
// 	sleep(20);
// 	//	return;
// }

// void producer()
// {
// 	int i = 0;
// 	for (i = 0; i < 5; i++)
// 	{
// 		printf("Fuel consumption value is: %4.2f\n", fuel_consumption[i]);
// 	}
// }

// int main(int argc, char *argv[])
// {
// 	//	printf("Welcomsdfsdafsadfe  thexzs354165414623adfsda QNX  IDEEEE\n");

// 	if (!(sizeof(fuel_consumption) == sizeof(engine_speed) &&
// 		  sizeof(engine_speed) == sizeof(engine_coolant_temperature) &&
// 		  sizeof(engine_coolant_temperature) == sizeof(current_gear) &&
// 		  sizeof(current_gear) == sizeof(vehicle_speed) &&
// 		  sizeof(vehicle_speed) == sizeof(acceleration_speed_longitudinal) &&
// 		  sizeof(acceleration_speed_longitudinal) == sizeof(indication_of_brake_switch_on_off)))
// 	{
// 		printf("Sizes do not match");
// 	}

// 	producer();

// 	// uint64_t timeout;
// 	// struct sigevent event;
// 	// int rval;
// 	// pthread_t thread_id;

// 	// // set up the event -- this can be done once

// 	// // This or event.sigev_notify = SIGEV_UNBLOCK:
// 	// SIGEV_UNBLOCK_INIT(&event);

// 	// // create a thread
// 	// pthread_create(&thread_id, NULL, long_thread, NULL);

// 	// // set up for 10 second timeout
// 	// timeout = 10LL * SEC_NSEC;

// 	// TimerTimeout(CLOCK_REALTIME, _NTO_TIMEOUT_JOIN, &event, &timeout, NULL);

// 	// rval = pthread_join(thread_id, NULL);
// 	// if (rval == ETIMEDOUT)
// 	// {
// 	// 	printf("Thread %d is still running after 10 seconds!\n",
// 	// 		   thread_id);
// 	// }

// 	// sleep(5);

// 	// TimerTimeout(CLOCK_REALTIME, _NTO_TIMEOUT_JOIN, &event, &timeout, NULL);
// 	// rval = pthread_join(thread_id, NULL);
// 	// if (rval == ETIMEDOUT)
// 	// {
// 	// 	printf("Thread %d is still running after 25 seconds (bad)!\n",
// 	// 		   thread_id);
// 	// }
// 	// else
// 	// {
// 	// 	printf("Thread %d finished (expected!)\n", thread_id);
// 	// }

// 	// /* Timer */
// 	// int res;

// 	// //set and activate a timer
// 	// // res = start_periodic_timer(OFFSET, PERIOD);
// 	// res = start_periodic_timer(PERIOD);
// 	// if (res < 0)
// 	// {
// 	// 	perror("Start periodic timer");
// 	// 	return -1;
// 	// }

// 	// while (1)
// 	// {
// 	// 	wait_next_activation(); //wait for timer expiration
// 	// 	task_body();			//executes the task
// 	// }

// 	// /* Timer */

// 	return EXIT_SUCCESS;
// }

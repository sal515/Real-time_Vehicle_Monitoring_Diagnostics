/*
 * Timer.cpp
 *
 *  Created on: Nov 14, 2020
 *      Author: Salman
 */

#include "Timer.h"
#include <iostream>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define DEBUG_PRINT 0

namespace realtime_vehicle_monitoring_diagnostics
{
	Timer::Timer(int period_ns,
				 char *timer_name,
				 const int signal_type)
	{
		if (DEBUG_PRINT)
		{
			printf("Timer object created\n");
		}

		this->period_ns = period_ns;
		this->signal_type = signal_type;
		this->timer_name = timer_name;

		/* Setting timer param and Creating a timer */

		/* Timer timeout settings */
		this->timer_spec.it_value.tv_sec = 0;
		this->timer_spec.it_value.tv_nsec = period_ns;
		this->timer_spec.it_interval.tv_sec = 0;
		this->timer_spec.it_interval.tv_nsec = period_ns;

		/* add the signal to sig set */
		sigemptyset(&this->sigst);					// initialize a signal set
		sigaddset(&this->sigst, this->signal_type); // add SIGALRM to the signal set
		// sigprocmask(SIG_BLOCK, &sigst, NULL); //block the signal

		/* set the signal event a timer expiration */
		memset(&this->sigev, 0, sizeof(struct sigevent));
		this->sigev.sigev_notify = SIGEV_SIGNAL;
		this->sigev.sigev_signo = this->signal_type;

		/* create timer */
		if (timer_create(CLOCK_MONOTONIC, &this->sigev, &this->timer) < 0)
		{
			printf("%s - Creation Failed \n", timer_name);
			exit(-1);
		}

		return;
	}

	Timer::~Timer()
	{
		printf("Timer object destroyed\n");
		/* TODO: NEEDS IMPLEMENTATION */
	}

	int Timer::start()
	{
		/* activate the timer */
		return timer_settime(this->timer, 0, &this->timer_spec, NULL);
	}

	int Timer::destroy()
	{
		/* activate the timer */
		return timer_delete(this->timer);
	}

} // namespace realtime_vehicle_monitoring_diagnostics

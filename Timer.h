/*
 * Timer.h
 *
 *  Created on: Nov 14, 2020
 *      Author: Salman
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <time.h>
#include <sys/siginfo.h>
#include <signal.h>
#include "Timer.h"

namespace realtime_vehicle_monitoring_diagnostics
{

#define TIMER_1_MS_IN_NS (1000000)
#define TIMER_10_MS_IN_NS (10000000)
#define ONE_MILLION (1000000)

	class Timer
	{
	public:
		Timer(int period_ns,
			  char *timer_name,
			  const int signal_type); // create a timer

		virtual ~Timer();

		int period_ns;
		char *timer_name;
		int signal_type;

		itimerspec timer_spec;
		sigevent sigev;
		timer_t timer;
		sigset_t sigst;

		int start();
		int destroy();
	};

} // namespace realtime_vehicle_monitoring_diagnostics

#endif /* TIMER_H_ */

/*
 * Timer.cpp
 *
 *  Created on: Nov 14, 2020
 *      Author: Salman
 */

#include "Timer.h"
#include <iostream>



namespace realtime_vehicle_monitoring_diagnostics
{
	Timer::Timer()
	{
		// TODO Auto-generated constructor stub
		std::cout << "Timer object created" << std::endl;
		
		return;

		/* Create a timer */
		int timer_create(clockid_t clock_id,
						 struct sigevent * event,
						 timer_t * timerid);
	}

	Timer::~Timer()
	{
		// TODO Auto-generated destructor stub
		std::cout << "Timer object destroyed" << std::endl;
	}

} // namespace realtime_vehicle_monitoring_diagnostics

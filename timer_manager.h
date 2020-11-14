/*
 * timer_manager.h
 *
 *  Created on: Nov 14, 2020
 *      Author: Salman
 */

#ifndef TIMER_MANAGER_H_
#define TIMER_MANAGER_H_

namespace realtime_vehicle_monitoring_diagnostics
{

	class timer_manager
	{
	public:
		timer_manager(); // create a timer
		virtual ~timer_manager();

		// int create_timer();
		int start_timer();
		int stop_timer();
		void get_timer_value();
	};

} // namespace realtime_vehicle_monitoring_diagnostics

#endif /* TIMER_MANAGER_H_ */

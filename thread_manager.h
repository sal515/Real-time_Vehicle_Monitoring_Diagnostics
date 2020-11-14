/*
 * thread_manager.h
 *
 *  Created on: Nov 14, 2020
 *      Author: Salman
 */

#ifndef THREAD_MANAGER_H_
#define THREAD_MANAGER_H_

namespace realtime_vehicle_monitoring_diagnostics
{

	class thread_manager
	{
	public:
		thread_manager();
		virtual ~thread_manager();

		int create_thread();
		int destroy_thread();
		void check_status_thread();
		int change_priority_of_thread();
	};

} // namespace realtime_vehicle_monitoring_diagnostics

#endif /* THREAD_MANAGER_H_ */

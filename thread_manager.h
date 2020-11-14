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
	private:
		thread_manager();
		virtual ~thread_manager();

	public:
		static int create_thread();
		static int destroy_thread();
		static void check_status_thread();
		static int change_priority_of_thread();
	};

} // namespace realtime_vehicle_monitoring_diagnostics

#endif /* THREAD_MANAGER_H_ */

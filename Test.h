/*
 * Test.h
 *
 *  Created on: Dec 3, 2020
 *      Author: Salman
 */

#ifndef TEST_H_
#define TEST_H_
#include "Thread.h"

namespace realtime_vehicle_monitoring_diagnostics
{

	class Test
	{
	public:
		Test();
		virtual ~Test();
		static void test_thread(start_routine_t producer, start_routine_t consumer);
	};

} // namespace realtime_vehicle_monitoring_diagnostics

#endif /* TEST_H_ */

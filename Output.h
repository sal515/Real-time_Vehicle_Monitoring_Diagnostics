/*
 * Output.h
 *
 *  Created on: Dec 6, 2020
 *      Author: Salman
 */

#ifndef OUTPUT_H_
#define OUTPUT_H_

#include <string>

namespace realtime_vehicle_monitoring_diagnostics
{

	class Output
	{
	public:
		Output(char * task_name, std::string value);
		virtual ~Output();

		char *task_name;
		std::string value;
	};

} // namespace realtime_vehicle_monitoring_diagnostics

#endif /* OUTPUT_H_ */

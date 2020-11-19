/*
 * Task->cpp
 *
 *  Created on: Nov 14, 2020
 *      Author: Salman
 */

#include "Task.h"
#include <iostream>

namespace realtime_vehicle_monitoring_diagnostics
{

    Task::Task()
    {
		std::cout << "Task object created" << std::endl;
        std::cout << "**Default constructor is not permitted**" << std::endl;

        // TODO Auto-generated constructor stub
        // exit(-1);
    }

    Task::~Task()
    {
        // TODO Auto-generated destructor stub
		std::cout << "Task object destroyed" << std::endl;
    }



} // namespace realtime_vehicle_monitoring_diagnostics

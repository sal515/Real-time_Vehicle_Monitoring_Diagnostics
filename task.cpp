/*
 * Task->cpp
 *
 *  Created on: Nov 14, 2020
 *      Author: Salman
 */

#include "task.h"
#include <iostream>

namespace realtime_vehicle_monitoring_diagnostics
{

    Task::Task()
    {
        std::cout << "Default constructor is not permitted" << std::endl;

        // TODO Auto-generated constructor stub
        // exit(-1);
    }

    Task::~Task()
    {
        // TODO Auto-generated destructor stub
    }

    // Task::Task(long period, long execution_time, long relative_deadline, long phase)
    // {
    //     if (relative_deadline == -1)
    //     {
    //         this->relative_deadline = period;
    //     }

    //     this->period = period;
    //     this->relative_deadline = relative_deadline;
    //     this->execution_time = execution_time;
    //     this->phase = phase;

    //     this->executed_time = 0;
    //     this->last_started_time = 0;
    // }

} // namespace realtime_vehicle_monitoring_diagnostics

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
    // std::cout << "Task object created" << std::endl;
  }

  Task::~Task()
  {
    // std::cout << "Task object destroyed" << std::endl;
  }

  void Task::debug_print()
  {
    std::cout << "Task class debug print" << std::endl;
  }

} // namespace realtime_vehicle_monitoring_diagnostics

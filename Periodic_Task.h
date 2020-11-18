/*
 * Periodic_Task.h
 *
 *  Created on: Nov 16, 2020
 *      Author: Salman
 */

#ifndef PERIODIC_TASK_H_
#define PERIODIC_TASK_H_

#include "task.h"

namespace realtime_vehicle_monitoring_diagnostics {

class Periodic_Task: public realtime_vehicle_monitoring_diagnostics::Task {
public:
	Periodic_Task();
	virtual ~Periodic_Task();
};

}

#endif /* PERIODIC_TASK_H_ */

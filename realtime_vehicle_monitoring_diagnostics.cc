#include <cstdlib>
#include <iostream>

#include "dataset_manager.h"
#include "scheduler.h"
#include "thread_manager.h"
#include "timer_manager.h"
#include "task.h"
#include "Periodic_Task.h"

using namespace realtime_vehicle_monitoring_diagnostics;

int main(int argc, char *argv[])
{
	Dataset_Manager ds_manager_obj = Dataset_Manager();
	Scheduler scheduler_obj = Scheduler();
	//	Thread_Manager thread_manager_obj = Thread_Manager();
	Timer_Manager timer_manager_obj = Timer_Manager();
	Periodic_Task periodic_task = Periodic_Task();
	// Task task = Task();
	// task.task_type = PERIODIC;

	return EXIT_SUCCESS;
}

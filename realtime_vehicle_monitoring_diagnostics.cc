#include <cstdlib>
#include <iostream>

#include "DatasetManager.h"
#include "Scheduler.h"
#include "Thread.h"
#include "Timer.h"
#include "Task.h"
#include "PeriodicTask.h"

using namespace realtime_vehicle_monitoring_diagnostics;

int main(int argc, char *argv[])
{
	DatasetManager ds_manager_obj = DatasetManager();
	Scheduler scheduler_obj = Scheduler();
	//	Thread thread_manager_obj = Thread();
	// Thread.create_thread();
	Timer timer = Timer();
	PeriodicTask periodic_task = PeriodicTask();
	// Task task = Task();
	// task.task_type = PERIODIC;

	return EXIT_SUCCESS;
}

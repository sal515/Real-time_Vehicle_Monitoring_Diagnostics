#include <cstdlib>
#include <iostream>

#include "dataset_manager.h"
#include "scheduler.h"
#include "thread_manager.h"
#include "timer_manager.h"

using namespace realtime_vehicle_monitoring_diagnostics;

int main(int argc, char *argv[])
{
	dataset_manager ds_manager_obj = dataset_manager();
	scheduler scheduler_obj = scheduler();
	thread_manager thread_manager_obj = thread_manager();
	timer_manager timer_manager_obj = timer_manager();

	return EXIT_SUCCESS;
}

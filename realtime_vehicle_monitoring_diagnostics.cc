#include <cstdlib>
#include <iostream>

#include "DatasetManager.h"
#include "Scheduler.h"
#include "Thread.h"
#include "Timer.h"
#include "Task.h"
#include "PeriodicTask.h"

/* TODO: TEST INCLUDES */
#include <vector>

using namespace realtime_vehicle_monitoring_diagnostics;

int main(int argc, char *argv[])
{
	// DatasetManager ds_manager_obj = DatasetManager();
	// Scheduler scheduler_obj = Scheduler();
	// //	Thread thread_manager_obj = Thread();
	// // Thread.create_thread();
	// Timer timer = Timer();
	// PeriodicTask periodic_task = PeriodicTask();
	// // Task task = Task();
	// // task.task_type = PERIODIC;

	std::vector<Task *> taskQueue;
	// std::vector<PeriodicTask> taskQueue;
	taskQueue.push_back(new PeriodicTask(10, 5));
	taskQueue.push_back(new PeriodicTask(500, 15));
	taskQueue.push_back(new PeriodicTask(2000, 25));

	std::cout << "Size of Task Queue is : " << taskQueue.size() << std::endl;

	int taskQueueSize = taskQueue.size();

	for (int i = 0; i < taskQueueSize; i++)
	{
		Task *tempTask = taskQueue.front();
		tempTask->debug_print();
		taskQueue.erase(taskQueue.begin());
		delete tempTask;
	}

	// Task *taskQueue[3];
	// taskQueue[0] = new PeriodicTask(10, 1);
	// taskQueue[1] = new PeriodicTask(500, 5);
	// taskQueue[2] = new PeriodicTask(200, 10);

	// for (int i = 0; i < taskQueue.size(); i++)
	// {
	// 	delete taskQueue[i];
	// }

	std::cout << "Testing Vector" << std::endl;
	int pause = 0;
	return EXIT_SUCCESS;
}

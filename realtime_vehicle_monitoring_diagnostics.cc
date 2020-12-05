#include <cstdlib>
#include <iostream>

#include "Test.h"
#include "Thread.h"
#include "Task.h"
#include "Timer.h"
#include "Scheduler.h"
#include "PeriodicTask.h"
#include "AperiodicTask.h"
#include "SporadicTask.h"
// #include "DatasetManager.h"

#include <atomic.h>

// #include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <unistd.h>
#include <vector>
#include <fstream>
#include <sstream>

using namespace realtime_vehicle_monitoring_diagnostics;

#define DEBUG_PRINT 0
// #define DEBUG_PRINT 1

// #define RUN_TIME 30000
// #define RUN_TIME 5000
// #define RUN_TIME 2000
// #define RUN_TIME 10
#define RUN_TIME 11
// #define RUN_TIME 5

#define TIMER_1_MS_IN_NS (1000000)
#define TIMER_10_MS_IN_NS (10000000)
#define ONE_MILLION (1000000)

#define CONSUMER_EXECUTION_TIME (1)
#define PRODUCER_EXECUTION_TIME (1)

/* Timer */
/* Rotates in 4294967295 ~1.6months */
volatile unsigned timer_storage = 0;
Scheduler scheduler = Scheduler();

/* Function prototypes */
void *consumer(void *args);
void *producer(void *args);
void build_periodic_tasks_list(Scheduler *scheduler);
void timer_timeout_handler(int sig_number);

enum TASK_NAME
{
	FUEL_CONSUMPTION,
	ENGINE_SPEED_RPM,
	ENGINE_COOLANT_TEMP,
	CURRENT_GEAR,
	TRANSMISSION_OIL_TEMP,
	VEHICLE_SPEED,
	ACCELERATION_SPEED_LONGITUDINAL,
	INDICATION_BREAK_SWITCH
};

struct PRODUCER_VALUES
{
	std::string fuel_consumption;
	std::string engine_speed_rpm;
	std::string engine_coolant_temp;
	std::string current_gear;
	std::string transmission_oil_temp;
	std::string vehicle_speed;
	std::string acceleration_speed_longitudinal;
	std::string indication_break_switch;
};

PRODUCER_VALUES producer_buffer;
pthread_mutex_t data_mutex;

int string_to_enum_converter(char *task_name)
{
	// if(task_name == "fuel_consumption"){
	// 	return FUEL_CONSUMPTION;
	// }
	// else if()
	/* TODO: Implement  */
}

/* Provides the value for the task identified by the parameter */
std::string read_next_value(int task_name, std::string time_now_ms)
{
	std::string next_value;
	//producer_buffer.fuel_consumption = next_value;
	std::string time = time_now_ms;
	std::ifstream input_from_file("data.csv");
	std::string line;
	while (getline(input_from_file, line))
	{
		line += ",";
		std::stringstream ss(line);
		std::string word;
		std::vector<std::string> words;
		while (getline(ss, word, ','))
		{
			words.push_back(word);
		}
		while (1)
		{
			if (words[7] == time)
			{
				printf("In the fct: %s\n", words[task_name].c_str());
				next_value = words[task_name];
				break;
			}
			else
			{
				break;
			}
		}
	}
	return next_value;
}

int main(int argc, char *argv[])
{
	// make a for loop and pass different values to the next_value function
	// check the printout against the csv file

	/* CLEAN: Test */
	// Test::test_thread(producer, consumer);
	// return 0;
	/* CLEAN: Test */

	std::string time = "5";
	producer_buffer.engine_speed_rpm = read_next_value(ENGINE_SPEED_RPM, time);
	printf("in main: %s\n", producer_buffer.engine_speed_rpm.c_str());

	return 0;
	
	pthread_mutex_init(&data_mutex, NULL);
	build_periodic_tasks_list(&scheduler);

	const int signal_type = SIGUSR1;
	signal(signal_type, timer_timeout_handler);

	Timer one_ms_timer = Timer(TIMER_1_MS_IN_NS,
							   "Task Release Timer",
							   signal_type);
	if (one_ms_timer.start() < 0)
	{
		printf("Failed to start perioidc timer - %s\n", one_ms_timer.timer_name);
		return -1;
	}

	while (1)
	{
		if (timer_storage >= RUN_TIME)
		{
			/* CLEAN: Test */
			// Test::test_priority_queues_EDF(&scheduler);
			/* CLEAN: Test */

			return 0;
		}
	}

	int pause = 0;
	return EXIT_SUCCESS;
}

void *consumer(void *args)
{
	printf("***Consumer Thread***\n");
	Thread *thread = (Thread *)(args);
	// while (1)
	// {
	// 	thread->is_complete = 0;
	// 	thread->block();
	// 	thread->is_complete = 1;
	// 	printf("Consumer: Data Processed\n");
	// 	thread->unblock();
	// }
	char *task_name = thread->thread_name;

	thread->block();
	pthread_mutex_lock(&data_mutex);
	printf("Consumer: Data Processed\n");
	// read from producer_buffer and print out using printf
	// read_next_value(task_name, time_now_ms);
	pthread_mutex_unlock(&data_mutex);
	thread->unblock();
}

void *producer(void *args)
{
	printf("***Producer Thread***\n");
	Thread *thread = (Thread *)(args);

	// while (1)
	// {
	// 	thread->block();
	// 	printf("Producer: Data Processed\n");
	// 	thread->unblock();
	// }

	char *task_name = thread->thread_name;
	thread->block();
	pthread_mutex_lock(&data_mutex);
	printf("Producer: Data Processed\n");
	// write to producer_buffer from file
	// read_next_value(task_name, time_now_ms);
	pthread_mutex_unlock(&data_mutex);
	thread->unblock();
}

void build_periodic_tasks_list(Scheduler *scheduler)
{
	/* Initialize Given Periodic Tasks */
	scheduler->add_periodic_task(PeriodicTask(10,
											  PRODUCER_EXECUTION_TIME,
											  "fuel_consumption")); // total - 3000
	scheduler->add_periodic_task(PeriodicTask(500,
											  PRODUCER_EXECUTION_TIME,
											  "engine_speed_rpm")); // total - 60
	scheduler->add_periodic_task(PeriodicTask(2000,
											  PRODUCER_EXECUTION_TIME,
											  "engine_coolant_temp")); // total - 15
	scheduler->add_periodic_task(PeriodicTask(100,
											  PRODUCER_EXECUTION_TIME, "current_gear")); // total - 300
	scheduler->add_periodic_task(PeriodicTask(5000,
											  PRODUCER_EXECUTION_TIME,
											  "transmission_oil_temp")); // total - 6
	scheduler->add_periodic_task(PeriodicTask(100,
											  PRODUCER_EXECUTION_TIME,
											  "vehicle_speed")); // total - 300
	scheduler->add_periodic_task(PeriodicTask(150,
											  PRODUCER_EXECUTION_TIME,
											  "acceleration_speed_longitudinal")); // total - 200
	scheduler->add_periodic_task(PeriodicTask(100,
											  PRODUCER_EXECUTION_TIME,
											  "indication_break_switch")); // total - 300
}

/* Signal handler */
void timer_timeout_handler(int sig_number)
{

	/* Release Periodic Tasks */
	scheduler.release_periodic_tasks(timer_storage);
	/* Update Priority */
	// scheduler.update_executed_priority(timer_storage);
	/* Run Tasks */

	if (DEBUG_PRINT)
	{
		printf("At time t = : %u\n", timer_storage);
		printf("Number of Tasks: %u\n", scheduler.get_running_queue_size());
	}

	/* TODO : Task list */
	/* Update Priority */
	/* Update Running Queue */
	/* Update Update Execution Time */
	/* Update Run Tasks */

	/* Increment Timer Value */
	atomic_add(&timer_storage, TIMER_1_MS_IN_NS / ONE_MILLION);
}

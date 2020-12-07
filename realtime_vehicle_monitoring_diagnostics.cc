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
#include "Logger.h"
// #include "DatasetManager.h"

#include <atomic.h>

// #include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
// #include <string.h>
#include <string>
#include <unistd.h>

using namespace realtime_vehicle_monitoring_diagnostics;

#define DEBUG_PRINT 0
// #define DEBUG_PRINT 1

//  #define RUN_TIME (5*60*1000)
//  #define RUN_TIME (30000)
// #define RUN_TIME (5000)
// #define RUN_TIME (2000)
// #define RUN_TIME (1000)
// #define RUN_TIME (500)
// #define RUN_TIME (101)
#define RUN_TIME (31)
// #define RUN_TIME (11)
// #define RUN_TIME (10)
// #define RUN_TIME (5)

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

int file_id;
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

int main(int argc, char *argv[])
{
	/* For tests */
	// 		// test code here
	// return 0;

	// while (1)
	// {

	Logger::create_open_log_file(file_id);

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

	while (timer_storage < RUN_TIME)
	{
		/* Run program */
	}

	int pause = 0;
	// }
	return EXIT_SUCCESS;
}

void *consumer(void *args)
{
	char buffer[500];
	int string_size;
	std::string regular_str;

	Thread *thread = (Thread *)(args);
	char *task_name = thread->thread_name;

	printf("\n***%s task --> execution started***\n", task_name);
	Logger::log_thread_details(thread, "Details of the thread - going to sleep:");
	string_size = sprintf(buffer, "\n***%s task --> execution started***\n", task_name);
	Logger::write_to_file(file_id, buffer, string_size);

	thread->block();
	pthread_mutex_lock(&data_mutex);

	regular_str = "Details of the thread - waking up:";
	Logger::log_thread_details(thread, regular_str.c_str());
	Logger::write_to_file(file_id, regular_str.c_str(), regular_str.size());
	// -- critical section --

	// -- critical section --
	pthread_mutex_unlock(&data_mutex);
	thread->unblock();

	printf("***%s task --> execution ended***\n", task_name);
	string_size = sprintf(buffer, "***%s task --> execution ended***\n", task_name);
	Logger::write_to_file(file_id, buffer, string_size);
}

void *producer(void *args)
{
	char buffer[500];
	int string_size;
	std::string regular_str;

	Thread *thread = (Thread *)(args);
	char *task_name = thread->thread_name;

	printf("\n***%s task --> execution started***\n", task_name);
	Logger::log_thread_details(thread, "Details of the thread - going to sleep:");
	string_size = sprintf(buffer, "\n***%s task --> execution started***\n", task_name);
	Logger::write_to_file(file_id, buffer, string_size);

	thread->block();
	pthread_mutex_lock(&data_mutex);

	regular_str = "Details of the thread - waking up:";
	Logger::log_thread_details(thread, regular_str.c_str());
	Logger::write_to_file(file_id, regular_str.c_str(), regular_str.size());
	// -- critical section --

	// -- critical section --
	pthread_mutex_unlock(&data_mutex);
	thread->unblock();

	printf("***%s task --> execution ended***\n", task_name);
	string_size = sprintf(buffer, "***%s task --> execution ended***\n", task_name);
	Logger::write_to_file(file_id, buffer, string_size);
}

void build_periodic_tasks_list(Scheduler *scheduler)
{
	/* Initialize Given Periodic Tasks */
	PeriodicTask p = PeriodicTask(10,
								  PRODUCER_EXECUTION_TIME,
								  "fuel_consumption",
								  producer);
	scheduler->add_periodic_task(p);
	p = PeriodicTask(500,
					 PRODUCER_EXECUTION_TIME,
					 "engine_speed_rpm",
					 producer);
	scheduler->add_periodic_task(p);
	p = PeriodicTask(2000,
					 PRODUCER_EXECUTION_TIME,
					 "engine_coolant_temp",
					 producer);
	scheduler->add_periodic_task(p);
	p = PeriodicTask(100,
					 PRODUCER_EXECUTION_TIME, "current_gear",
					 producer);
	scheduler->add_periodic_task(p);
	p = PeriodicTask(5000,
					 PRODUCER_EXECUTION_TIME,
					 "transmission_oil_temp",
					 producer);
	scheduler->add_periodic_task(p);
	p = PeriodicTask(100,
					 PRODUCER_EXECUTION_TIME,
					 "vehicle_speed",
					 producer);
	scheduler->add_periodic_task(p);
	p = PeriodicTask(150,
					 PRODUCER_EXECUTION_TIME,
					 "acceleration_speed_longitudinal",
					 producer);
	scheduler->add_periodic_task(p);
	p = PeriodicTask(100,
					 PRODUCER_EXECUTION_TIME,
					 "indication_break_switch",
					 producer);
	scheduler->add_periodic_task(p);

	p = PeriodicTask(10,
					 CONSUMER_EXECUTION_TIME,
					 "Consumer_Print_Function",
					 consumer);

	scheduler->add_periodic_task(p);
}

/* Signal handler */
void timer_timeout_handler(int sig_number)
{
	printf("\n\n\n=======================================================================================\n", timer_storage);
	printf("================================== At time t = : %u  ==================================\n", timer_storage);
	printf("=======================================================================================\n", timer_storage);

	char buffer[200];
	int string_size = sprintf(buffer, "\n\nAt time t = : %u\n", timer_storage);
	Logger::write_to_file(file_id, buffer, string_size);

	/* Release Periodic Tasks */
	scheduler.release_periodic_tasks(timer_storage);

	// /* Update Priority */
	scheduler.update_periodic_priority();

	// /* Update Executed Time */
	scheduler.update_periodic_executed_time(timer_storage);

	// /* Run Tasks */
	scheduler.run_tasks();

	/* Increment Timer Value */
	atomic_add(&timer_storage, TIMER_1_MS_IN_NS / ONE_MILLION);
}

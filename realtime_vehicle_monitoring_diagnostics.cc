#include <cstdlib>
#include <iostream>

#include "Test.h"
#include "Thread.h"
#include "Output.h"
#include "Task.h"
#include "Timer.h"
#include "Scheduler.h"
#include "PeriodicTask.h"
#include "AperiodicTask.h"
#include "SporadicTask.h"
#include <cmath>
#include "Logger.h"
#include "csv_data.h"
// #include "DatasetManager.h"

#include <atomic.h>
#include <queue>

// #include <stdint.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string>
#include <unistd.h>
#include <vector>
#include <fstream>
#include <sstream>

using namespace realtime_vehicle_monitoring_diagnostics;

#define DEBUG_PRINT 0
// #define DEBUG_PRINT 1

//  #define RUN_TIME (5*60*1000)
// #define RUN_TIME (30000)
// #define RUN_TIME (5000)
// #define RUN_TIME (2000)
// #define RUN_TIME (1000)
// #define RUN_TIME (500)
// #define RUN_TIME (101)
// #define RUN_TIME (31)
// #define RUN_TIME (11)
// #define RUN_TIME (10)
// #define RUN_TIME (5)

#define CONSUMER_EXECUTION_TIME (1)
#define PRODUCER_EXECUTION_TIME (1)

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
	VEHICLE_SPEED,
	ACCELERATION_SPEED_LONGITUDINAL,
	INDICATION_BREAK_SWITCH
};

// struct PRODUCER_VALUES
// {
// 	std::string fuel_consumption;
// 	std::string engine_speed_rpm;
// 	std::string engine_coolant_temp;
// 	std::string current_gear;
// 	std::string transmission_oil_temp;
// 	std::string vehicle_speed;
// 	std::string acceleration_speed_longitudinal;
// 	std::string indication_break_switch;
// };
// PRODUCER_VALUES producer_buffer;

/* Timer */
/* Rotates in 4294967295 ~1.6months */
int file_id;
volatile unsigned timer_storage = 0;
Scheduler scheduler = Scheduler();
pthread_mutex_t data_mutex;
std::queue<Output> output_queue;

int producer_string_to_enum_converter(char *task_name)
{
	if (!std::strcmp("fuel_consumption", task_name))
	{
		return FUEL_CONSUMPTION;
	}
	else if (!std::strcmp("engine_speed_rpm", task_name))
	{
		return ENGINE_SPEED_RPM;
	}
	else if (!std::strcmp("engine_coolant_temp", task_name))
	{
		return ENGINE_COOLANT_TEMP;
	}
	else if (!std::strcmp("current_gear", task_name))
	{
		return CURRENT_GEAR;
	}
	// else if (!std::strcmp("transmission_oil_temp", task_name))
	// {
	// 	return TRANSMISSION_OIL_TEMP;
	// }
	else if (!std::strcmp("vehicle_speed", task_name))
	{
		return VEHICLE_SPEED;
	}
	else if (!std::strcmp("acceleration_speed_longitudinal", task_name))
	{
		return ACCELERATION_SPEED_LONGITUDINAL;
	}
	else if (!std::strcmp("indication_break_switch", task_name))
	{
		return INDICATION_BREAK_SWITCH;
	}
}

// /* Provides the value for the task identified by the parameter */
// std::string read_next_value(int task_name, std::string time_now_ms)
// {
// 	std::string next_value;
// 	//producer_buffer.fuel_consumption = next_value;
// 	std::string time = time_now_ms;
// 	std::ifstream input_from_file("data.csv");
// 	std::string line;
// 	while (getline(input_from_file, line))
// 	{
// 		line += ",";
// 		std::stringstream ss(line);
// 		std::string word;
// 		std::vector<std::string> words;
// 		while (getline(ss, word, ','))
// 		{
// 			words.push_back(word);
// 		}
// 		while (1)
// 		{
// 			if (words[7] == time)
// 			{
// 				printf("In the fct: %s\n", words[task_name].c_str());
// 				next_value = words[task_name];
// 				break;
// 			}
// 			else
// 			{
// 				break;
// 			}
// 		}
// 	}

// 	if (input_from_file.is_open())
// 	{
// 		input_from_file.close();
// 	}

// 	return next_value;
// }

float read_next_value(char *task_name, unsigned timer_storage)
{
	int time_at = timer_storage / 1000;
	time_at -= 1;
	if (time_at < 0)
	{
		time_at = 0;
	}

	if (!std::strcmp("fuel_consumption", task_name))
	{
		return fuel_consumption[time_at];
	}
	else if (!std::strcmp("engine_speed_rpm", task_name))
	{
		return engine_speed[time_at];
	}
	else if (!std::strcmp("engine_coolant_temp", task_name))
	{
		return engine_coolant_temperature[time_at];
	}
	else if (!std::strcmp("current_gear", task_name))
	{
		return current_gear[time_at];
	}
	// else if (!std::strcmp("transmission_oil_temp", task_name))
	// {
	// 	return TRANSMISSION_OIL_TEMP;
	// }
	else if (!std::strcmp("vehicle_speed", task_name))
	{
		return vehicle_speed[time_at];
	}
	else if (!std::strcmp("acceleration_speed_longitudinal", task_name))
	{
		return acceleration_speed_longitudinal[time_at];
	}
	else if (!std::strcmp("indication_break_switch", task_name))
	{
		return indication_of_brake_switch_on_off[time_at];
	}
}

int main(int argc, char *argv[])
{
	/* For tests */
	// 		// test code here
	// std::string RUN_TIME_STR;
	// float output;
	// for (int i = 0; i < 10000; i += 990)
	// {
	// 	output = read_next_value("current_gear", i);
	// 	printf("Time: %d, Found value is: %f \n", i, output);
	// }

	// return 0;

	build_periodic_tasks_list(&scheduler);
	Timer *one_ms_timer;
	std::string RUN_TIME_STR;
	unsigned long RUN_TIME;
	const int signal_type = SIGUSR1;
	signal(signal_type, timer_timeout_handler);
	pthread_mutex_init(&data_mutex, NULL);

	while (1)
	{
		printf("\n\nPlease enter the the duration you would like the real-time monitoring program to run (in seconds): ");
		std::cin >> RUN_TIME_STR;
		for (int i = 0; i < RUN_TIME_STR.size(); i++)
		{
			if (!isdigit(RUN_TIME_STR[i]))
			{
				printf("Not a digit %c\n", RUN_TIME_STR[i]);
				continue;
			}
		}
		RUN_TIME = atoi(RUN_TIME_STR.c_str()) * 1000;
		// RUN_TIME = stoul(RUN_TIME_STR.c_str(), nullptr, 10) * 1000;
		printf("\nThe program is going to run for %d seconds \n", RUN_TIME);

		Logger::create_open_log_file(file_id);

		one_ms_timer = new Timer(TIMER_1_MS_IN_NS,
								 "Task Release Timer",
								 signal_type);
		if (one_ms_timer->start() < 0)
		{
			printf("Failed to start perioidc timer - %s\n", one_ms_timer->timer_name);
			return -1;
		}

		while (timer_storage < RUN_TIME)
		{
			/* Run program */
		}
		timer_storage = 0;
		one_ms_timer->destroy();
		delete one_ms_timer;
		scheduler.cleanup();
		// pthread_mutex_destroy(&data_mutex);
		Logger::close_file(file_id);
	}
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

	Logger::log_thread_details(thread, "Details of the thread - waking up:\n");
	// -- critical section --

	while (!output_queue.empty())
	{
		printf("Updated value for \nTask Name: %s, Value: %s\n", output_queue.front().task_name, output_queue.front().value.c_str());
		output_queue.pop();
	}

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

	Logger::log_thread_details(thread, "Details of the thread - waking up:\n");
	// -- critical section --

	// int timer_s = 0;
	// std::string string_time; //time we pass to the function
	// 						 // write to producer_buffer from file
	// 						 /*take timer_s storage and take the floor */

	// //floor of timer_s storage
	// timer_s = timer_storage_ms / 1000;
	// if (timer_s < 1)
	// {
	// 	timer_s = 1;
	// }
	// std::stringstream ss;
	// ss << timer_s;
	// string_time = ss.str();

	//	std::string value;

	//	value = read_next_value(producer_string_to_enum_converter(task_name), string_time);

	float new_value = read_next_value(task_name, timer_storage_ms);
	std::stringstream string_builder;
	string_builder << new_value;
	Output o = Output(task_name, string_builder.str());
	output_queue.push(o);

	printf("New Output pushed to output queue is: \nTask Name: %s, Value: %s\n", o.task_name, o.value.c_str());

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
	// p = PeriodicTask(5000,
	// 				 PRODUCER_EXECUTION_TIME,
	// 				 "transmission_oil_temp",
	// 				 producer);
	// scheduler->add_periodic_task(p);
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
	printf("\n\n\n=======================================================================================\n", timer_storage_ms);
	printf("================================== At time t = : %u  ==================================\n", timer_storage_ms);
	printf("=======================================================================================\n", timer_storage_ms);

	char buffer[200];
	int string_size = sprintf(buffer, "\n\nAt time t = : %u\n", timer_storage);
	Logger::write_to_file(file_id, buffer, string_size);

	/* Release Periodic Tasks */
	scheduler.release_periodic_tasks(timer_storage_ms);

	// /* Update Priority */
	scheduler.update_periodic_priority();

	// /* Update Executed Time */
	scheduler.update_periodic_executed_time(timer_storage_ms);

	// /* Run Tasks */
	scheduler.run_tasks();

	/* Increment Timer Value */
	atomic_add(&timer_storage_ms, TIMER_1_MS_IN_NS / ONE_MILLION);
}

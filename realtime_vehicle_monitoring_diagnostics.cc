#include <unistd.h>
char *getcwd(char *buf, size_t size);
#include <fstream>
#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <string>
using namespace std;
#include <iostream>

enum Task_Name
{
	fuel_consumption,
	engine_speed_rpm,
	engine_coolant_temp,
	current_gear,
	transmission_oil_temp,
	vehicle_speed,
	acceleration_speed_longitudinal,
	indication_break_switch
}

/* Provides the value for the task identified by the parameter */
int
read_next_value(Task_Name task_name, unsigned time_now_ms)
{
	int next_value;
	return next_value;

	//eg.
	/* 
	Last time @t=0;
	Next time this should return the value for the task at @t=1
	 */
}

int main()
{

	int counter = 0;
	std::ifstream file("data.csv");
	if (file.is_open())
	{
		std::string line;
		while (std::getline(file, line))
		{
			if (counter > 5)
			{
				return 0;
			}
			// using printf() in all tests for consistency
			printf("%s", line.c_str());
			counter++;
		}
		file.close();
	}

	return 0;
}

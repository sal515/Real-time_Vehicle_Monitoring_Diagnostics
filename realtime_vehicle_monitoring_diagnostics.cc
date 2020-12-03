#include <unistd.h>
char *getcwd(char *buf, size_t size);
#include <fstream>
#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <string>
using namespace std;
#include <iostream>

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
	int fuel_consumption;
	int engine_speed_rpm;
	int engine_coolant_temp;
	int current_gear;
	int transmission_oil_temp;
	int vehicle_speed;
	int acceleration_speed_longitudinal;
	int indication_break_switch;
};

PRODUCER_VALUES producer_buffer;

/* Provides the value for the task identified by the parameter */
int read_next_value(int task_name, unsigned int time_now_ms)
{
	int next_value = 0;
	producer_buffer.fuel_consumption = next_value;
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
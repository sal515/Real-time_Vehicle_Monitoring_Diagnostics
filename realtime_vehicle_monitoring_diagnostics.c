#include <stdlib.h>
#include <stdio.h>
//#include <iostream>

#include "csv_data.hpp"

int main(int argc, char *argv[])
{
	//	printf("Welcomsdfsdafsadfe  thexzs354165414623adfsda QNX  IDEEEE\n");

	if (!(sizeof(fuel_consumption) == sizeof(engine_speed) &&
		  sizeof(engine_speed) == sizeof(engine_coolant_temperature) &&
		  sizeof(engine_coolant_temperature) == sizeof(current_gear) &&
		  sizeof(current_gear) == sizeof(vehicle_speed) &&
		  sizeof(vehicle_speed) == sizeof(acceleration_speed_longitudinal) &&
		  sizeof(acceleration_speed_longitudinal) == sizeof(indication_of_brake_switch_on_off)))
	{
		printf("Sizes do not match");
	}

	 int i = 0;
	 for(i = 0; i < 5; i++){
	 	printf("Fuel consumption value is: %4.2f\n", fuel_consumption[i]);
	 }

	return EXIT_SUCCESS;
}

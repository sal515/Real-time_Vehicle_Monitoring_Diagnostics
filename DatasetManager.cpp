/*
 * DatasetManager.cpp
 *
 *  Created on: Nov 14, 2020
 *      Author: Salman
 */

#include "DatasetManager.h"
#include <iostream>

namespace realtime_vehicle_monitoring_diagnostics
{

	DatasetManager::DatasetManager()
	{
		std::cout << "DatasetManager object created" << std::endl;
	}

	DatasetManager::~DatasetManager()
	{
		std::cout << "DatasetManager object destroyed" << std::endl;
	}

} // namespace realtime_vehicle_monitoring_diagnostics

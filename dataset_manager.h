/*
 * Dataset_Manager.h
 *
 *  Created on: Nov 14, 2020
 *      Author: Salman
 */

#ifndef DATASET_MANAGER_H_
#define DATASET_MANAGER_H_

namespace realtime_vehicle_monitoring_diagnostics
{

	class Dataset_Manager
	{
	public:
		Dataset_Manager();
		virtual ~Dataset_Manager();

		int extract_dataset();
		int validate_dataset();
		long get_new_data(long currentTimer);
	};

} // namespace realtime_vehicle_monitoring_diagnostics

#endif /* DATASET_MANAGER_H_ */

#include <unistd.h>
char *getcwd(char *buf, size_t size);
#include <fstream>
#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <string>
using namespace std;
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

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
	string fuel_consumption;
	string engine_speed_rpm;
	string engine_coolant_temp;
	string current_gear;
	string transmission_oil_temp;
	string vehicle_speed;
	string acceleration_speed_longitudinal;
	string indication_break_switch;
};

PRODUCER_VALUES producer_buffer;

/* Provides the value for the task identified by the parameter */
string read_next_value(int task_name, string time_now_ms)
{
	string next_value;
	//producer_buffer.fuel_consumption = next_value;
	string time = time_now_ms;
	ifstream input_from_file("data.csv");
	    string line;
	    //row x =time
	    while (getline(input_from_file, line)) {
	        line += ",";
	        stringstream ss(line);
	        string word;

	        //new vector each iteration
	        vector<string> words;

	     //column of row x (time)
	        while (getline(ss, word, ',')){

                //cout<<"word is: "<<word<<endl;
                words.push_back(word);
	        }
                while(1){
                	        	if(words[7]==time){
                                cout<<"In the fct: "<<words[task_name]<<endl;
                                next_value = words[task_name];
                               // words.push_back(word);
                                break;}else{break;}


                }
/*
	        pour le begin = 0 to end = 1000 ms
	        time == end / 1000 in seconds

	       for (time/period_of_variable)
	    	   oil temp = 268.8



	        temps est ce qui est representer dans le file
	        next period : begin=begin+1000; end=end+1000;

	        //cout<<"new row coming up"<<endl;
	       // cout<<"word[5] : "<<words[5]<<endl;
	        //

*/
	           // while (getline(ss, word, ','))
	             //              cout<<"word is: "<<word<<endl;
	           	     //       words.push_back(word);

	    }

	     return next_value;

	//eg.
	/*
	Last time @t=0;
	Next time this should return the value for the task at @t=1
	 */
}

int main()
{

//	int output = read_next_value(FUEL_CONSUMPTION, 2005);
//	printf("%d", output);
/*
	int counter = 0;
	std::ifstream file("data.csv");
	if (file.is_open())
	{
		std::string line;
		while (std::getline(file, line))
		{
			if (counter > 6)
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
*/
string time = "5";

	    producer_buffer.engine_speed_rpm = read_next_value(ENGINE_SPEED_RPM, time);

	    cout<<"in main: "<<producer_buffer.engine_speed_rpm<<endl;

	    return 0;
	}

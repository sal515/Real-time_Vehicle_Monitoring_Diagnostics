#include <unistd.h>
char *getcwd(char *buf, size_t size);
#include <fstream>
#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <string>
using namespace std;
#include <iostream>

int main() {

  int counter=0;
	std::ifstream file("data.csv");
	if (file.is_open()) {
	    std::string line;
	    while (std::getline(file, line)) {
	    	if (counter > 5)
	    	{return 0; }
	        // using printf() in all tests for consistency
	        printf("%s", line.c_str());
	        counter ++;
	    }
	    file.close();
	}


return 0;
}

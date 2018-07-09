#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <time.h>
#include <sys/time.h>
#include <iostream>
#include <string>
#include <unistd.h>
#include "jetsonGPIO.h"
using namespace std;

int gpioGetValue01 ( jetsonGPIO gpio, unsigned int *value);


int main()
{
	 jetsonTX1GPIONumber pir = gpio38;
	 
	 gpioExport(pir);
	 gpioSetDirection(pir,inputPin);
	 
	 unsigned int value = low;
	 
	 while(1)
	 {
		 //gpioGetValue(pir, &value);
		 //if(value==high)
		 if(gpioGetValue(pir, &value))
		 {
			 cout << "detected" << value << endl;
		 }
		 else
		 {
			 cout << "not" << value<< endl;
		 }
		 usleep(1000); // sleep for a millisecond
	 }
	 gpioUnexport(pir);     // unexport the LED
	 
	 return 0;
}

/*
//
// gpioGetValue
// Get the value of the requested GPIO pin ; value return is 0 or 1
// Return: Success = 0 ; otherwise open file error
int gpioGetValue01 ( jetsonGPIO gpio, unsigned int *value)
{
    int fileDescriptor;
    char commandBuffer[MAX_BUF];
    char ch;

    snprintf(commandBuffer, sizeof(commandBuffer), SYSFS_GPIO_DIR "/gpio%d/value", gpio);

    fileDescriptor = open(commandBuffer, O_RDONLY);
    if (fileDescriptor < 0) {
        char errorBuffer[128] ;
        snprintf(errorBuffer,sizeof(errorBuffer), "gpioGetValue unable to open gpio%d",gpio) ;
        perror(errorBuffer);
        return fileDescriptor;
    }

    if (read(fileDescriptor, &ch, 1) != 1) {
        perror("gpioGetValue") ;
        return fileDescriptor ;
     }

    if (ch != '0') {
        *value = 1;
    } else {
        *value = 0;
    }

    close(fileDescriptor);
    return 0;
}*/

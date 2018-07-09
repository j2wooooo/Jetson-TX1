/// simpleHCSR04.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <time.h>
#include <sys/time.h>
#include <iostream>
#include <unistd.h>
#include <jetsonGPIO.h>
#include <hcsr04.h>

using namespace std;

int main(int argc, char *argv[]){

    // Use gpio165 as trigger, gpio166 as echo
    HCSR04 *hcsr04 = new HCSR04();
    // Make the HC-SR04 available in user space
    hcsr04->exportGPIO() ;
    // Then set the direction of the pins
    hcsr04->setDirection() ;
    
    while(1){
        // unsigned int duration = ping() ;
        // unsigned int duration = ping_median(5) ;
        unsigned int duration = hcsr04->pingMedian(5) ;
        if (duration == NO_ECHO) {
          cout << "No echo" << endl ;
        } else {
            // print out distance in inches and centimeters
            cout << "Duration: " << duration << " Distance (in): " << duration/148 << " Distance (cm): " << duration/58.0 << endl ;
        }
        usleep(10000); // sleep 10 milliseconds
    }
    cout << "HC-SR04 example finished." << endl;
    hcsr04->unexportGPIO() ;
    return 0;
}

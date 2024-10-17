// first compile
// g++ -std=c++11 -o SAR_TEST SAR_TEST.cpp -lwiringPi
#include <wiringPi.h>
#include <iostream>
#include <bitset>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

// GPIO Pin Setup
const int sar_pins[4] = {26, 27, 28, 29}; // SAR OUTPUT

void setupGPIO() {
    wiringPiSetup();  // Initialize wiringPi

    // Set SAR pins as input
    for (int i = 0; i < 4 ; ++i) {
        pinMode(sar_pins[i], INPUT);
    }
}

int readSAR() {
    int sar_value = 0;

    // Read the 4-bit SAR value
    for (int i = 0; i < 4; ++i) {
        sar_value |= digitalRead(sar_pins[i]) << i;
    }

    return sar_value;
}

int main() {
    setupGPIO();
    while (true) {
        // Read the 4-bit SAR value
        int sar_value = readSAR();
        double scaled_out = double(sar_value) * (5.0/16.0);
        std::cout << "SAR Value: " << scaled_out << "V" << std::endl;
        usleep(100);
    }
    return 0;
}

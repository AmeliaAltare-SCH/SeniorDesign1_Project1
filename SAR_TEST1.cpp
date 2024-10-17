// First compile
// g++ -std=c++11 -o SAR_TEST1 SAR_TEST1.cpp -lwiringPi
#include <wiringPi.h>
#include <iostream>
#include <bitset>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

// GPIO Pin Setup
const int sar_pins[4] = {21, 22, 23, 24}; // GPIO pins connected to your 4-bit SAR output
const int start_pin = 1;              // Pin to trigger start of conversion
const int end_pin = 4;                // Pin to signal end of conversion

void setupGPIO() {
    wiringPiSetup();  // Initialize wiringPi

    // Set SAR pins as input
    for (int i = 0; i < 4; ++i) {
        pinMode(sar_pins[i], INPUT);
    }

    // Set control pins
    pinMode(start_pin, OUTPUT);
    pinMode(end_pin, INPUT);
}

int readSAR() {
    int sar_value = 0;

    // Read the 4-bit SAR value in reverse order (if needed based on wiring)
    for (int i = 0; i < 4; ++i) {
        sar_value |= digitalRead(sar_pins[i]) << i;
    }

    return sar_value;
}

int main() {
    setupGPIO();

    while (true) {
        // Trigger start of conversion
        digitalWrite(start_pin, HIGH);  // Start signal high
        delay(1);                       // Wait briefly
        digitalWrite(start_pin, LOW);   // Start signal low

        // Wait for SAR to finish conversion
        while (!digitalRead(end_pin)) {
            // Polling for end signal
            delay(1);
        }

        // Read the 4-bit SAR value when conversion is complete
        int sar_value = readSAR();
        std::cout << "SAR Value: " << std::bitset<4>(sar_value) << std::endl;

        usleep(100000);  // Short delay before next conversion (100 ms)
    }

    return 0;
}

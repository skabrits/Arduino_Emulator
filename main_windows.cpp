#include <iostream>
#include <thread>
#include "constants_and_types.cpp"
#include "serial_windows.cpp"
#include "the_random.cpp"
#include "the_string.cpp"

void setup() {
    Serial.begin(9600);
}

void loop() {
    if(Serial.available()) {
        byte a = Serial.read();
        Serial.write(a);
    }
}

void irq()
{
    Serial._rx_complete_irq();
}

int main() {
    std::thread th1(irq);
    setup();
    for (;;) {
        loop();
    }
    return 0;
}

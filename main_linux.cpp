#include <iostream>
#include "constants_and_types.cpp"
#include "serial_linux.cpp"
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
    setup();
    for (;;) {
        irq();
        loop();
    }
    return 0;
}

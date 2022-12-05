#include <iostream>
#include <thread>
#include <fstream>
#include <fcntl.h>
#include <chrono>
#include "../constants_and_types.cpp"
#include "../serial_windows.cpp"
#include "../the_random.cpp"
#include "../the_string.cpp"

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

    std::ifstream in("in_a.txt");
    std::cin.rdbuf(in.rdbuf());

    std::ofstream out("out_a.txt");
    std::streambuf *coutbuf = std::cout.rdbuf();
    std::cout.rdbuf(out.rdbuf());

    std::thread th1(irq);
    setup();
    for (int i = 0; i < 100; i++) {
        loop();
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    pthread_cancel( th1.native_handle() );
    th1.join();
    in.close();
    out.close();

    std::ifstream myfile;
    myfile.open("out_a.txt");

    std::string output;

    std::getline(myfile, output);

    myfile.close();

    std::cout.rdbuf(coutbuf);

    std::cout << output << " vs Hello world!" << std::endl;

    if(output == "Hello world!"){
        return 0;
    } else if (output == "Hello"){
        return -1;
    }

    return 1;
}

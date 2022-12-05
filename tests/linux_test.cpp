#include <iostream>
#include <fstream>
#include "../constants_and_types.cpp"
#include "../serial_linux.cpp"
#include "../the_random.cpp"
#include "../the_string.cpp"

void setup() {
//    Serial.begin(9600);
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

    setup();
    for (int i = 0; i < 1000; i++) {
        irq();
        loop();
    }

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

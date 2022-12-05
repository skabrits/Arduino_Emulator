//
// Created by sevak on 12/3/2022.
//

#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include "constants_and_types.cpp"

class SerialExample{
public:

    void _rx_complete_irq()
    {
        if (!isRunning) {
            return;
        }
        fd_set fds;
        struct timeval timeout;
        int selectRetVal;

        /* Set time limit you want to WAIT for the fdescriptor to have data,
           or not( you can set it to ZERO if you want) */
        timeout.tv_sec = 1;
        timeout.tv_usec = 10;

        /* Create a descriptor set containing our remote socket
           (the one that connects with the remote troll at the client side).  */
        FD_ZERO(&fds);
        FD_SET(0, &fds);

        selectRetVal = select(sizeof(fds)*8, &fds, NULL, NULL, &timeout);
        std::cout << selectRetVal << " a var" << std::endl;
        while (!std::cin.eof() && selectRetVal != 0 && selectRetVal != -1){
            char c;
            std::cin.get(c);
            byte i = (unsigned int)(_rx_buffer_head + 1) % SERIAL_RX_BUFFER_SIZE;

            // if we should be storing the received character into the location
            // just before the tail (meaning that the head would advance to the
            // current location of the tail), we're about to overflow the buffer,
            // and so we don't write the character or advance the head.
            if (i != _rx_buffer_tail) {
                _rx_buffer[_rx_buffer_head] = c;
                _rx_buffer_head = i;
            } else {
                break;
            }
            if (c == '\n'){
                break;
            }
        }
    }

    void begin(int baudrate){
        isRunning = true;
    }

    void end(){
        isRunning = false;
    }

    int available()
    {
        return ((unsigned int)(SERIAL_RX_BUFFER_SIZE + _rx_buffer_head - _rx_buffer_tail)) % SERIAL_RX_BUFFER_SIZE;
    }

    int peek()
    {
        if (_rx_buffer_head == _rx_buffer_tail) {
            return -1;
        } else {
            return _rx_buffer[_rx_buffer_tail];
        }
    }

    int read()
    {
        // if the head isn't ahead of the tail, we don't have any characters
        if (_rx_buffer_head == _rx_buffer_tail) {
            return -1;
        } else {
            unsigned char c = _rx_buffer[_rx_buffer_tail];
            _rx_buffer_tail = (byte)(_rx_buffer_tail + 1) % SERIAL_RX_BUFFER_SIZE;
            return c;
        }
    }

    int availableForWrite()
    {
        return 64;
    }

    void flush(){}

    size_t write(uint8_t c)
    {
        if (!isRunning) {
            return 0;
        }
        std::cout << c;
        return 1;
    }

    inline size_t write(unsigned long n) { return write((uint8_t)n); }
    inline size_t write(long n) { return write((uint8_t)n); }
    inline size_t write(unsigned int n) { return write((uint8_t)n); }
    inline size_t write(int n) { return write((uint8_t)n); }

//    size_t Print::print(const char str[])
//    {
//      return write(str);
//    }
//
//    size_t Print::print(char c)
//    {
//      return write(c);
//    }
//
//    size_t Print::print(unsigned char b, int base)
//    {
//      return print((unsigned long) b, base);
//    }
//
//    size_t Print::print(int n, int base)
//    {
//      return print((long) n, base);
//    }
//
//    size_t Print::print(unsigned int n, int base)
//    {
//      return print((unsigned long) n, base);
//    }
//
//    size_t Print::print(long n, int base)
//    {
//      if (base == 0) {
//        return write(n);
//      } else if (base == 10) {
//        if (n < 0) {
//          int t = print('-');
//          n = -n;
//          return printNumber(n, 10) + t;
//        }
//        return printNumber(n, 10);
//      } else {
//        return printNumber(n, base);
//      }
//    }
//
//    size_t Print::print(unsigned long n, int base)
//    {
//      if (base == 0) return write(n);
//      else return printNumber(n, base);
//    }
//
//    size_t Print::print(double n, int digits)
//    {
//      return printFloat(n, digits);
//    }
//
//    size_t Print::println(const __FlashStringHelper *ifsh)
//    {
//      size_t n = print(ifsh);
//      n += println();
//      return n;
//    }
//
//    size_t Print::print(const Printable& x)
//    {
//      return x.printTo(*this);
//    }
//
//    size_t Print::println(void)
//    {
//      return write("\r\n");
//    }
//
//    size_t Print::println(const String &s)
//    {
//      size_t n = print(s);
//      n += println();
//      return n;
//    }
//
//    size_t Print::println(const char c[])
//    {
//      size_t n = print(c);
//      n += println();
//      return n;
//    }
//
//    size_t Print::println(char c)
//    {
//      size_t n = print(c);
//      n += println();
//      return n;
//    }
//
//    size_t Print::println(unsigned char b, int base)
//    {
//      size_t n = print(b, base);
//      n += println();
//      return n;
//    }
//
//    size_t Print::println(int num, int base)
//    {
//      size_t n = print(num, base);
//      n += println();
//      return n;
//    }
//
//    size_t Print::println(unsigned int num, int base)
//    {
//      size_t n = print(num, base);
//      n += println();
//      return n;
//    }
//
//    size_t Print::println(long num, int base)
//    {
//      size_t n = print(num, base);
//      n += println();
//      return n;
//    }
//
//    size_t Print::println(unsigned long num, int base)
//    {
//      size_t n = print(num, base);
//      n += println();
//      return n;
//    }
//
//    size_t Print::println(double num, int digits)
//    {
//      size_t n = print(num, digits);
//      n += println();
//      return n;
//    }

private:

    static const byte SERIAL_RX_BUFFER_SIZE=64;

    bool isRunning = false;

    byte _rx_buffer_head=0;
    byte _rx_buffer_tail=0;

    byte _rx_buffer[SERIAL_RX_BUFFER_SIZE];

};

SerialExample Serial;
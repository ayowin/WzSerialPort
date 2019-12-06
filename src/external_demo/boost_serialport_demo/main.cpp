
#include <iostream>
#include <stdio.h>

#include <thread>
#include <chrono>

#include <boost/asio.hpp>

#include <boost/bind.hpp>

void sendThreadRun(boost::asio::serial_port *serialPort)
{
    char sendBuffer[128];
    int testCount = 0;

    boost::system::error_code errorCode;

    while(true)
    {
        memset(sendBuffer,0,sizeof(sendBuffer));

        testCount++;
        sprintf(sendBuffer,"serialport send test , test count %d\n",testCount);

        printf("%s\n",sendBuffer);

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        
        serialPort->write_some(boost::asio::buffer(sendBuffer,sizeof(sendBuffer)));
    }
}

void receiveThreadRun(boost::asio::serial_port *serialPort)
{
    char receiveBuffer[1024];
    int readCount = 0;

    while(true)
    {
        memset(receiveBuffer,0,sizeof(receiveBuffer));

        readCount = serialPort->read_some(boost::asio::buffer(receiveBuffer,sizeof(receiveBuffer)));
        if(readCount)
        {
            printf("[received] %s\n",receiveBuffer);
            readCount = 0;
        }
    }
}

int main(int argc, char **argv)
{
    printf("============boost serialport demo===============\n");

    boost::asio::io_service ioService;
    boost::asio::serial_port serialPort(ioService, "/dev/ttyS1");

    serialPort.set_option(boost::asio::serial_port::baud_rate(9600));
    serialPort.set_option(boost::asio::serial_port::flow_control(boost::asio::serial_port::flow_control::none));
    serialPort.set_option(boost::asio::serial_port::parity(boost::asio::serial_port::parity::none));
    serialPort.set_option(boost::asio::serial_port::stop_bits(boost::asio::serial_port::stop_bits::one));
    serialPort.set_option(boost::asio::serial_port::character_size(8));

    std::thread sendThread(sendThreadRun,&serialPort);

    std::thread receiveThread(receiveThreadRun,&serialPort);
    
    sendThread.join();
    receiveThread.join();

    return 0;
}

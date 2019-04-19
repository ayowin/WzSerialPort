
#include <iostream>
#include "WzSerialPort.h"

using namespace std;

void sendDemo()
{
	WzSerialPort w;
	if (w.open("COM1", 9600, 0, 8, 1))
	{
		for (int i = 0;i < 10;i++)
		{
			w.send("helloworld", 10);
		}
		cout << "send demo finished...";
	}
	else
	{
		cout << "open serial port failed...";
	}
}

void receiveDemo()
{
	WzSerialPort w;
	if (w.open("COM1", 9600, 0, 8, 1))
	{
		char buf[1024];
		while (true)
		{
			memset(buf, 0,1024);
			w.receive(buf, 1024);
			cout << buf;
		}
	}
}

int main(int argumentCount, const char* argumentValues[]) 
{
	// 假设COM1已经和另外一个串口连接好了

	// 发送 demo
	sendDemo();

	// 接收 demo
	//receiveDemo();

	getchar();
	return 0;
}
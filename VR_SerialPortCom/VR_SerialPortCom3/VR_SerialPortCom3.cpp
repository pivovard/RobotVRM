#include "SerialPort.h"
#include <iostream>

#define DATA_LENGTH 255

char* portName = (char*)("\\\\.\\COM13");
std::string port = "\\\\.\\COM13";

//Declare a global object
SerialPort* arduino;

int main(void)
{
	arduino = new SerialPort(portName);
	std::cout << "is connected: " << arduino->isConnected() << std::endl;


	char* sendString = "Hello World\n";

	bool hasWritten = arduino->writeSerialPort(sendString, DATA_LENGTH);
	if (hasWritten) std::cout << "Data Written Successfully" << std::endl;
	else std::cout << "Data was not written" << std::endl;
}
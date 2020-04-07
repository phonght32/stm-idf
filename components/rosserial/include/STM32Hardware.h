#ifndef _STM32HARDWARE_H_
#define _STM32HARDWARE_H_

#include "SerialClass.h"

class STM32Hardware
{
public:
	STM32Hardware() :
			com(&serial)
	{

	}

	void init()
	{
		com->init();
	}

	int read()
	{
		return com->read();
	}

	void write(uint8_t* data, int length)
	{
		com->write(data, length);
	}

	unsigned long time()
	{
		return HAL_GetTick();
	}

protected:
	SerialClass* com;
	//long baud_;
};

#endif


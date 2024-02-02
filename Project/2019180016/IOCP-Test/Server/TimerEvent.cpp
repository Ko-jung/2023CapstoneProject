#include "TimerEvent.h"

#include "iostream"

void NullEvent::NullFunction()
{
	std::cout << "Null Event has Called!" << std::endl;
}

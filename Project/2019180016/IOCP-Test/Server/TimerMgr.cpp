#include "TimerMgr.h"
#include "TimerEvent.h"

// PPL 라이브러리
//#include <concurrent_unordered_map.h>

TimerMgr::TimerMgr()
{
	m_TimerQueue = new Concurrency::concurrent_priority_queue<TimerEvent*>();
}

TimerMgr::~TimerMgr()
{
	TimerEvent* temp = nullptr;
	while (!m_TimerQueue->empty())
	{
		while (m_TimerQueue->try_pop(temp))
		{
			delete temp;
		}
	}
	delete m_TimerQueue;
}

TimerEvent* TimerMgr::Pop()
{
	TimerEvent* evnet;
	if (m_TimerQueue->try_pop(evnet))
	{
		return evnet;
	}
	else
	{
		return new NullEvent(std::chrono::system_clock::now(), NullEvent::NullFunction);
	}
}

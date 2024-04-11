#include "TimerMgr.h"
#include "../TimerEvent.h"

#include <thread>

// PPL ���̺귯��
//#include <concurrent_unordered_map.h>

TimerMgr::TimerMgr()
{
	m_TimerQueue = new Concurrency::concurrent_priority_queue<TimerEvent>();
}

TimerMgr::~TimerMgr()
{
	//TimerEvent* temp = nullptr;
	//while (!m_TimerQueue->empty())
	//{
	//	while (m_TimerQueue->try_pop(temp))
	//	{
	//		delete temp;
	//	}
	//}
	delete m_TimerQueue;
}

void TimerMgr::Pop()
{
	TimerEvent Event;
	auto now = std::chrono::system_clock::now();
	while (m_TimerQueue->try_pop(Event))
	{
		// Do Bind Func
		if (Event.GetActiveTime() <= std::chrono::system_clock::now())
		{
			Event.DoFuction(0, 0, nullptr);
		}
		else
		{
			// Re Push
			m_TimerQueue->push(Event);
			std::this_thread::yield();
			return;
		}
	}
	std::this_thread::yield();
}

void TimerMgr::Insert(TimerEvent TE)
{
	//TODO: TimerEvent 포인터가 아니기 때문에 매우 위험함 (현재 DefaultEvent까지는 괜찮음)
	m_TimerQueue->push(TE);
}

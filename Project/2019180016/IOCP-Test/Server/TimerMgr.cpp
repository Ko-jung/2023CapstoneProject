#include "TimerMgr.h"
#include "TimerEvent.h"

// PPL 라이브러리
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
		// 발동 시간을 넘겼는지
		if (Event.GetActiveTime() <= std::chrono::system_clock::now())
		{
			Event.DoFuction()();
		}
		else
		{
			// 안 넘겼다면 다시 큐에 담기
			m_TimerQueue->push(Event);
			return;
		}
	}
}

void TimerMgr::Insert(TimerEvent TE)
{
	m_TimerQueue->push(TE);
}

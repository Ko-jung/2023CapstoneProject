#include "TimerMgr.h"
#include "TimerEvent.h"

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
		// �ߵ� �ð��� �Ѱ����
		if (Event.GetActiveTime() <= std::chrono::system_clock::now())
		{
			Event.DoFuction()();
		}
		else
		{
			// �� �Ѱ�ٸ� �ٽ� ť�� ���
			m_TimerQueue->push(Event);
			std::this_thread::yield();
			return;
		}
	}
}

void TimerMgr::Insert(TimerEvent TE)
{
	m_TimerQueue->push(TE);
}

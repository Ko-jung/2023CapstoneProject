#pragma once

#include <concurrent_priority_queue.h>
#include <functional>

class TimerEvent;

// 타이머 매니저, 방 당 하나씩 보유할 예정
class TimerMgr
{
public:
	TimerMgr();
	virtual ~TimerMgr();

public:
	TimerEvent* Pop();

protected:
	// Pop해야하는 시간, Pop시 작동해야할 함수 pair를 담는 큐
	Concurrency::concurrent_priority_queue<TimerEvent*>* m_TimerQueue;
};


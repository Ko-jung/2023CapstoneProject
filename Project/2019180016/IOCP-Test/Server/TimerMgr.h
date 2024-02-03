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
	void Pop();
	void Insert(TimerEvent* TE);

	Concurrency::concurrent_priority_queue<TimerEvent*>* m_TimerQueue;
protected:
};


#pragma once

#include <concurrent_priority_queue.h>
#include <functional>

#include "TimerEvent.h"

// Ÿ�̸� �Ŵ���, �� �� �ϳ��� ������ ����
class TimerMgr
{
public:
	TimerMgr();
	virtual ~TimerMgr();

public:
	void Pop();
	void Insert(TimerEvent TE);

	Concurrency::concurrent_priority_queue<TimerEvent>* m_TimerQueue;
protected:
};


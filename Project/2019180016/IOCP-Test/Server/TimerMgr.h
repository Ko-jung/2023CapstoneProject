#pragma once

#include <concurrent_priority_queue.h>
#include <functional>

class TimerEvent;

// Ÿ�̸� �Ŵ���, �� �� �ϳ��� ������ ����
class TimerMgr
{
public:
	TimerMgr();
	virtual ~TimerMgr();

public:
	TimerEvent* Pop();

protected:
	// Pop�ؾ��ϴ� �ð�, Pop�� �۵��ؾ��� �Լ� pair�� ��� ť
	Concurrency::concurrent_priority_queue<TimerEvent*>* m_TimerQueue;
};


#pragma once

#include <concurrent_priority_queue.h>
#include <functional>

#include "../TimerEvent.h"
#include "../../Common/Define.h"

// Ÿ�̸� �Ŵ���, �� �� �ϳ��� ������ ����
class TimerMgr
{
	//static TimerMgr* Instance()
	//{
	//	static TimerMgr inst;
	//	return &inst;
	//}
	SingleTon(TimerMgr)

public:
	TimerMgr();
	virtual ~TimerMgr();

public:
	void Pop();
	void Insert(TimerEvent TE);

protected:
	Concurrency::concurrent_priority_queue<TimerEvent>* m_TimerQueue;
};


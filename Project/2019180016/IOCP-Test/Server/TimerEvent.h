#pragma once

#include <functional>

#include <chrono>

class TimerEvent
{
public:
	TimerEvent(std::chrono::system_clock::time_point ActiveTime, std::function<void()> Func)
		: m_fActiveTime(ActiveTime), m_Fuction(Func)
	{}
	TimerEvent(std::chrono::system_clock::time_point NowTime, float AboveTime, std::function<void()> Func)
		: m_Fuction(Func)
	{ m_fActiveTime = NowTime + AboveTime; }

	virtual ~TimerEvent() {}

protected:
	// ���Ǿ���� �ð�
	std::chrono::system_clock::time_point m_fActiveTime;

	std::function<void()> m_Fuction;
};

// �� ������Ʈ ����
class NullEvent : public TimerEvent
{
public:
	NullEvent(std::chrono::system_clock::time_point ActiveTime, std::function<void()> Func)
		: TimerEvent(ActiveTime, Func)
	{}
	NullEvent(std::chrono::system_clock::time_point NowTime, float AboveTime, std::function<void()> Func)
		: TimerEvent(NowTime, AboveTime, Func)
	{}

	void NullFunction();
};

class DefaultEvent : public TimerEvent
{
public:
	DefaultEvent(std::chrono::system_clock::time_point ActiveTime, std::function<void()> Func)
		: TimerEvent(ActiveTime, Func)
	{}
	DefaultEvent(std::chrono::system_clock::time_point NowTime, float AboveTime, std::function<void()> Func)
		: TimerEvent(NowTime, AboveTime, Func)
	{}
};
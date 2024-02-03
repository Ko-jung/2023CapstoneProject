#pragma once

#include <functional>

#include <chrono>
#include <iostream>

class TimerEvent
{
public:
	TimerEvent(std::chrono::seconds ExecutionTime,
		std::function<void()> Func)
		: m_Fuction(Func)
	{
		m_fActiveTime = std::chrono::system_clock::now() + ExecutionTime;
	}

	TimerEvent(std::chrono::system_clock::time_point NowTime,
		std::chrono::seconds AboveTimeSec,
		std::function<void()> Func)
		: m_Fuction(Func)
	{
		m_fActiveTime = NowTime + AboveTimeSec;
	}

	virtual ~TimerEvent() {}

	std::chrono::system_clock::time_point GetActiveTime() { return m_fActiveTime; }
	std::function<void()> DoFuction() { return m_Fuction; }

	//std::strong_ordering operator<=> (const TimerEvent& other) {
	//	return m_fActiveTime <=> other.m_fActiveTime;
	//}

	bool operator<(const TimerEvent& other) const
	{
		std::cout << "operator< Active" << std::endl;
		return m_fActiveTime < other.m_fActiveTime;
	}

protected:
	// 사용되어야할 시간
	std::chrono::system_clock::time_point m_fActiveTime;

	std::function<void()> m_Fuction;
};

// 널 오브젝트 패턴
class NullEvent : public TimerEvent
{
public:
	NullEvent(std::function<void()> Func)
		: TimerEvent(std::chrono::system_clock::now(), std::chrono::seconds(1), Func)
	{}
	NullEvent(std::chrono::seconds ExecutionTime,
		std::function<void()> Func)
		: TimerEvent(ExecutionTime, Func)
	{}
	NullEvent(std::chrono::system_clock::time_point NowTime, std::chrono::seconds AboveTimeSec, std::function<void()> Func)
		: TimerEvent(NowTime, AboveTimeSec, Func)
	{}

	void NullFunction();
};

class DefaultEvent : public TimerEvent
{
public:
	DefaultEvent(std::chrono::seconds ExecutionTime,
		std::function<void()> Func)
		: TimerEvent(ExecutionTime, Func)
	{}
	DefaultEvent(std::chrono::system_clock::time_point NowTime,
		std::chrono::seconds AboveTimeSec,
		std::function<void()> Func)
		: TimerEvent(NowTime, AboveTimeSec, Func)
	{}
};
#pragma once

#include <functional>

#include <chrono>
#include <iostream>

class TimerEvent
{
public:
	TimerEvent() {}

	TimerEvent(std::chrono::seconds ExecutionTime,
		std::function<void(int, int, void*)> Func)
		: m_Fuction(Func)
	{
		m_fActiveTime = std::chrono::system_clock::now() + ExecutionTime;
	}

	TimerEvent(std::chrono::system_clock::time_point NowTime,
		std::chrono::seconds AboveTimeSec,
		std::function<void(int, int, void*)> Func)
		: m_Fuction(Func)
	{
		m_fActiveTime = NowTime + AboveTimeSec;
	}

	virtual ~TimerEvent() {}

	std::chrono::system_clock::time_point GetActiveTime() { return m_fActiveTime; }
	//std::function<void()> DoFuction() { return m_Fuction; }
	void DoFuction(int RoomNum, int ClientNum, void* etc) { m_Fuction(RoomNum, ClientNum, etc); }

	bool operator<(const TimerEvent& other) const
	{
		// �������� ���� ȭ��ǥ ������ �ݴ��.
		return m_fActiveTime > other.m_fActiveTime;
	}

protected:
	// ���Ǿ���� �ð�
	std::chrono::system_clock::time_point m_fActiveTime;

	// return void, Argu is RoomNum, ClientNum, etc
	std::function<void(int, int, void*)> m_Fuction;
};

// �� ������Ʈ ����
class NullEvent : public TimerEvent
{
public:
	NullEvent(std::function<void(int, int, void*)> Func)
		: TimerEvent(std::chrono::system_clock::now(), std::chrono::seconds(1), Func)
	{}
	NullEvent(std::chrono::seconds ExecutionTime,
		std::function<void(int, int, void*)> Func)
		: TimerEvent(ExecutionTime, Func)
	{}
	NullEvent(std::chrono::system_clock::time_point NowTime, std::chrono::seconds AboveTimeSec, std::function<void(int, int, void*)> Func)
		: TimerEvent(NowTime, AboveTimeSec, Func)
	{}

	void NullFunction();
};

class DefaultEvent : public TimerEvent
{
public:
	DefaultEvent(std::chrono::seconds ExecutionTime,
		std::function<void(int, int, void*)> Func)
		: TimerEvent(ExecutionTime, Func)
	{}
	DefaultEvent(std::chrono::system_clock::time_point NowTime,
		std::chrono::seconds AboveTimeSec,
		std::function<void(int, int, void*)> Func)
		: TimerEvent(NowTime, AboveTimeSec, Func)
	{}
};
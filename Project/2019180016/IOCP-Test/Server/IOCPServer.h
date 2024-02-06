#pragma once

#include "Define.h"

class ClientInfo;

class IOCPServer
{
public:
	IOCPServer();
	virtual ~IOCPServer();

	bool Init(const int);
	bool BindListen(const int);

public:
	static void error_display(int err_no);
	void StartServer();
	void Worker();
	void ThreadJoin();
	void Timer();

	ClientInfo* GetEmptyClient();

public:
	void Accept(int id, int bytes, EXP_OVER* exp);
	void Send(int id, int bytes, EXP_OVER* exp);
	void Recv(int id, int bytes, EXP_OVER* exp);

	void RecvNewPosition(int id, int bytes, EXP_OVER* exp);

	void TestSend();
	std::thread TempSendThread;

protected:
	// IOCP¿ë ÇÚµé
	HANDLE m_hIocp;

	SOCKET m_ListenSocket;

	SOCKET m_ClientSocket;

	EXP_OVER m_AcceptExpOver;

	std::vector<std::thread> m_tWorkerThreads;
	std::thread m_tTimerThread;

	std::unordered_map < COMP_OP, std::function<void(int, int, EXP_OVER*)>> m_IocpFunctionMap;

	std::unordered_map <int, class TimerMgr*> m_TimerMgrMap;

	std::array<ClientInfo*, MAXCLIENT> m_Clients;

	int m_iWorkerNum;

	int m_iClientId;

	int m_iClientCount;

	int m_iRoomId;
};
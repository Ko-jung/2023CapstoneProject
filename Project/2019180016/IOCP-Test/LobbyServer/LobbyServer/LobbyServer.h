#pragma once

#include "../../Common/Define.h"
#include <concurrent_priority_queue.h>
#include <list>

class LobbyClientInfo;

class LobbyServer
{
public:
	LobbyServer();
	virtual ~LobbyServer() {}

	bool Init(const int);
	bool BindListen(const int);
	static void error_display(int err_no);
	void StartServer();
	void ThreadJoin();
	void Worker();


	void Accept(int id, int bytes, EXP_OVER* exp);
	void Send(int id, int bytes, EXP_OVER* exp);
	void Recv(int id, int bytes, EXP_OVER* exp);
	bool ReadyToNextAccept();

private:
	HANDLE m_hIocp;

	SOCKET m_ListenSocket;


	std::vector<std::thread> m_tWorkerThreads;
	int m_iWorkerNum;

	std::unordered_map < COMP_OP, std::function<void(int, int, EXP_OVER*)>> m_IocpFunctionMap;

	EXP_OVER m_AcceptExpOver;
};


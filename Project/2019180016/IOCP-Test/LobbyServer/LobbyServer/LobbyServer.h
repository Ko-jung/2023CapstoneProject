#pragma once

#include "../../Server/Define.h"
#include <concurrent_priority_queue.h>

class ClientInfo;

class LobbyServer
{
public:
	LobbyServer() {}
	virtual ~LobbyServer() {}

	bool Init(const int);
	bool BindListen(const int);
	static void error_display(int err_no);
	void StartServer();
	void ThreadJoin();

	void AcceptNewSocket();
	void RecvProcess();

private:
	SOCKET m_ListenSocket;

	std::array<ClientInfo*, MAXCLIENT> m_Clients;
	Concurrency::concurrent_priority_queue< ClientInfo*> m_MatchingQueue;

	std::thread m_RecvThread;
	char buf[1024];
};


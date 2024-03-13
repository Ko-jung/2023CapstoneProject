#pragma once

#include "../../Common/Define.h"
#include <concurrent_priority_queue.h>

class ClientInfo;

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

	ClientInfo* GetEmptyClient();

	void CheckingMatchingQueue();
	bool ConnectToGameServer();

	void Accept(int id, int bytes, EXP_OVER* exp);
	void Send(int id, int bytes, EXP_OVER* exp);
	void Recv(int id, int bytes, EXP_OVER* exp);

private:
	HANDLE m_hIocp;

	SOCKET m_ListenSocket;

	EXP_OVER* m_GameServerOver;
	SOCKET m_GameServerSocket;

	std::array<ClientInfo*, MAXCLIENT> m_Clients;
	Concurrency::concurrent_priority_queue< ClientInfo*> m_MatchingQueue;

	std::vector<std::thread> m_tWorkerThreads;
	int m_iWorkerNum;
	int m_iClientCount;
	int m_iClientId;

	std::unordered_map < COMP_OP, std::function<void(int, int, EXP_OVER*)>> m_IocpFunctionMap;

	EXP_OVER m_AcceptExpOver;
};


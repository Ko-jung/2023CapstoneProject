#pragma once
#include "../../../Common/Define.h"
#include "concurrent_priority_queue.h"

constexpr int GAMESERVER = 9998;

class LobbyClientInfo;

class ClientMgr
{
	SingleTon(ClientMgr)

public:
	ClientMgr();

	void Disconnect(int SerialNum);
	void Send(int id, Packet* p);
	void Recv(int id, const DWORD& bytes, EXP_OVER* exp);

	LobbyClientInfo* GetEmptyClient(int& ClientNum);
	void CheckingMatchingQueue();
	bool ConnectToGameServer(const HANDLE& hIocp);

	void ProcessRecvFromGame(int id, int bytes, EXP_OVER* exp);
	void ProcessTryLogin(LobbyClientInfo* Target, PTryLogin* PTL);
	void ProcessStartMatching(LobbyClientInfo* Target);

	std::array<LobbyClientInfo*, MAXCLIENT> Clients;
	Concurrency::concurrent_priority_queue<LobbyClientInfo*> m_MatchingQueue;

	std::atomic<int> ClientCount;

	EXP_OVER* m_GameServerOver;
	LobbyClientInfo* m_GameServerSocket;
};


#pragma once

#include "../Common/Define.h"
#include <concurrent_priority_queue.h>

class ClientInfo;
class RoomMgr;

class IOCPServer
{
public:
	IOCPServer();
	virtual ~IOCPServer();

	bool Init(const int);
	bool BindListen(const int);

public:
	void StartServer();
	void Worker();
	void ThreadJoin();
	void Timer();

	ClientInfo* GetEmptyClient();
	bool ReadyToNextAccept();
	void AccpetLobbyServer();

public:
	void Accept(int id, int bytes, EXP_OVER* exp);
	void Send(int id, int bytes, EXP_OVER* exp);
	void Recv(int id, int bytes, EXP_OVER* exp);

	void SendPlayerJoinPacket(int JoinPlayerSerial);
	void SendTileDrop(int id/*, BYTE tileDropLevel*/);

	void ProcessPlayerPosition(PPlayerPosition p);
	void ProcessDisconnectPlayer(PDisconnect p);
	//void ProcessNewPlayers(PSendPlayerSockets p);

	void TestSend();
	std::thread TempSendThread;

protected:
	// IOCP�� �ڵ�
	HANDLE m_hIocp;

	SOCKET m_ListenSocket;

	ClientInfo* m_LobbyServerSocket;
	bool IsLobbyServerConnect;

	EXP_OVER m_AcceptExpOver;

	std::vector<std::thread> m_tWorkerThreads;
	std::thread m_tTimerThread;

	std::unordered_map < COMP_OP, std::function<void(int, int, EXP_OVER*)>> m_IocpFunctionMap;

	//std::unordered_map <int, class TimerMgr*> m_TimerMgrMap;
	std::shared_ptr<class TimerMgr> m_TimerMgr;

	std::array<ClientInfo*, MAXCLIENT> m_Clients;

	Concurrency::concurrent_priority_queue<ClientInfo*> m_MatchingQueue;

	int m_iWorkerNum;

	int m_iClientId;

	int m_iClientCount;

	int m_iRoomId;
};
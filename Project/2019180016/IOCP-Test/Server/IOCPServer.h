#pragma once

#include "../Common/Define.h"
#include <concurrent_priority_queue.h>

#define LOBBYSERVER 9998

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
	//const int GetEmptyRoomNum();
	bool ReadyToNextAccept();
	void AccpetLobbyServer();

	int GetWeaponDamage(bool isMelee, int weaponEnum);

public:
	void Accept(int id, int bytes, EXP_OVER* exp);
	void Send(int id, int bytes, EXP_OVER* exp);
	void Recv(int id, int bytes, EXP_OVER* exp);

	void ProcessRecvFromLobby(int id, int bytes, EXP_OVER* exp);

	void SendPlayerJoinPacket(int JoinPlayerSerial);
	void SendTileDrop(int id/*, BYTE tileDropLevel*/);
	void SendSelectTime(int NowClientNum, float time);
	void SendPacketToAllSocketsInRoom(int roomId, Packet* p, int packetSize);
	//void SendPacketToAllSocketsInRoomAfterTimer(int roomId, COMP_OP packetType);

	void ProcessPlayerPosition(PPlayerPosition p);
	void ProcessDisconnectPlayer(PDisconnect p);
	//void ProcessNewPlayers(PSendPlayerSockets p);
	bool CheckSelectDuplication(int id, ECharacter c);

	void TestSend();
	std::thread TempSendThread;

public:
	// Timer Function
	void StartGame(int RoomNum, int ClientNum, void* etc);

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

	std::shared_ptr<class TimerMgr> m_TimerMgr;

	std::array<ClientInfo*, MAXCLIENT> m_Clients;

	//Concurrency::concurrent_priority_queue<ClientInfo*> m_ClientSocketPool;

	int m_iWorkerNum;

	std::atomic<int> m_iClientId;
	std::atomic<int> m_iClientCount;

	int m_iRoomId;
};
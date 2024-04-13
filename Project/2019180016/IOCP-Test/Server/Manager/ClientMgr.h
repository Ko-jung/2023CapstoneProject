#pragma once

#include <atomic>
#include <array>

#include "../../Common/Define.h"

class ClientInfo;

class ClientMgr
{
	SingleTon(ClientMgr)
public:
	ClientMgr();

	void Disconnect(int SerialNum);
	void SendPacketToAllSocketsInRoom(int roomId, Packet* p, int packetSize);
	void RecvProcess(int id, const DWORD& bytes, EXP_OVER* exp);
	void ProcessPlayerPosition(PPlayerPosition p);

	bool CheckSelectDuplication(int id, ECharacter c);

	ClientInfo* GetEmptyClient();
	ClientInfo* GetEmptyClient(int& clientNum);
	const int GetClientCount() { return m_iClientCount; }
	std::array<ClientInfo*, MAXCLIENT>& GetClients() { return m_Clients; }
private:
	// TODO: Atomic하게 하지 않아도 되나?
	std::array<ClientInfo*, MAXCLIENT> m_Clients;

	std::atomic<int> m_iClientId;
	std::atomic<int> m_iClientCount;
};


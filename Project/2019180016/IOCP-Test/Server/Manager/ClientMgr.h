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
	void RecvProcess(int id, const DWORD& bytes, EXP_OVER* exp);

	bool CheckSelectDuplication(int id, ECharacter c);
	bool CheckFallDie(int id, PPlayerPosition PPP);
	void ProcessMove(int id, PPlayerPosition PPP);
	void ChangeState(int id, ECharacterState state);

	void Heal(int id, float damage);

	void Send(int id, Packet* p, int size);
	void SendPacketToAllSocketsInRoom(int roomId, Packet* p, int packetSize);
	void SendPacketToAllExceptSelf(int id, Packet* p, int packetSize);

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


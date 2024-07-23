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
	void Init(int id);
	void Recv(int id, const DWORD& bytes, EXP_OVER* exp);
	void Send(int id, Packet* p, int size);

	bool CheckSelectDuplication(int id, ECharacter c);
	bool CheckFallDie(int id, PPlayerPosition PPP);
	void ProcessMove(int id, PPlayerPosition PPP);
	void ChangeState(int id, ECharacterState state);
	void ProcessItem(int id, PUseItem PUI);
	void ProcessTeamItem(int id, PUseItem PUI);
	void ProcessShieldSphereHeal(int id, PSkillInteract PSI);
	float ProcessShieldDamaged(int id, PDamagedSkillActor PDSA, float Damage);

	void Heal(int id, float damage);
	void ItemHeal(int id, EItemRareLevel level);
	void IncreaseMaxHp(int id, float IncreaseAmount, int Sec);
	void DecreaseMaxHp(int id, float DecreaseAmount);
	void ShieldSphereHeal(int id);

	void ItemPower(int id, EItemRareLevel level);
	void IncreasePower(int id, float IncreaseAmount, int Sec);
	void DecreasePower(int id, float DecreaseAmount);

	void SendPacketToAllSocketsInRoom(int roomId, Packet* p, int packetSize);
	void SendPacketToAllExceptSelf(int id, Packet* p, int packetSize);
	void SendPacketToAllience(int id, Packet* p, int packetSize);
	void SendOldPlayerList(int id);

	ClientInfo* GetEmptyClient();
	ClientInfo* GetEmptyClient(int& clientNum);
	const int GetClientCount() { return m_iClientCount; }
	std::array<ClientInfo*, MAXCLIENT>& GetClients() { return m_Clients; }
private:
	// Timer Func
	void SendItemOff(int id);

	// TODO: Atomic하게 하지 않아도 되나?
	std::array<ClientInfo*, MAXCLIENT> m_Clients;

	std::atomic<int> m_iClientId;
	std::atomic<int> m_iClientCount;
};


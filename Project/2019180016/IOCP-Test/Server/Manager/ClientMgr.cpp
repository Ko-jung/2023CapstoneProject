#include "ClientMgr.h"

#include "../ClientInfo.h"

ClientMgr::ClientMgr() : 
	m_iClientId(0),
	m_iClientCount(0)
{
	for (auto& c : m_Clients)
	{
		c = new ClientInfo();
	}
}

void ClientMgr::Disconnect(int SerialNum)
{
	m_Clients[SerialNum]->Init();
	m_iClientCount--;
}

void ClientMgr::SendPacketToAllSocketsInRoom(int roomId, Packet* p, int packetSize)
{
	for (int i = 0; i < MAXPLAYER; i++)
	{
		SOCKET s = m_Clients[roomId * MAXPLAYER + i]->GetSocket();

		if (s != INVALID_SOCKET)
		{
			m_Clients[roomId * MAXPLAYER + i]->SendProcess(packetSize, p);
		}
	}
}

void ClientMgr::RecvProcess(int id, const DWORD& bytes, EXP_OVER* exp)
{
	m_Clients[id]->RecvProcess(bytes, exp);
}

ClientInfo* ClientMgr::GetEmptyClient()
{
	auto it = std::find_if(m_Clients.begin(), m_Clients.end(), [](ClientInfo* a) {return a->GetClientNum() == -1; });
	if (it != m_Clients.end())
	{
		return *it;
	}
	else
	{
		return nullptr;
	}
}

ClientInfo* ClientMgr::GetEmptyClient(int& clientNum)
{
	for (int i = 0; i < m_Clients.size(); i++)
	{
		if (m_Clients[i]->GetClientNum() == -1)
		{
			clientNum = i;
			m_iClientCount++;
			return m_Clients[i];
		}
	}
	return nullptr;
}

void ClientMgr::SendPacketToAllExceptSelf(int id, Packet* p, int packetSize)
{
	int RoomNum = id / MAXPLAYER;
	for (int i = 0; i < MAXPLAYER; i++)
	{
		if (m_Clients[RoomNum * MAXPLAYER + i]->GetSocket() == INVALID_SOCKET
			|| RoomNum * MAXPLAYER + i == id) continue;

		m_Clients[RoomNum * MAXPLAYER + i]->SendProcess(packetSize, p);
	}
}

bool ClientMgr::CheckSelectDuplication(int id, ECharacter c)
{
	int roomNum = id / MAXPLAYER;
	int clientNum = id % MAXPLAYER;

	int temp = 6;//MAXPLAYER

	if (clientNum < temp / 2)
	{
		for (int i = 0; i < temp / 2; i++)
		{
			if (m_Clients[roomNum * temp + i]->GetECharacter() == c)
			{
				return true;
			}
		}
	}
	else
	{
		for (int i = temp / 2; i < temp; i++)
		{
			if (m_Clients[roomNum * temp + i]->GetECharacter() == c)
			{
				return true;
			}
		}
	}

	return false;
}

void ClientMgr::Heal(int id, float HealAmount)
{
	m_Clients[id]->Heal(HealAmount);
}

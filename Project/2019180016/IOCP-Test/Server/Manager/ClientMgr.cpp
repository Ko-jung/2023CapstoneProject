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
		SOCKET s = m_Clients[roomId * 6 + i]->GetSocket();

		if (s != INVALID_SOCKET)
		{
			m_Clients[roomId * 6 + i]->SendProcess(packetSize, p);
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

void ClientMgr::ProcessPlayerPosition(PPlayerPosition p)
{
	int serial = p.PlayerSerial;
	auto Client = m_Clients[serial];
	int RoomNum = Client->GetRoomNum();

	//Client->SetPos(p.x, p.y, p.z);

	for (const auto& c : m_Clients)
	{
		int CNum = c->GetClientNum();
		if (CNum != -1 && CNum != serial)
		{
			c->SendProcess(sizeof(PPlayerPosition), &p);
		}
	}
}

bool ClientMgr::CheckSelectDuplication(int id, ECharacter c)
{
	int roomNum = id / MAXPLAYER;
	int clientNum = id % MAXPLAYER;

	int temp = 6; // MAXPLAYER

	// Blue Team
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
	// Red Team
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

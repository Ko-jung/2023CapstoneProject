#include "ClientMgr.h"
#include "../LobbyClientInfo.h"

#include "DBMgr.h"

ClientMgr::ClientMgr()
{
	for (int i = 0; i < MAXCLIENT; i++)
	{
		Clients[i] = nullptr;
	}
}

void ClientMgr::Disconnect(int SerialNum)
{
	if (GameServerKeySet.find(SerialNum) == GameServerKeySet.end())
	{
		GameServerKeySet.unsafe_erase(SerialNum);
	}

	PDisconnect PD;
	Clients[SerialNum]->SendProcess(&PD);

	Clients[SerialNum]->Init();
	ClientCount--;
}

void ClientMgr::Send(int id, Packet* p)
{
	Clients[id]->SendProcess(p);
}

void ClientMgr::Recv(int id, const DWORD& bytes, EXP_OVER* exp)
{
	if (GameServerKeySet.find(id) == GameServerKeySet.end())
	{
		Clients[id]->RecvPacketReassemble(bytes, exp);
	}
	else
	{
		ProcessRecvFromGame(id, bytes, exp);
	}
}

LobbyClientInfo* ClientMgr::GetEmptyClient(int& ClientNum)
{
	if (ClientCount >= MAXCLIENT) return nullptr;

	while(true)
	{
		for (int i = 0; i < Clients.size(); i++)
		{
			if (!Clients[i])
			{
				auto NewClient = new LobbyClientInfo();

				LobbyClientInfo* llNullptr = nullptr;
				bool succ = std::atomic_compare_exchange_strong(
					reinterpret_cast<std::atomic<LobbyClientInfo*>*>(&Clients[i]),
					&llNullptr,
					NewClient);

				if (succ)
				{
					ClientNum = i;
					ClientCount++;
					return Clients[i];
				}
				else
				{
					delete NewClient;
					break;
				}
			}
		}
	}
	return nullptr;
}

void ClientMgr::CheckingMatchingQueue()
{
	if (GameServerKeySet.empty())
	{
		cout << "GameServerKeySet is EMPTY!" << endl;
		return;
	}

	if (m_MatchingQueue.size() >= MAXPLAYER)
	{
		PEmptyRoomNum PER;
		Clients[(*GameServerKeySet.begin())]->SendProcess(&PER);
	}
}

void ClientMgr::NewGameServerConnect(int GameServerKey)
{
	GameServerKeySet.insert(GameServerKey);
	cout << "[" << GameServerKey << "] Client Is GAMESERVER" << endl;
}

void ClientMgr::ProcessRecvFromGame(int id, int bytes, EXP_OVER* exp)
{
	Packet* packet = reinterpret_cast<Packet*>(exp->_wsa_buf.buf);
	switch (packet->PacketType)
	{
	case(int)COMP_OP::OP_SS_EMPTYROOMNUM:
	{
		// Get Room num from Gameserver
		PEmptyRoomNum PER;
		memcpy(&PER, exp->_wsa_buf.buf, sizeof(PER));

		LobbyClientInfo* client;
		std::vector<int> MatchingSerial;
		PPlayerID PPI;
		for (int i = 0; i < MAXPLAYER; )
		{
			while (m_MatchingQueue.try_pop(client))
			{
				if (client->ClientNum == -1)
				{
					m_MatchingQueue.push(client);
					return;
				}
				MatchingSerial.push_back(client->ClientNum);
				memcpy_s(PPI.IDs[i], IDSIZE, client->ClientID, IDSIZE);
				i++;
			}
		}

		PConnectToGameserver SPS;
		for (const auto i : MatchingSerial)
		{
			// TODO: i : -1 이라면 패스
			Clients[i]->SendProcess(&PPI);
			Clients[i]->SendProcess(&SPS);
			std::this_thread::sleep_for(std::chrono::milliseconds(300));
		}
	}
	break;
	default:
		break;
	}

	Clients[id]->Recv();
}

void ClientMgr::ProcessTryLogin(LobbyClientInfo* Target, PTryLogin* PTL)
{
	PLoginResult PLR;
	if (PTL->IsRegister)
	{	// REGISTER
		PLR.IsRegister = true;

		// ID Duplication Checking
		int Result = DBMgr::Instance()->ExecLogin(L"SELECT ID, Password FROM [2024_CapstoneProject].[dbo].[Login_Table]", *PTL);
		if (Result == (int)ELoginResult::Success || Result == (int)ELoginResult::PasswordError)
		{
			PLR.LoginResult = (char)ELoginResult::IDError;
			Target->SendProcess(&PLR);
			return;
		}

		wchar_t query[150];
		int WCharSize = MultiByteToWideChar(CP_ACP, 0, PTL->ID, -1, NULL, NULL);
		wchar_t* WID = new wchar_t[WCharSize];
		MultiByteToWideChar(CP_ACP, 0, PTL->ID, strlen(PTL->ID) + 1, WID, WCharSize);

		WCharSize = MultiByteToWideChar(CP_ACP, 0, PTL->Password, -1, NULL, NULL);
		wchar_t* WPassword = new wchar_t[WCharSize];
		MultiByteToWideChar(CP_ACP, 0, PTL->Password, strlen(PTL->Password) + 1, WPassword, WCharSize);

		wsprintf(query, L"INSERT INTO [2024_CapstoneProject].[dbo].[Login_Table] VALUES ('%s', '%s')", WID, WPassword);
		PLR.LoginResult = DBMgr::Instance()->ExecRegister(query, *PTL);

		delete[] WID;
		delete[] WPassword;
	}
	else
	{	// LOGIN
		PLR.LoginResult = DBMgr::Instance()->ExecLogin(L"SELECT ID, Password FROM [2024_CapstoneProject].[dbo].[Login_Table]", *PTL);
		PLR.IsRegister = false;

		if (PLR.LoginResult == (char)ELoginResult::Success)
		{
			memcpy_s(Target->ClientID, IDSIZE, PTL->ID, IDSIZE);
		}
	}
	Target->SendProcess(&PLR);
}

void ClientMgr::ProcessStartMatching(LobbyClientInfo* Target)
{
	m_MatchingQueue.push(Target);
	cout << Target->ClientNum << "Client Ready" << endl;
	CheckingMatchingQueue();
}

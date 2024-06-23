#include "ClientMgr.h"
#include "../LobbyClientInfo.h"

#include "DBMgr.h"

ClientMgr::ClientMgr()
{
	for (int i = 0; i < MAXCLIENT; i++)
	{
		Clients[i] = nullptr;
	}

	m_GameServerSocket = new LobbyClientInfo();
	m_GameServerSocket->SetSocket(WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, 0, 0, WSA_FLAG_OVERLAPPED));
}

void ClientMgr::Send(int id, Packet* p)
{
}

void ClientMgr::Recv(int id, const DWORD& bytes, EXP_OVER* exp)
{
	Clients[id]->RecvPacketReassemble(bytes, exp);
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
	if (m_MatchingQueue.size() >= MAXPLAYER)
	{
		PEmptyRoomNum PER;
		m_GameServerSocket->SendProcess(&PER);
	}
}

bool ClientMgr::ConnectToGameServer(const HANDLE& hIocp)
{
	sockaddr_in serveraddr;
	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	int a = inet_pton(AF_INET, GAMESERVERIP, &serveraddr.sin_addr.s_addr);
	serveraddr.sin_port = htons(GAMESERVERPORT);
	int retval = connect(m_GameServerSocket->GetSocket(), (sockaddr*)&serveraddr, sizeof(sockaddr));

	CreateIoCompletionPort(reinterpret_cast<HANDLE>(m_GameServerSocket->GetSocket()), hIocp, GAMESERVER, 0);
	m_GameServerSocket->Recv();

	if (retval == SOCKET_ERROR)
	{
		LogUtil::error_display("LobbyServer::ConnectToGameServer() GameServer connect FAILED");
		return false;
	}

	cout << "Connect Success to Game Server" << endl;
	return true;
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

		// Notify Room Num to Clients
		PConnectToGameserver SPS;
		//SPS.RoomNum = 0;
		//SPS.RoomNum = PER.RoomNum;

		LobbyClientInfo* client;

		// TODO: m_MatchingQueue 에 Lock을 걸고 진행.
		// 6개가 되어 pop 진행 중 매칭 취소가 들어오면 안되므로
		for (int i = 0; i < MAXPLAYER; )
		{
			while (m_MatchingQueue.try_pop(client))
			{
				client->SendProcess(&SPS);

				i++;
			}
		}
	}
	break;
	default:
		break;
	}
}

void ClientMgr::ProcessTryLogin(LobbyClientInfo* Target, PTryLogin* PTL)
{
	PLoginResult PLR;
	if (PTL->IsRegister)
	{	// REGISTER

		// ID Duplication Checking
		int Result = DBMgr::Instance()->ExecRegister(L"SELECT ID, Password FROM [2024_CapstoneProject].[dbo].[Login_Table]", *PTL);
		if (Result == (int)ELoginResult::Success || Result == (int)ELoginResult::PasswordError)
		{

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
		PLR.IsRegister = true;

		delete[] WID;
		delete[] WPassword;
	}
	else
	{	// LOGIN
		PLR.LoginResult = DBMgr::Instance()->ExecLogin(L"SELECT ID, Password FROM [2024_CapstoneProject].[dbo].[Login_Table]", *PTL);
		PLR.IsRegister = false;
	}
	Target->SendProcess(&PLR);
}

void ClientMgr::ProcessStartMatching(LobbyClientInfo* Target)
{
	m_MatchingQueue.push(Target);
	cout << Target->ClientNum << "번 Ready" << endl;
	CheckingMatchingQueue();
}

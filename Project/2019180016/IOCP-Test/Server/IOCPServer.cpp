#define _CRT_SECURE_NO_WARNINGS
#include "IOCPServer.h"
#include "../Common/Define.h"

#include "ClientInfo.h"
#include "Object.h"

#include "TimerMgr.h"
#include "TimerEvent.h"
#include "RoomMgr.h"

#include <chrono>

//#include <ppl.h>

IOCPServer::IOCPServer()
{
	m_IocpFunctionMap.insert({ COMP_OP::OP_ACCEPT,	[this](int id, int bytes, EXP_OVER* exp) {Accept(id, bytes, exp); } });
	m_IocpFunctionMap.insert({ COMP_OP::OP_SEND,	[this](int id, int bytes, EXP_OVER* exp) {Send(id, bytes, exp); } });
	m_IocpFunctionMap.insert({ COMP_OP::OP_RECV,	[this](int id, int bytes, EXP_OVER* exp) {Recv(id, bytes, exp); } });

	//m_IocpFunctionMap.insert({ COMP_OP::OP_POSITION,[this](int id, int bytes, EXP_OVER* exp) {RecvNewPosition(id, bytes, exp); } });

	m_iClientId = 0;
	m_iClientCount = 0;
	m_iRoomId = 0;

	m_TimerMgr = std::make_shared<TimerMgr>();

	IsLobbyServerConnect = false;
}

IOCPServer::~IOCPServer()
{
}

bool IOCPServer::Init(const int WorkerNum)
{
	WSADATA WSAData;
	if (WSAStartup(MAKEWORD(2, 2), &WSAData) != 0)
		return false;

	m_ListenSocket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, 0, 0, WSA_FLAG_OVERLAPPED);
	if (INVALID_SOCKET == m_ListenSocket)
	{
		LogUtil::error_display(WSAGetLastError());
		return false;
	}

	m_LobbyServerSocket = new ClientInfo();

	m_iWorkerNum = WorkerNum - 2;

	for (auto& c : m_Clients)
	{
		c = new ClientInfo();
	}

	return true;
}

bool IOCPServer::BindListen(const int PortNum)
{

	SOCKADDR_IN server_addr;
	ZeroMemory(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PortNum);
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	int retval = bind(m_ListenSocket, reinterpret_cast<sockaddr*>(&server_addr), sizeof(server_addr));
	if (0 != retval)
	{
		LogUtil::error_display(WSAGetLastError());
		return false;
	}

	retval = listen(m_ListenSocket, SOMAXCONN);
	if (0 != retval)
	{
		LogUtil::error_display(WSAGetLastError());
		return false;
	}

	// IOCP �ڵ� ����
	m_hIocp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, NULL, 0);
	//Listen ���� IOCP �ڵ鿡 ����
	CreateIoCompletionPort(reinterpret_cast<HANDLE>(m_ListenSocket), m_hIocp, 9999, 0);

	//=====================================================
	SOCKET c_socket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, 0, 0, WSA_FLAG_OVERLAPPED);
	char	accept_buf[sizeof(SOCKADDR_IN) * 2 + 32 + 100];

	*(reinterpret_cast<SOCKET*>(&m_AcceptExpOver._net_buf)) = c_socket;
	ZeroMemory(&m_AcceptExpOver._wsa_over, sizeof(m_AcceptExpOver._wsa_over));
	m_AcceptExpOver._comp_op = COMP_OP::OP_ACCEPT;

	AcceptEx(m_ListenSocket, c_socket, accept_buf, 0, sizeof(SOCKADDR_IN) + 16,
		sizeof(SOCKADDR_IN) + 16, NULL, &m_AcceptExpOver._wsa_over);
	std::cout << "Aceept Called\n";
	//========================�̰Ź���?======================

	return true;
}

void IOCPServer::StartServer()
{
	for (int i = 0; i < m_iWorkerNum; i++)
	{
		m_tWorkerThreads.emplace_back([this]() { Worker(); });
	}

	m_tTimerThread = std::thread(&IOCPServer::Timer, this);

	//TempSendThread = std::thread(&IOCPServer::TestSend, this);
}

void IOCPServer::Worker()
{
	while (true)
	{
		// I/O�۾����� ���۵� ����Ʈ ���� �����ϴ� ����
		DWORD num_byte;
		// I/O�۾��� �Ϸ�� ���� �ڵ�� ����� �Ϸ� Ű, ���⼱ Ŭ���̾�Ʈ ���� ��ȣ
		LONG64 iocp_key;
		// I/O �۾��� ���۵� �� ������ OVERLAAPED ����ü �ּ�
		WSAOVERLAPPED* p_over;

		BOOL ret = GetQueuedCompletionStatus(m_hIocp, &num_byte, (PULONG_PTR)&iocp_key, &p_over, INFINITE);

		int client_id = static_cast<int>(iocp_key);
		EXP_OVER* exp_over = reinterpret_cast<EXP_OVER*>(p_over);

		if (FALSE == ret)
		{
			int err_no = WSAGetLastError();
			cout << "GQCS Error : ";
			LogUtil::error_display(err_no);
			cout << endl;
			//Disconnect(client_id);
			//if (exp_over->_comp_op == COMP_OP::OP_SEND)
			//	delete exp_over;
			continue;
		}

		auto FuncIt = m_IocpFunctionMap.find(exp_over->_comp_op);
		if (FuncIt != m_IocpFunctionMap.end())
		{
			FuncIt->second(client_id, num_byte, exp_over);
		}
		else
		{
			std::cerr << "Cant Find mapping Function! _comp_op is: " << (int)exp_over->_comp_op << endl;
		}
	}
}

void IOCPServer::ThreadJoin()
{
	for (auto& t : m_tWorkerThreads)
	{
		t.join();
	}
	m_tTimerThread.join();
}

void IOCPServer::Timer()
{
	while (true)
	{
		m_TimerMgr->Pop();
	}
}

ClientInfo* IOCPServer::GetEmptyClient()
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

//const int IOCPServer::GetEmptyRoomNum()
//{
//	//auto it = std::find_if(m_Clients.begin(), m_Clients.end(),
//	//	[](const std::array<ClientInfo*, MAXPLAYER>& a)
//	//	{
//	//		return a[0]->GetClientNum() == -1;
//	//	});
//
//	for (int i = 0; i < MAXROOM; i++)
//	{
//		if (m_Clients[i][0]->GetClientNum() == -1)
//		{
//			return i;
//		}
//	}
//
//	return -1;
//}

bool IOCPServer::ReadyToNextAccept()
{
	SOCKET c_socket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, 0, 0, WSA_FLAG_OVERLAPPED);
	*(reinterpret_cast<SOCKET*>(&m_AcceptExpOver._net_buf)) = c_socket;
	ZeroMemory(&m_AcceptExpOver._wsa_over, sizeof(m_AcceptExpOver._wsa_over));

	int ret = AcceptEx(m_ListenSocket,						// ������ �����ڵ�
		c_socket/*socket->GetSocket()*/,					// ������ ������ ������ ����
		m_AcceptExpOver._net_buf + 8,											// ���� �ּҿ� ����Ʈ �ּҸ� ���� ����
		0,													// ���� �� ���۵Ǵ� ���� �����͸� �����ϱ� ���� ������ ũ��
		sizeof(SOCKADDR_IN) + 16,							// �ּ�ȹ���� ���� ������ ũ�⸦ �˷��ֱ� ���� ���� �ּ��� ����
		sizeof(SOCKADDR_IN) + 16,							// �ּ�ȹ���� ���� ������ ũ�⸦ �˷��ֱ� ���� ����Ʈ �ּ��� ����
		0,													// �Լ� ȣ�� �� ������ ���� �������� ũ�� overlapped ���� ���õ�
		(LPWSAOVERLAPPED)&m_AcceptExpOver._wsa_over);		// Overlapped ����ü ������


	if (0 != ret)
	{
		cout << "AcceptEx Error\n";
		LogUtil::error_display(WSAGetLastError());
		return false;
	}

	return true;
}

void IOCPServer::AccpetLobbyServer()
{
	CreateIoCompletionPort(reinterpret_cast<HANDLE>(m_LobbyServerSocket->GetSocket()), m_hIocp, LOBBYSERVER, 0);
	m_LobbyServerSocket->Recv();
}

int IOCPServer::GetWeaponDamage(bool isMelee, int weaponEnum)
{
	if (isMelee)
	{
		switch (weaponEnum)
		{
		case (int)EMeleeWeapon::Dagger:
			return 120;
		case (int)EMeleeWeapon::Greatsword:
			return 200;
		case (int)EMeleeWeapon::Katana:
			return 150;
		default:
			return 0;
		}
	}
	else
	{
		switch (weaponEnum)
		{
		case (int)ERangeWeapon::AssaultRifle:
			return 100;
		case (int)ERangeWeapon::GrenadeLauncher:
			return 300;
		case (int)ERangeWeapon::SubmachineGun:
			return 50;
		default:
			return 0;
		}
	}
}

void IOCPServer::Accept(int id, int bytes, EXP_OVER* exp)
{
	if (!IsLobbyServerConnect)
	{
		m_LobbyServerSocket->SetSocket(*(reinterpret_cast<SOCKET*>(exp->_net_buf)));
		AccpetLobbyServer();
		IsLobbyServerConnect = true;

		LogUtil::PrintLog("Connect Success to Lobby Server");

		if (!ReadyToNextAccept())
		{
			return;
		}
	}
	else
	{
		// id�� �������� ��ȣ 9999�� ������ ��?
		if (m_iClientCount < MAXCLIENT)
		{
			// ��� Ŭ���� ���� ��ȣ�� ����??
			ClientInfo* socket = GetEmptyClient();

			int NowClientNum = m_iClientId++;

			socket->SetClientNum(NowClientNum);
			socket->SetSocket(*(reinterpret_cast<SOCKET*>(exp->_net_buf)));

			CreateIoCompletionPort(reinterpret_cast<HANDLE>(socket->GetSocket()), m_hIocp, NowClientNum, 0);

			socket->Recv();

			PPlayerJoin PPJ(NowClientNum % 6);
			socket->SendProcess(sizeof(PPJ), &PPJ);

			// Push Game Start Timer (Time to Select Weapon)
			if (NowClientNum % MAXPLAYER == MAXPLAYER - 1)
			{
				// 너무 빨리 보내면 못 받는다
				TimerEvent TE1(std::chrono::seconds(1),
					std::bind(&IOCPServer::SendSelectTime, this, NowClientNum, 40.f));
				m_TimerMgr->Insert(TE1);

				TimerEvent TE2(std::chrono::seconds(40),
					std::bind(&IOCPServer::StartGame, this, NowClientNum / 6, NowClientNum % 6, nullptr));
				m_TimerMgr->Insert(TE2);
			}

			// SendPlayerJoinPacket(m_iClientId);

			cout << NowClientNum << "번 Accept" << endl;

			//m_iClientId++;
			m_iClientCount++;

			if (!ReadyToNextAccept())
			{
				return;
			}
		}
		else
		{
			std::cerr << "Client MAX!" << std::endl;
		}
	}
}

void IOCPServer::Send(int id, int bytes, EXP_OVER* exp)
{
	delete exp;
}

void IOCPServer::Recv(int id, int bytes, EXP_OVER* exp)
{
	if (id == LOBBYSERVER)
	{
		ProcessRecvFromLobby(id, bytes, exp);
		return;
	}

	const BYTE PacketType = *(BYTE*)exp->_wsa_buf.buf;

	switch (PacketType)
	{
	case (int)COMP_OP::OP_POSITION:

		break;
	case (int)COMP_OP::OP_PLAYERPOSITION:
	{
		PPlayerPosition PPP;
		//memcpy(&PPP, exp->_wsa_buf.buf, sizeof(PPlayerPosition));
		MEMCPYBUFTOPACKET(PPP);
		ProcessPlayerPosition(PPP);
	}
	break;
	case (int)COMP_OP::OP_DISCONNECT:
	{
		PDisconnect disconnect(-1);
		memcpy(&disconnect, exp->_wsa_buf.buf, sizeof(PDisconnect));
		ProcessDisconnectPlayer(disconnect);
	}
	break;
	case (int)COMP_OP::OP_SELECTWEAPONINFO:
	{
		PPlayerSelectInfo PPS;
		MEMCPYBUFTOPACKET(PPS);

		int SendPlayerRoomNum = id / 6;

		// Send To Other Player Pick State
		SendPacketToAllSocketsInRoom(SendPlayerRoomNum, &PPS, sizeof(PPS));
	}
	break;
	case (int)COMP_OP::OP_CHANGEDPLAYERHP:
	{
		PDamagedPlayer PDP;
		MEMCPYBUFTOPACKET(PDP);
		int TargetPlayerHp = PDP.ChangedPlayerSerial;
		int Damage = GetWeaponDamage(PDP.IsMelee, PDP.WeaponEnum);

		PChangedPlayerHP PCPHP(TargetPlayerHp, m_Clients[TargetPlayerHp]->ChangeHp(Damage));
		int SendPlayerRoomNum = id / 6;
		SendPacketToAllSocketsInRoom(id / 6, &PCPHP, sizeof(PCPHP));
	}
	break;
	default:
		break;
	}

	m_Clients[id]->RecvProcess(bytes, exp);
}

void IOCPServer::ProcessRecvFromLobby(int id, int bytes, EXP_OVER* exp)
{
	const int PacketType = *(int*)exp->_wsa_buf.buf;
	switch (PacketType)
	{
	case(int)COMP_OP::OP_SS_EMPTYROOMNUM:
	{
		PEmptyRoomNum PER;
		PER.RoomNum = 0;// GetEmptyRoomNum();
		m_LobbyServerSocket->SendProcess(sizeof(PEmptyRoomNum), &PER);
	}
	break;
	default:
		break;
	}
}

void IOCPServer::SendPlayerJoinPacket(int JoinPlayerSerial)
{
	PPlayerJoin JoinPacket(m_iClientId);
	for (const auto& socket : m_Clients)
	{
		if (socket->GetClientNum() != -1)
		{
			socket->SendProcess(sizeof(PPlayerJoin), &JoinPacket);
		}
	}
}

void IOCPServer::SendTileDrop(int id)
{
	PTileDrop PTD;
	m_Clients[id]->SendProcess(sizeof(PTileDrop), &PTD);
}

void IOCPServer::SendSelectTime(int NowClientNum, float time)
{
	PSetTimer PST = PSetTimer(ETimer::SelectTimer, time);
	SendPacketToAllSocketsInRoom(NowClientNum / 6, &PST, sizeof(PST));
}

void IOCPServer::SendPacketToAllSocketsInRoom(int roomId, Packet* p, int packetSize)
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

void IOCPServer::ProcessPlayerPosition(PPlayerPosition p)
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

void IOCPServer::ProcessDisconnectPlayer(PDisconnect p)
{
	m_Clients[p.DisconnectPlayerSerial]->Init();
	m_iClientCount--;
}

//void IOCPServer::ProcessNewPlayers(PSendPlayerSockets p)
//{
//	for (int i = 0; i < MAXPLAYER; i++)
//	{
//		ClientInfo* c = GetEmptyClient();
//
//		c->SetClientNum(m_iClientId);
//		c->SetSocket(p.sockets[i]);
//		CreateIoCompletionPort(reinterpret_cast<HANDLE>(c->GetSocket()), m_hIocp, m_iClientId, 0);
//
//		c->Recv();
//		m_iClientId++;
//
//		SendPlayerJoinPacket(m_iClientId);
//	}
//}

void IOCPServer::TestSend()
{
	//m_TimerMgrMap.insert({0, new TimerMgr()});
	//int i{ 0 };
	//while (true)
	//{    
	//	auto currentTime = std::chrono::system_clock::now();

	//	// time_point�� time_t�� ��ȯ
	//	std::time_t tt = std::chrono::system_clock::to_time_t(currentTime);

	//	// time_t�� tm ����ü�� ��ȯ
	//	std::tm* localTime = std::localtime(&tt);

	//	// �ð��� ���
	//	std::cout << "Timer Func Num:" << i << " Insert! " << std::put_time(localTime, "%Y-%m-%d %H:%M:%S") << std::endl;

	//	//cout << i << "Num Timer Insert //" << std::chrono::system_clock::now() << endl;
	//	DefaultEvent Event(std::chrono::seconds(4),
	//		[i]()
	//		{
	//			auto currentTime = std::chrono::system_clock::now();

	//			// time_point�� time_t�� ��ȯ
	//			std::time_t tt = std::chrono::system_clock::to_time_t(currentTime);

	//			// time_t�� tm ����ü�� ��ȯ
	//			std::tm* localTime = std::localtime(&tt);

	//			// �ð��� ���
	//			std::cout << "Timer Func Num:" << i << " Activative! " << std::put_time(localTime, "%Y-%m-%d %H:%M:%S") << std::endl;
	//		});
	//	m_TimerMgrMap[0]->Insert(Event);
	//	i++;

	//	std::this_thread::sleep_for(std::chrono::seconds(3));
	//}
	//delete m_TimerMgrMap[0];
}

void IOCPServer::StartGame(int RoomNum, int ClientNum, void* etc)
{
	PStartGame PSG;
	SendPacketToAllSocketsInRoom(RoomNum, &PSG, sizeof(PSG));
}

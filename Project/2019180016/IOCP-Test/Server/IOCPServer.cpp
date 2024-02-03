#define _CRT_SECURE_NO_WARNINGS
#include "IOCPServer.h"
#include "Define.h"

#include "ClientInfo.h"
#include "Object.h"

#include "TimerMgr.h"
#include "TimerEvent.h"

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
		error_display(WSAGetLastError());
		return false;
	}
	m_iWorkerNum = WorkerNum - 2;

	for (int i = 0; i < MAXCLIENT; i++)
	{
		m_Clients[i] = new ClientInfo();

		//CreateIoCompletionPort(reinterpret_cast<HANDLE>(m_Clients[i]), m_hIocp, i, 0);
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
		error_display(WSAGetLastError());
		return false;
	}

	retval = listen(m_ListenSocket, SOMAXCONN);
	if (0 != retval)
	{
		error_display(WSAGetLastError());
		return false;
	}

	// IOCP 핸들 생성
	m_hIocp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, NULL, 0);
	//Listen 소켓 IOCP 핸들에 연결
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
	//========================이거뭐임?======================

    return true;
}

void IOCPServer::error_display(int err_no)
{
	WCHAR* lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, err_no,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, 0);
	std::wcout << lpMsgBuf << std::endl;
	//while (true);
	LocalFree(lpMsgBuf);
}

void IOCPServer::StartServer()
{
	for (int i = 0; i < m_iWorkerNum; i++)
	{
		m_tWorkerThreads.emplace_back([this]() { Worker(); });
	}

	m_tTimerThread = std::thread(&IOCPServer::Timer, this);

	TempSendThread = std::thread(&IOCPServer::TestSend, this);
}

void IOCPServer::Worker()
{
	while (true)
	{
		// I/O작업에서 전송된 바이트 수를 수신하는 변수
		DWORD num_byte;
		// I/O작업이 완료된 파일 핸들과 연결된 완료 키, 여기선 클라이언트 고유 번호
		LONG64 iocp_key;
		// I/O 작업이 시작될 떄 지정된 OVERLAAPED 구조체 주소
		WSAOVERLAPPED* p_over;

		BOOL ret = GetQueuedCompletionStatus(m_hIocp, &num_byte, (PULONG_PTR)&iocp_key, &p_over, INFINITE);

		int client_id = static_cast<int>(iocp_key);
		EXP_OVER* exp_over = reinterpret_cast<EXP_OVER*>(p_over);

		if (FALSE == ret)
		{
			int err_no = WSAGetLastError();
			cout << "GQCS Error : ";
			error_display(err_no);
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
		for (const auto& t : m_TimerMgrMap)
		{
			t.second->Pop();
		}
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

void IOCPServer::Accept(int id, int bytes, EXP_OVER* exp)
{
	// id는 리슨소켓 번호 9999가 들어오는 듯?
	if (m_iClientCount < MAXCLIENT)
	{
		ClientInfo* socket = GetEmptyClient();
		socket->SetClientNum(m_iClientId);
		socket->SetSocket(*(reinterpret_cast<SOCKET*>(exp->_net_buf)));

		CreateIoCompletionPort(reinterpret_cast<HANDLE>(socket->GetSocket()), m_hIocp, m_iClientId, 0);

		socket->Recv();
		socket->Send();

		m_iClientId++;
		m_iClientCount++;

		int ret = AcceptEx(m_ListenSocket,						// 리슨용 소켓핸들
			socket->GetSocket(),								// 들어오는 접속을 수용할 소켓
			m_AcceptExpOver._net_buf,							// 로컬 주소와 리모트 주소를 담을 버퍼
			0,													// 접속 후 전송되는 최초 데이터를 수신하기 위한 버퍼의 크기
			sizeof(SOCKADDR_IN) + 16,							// 주소획득을 위한 버퍼의 크기를 알려주기 위한 로컬 주소의 길이
			sizeof(SOCKADDR_IN) + 16,							// 주소획득을 위한 버퍼의 크기를 알려주기 위한 리모트 주소의 길이
			0,													// 함수 호출 후 실제로 받은 데이터의 크기 overlapped 사용시 무시됨
			(LPWSAOVERLAPPED)&m_AcceptExpOver._wsa_over);		// Overlapped 구조체 포인터


		if (0 != ret)
		{
			cout << "AcceptEx오류\n";
			error_display(WSAGetLastError());
			return;
		}
	}
	else
	{
		std::cerr << "Client MAX!" << std::endl;
	}
}

void IOCPServer::Send(int id, int bytes, EXP_OVER* exp)
{
	static Object TempCube(200.f, 200, 200, 0, 0, 0);
	std::stringstream SendData;

	float x, y, z;
	TempCube.MoveLocation(0.01, 0.01, 0.01);
	TempCube.GetLocation(x, y, z);

	PPosition SendPosition(x, y, z);

	SendData << (int)COMP_OP::OP_POSITION;
	// TODO: 직렬화 수정해야함
	SendData << x << y << z;

	m_Clients[id]->SendProcess(sizeof(SendPosition), &SendPosition);
}

void IOCPServer::Recv(int id, int bytes, EXP_OVER* exp)
{
	std::stringstream RecvData;
	int PacketType;
	
	RecvData << exp->_wsa_buf.buf;
	RecvData >> PacketType;

	switch (PacketType)
	{
	case (int)COMP_OP::OP_POSITION:

		break;


	default:
		break;
	}

	m_Clients[id]->RecvProcess(bytes, exp);
}

void IOCPServer::RecvNewPosition(int id, int bytes, EXP_OVER* exp)
{

}

void IOCPServer::TestSend()
{
	m_TimerMgrMap.insert({0, new TimerMgr()});
	int i{ 0 };
	while (true)
	{    
		auto currentTime = std::chrono::system_clock::now();

		// time_point을 time_t로 변환
		std::time_t tt = std::chrono::system_clock::to_time_t(currentTime);

		// time_t를 tm 구조체로 변환
		std::tm* localTime = std::localtime(&tt);

		// 시간을 출력
		std::cout << "Timer Func Num:" << i << " Insert! " << std::put_time(localTime, "%Y-%m-%d %H:%M:%S") << std::endl;

		//cout << i << "Num Timer Insert //" << std::chrono::system_clock::now() << endl;
		m_TimerMgrMap[0]->Insert(new DefaultEvent(
			std::chrono::seconds(4),													
			[i]()
			{
				auto currentTime = std::chrono::system_clock::now();

				// time_point을 time_t로 변환
				std::time_t tt = std::chrono::system_clock::to_time_t(currentTime);

				// time_t를 tm 구조체로 변환
				std::tm* localTime = std::localtime(&tt);

				// 시간을 출력
				std::cout << "Timer Func Num:" << i << " Activative! " << std::put_time(localTime, "%Y-%m-%d %H:%M:%S") << std::endl;
			}));
		i++;
		//for (int i = 0; i < MAXCLIENT; i++)
		//{
		//	if (m_Clients[i]->GetClientNum() == -1)
		//	{
		//		return;
		//	}

		//	EXP_OVER temp;
		//	Send(i, 0, &temp);

		//	//const char* text = "asdasd";
		//	//EXP_OVER exp{ COMP_OP::OP_SEND, (char)(sizeof(text)), (void*)text };
		//	//exp.room_id = 0;
		//	//exp.target_id = 0;
		//	//WSAOVERLAPPED a;
		//	//ZeroMemory(&a, sizeof(a));

		//	//int ret = WSASend(m_ListenSocket, &exp._wsa_buf, 1, 0, 0, &a, 0);
		//	//if (SOCKET_ERROR == ret) {
		//	//	int error_num = WSAGetLastError();
		//	//	if (ERROR_IO_PENDING != error_num)
		//	//		IOCPServer::error_display(error_num);
		//	//}
		//}

		std::this_thread::sleep_for(std::chrono::seconds(3));
	}
	delete m_TimerMgrMap[0];
}

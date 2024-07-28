#include "LobbyServer.h"
#include "LobbyClientInfo.h"
#include "../../Common/LogUtil.h"

#include "Manager/DBMgr.h"
#include "Manager/ClientMgr.h"

LobbyServer::LobbyServer()
{
	m_IocpFunctionMap.insert({ COMP_OP::OP_ACCEPT,	[this](int id, int bytes, EXP_OVER* exp) {Accept(id, bytes, exp); } });
	m_IocpFunctionMap.insert({ COMP_OP::OP_SEND,	[this](int id, int bytes, EXP_OVER* exp) {Send(id, bytes, exp); } });
	m_IocpFunctionMap.insert({ COMP_OP::OP_RECV,	[this](int id, int bytes, EXP_OVER* exp) {Recv(id, bytes, exp); } });


}

bool LobbyServer::Init(const int WorkerNum)
{
	WSADATA WSAData;
	if (WSAStartup(MAKEWORD(2, 2), &WSAData) != 0)
		return false;

	m_ListenSocket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, 0, 0, WSA_FLAG_OVERLAPPED);
	if (INVALID_SOCKET == m_ListenSocket)
	{
		cout << "[LobbyServer::Init WSASocket Error] ";
		error_display(WSAGetLastError());
		return false;
	}

	if (WorkerNum > 2)
		m_iWorkerNum = WorkerNum - 2;
	else
		m_iWorkerNum = 1;


	DBMgr::Instance();

	return true;
}

bool LobbyServer::BindListen(const int PortNum)
{
	SOCKADDR_IN server_addr;
	ZeroMemory(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PortNum);
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	int retval = bind(m_ListenSocket, reinterpret_cast<sockaddr*>(&server_addr), sizeof(server_addr));
	if (0 != retval)
	{
		cout << "[LobbyServer::BindListen bind Error] ";
		error_display(WSAGetLastError());
		return false;
	}

	retval = listen(m_ListenSocket, SOMAXCONN);
	if (0 != retval)
	{
		cout << "[LobbyServer::BindListen listen Error] ";
		error_display(WSAGetLastError());
		return false;
	}

	m_hIocp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, NULL, 0);
	CreateIoCompletionPort(reinterpret_cast<HANDLE>(m_ListenSocket), m_hIocp, 9999, 0);

	SOCKET c_socket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, 0, 0, WSA_FLAG_OVERLAPPED);
	char	accept_buf[sizeof(SOCKADDR_IN) * 2 + 32 + 100];

	*(reinterpret_cast<SOCKET*>(&m_AcceptExpOver._net_buf)) = c_socket;
	ZeroMemory(&m_AcceptExpOver._wsa_over, sizeof(m_AcceptExpOver._wsa_over));
	m_AcceptExpOver._comp_op = COMP_OP::OP_ACCEPT;

	AcceptEx(m_ListenSocket, c_socket, accept_buf, 0, sizeof(SOCKADDR_IN) + 16,
		sizeof(SOCKADDR_IN) + 16, NULL, &m_AcceptExpOver._wsa_over);
	std::cout << "Aceept Called\n";

	return true;
}

void LobbyServer::error_display(int err_no)
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

void LobbyServer::StartServer()
{
	for (int i = 0; i < m_iWorkerNum; i++)
	{
		m_tWorkerThreads.emplace_back([this]() { Worker(); });
	}
}

void LobbyServer::ThreadJoin()
{
	for (auto& t : m_tWorkerThreads)
	{
		t.join();
	}
}

void LobbyServer::Worker()
{
	while (true)
	{
		DWORD num_byte;
		LONG64 iocp_key;
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
			ClientMgr::Instance()->Disconnect(client_id);
			if (exp_over->_comp_op == COMP_OP::OP_SEND)
				delete exp_over;
			continue;
		}

		if (0 == num_byte)
		{
			if (exp_over->_comp_op == COMP_OP::OP_SEND || exp_over->_comp_op == COMP_OP::OP_RECV)
				ClientMgr::Instance()->Disconnect(client_id);
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

void LobbyServer::Accept(int id, int bytes, EXP_OVER* exp)
{
	if (ClientMgr::Instance()->ClientCount < MAXCLIENT)
	{
		// ��� Ŭ���� ���� ��ȣ�� ����??

		int ClientNum;
		LobbyClientInfo* socket = ClientMgr::Instance()->GetEmptyClient(ClientNum);
		socket->SetClientNum(ClientNum);
		socket->SetSocket(*(reinterpret_cast<SOCKET*>(exp->_net_buf)));
		ZeroMemory(&socket->Exp, sizeof(socket->Exp));

		CreateIoCompletionPort(reinterpret_cast<HANDLE>(socket->GetSocket()), m_hIocp, ClientNum, 0);

		socket->Recv();
		//socket->Send();

		cout << ClientNum << " Client Accept" << endl;

		ReadyToNextAccept();
	}
	else
	{
		std::cerr << "Client MAX!" << std::endl;
	}
}

void LobbyServer::Send(int id, int bytes, EXP_OVER* exp)
{
	delete exp;
}

void LobbyServer::Recv(int id, int bytes, EXP_OVER* exp)
{
	ClientMgr::Instance()->Recv(id, bytes, exp);
}

bool LobbyServer::ReadyToNextAccept()
{
	SOCKET c_socket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, 0, 0, WSA_FLAG_OVERLAPPED);
	*(reinterpret_cast<SOCKET*>(&m_AcceptExpOver._net_buf)) = c_socket;
	ZeroMemory(&m_AcceptExpOver._wsa_over, sizeof(m_AcceptExpOver._wsa_over));

	int ret = AcceptEx(m_ListenSocket,
		c_socket/*socket->GetSocket()*/,
		m_AcceptExpOver._net_buf + 8,
		0,
		sizeof(SOCKADDR_IN) + 16,
		sizeof(SOCKADDR_IN) + 16,
		0,
		(LPWSAOVERLAPPED)&m_AcceptExpOver._wsa_over);

	if (0 != ret)
	{
		cout << "AcceptEx Error\n";
		error_display(WSAGetLastError());
		return false;
	}
	return true;
}

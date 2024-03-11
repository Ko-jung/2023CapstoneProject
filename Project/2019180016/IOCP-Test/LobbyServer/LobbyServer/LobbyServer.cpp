#include "LobbyServer.h"
#include "../../Server/ClientInfo.h"

#define SERVERPORT 9000

bool LobbyServer::Init(const int)
{
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return false;

	m_ListenSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (m_ListenSocket == INVALID_SOCKET)
	{
		error_display(WSAGetLastError());
		return false;
	}
	return true;
}

bool LobbyServer::BindListen(const int)
{
	// bind()
	struct sockaddr_in serveraddr;
	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(SERVERPORT);
	int retval = bind(m_ListenSocket, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) error_display(WSAGetLastError());

	// listen()
	retval = listen(m_ListenSocket, SOMAXCONN);
	if (retval == SOCKET_ERROR) error_display(WSAGetLastError());

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
	m_RecvThread = std::thread(&LobbyServer::RecvProcess, this);

	AcceptNewSocket();
}

void LobbyServer::ThreadJoin()
{
}

void LobbyServer::AcceptNewSocket()
{
	SOCKET client_sock;
	struct sockaddr_in clientaddr;
	int addrlen;
	while (1)
	{
		// accept()
		addrlen = sizeof(clientaddr);
		client_sock = accept(m_ListenSocket, (struct sockaddr*)&clientaddr, &addrlen);
		if (client_sock == INVALID_SOCKET) {
			error_display(WSAGetLastError());
			break;
		}

		char addr[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &clientaddr.sin_addr, addr, sizeof(addr));
		printf("\n[TCP 접속] IP 번호 = %s, 포트 번호 = %d\n",
			addr, ntohs(clientaddr.sin_port));

	}
}

void LobbyServer::RecvProcess()
{
	int retval;
	int BufSize;

	while (true)
	{
		retval = recv(m_ListenSocket, (char*)&BufSize, sizeof(int), MSG_WAITALL);
		if (retval == SOCKET_ERROR) {
			error_display(WSAGetLastError());
		}
		retval = recv(m_ListenSocket, (char*)buf, BufSize, MSG_WAITALL);
		if (retval == SOCKET_ERROR) {
			error_display(WSAGetLastError());
		}
	}
}

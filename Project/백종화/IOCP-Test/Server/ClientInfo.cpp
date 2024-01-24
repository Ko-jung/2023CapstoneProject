#include "ClientInfo.h"
#include "IOCPServer.h"

ClientInfo::ClientInfo(int ClientNum):
	m_iRemainDataLen(0),
	m_iClientNum(ClientNum)
{
	m_sClientSocket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	if (INVALID_SOCKET == m_sClientSocket)
	{
		std::cout << "ClientInfo Socket Create FAIL" << std::endl;
		IOCPServer::error_display(WSAGetLastError());
	}
}

void ClientInfo::Recv()
{
}

void ClientInfo::RecvProcess(const DWORD& bytes, EXP_OVER* exp)
{
	int remaindata = bytes + m_iRemainDataLen;
	char* packet = exp->_net_buf;

	// 패킷 재조립
	//while (remaindata > 0) {
	//	BASE_PACKET* p = reinterpret_cast<BASE_PACKET*>(packet);

	//	if (p->size <= remaindata) {
	//		CPacketMgr::GetInstance()->Packet_Exec(p, this);
	//		packet += p->size;
	//		remaindata -= p->size;
	//	}
	//	else break;
	//}
	m_iRemainDataLen = remaindata;
	if (remaindata > 0)
		memmove(exp->_net_buf, packet, remaindata);
	Recv();
}

void ClientInfo::Send()
{
	if (m_sClientSocket == INVALID_SOCKET)
	{
		std::cout << "ClientInfo Socket is INVALID_SOCKET" << std::endl;
		return;
	}
	//WSABUF temp;
	const char* text = "asdasd";
	//memcpy(temp.buf, text, sizeof(text));
	//temp.len = strlen(text);

	EXP_OVER exp {COMP_OP::OP_SEND, (char)(sizeof(text)), (void*)text};
	//cout << sizeof(text) << endl;
	//memcpy(exp._wsa_buf.buf, text, sizeof(text));
	//exp._wsa_buf.len = strlen(text);
	exp.room_id = 0;
	exp.target_id = 0;
	//exp._comp_op = COMP_OP::OP_SEND;
	WSAOVERLAPPED a;
	ZeroMemory(&a, sizeof(a));

	int ret = WSASend(m_sClientSocket, &exp._wsa_buf, 1, 0, 0, &a, 0);
	if (SOCKET_ERROR == ret) {
		int error_num = WSAGetLastError();
		if (ERROR_IO_PENDING != error_num)
			IOCPServer::error_display(error_num);
	}
}

void ClientInfo::SendProcess()
{
	Send();
}

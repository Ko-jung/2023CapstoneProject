#include "LobbyClientInfo.h"

LobbyClientInfo::LobbyClientInfo(int ClientNum) : 
	m_iRemainDataLen(0),
	m_iClientNum(ClientNum),
	m_iRoomNum(-1)
{
	ZeroMemory(&m_Exp, sizeof(m_Exp));
}

void LobbyClientInfo::Init()
{
	closesocket(m_sClientSocket);
	m_iRemainDataLen = 0;
	m_iClientNum = -1;
	m_iRoomNum = -1;
	ZeroMemory(&m_Exp, sizeof(m_Exp));
}

void LobbyClientInfo::RecvProcess(const DWORD& bytes, EXP_OVER* exp)
{
	//int remaindata = bytes + m_iRemainDataLen;
	//char* packet = exp->_net_buf;

	//// ��Ŷ ������
	//while (remaindata > 0) {
	//	Packet* p = reinterpret_cast<Packet*>(packet);

	//	if (p->PacketSize <= remaindata) {
	//		PacketMgr::Instance()->ProcessPacket(p, this);
	//		packet += p->PacketSize;
	//		remaindata -= p->PacketSize;
	//	}
	//	else break;
	//}
	//m_iRemainDataLen = remaindata;
	//if (remaindata > 0)
	//	memmove(exp->_net_buf, packet, remaindata);
	Recv();
}

void LobbyClientInfo::SendProcess(int PacketSize, Packet* PacketData)
{
	if (m_sClientSocket == INVALID_SOCKET)
	{
		std::cout << "ClientInfo Socket is INVALID_SOCKET" << std::endl;
		return;
	}

	EXP_OVER* exp = new EXP_OVER{ COMP_OP::OP_SEND, (char)(PacketSize), (void*)PacketData };

	int ret = WSASend(m_sClientSocket, &exp->_wsa_buf, 1, 0, 0, &exp->_wsa_over, 0);
	if (SOCKET_ERROR == ret) {
		int error_num = WSAGetLastError();
		if (ERROR_IO_PENDING != error_num)
			LogUtil::error_display(error_num);
	}
}

void LobbyClientInfo::Recv()
{
	DWORD recv_flag = 0;

	ZeroMemory(&m_Exp._wsa_over, sizeof(m_Exp._wsa_over));
	m_Exp._wsa_buf.buf = reinterpret_cast<char*>(m_Exp._net_buf + m_iRemainDataLen);
	m_Exp._wsa_buf.len = sizeof(m_Exp._net_buf) - m_iRemainDataLen;

	int ret = WSARecv(m_sClientSocket, &m_Exp._wsa_buf, 1, 0, &recv_flag, &m_Exp._wsa_over, NULL);
	if (SOCKET_ERROR == ret) {
		int error_num = WSAGetLastError();
		if (ERROR_IO_PENDING != error_num)
			LogUtil::error_display(error_num);
	}

	if (ret == SOCKET_ERROR && WSAGetLastError() != WSA_IO_PENDING)
	{
		printf_s("[ERROR] WSARecv 에러, 코드 : %d", WSAGetLastError());
	}
}

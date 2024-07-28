#include "LobbyClientInfo.h"

#include "Manager/PacketMgr.h"

LobbyClientInfo::LobbyClientInfo(int ClientNum) : 
	RemainDataLen(0),
	ClientNum(ClientNum)
{
	ClientSocket = INVALID_SOCKET;
	ZeroMemory(&Exp, sizeof(Exp));
	ZeroMemory(&ClientID, sizeof(ClientID));
}

void LobbyClientInfo::Init()
{
	closesocket(ClientSocket);
	RemainDataLen = 0;
	ClientNum = -1;
	//ZeroMemory(&Exp, sizeof(Exp));
}

void LobbyClientInfo::RecvPacketReassemble(const DWORD& bytes, EXP_OVER* exp)
{
	int remaindata = bytes + RemainDataLen;
	char* packet = exp->_net_buf;

	// ��Ŷ ������
	while (remaindata > 0) {
		Packet* p = reinterpret_cast<Packet*>(packet);

		if (p->PacketSize <= remaindata) {
			PacketMgr::Instance()->ProcessPacket(p, this);
			if (p->PacketSize == 0)
				return;
			packet += p->PacketSize;
			remaindata -= p->PacketSize;
		}
		else break;
	}
	RemainDataLen = remaindata;
	if (remaindata > 0)
		memmove(exp->_net_buf, packet, remaindata);
	Recv();
}

void LobbyClientInfo::SendProcess(Packet* PacketData)
{
	if (ClientSocket == INVALID_SOCKET)
	{
		std::cout << "ClientInfo Socket is INVALID_SOCKET" << std::endl;
		return;
	}

	EXP_OVER* exp = new EXP_OVER{ COMP_OP::OP_SEND, (BYTE)(PacketData->PacketSize), (void*)PacketData };

	int ret = WSASend(ClientSocket, &exp->_wsa_buf, 1, 0, 0, &exp->_wsa_over, 0);
	if (SOCKET_ERROR == ret) {
		int error_num = WSAGetLastError();
		if (ERROR_IO_PENDING != error_num)
		{
			cout << "[" << ClientNum << "] Send ERROR -> ";
			LogUtil::error_display(error_num);
		}
	}
}

void LobbyClientInfo::Recv()
{
	DWORD recv_flag = 0;

	ZeroMemory(&Exp._wsa_over, sizeof(Exp._wsa_over));
	Exp._wsa_buf.buf = reinterpret_cast<char*>(Exp._net_buf + RemainDataLen);
	Exp._wsa_buf.len = sizeof(Exp._net_buf) - RemainDataLen;

	int ret = WSARecv(ClientSocket, &Exp._wsa_buf, 1, 0, &recv_flag, &Exp._wsa_over, NULL);
	if (SOCKET_ERROR == ret) {
		int error_num = WSAGetLastError();
		if (ERROR_IO_PENDING != error_num)
		{
			cout << "[" << ClientNum << "] Recv ERROR -> ";
			LogUtil::error_display(error_num);
		}
	}

	if (ret == SOCKET_ERROR && WSAGetLastError() != WSA_IO_PENDING)
	{
		printf_s("[ERROR] WSARecv, Code: %d\n", WSAGetLastError());
	}
}

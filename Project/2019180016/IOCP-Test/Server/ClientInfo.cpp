#include "ClientInfo.h"
//#include "IOCPServer.h"
#include "../Common/LogUtil.h"

#include <sstream>
#include "Manager/PacketMgr.h"

ClientInfo::ClientInfo(int ClientNum):
	RemainDataLen(0),
	ClientNum(ClientNum),
	//m_iRoomNum(-1),
	MaxHP(1000.f),
	CurrentHp(1000.f),
	SelectInfo(ECharacter::NullCharacter),
	State(ECharacterState::LIVING)
{
	//m_sClientSocket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	//if (INVALID_SOCKET == m_sClientSocket)
	//{
	//	std::cout << "ClientInfo Socket Create FAIL" << std::endl;
	//	IOCPServer::error_display(WSAGetLastError());
	//}
	ClientSocket = INVALID_SOCKET;
	ZeroMemory(&ExpOver, sizeof(ExpOver));
}

ClientInfo::ClientInfo(const SOCKET& s) :
	ClientSocket(s)
{
	Init();
}

void ClientInfo::Init()
{
	int ret = closesocket(ClientSocket);
	if (ret == SOCKET_ERROR)
	{
		cout << "[" << ClientNum << "] ";
		LogUtil::error_display("ClientInfo::Init() closesocket Error");
	}
	//ClientSocket = INVALID_SOCKET;
	RemainDataLen = 0;
	ClientNum = -1;
	//m_iRoomNum = -1;
	CurrentHp = MaxHP;
	ZeroMemory(&ExpOver, sizeof(ExpOver));
}

void ClientInfo::Recv()
{
	DWORD recv_flag = 0;

	ZeroMemory(&ExpOver._wsa_over, sizeof(ExpOver._wsa_over));
	ExpOver._wsa_buf.buf = reinterpret_cast<char*>(ExpOver._net_buf + RemainDataLen);
	ExpOver._wsa_buf.len = sizeof(ExpOver._net_buf) - RemainDataLen;

	int ret = WSARecv(ClientSocket, &ExpOver._wsa_buf, 1, 0, &recv_flag, &ExpOver._wsa_over, NULL);
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
		LogUtil::error_display("ClientInfo::Recv() ERROR");
	}
}

bool ClientInfo::TakeDamage(float damage)
{
	CurrentHp = CurrentHp - damage;
	if (CurrentHp <= 0.0f)
	{
		CurrentHp = 0.f;
		return true;
	}
	return false;
}

void ClientInfo::Heal(float HealAmount)
{
	if (HealAmount <= 0.f)
	{
		CurrentHp = MaxHP;
		return;
	}

	CurrentHp = CurrentHp + HealAmount;
	if (CurrentHp > MaxHP)
	{
		CurrentHp = MaxHP;
	}
}

void ClientInfo::RecvProcess(const DWORD& bytes, EXP_OVER* exp)
{
	int remaindata = bytes + RemainDataLen;
	char* packet = exp->_net_buf;

	// ��Ŷ ������
	while (remaindata > 0) {
		Packet* p = reinterpret_cast<Packet*>(packet);

		if (p->PacketSize <= remaindata) {
			PacketMgr::Instance()->ProcessPacket(p, this);

			if (p->PacketSize == 0)
			{
				cout << "@@@@" << endl;
				return;
			}
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

void ClientInfo::SendProcess(int PacketSize, Packet* PacketData)
{
	if (ClientSocket == INVALID_SOCKET)
	{
		std::cout << "ClientInfo Socket is INVALID_SOCKET" << std::endl;
		return;
	}

	EXP_OVER* exp = new EXP_OVER{ COMP_OP::OP_SEND, (char)(PacketSize), (void*)PacketData };

	int ret = WSASend(ClientSocket, &exp->_wsa_buf, 1, 0, 0, &exp->_wsa_over, 0);
	if (0 != ret) {
		int error_num = WSAGetLastError();
		if (ERROR_IO_PENDING != error_num)
		{
			cout << "[" << ClientNum << "] Send ERROR -> ";
			LogUtil::error_display(error_num);
		}
	}
}

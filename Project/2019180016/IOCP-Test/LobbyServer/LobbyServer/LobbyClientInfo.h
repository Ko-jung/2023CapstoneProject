#pragma once

#include "../../Common/Define.h"

class LobbyClientInfo
{
public:
	LobbyClientInfo(int ClientNum = -1);

	virtual ~LobbyClientInfo() {}

	void Init();

	void RecvProcess(const DWORD& bytes, EXP_OVER* exp);

	void SendProcess(int PacketSize, Packet* PacketData);
	void Recv();

	SOCKET& GetSocket() { return m_sClientSocket; }
	int GetRemainDataLen() { return m_iRemainDataLen; }
	const int GetClientNum() { return m_iClientNum; }
	int GetRoomNum() { return m_iRoomNum; }
	EXP_OVER* GetExp() { return &m_Exp; }

	void SetSocket(const SOCKET& s) { m_sClientSocket = s; }
	void SetRemainDataLen(int len) { m_iRemainDataLen = len; }
	void SetClientNum(int num) { m_iClientNum = num; }
	void SetRoomNum(int num) { m_iRoomNum = num; }

protected:
	SOCKET m_sClientSocket;

	int m_iRemainDataLen;

	int m_iClientNum;
	int m_iRoomNum;

	EXP_OVER m_Exp;
};


#pragma once

#include "Define.h"

class ClientInfo
{
public:
	ClientInfo(int ClientNum = -1);
	ClientInfo(const SOCKET& s) :
		m_sClientSocket(s),
		m_iRemainDataLen(0),
		m_iClientNum(-1),
		m_iRoomNum(-1)
	{
		ZeroMemory(&m_Exp, sizeof(m_Exp));
	}

	virtual ~ClientInfo() {}

public:
	void RecvProcess(const DWORD& bytes, EXP_OVER* exp);
	
	void SendProcess(int PacketSize, Packet* PacketData);

public:
	SOCKET& GetSocket()							{ return m_sClientSocket; }
	int GetRemainDataLen()						{ return m_iRemainDataLen; }
	int GetClientNum()							{ return m_iClientNum; }
	int GetRoomNum()							{ return m_iRoomNum; }
	void GetPos(float& x, float& y, float& z)	{ x = PosX; y = PosY; z = PosZ; }

	void SetSocket(const SOCKET& s)			{ m_sClientSocket = s; }
	void SetRemainDataLen(int len)			{ m_iRemainDataLen = len; }
	void SetClientNum(int num)				{ m_iClientNum = num; }
	void SetRoomNum(int num)				{ m_iRoomNum = num; }
	void SetPos(float x, float y, float z)	{ PosX = x; PosY = y; PosZ = z; }

	void Recv();
	void Send();
private:


protected:
	float PosX;
	float PosY;
	float PosZ;

	SOCKET m_sClientSocket;

	int m_iRemainDataLen;

	int m_iClientNum;
	int m_iRoomNum;

	EXP_OVER m_Exp;
};


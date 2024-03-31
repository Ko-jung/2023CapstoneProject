#pragma once

#include "../Common/Define.h"

class ClientInfo
{
public:
	ClientInfo(int ClientNum = -1);
	ClientInfo(const SOCKET& s);

	virtual ~ClientInfo() {}

	void Init();

public:
	void RecvProcess(const DWORD& bytes, EXP_OVER* exp);
	
	void SendProcess(int PacketSize, Packet* PacketData);
	void Recv();

public:
	float ChangeHp(float damage) { return (HP -= damage); }


	SOCKET& GetSocket()							{ return m_sClientSocket; }
	int GetRemainDataLen()						{ return m_iRemainDataLen; }
	const int GetClientNum()							{ return m_iClientNum; }
	int GetRoomNum()							{ return m_iRoomNum; }
	//void GetPos(float& x, float& y, float& z)	{ x = PosX; y = PosY; z = PosZ; }

	void SetSocket(const SOCKET& s)			{ m_sClientSocket = s; }
	void SetRemainDataLen(int len)			{ m_iRemainDataLen = len; }
	void SetClientNum(int num)				{ m_iClientNum = num; }
	void SetRoomNum(int num)				{ m_iRoomNum = num; }
	//void SetPos(float x, float y, float z)	{ PosX = x; PosY = y; PosZ = z; }

private:
	void Send();

protected:
	SOCKET m_sClientSocket;

	int m_iRemainDataLen;

	int m_iClientNum;
	int m_iRoomNum;

	EXP_OVER m_Exp;

	// Gaming data, later separated
	std::atomic<float> HP;
};


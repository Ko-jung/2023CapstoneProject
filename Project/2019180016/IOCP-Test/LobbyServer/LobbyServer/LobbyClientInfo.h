#pragma once

#include "../../Common/Define.h"

class LobbyClientInfo
{
public:
	LobbyClientInfo(int ClientNum = -1);

	virtual ~LobbyClientInfo() {}

	void Init();

	void RecvPacketReassemble(const DWORD& bytes, EXP_OVER* exp);

	void SendProcess(Packet* PacketData);
	void Recv();

	SOCKET& GetSocket() { return ClientSocket; }
	int GetRemainDataLen() { return RemainDataLen; }
	const int GetClientNum() { return ClientNum; }
	EXP_OVER* GetExp() { return &Exp; }
	
	void SetSocket(const SOCKET& s) { ClientSocket = s; }
	void SetRemainDataLen(int len) { RemainDataLen = len; }
	void SetClientNum(int num) { ClientNum = num; }
	// 
	// protected:

	SOCKET ClientSocket;

	int RemainDataLen;

	int ClientNum;

	EXP_OVER Exp;
};


#pragma once

#include "Define.h"

class ClientInfo
{
public:
	ClientInfo(int ClientNum = -1);
	ClientInfo(const SOCKET& s) :
		m_sClientSocket(s),
		m_iRemainDataLen(0),
		m_iClientNum(-1)
	{}

	virtual ~ClientInfo() {}

public:
	void RecvProcess(const DWORD& bytes, EXP_OVER* exp);
	
	void SendProcess();

public:
	SOCKET& GetSocket() { return m_sClientSocket; }
	int GetRemainDataLen() { return m_iRemainDataLen; }
	int GetClientNum() { return m_iClientNum; }

	void SetSocket(const SOCKET& s) { m_sClientSocket = s; }
	void SetRemainDataLen(int len) { m_iRemainDataLen = len; }
	void SetClientNum(int num) { m_iClientNum = num; }

private:
	void Recv();

	void Send();

protected:
	SOCKET m_sClientSocket;

	int m_iRemainDataLen;

	int m_iClientNum;
};


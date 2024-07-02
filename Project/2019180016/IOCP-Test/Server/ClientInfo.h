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
	// Return True if Dead
	bool TakeDamage(float damage);
	void Heal(float HealAmount);


	SOCKET& GetSocket()							{ return ClientSocket; }
	int GetRemainDataLen()						{ return RemainDataLen; }
	const int GetClientNum()					{ return ClientNum; }
	//int GetRoomNum()							{ return m_iRoomNum; }
	//void GetPos(float& x, float& y, float& z)	{ x = PosX; y = PosY; z = PosZ; }
	EXP_OVER* GetExp() { return &ExpOver; }

	void SetSocket(const SOCKET& s)			{ ClientSocket = s; }
	void SetRemainDataLen(int len)			{ RemainDataLen = len; }
	void SetClientNum(int num)				{ ClientNum = num; }
	//void SetRoomNum(int num)				{ m_iRoomNum = num; }
	//void SetPos(float x, float y, float z)	{ PosX = x; PosY = y; PosZ = z; }

	// Gaming data, later separated
	ECharacter GetECharacter() { return SelectInfo; }
	float GetCurrnetHp() { return CurrentHp; }
	ECharacterState GetState() { return State; }

	void SetECharacter(ECharacter c) { SelectInfo = c; }
	void SetState(ECharacterState state)	{ State = state; }

protected:
	SOCKET ClientSocket;

	int RemainDataLen;

	int ClientNum;
	//int m_iRoomNum;

	EXP_OVER ExpOver;

	// Gaming data, later separated
	float MaxHP;
	std::atomic<float> CurrentHp;
	ECharacter SelectInfo;
	ECharacterState State;
};


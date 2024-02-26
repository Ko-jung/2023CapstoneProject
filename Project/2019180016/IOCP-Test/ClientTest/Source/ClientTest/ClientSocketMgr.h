// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HAL/Runnable.h"

// winsock2 ����� ���� �Ʒ� �ڸ�Ʈ �߰�
#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
#include <iostream>
#include <map>

#include "../../Packet/Packet.h"

using namespace std;

class AClientController;

#define	MAX_BUFFER		512
#define SERVER_PORT		8000
#define SERVER_IP		"127.0.0.1"
#define MAX_CLIENTS		100

// ���� ��� ����ü
struct stSOCKETINFO
{
	WSAOVERLAPPED	overlapped;
	WSABUF			dataBuf;
	SOCKET			socket;
	char			messageBuffer[MAX_BUFFER];
	int				recvBytes;
	int				sendBytes;
};

// ��Ŷ ����
enum EPacketType
{
	LOGIN,
	ENROLL_PLAYER,
	SEND_PLAYER,
	RECV_PLAYER,
	LOGOUT_PLAYER,
	HIT_PLAYER,
	DAMAGED_PLAYER,
	CHAT,
	ENTER_NEW_PLAYER,
	SIGNUP,
	HIT_MONSTER,
	SYNC_MONSTER,
	SPAWN_MONSTER,
	DESTROY_MONSTER
};

// �÷��̾� ����
class cCharacter {
public:
	cCharacter() {};
	~cCharacter() {};

	//int SessionId;

	FVector Location;
	FRotator Rotate;
};

// �÷��̾� ����ȭ/������ȭ Ŭ����
class cCharactersInfo
{
public:
	cCharactersInfo() {};
	~cCharactersInfo() {};

	map<int, cCharacter> players;
};

// ���� ����
class Monster
{
public:
	float	X;				// X��ǥ
	float	Y;				// Y��ǥ
	float	Z;				// Z��ǥ
	float	Health;			// ü��
	int		Id;				// ���� id
	bool	IsAttacking;		// Ÿ��������

	friend ostream& operator<<(ostream& stream, Monster& info)
	{
		stream << info.X << endl;
		stream << info.Y << endl;
		stream << info.Z << endl;
		stream << info.Health << endl;
		stream << info.Id << endl;
		stream << info.IsAttacking << endl;

		return stream;
	}

	friend istream& operator>>(istream& stream, Monster& info)
	{
		stream >> info.X;
		stream >> info.Y;
		stream >> info.Z;
		stream >> info.Health;
		stream >> info.Id;
		stream >> info.IsAttacking;

		return stream;
	}
};

// ���� ����ȭ/������ȭ Ŭ����
class MonsterSet
{
public:
	map<int, Monster> monsters;

	friend ostream& operator<<(ostream& stream, MonsterSet& info)
	{
		stream << info.monsters.size() << endl;
		for (auto& kvp : info.monsters)
		{
			stream << kvp.first << endl;
			stream << kvp.second << endl;
		}

		return stream;
	}

	friend istream& operator>>(istream& stream, MonsterSet& info)
	{
		int nMonsters = 0;
		int PrimaryId = 0;
		Monster monster;
		info.monsters.clear();

		stream >> nMonsters;
		for (int i = 0; i < nMonsters; i++)
		{
			stream >> PrimaryId;
			stream >> monster;
			info.monsters[PrimaryId] = monster;
		}

		return stream;
	}
};

class ObjectInfo
{
public:
	ObjectInfo() { Location = FVector(0.f, 0.f, 0.f); }

	FVector Location;
	// float	X;				// X��ǥ
	// float	Y;				// Y��ǥ
	// float	Z;				// Z��ǥ
};

/**
 * 
 */
class CLIENTTEST_API ClientSocketMgr : public FRunnable
{
public:
	ClientSocketMgr();
	~ClientSocketMgr();

	void SetGamemode(class ASocketMode* gamemode) { Gamemode = gamemode; };

// Socket Function
public:
	void Send(int packetsize, Packet* packet);

	// ���� ��� �� ����
	bool InitSocket();
	// ������ ����
	bool Connect(const char* pszIP, int nPort);

	void Disconnect();
	// ȸ������
	//bool SignUp(const FText& Id, const FText& Pw);
	// ������ �α���
	//bool Login(const FText& Id, const FText& Pw);
	// �ʱ� ĳ���� ���
	//void EnrollPlayer(cCharacter& info);
	// ĳ���� ����ȭ
	void SendPlayerInfo(FTransform transform);
	// ĳ���� �α׾ƿ�
	//void LogoutPlayer(const int& SessionId);
	// ĳ���� �ǰ� ó��
	//void HitPlayer(const int& SessionId);
	// ���� �ǰ� ó��
	//void HitMonster(const int& MonsterId);
	// ä�� 
	void SendChat(const int& SessionId, const string& Chat);

// FRunnable Function
public:
	FRunnableThread* Thread;
	FThreadSafeCounter StopTaskCounter;

	// ������ ���� �� ����
	bool StartListen();
	void StopListen();

	virtual bool Init() override;
	virtual uint32 Run() override;
	virtual void Stop() override;
	virtual void Exit() override;

public:
	static ClientSocketMgr* Instance()
	{
		static ClientSocketMgr Instance;
		return &Instance;
	}

	ObjectInfo* TempCube;

private:
	SOCKET	m_ServerSocket;				// ������ ������ ����
	char 	m_sRecvBuffer[MAX_BUFFER];
	char 	m_sSendBuffer[MAX_BUFFER];

	UPROPERTY(BlueprintReadWrite)
	AClientController* m_PlayerController;

	int SerialNum;

	ASocketMode* Gamemode;

	PPlayerJoin NewPlayerJoin;
};

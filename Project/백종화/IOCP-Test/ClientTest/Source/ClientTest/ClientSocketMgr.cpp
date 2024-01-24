// Fill out your copyright notice in the Description page of Project Settings.


#include "ClientSocketMgr.h"
#include <cstring>

ClientSocketMgr::ClientSocketMgr() :
	m_PlayerController(nullptr),
	StopTaskCounter(0),
	Thread(nullptr)
{
}

ClientSocketMgr::~ClientSocketMgr()
{
	delete Thread;
	Thread = nullptr;

	closesocket(m_ServerSocket);
	WSACleanup();
}

bool ClientSocketMgr::InitSocket()
{
	WSADATA wsaData;
	// 윈속 버전을 2.2로 초기화
	int nRet = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (nRet != 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Socket Init Error"));
		return false;
	}

	// TCP 소켓 생성	
	m_ServerSocket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	if (m_ServerSocket == INVALID_SOCKET)
	{
		UE_LOG(LogTemp, Warning, TEXT("TCP Socket Error"));
		return false;
	}

	UE_LOG(LogTemp, Warning, TEXT("Socket Init Success"));
	return true;
}

bool ClientSocketMgr::Connect(const char* pszIP, int nPort)
{
	// 접속할 서버 정보를 저장할 구조체
	SOCKADDR_IN stServerAddr;

	stServerAddr.sin_family = AF_INET;
	// 접속할 서버 포트 및 IP
	stServerAddr.sin_port = htons(nPort);
	stServerAddr.sin_addr.s_addr = inet_addr(pszIP);

	int nRet = connect(m_ServerSocket, (sockaddr*)&stServerAddr, sizeof(sockaddr));
	if (nRet == SOCKET_ERROR)
	{
		UE_LOG(LogTemp, Warning, TEXT("Socket Connect Fail"));
		return false;
	}

	UE_LOG(LogTemp, Warning, TEXT("Socket Connect Success"));
	return true;
}

void ClientSocketMgr::SendChat(const int& SessionId, const string& Chat)
{
}

bool ClientSocketMgr::StartListen()
{
	// 스레드 시작
	if (Thread != nullptr) return false;
	Thread = FRunnableThread::Create(this, TEXT("BlockingConnectThread"), 0, TPri_BelowNormal);
	return (Thread != nullptr);
}

void ClientSocketMgr::StopListen()
{
	// 스레드 종료
	Stop();
	Thread->WaitForCompletion();
	Thread->Kill();
	delete Thread;
	Thread = nullptr;
	StopTaskCounter.Reset();
}

bool ClientSocketMgr::Init()
{
	return true;
}

uint32 ClientSocketMgr::Run()
{
	// 초기 init 과정을 기다림
	FPlatformProcess::Sleep(0.03);
	// recv while loop 시작
	// StopTaskCounter 클래스 변수를 사용해 Thread Safety하게 해줌
	// while (StopTaskCounter.GetValue() == 0 /*&& m_PlayerController != nullptr*/)
	for (int i = 0; i < 50; i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("adasd"));
		stringstream RecvStream;
		//int PacketType;
		int nRecvLen = recv(m_ServerSocket, (CHAR*)&m_sRecvBuffer, MAX_BUFFER, 0);

		if (nRecvLen > 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("Message Is: %s"), m_sRecvBuffer);
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("Recv Close"));
	return 0;
}

void ClientSocketMgr::Stop()
{
	// thread safety 변수를 조작해 while loop 가 돌지 못하게 함
	StopTaskCounter.Increment();
}

void ClientSocketMgr::Exit()
{
}

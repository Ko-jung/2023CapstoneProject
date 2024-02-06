#pragma once

#include <WS2tcpip.h>
#include <MSWSock.h>
#include <WinSock2.h>
#include <thread>
#include <vector>
#include <array>
#include <iostream>

#include <functional>
#include <unordered_map>

#include "../Packet/Packet.h"

#pragma comment(lib, "MSWSock.lib")
#pragma comment(lib, "ws2_32.lib")

#define BUFSIZE 2024
#define MAXCLIENT 2000

using std::cout;
using std::endl;

class EXP_OVER
{
public:
	WSAOVERLAPPED _wsa_over;				// IOCP 구조체
	COMP_OP		  _comp_op;					// 이벤트 구분
	WSABUF		  _wsa_buf;					// 송수신시 실제 데이터가 저장되는 공간
	int target_id;							// (내가추가)
	int room_id;							// (내가추가)
											//
	// 송수신용 버퍼						//
	char _net_buf[BUFSIZE];					// Recv 전 패킷 재조립하여 저장되는 위치. 실질적 사용 버퍼.

public:
	EXP_OVER(COMP_OP comp_op, char num_bytes, void* mess) : _comp_op(comp_op)
	{
		ZeroMemory(&_wsa_over, sizeof(_wsa_over));
		_wsa_buf.buf = reinterpret_cast<char*>(_net_buf);
		_wsa_buf.len = num_bytes;
		memcpy(_net_buf, mess, num_bytes);
	};
	EXP_OVER(COMP_OP comp_op) :_comp_op(comp_op) {}
	EXP_OVER() { _comp_op = COMP_OP::OP_RECV; }
	~EXP_OVER() {}
};
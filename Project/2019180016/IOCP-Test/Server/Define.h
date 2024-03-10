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

#include "../../../Packet/Packet.h"

#pragma comment(lib, "MSWSock.lib")
#pragma comment(lib, "ws2_32.lib")

#define BUFSIZE 128
#define MAXCLIENT 2100
#define MAXROOM 350
#define MAXPLAYER 6

using std::cout;
using std::endl;

class EXP_OVER
{
public:
	WSAOVERLAPPED _wsa_over;				// IOCP ����ü
	COMP_OP		  _comp_op;					// �̺�Ʈ ����
	WSABUF		  _wsa_buf;					// �ۼ��Ž� ���� �����Ͱ� ����Ǵ� ����
	int target_id;							// (�����߰�)
	int room_id;							// (�����߰�)
											//
	// �ۼ��ſ� ����						//
	char _net_buf[BUFSIZE];					// Recv �� ��Ŷ �������Ͽ� ����Ǵ� ��ġ. ������ ��� ����.

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
#pragma once

#include "../Common/Define.h"
#include <array>

class ClientInfo;

class RoomMgr
{
public:
	RoomMgr() : m_iMemberCount(0) {}
	RoomMgr(std::array<ClientInfo*, MAXPLAYER> member) : m_iMemberCount(6) { m_RoomMembers = member; }
	~RoomMgr() {}

	void AddMember(ClientInfo* c);

private:
	std::array<ClientInfo*, MAXPLAYER> m_RoomMembers;
	BYTE m_iMemberCount;
};


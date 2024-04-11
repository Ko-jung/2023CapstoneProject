#include "RoomMgr.h"

void RoomMgr::AddMember(ClientInfo* c)
{
	m_RoomMembers[m_iMemberCount++] = c;
}

#include "PacketMgr.h"

#include "ClientMgr.h"
#include "../LobbyClientInfo.h"

PacketMgr::PacketMgr()
{
}

void PacketMgr::ProcessPacket(Packet* p, LobbyClientInfo* c)
{
	switch (p->PacketType)
	{
	case (int)COMP_OP::OP_DISCONNECT:
		ClientMgr::Instance()->Disconnect(c->ClientNum);
		break;
	case (int)COMP_OP::OP_STARTMATCHING:
		ClientMgr::Instance()->ProcessStartMatching(c);
		break;
	case (int)COMP_OP::OP_CANCLEMATCHING:
		//m_MatchingQueue.push(m_Clients[id]);
		//CheckingMatchingQueue();
		break;
	case (int)COMP_OP::OP_TRYLOGIN:
		ClientMgr::Instance()->ProcessTryLogin(c, reinterpret_cast<PTryLogin*>(p));
		break;
	case (int)COMP_OP::OP_SERVERINFO:
		ClientMgr::Instance()->NewGameServerConnect(c->ClientNum);
		break;
	default:
		std::cout << "PacketMgr::ProcessPacket p->PacketType is DEFAULT" << std::endl;
		break;
	}
}

#include "RoomMgr.h"
#include "../Room.h"

RoomMgr::RoomMgr()
{
}

RoomMgr::~RoomMgr()
{
	for (auto& r : Rooms)
	{
		delete r;
	}
}

void RoomMgr::AddRoom(int roomId)
{
	Rooms[roomId] = new Room;
}

void RoomMgr::DeleteRoom(int roomId)
{
	delete Rooms[roomId];
	Rooms[roomId] = nullptr;
}

void RoomMgr::AddKillCount(int DeathTargetId)
{
	// Target's Room Id
	int roomId = DeathTargetId / MAXPLAYER;

	// Target's SeralNum (in Game)
	int PlayerSerialNum = DeathTargetId % MAXPLAYER;

	 //Is TeamA? or TeamB?
	bool isTeamA = PlayerSerialNum < (MAXPLAYER / 2);

	Rooms[roomId]->AddKillCount(isTeamA);
}

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

void RoomMgr::StartTime(int roomId)
{
	Rooms[roomId]->SetStartTime();
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

void RoomMgr::IncreaseTileDropLevel(int roomId)
{
	return Rooms[roomId]->IncreaseTileDropLevel();
}

BYTE* RoomMgr::GetBuildingExist(int roomId, int& size)
{
	return Rooms[roomId]->GetBuildingExist(size);
}

int RoomMgr::GetTileDropLevelAndIncrease(int roomId)
{
	BYTE TileDropLevel = Rooms[roomId]->GetTileDropLevel();
	Rooms[roomId]->IncreaseTileDropLevel();
	return TileDropLevel;
}

int RoomMgr::GetTileDropLevel(int roomId)
{
	return Rooms[roomId]->GetTileDropLevel();
}

float RoomMgr::GetRoomElapsedTime(int roomId)
{
	return Rooms[roomId]->GetRoomElapsedTime();
}

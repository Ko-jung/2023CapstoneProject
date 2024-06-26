#include "RoomMgr.h"
#include "../Room.h"

#include "TimerMgr.h"
#include "ClientMgr.h"

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

	for (int i = 0; i < 3; i++)
	{
		TimerEvent ItemSpawnTimer{ std::chrono::seconds(20 + 300 * (i) + SELECTTIMESECOND),
			std::bind(&RoomMgr::SendItemSpawn, this, roomId) };
		TimerMgr::Instance()->Insert(ItemSpawnTimer);
	}
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

int RoomMgr::IsEndGame(int roomId)
{
	return Rooms[roomId]->IsEndGame();
}

int RoomMgr::CharacterDead(int ClientId)
{
	return Rooms[ClientId / MAXPLAYER]->CharacterDead(ClientId % MAXPLAYER);
}

BYTE* RoomMgr::GetBuildingExist(int roomId, int& size)
{
	const std::vector<TileProperty>& BuildingExist = Rooms[roomId]->GetBuildingExist();
	BYTE* ReturnExist = new BYTE[37];
	for (int i = 0; i < BuildingExist.size(); i++)
	{
		ReturnExist[i] = BuildingExist[i].TileType;
	}
	size = BuildingExist.size();
	return ReturnExist;
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

int RoomMgr::GetTileDropCenterIndex(const int roomId, int& CenterIndex)
{
	return Rooms[roomId]->GetTileDropCenterIndex(CenterIndex);
}

void RoomMgr::RequestSendItemSpawn(int roomId)
{
	SendItemSpawn(roomId);
}

void RoomMgr::SendItemSpawn(int roomId)
{
	std::vector<PItemInfo> Items;
	Rooms[roomId]->SpawnItem(Items);

   	if (Items.empty())
	{
		LogUtil::PrintLog("RoomMgr::SendItemSpawn(int roomId) Error!");
	}

	PSpawnItem PSI(Items.size());
	for (int i = 0; i < Items.size(); i++)
	{
		PSI.Item[i].TileIndex = Items[i].TileIndex;
		PSI.Item[i].Floor = Items[i].Floor;
		PSI.Item[i].Effect = Items[i].Effect;
		PSI.Item[i].ItemLevel = Items[i].ItemLevel;
	}

	ClientMgr::Instance()->SendPacketToAllSocketsInRoom(roomId, &PSI, sizeof(PSI));
}

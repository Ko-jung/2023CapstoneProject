#pragma once

#include "../../Common/Define.h"
#include <array>

class Room;

// Room 생성 및 파괴 시 Data Race 없게 코딩 필요
class RoomMgr
{
	SingleTon(RoomMgr);

public:
	RoomMgr();
	~RoomMgr();

	void AddRoom(int roomId);
	void DeleteRoom(int roomId);
	void StartTime(int roomId);

	void AddKillCount(int DeathTargetId);
	void IncreaseTileDropLevel(int roomId);

	BYTE* GetBuildingExist(int roomId, int& size);
	int GetTileDropLevelAndIncrease(int roomId);
	int GetTileDropLevel(int roomId);
	float GetRoomElapsedTime(int roomId);
	int GetTileDropCenterIndex(const int roomId, int& CenterIndex);

private:
	std::array<Room*, MAXROOM> Rooms{ nullptr, };
};


#pragma once

#include "../../Common/Define.h"
#include <array>

class Room;

// Room ���� �� �ı� �� Data Race ���� �ڵ� �ʿ�
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


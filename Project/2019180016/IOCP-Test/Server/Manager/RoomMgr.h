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

	void AddKillCount(int DeathTargetId);

	BYTE* GetBuildingExist(int roomId, int& size);

private:
	std::array<Room*, MAXPLAYER> Rooms{ nullptr, };
};


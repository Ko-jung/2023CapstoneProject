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

	void AddKillCount(int DeathTargetId);

private:
	std::array<Room*, MAXPLAYER> Rooms{ nullptr, };
};


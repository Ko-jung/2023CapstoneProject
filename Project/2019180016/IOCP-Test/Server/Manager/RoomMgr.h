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
	//void RemoveItem(int roomId);

	void AddKillCount(int DeathTargetId);
	void IncreaseTileDropLevel(int roomId);
	int IsEndGame(int roomID);

	// 타일드랍 3단계부터 스폰불가, 팀 전체가 죽어있는지 판단
	int CharacterDead(int ClientId);

	BYTE* GetBuildingExist(int roomId, int& size);
	int GetTileDropLevelAndIncrease(int roomId);
	int GetTileDropLevel(int roomId);
	float GetRoomElapsedTime(int roomId);
	int GetTileDropCenterIndex(const int roomId, int& CenterIndex);
	const WORD GetNowSkillActorSerial(int RoomId);

	void RequestSendItemSpawn(int roomId);

private:
	// Timer Func
	void SendItemSpawn(int roomId);

	std::array<Room*, MAXROOM> Rooms{ nullptr, };
};


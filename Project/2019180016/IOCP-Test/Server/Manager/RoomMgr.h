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
	//void RemoveItem(int roomId);

	void AddKillCount(int DeathTargetId);
	void IncreaseTileDropLevel(int roomId);
	int IsEndGame(int roomID);

	// Ÿ�ϵ�� 3�ܰ���� �����Ұ�, �� ��ü�� �׾��ִ��� �Ǵ�
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


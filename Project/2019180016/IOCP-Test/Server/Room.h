#pragma once

#include <array>
#include <atomic>
#include <vector>
#include <Windows.h>
#include <chrono>

constexpr int TILE_MIDDLE_COUNT = 1;
constexpr int TILE_SECTION3_COUNT = 6;
constexpr int TILE_SECTION2_COUNT = 12;
constexpr int TILE_SECTION1_COUNT = 18;

constexpr int BUILDING_MIDDLE_COUNT = 1;
constexpr int BUILDING_SECTION3_COUNT = 0;	// +2 SpawnBuilding
constexpr int BUILDING_SECTION2_COUNT = 4;
constexpr int BUILDING_SECTION1_COUNT = 6;	// +2 SpawnBuilding

constexpr int FLOATING_TILE_SECTION3_COUNT = 1;
constexpr int FLOATING_TILE_SECTION2_COUNT = 2;
constexpr int FLOATING_TILE_SECTION1_COUNT = 4;

class Room
{
	enum class ETEAM : BYTE {A, B};
	enum class ESETION : BYTE { MIDDLE, SECTION3, SECTION2, SECTION1 };
	enum class ETILETYPE : BYTE { NONTILE, BUILDING, FLOATINGTILE, SPAWNBUILDING_A, SPAWNBUILDING_B };

public:
	Room();
	~Room() {}

	void IncreaseTileDropLevel() { ++TileDropLevel; }
	void AddKillCount(bool IsTeamA);
	void SetStartTime();

	BYTE* GetBuildingExist(int& size);
	BYTE GetTileDropLevel() { return TileDropLevel; }
	float GetRoomElapsedTime();			// 게임이 시작하고 경과시간

	void SpawnItem(int ItemCount);

private:
	std::array<std::atomic<int>, 2> KillScore;
	int TileDropLevel;
	std::chrono::system_clock::time_point RoomStartTime;
	
	/// <summary>
	/// <para>If 0, No TileActor(Building, Floating) </para>
	/// <para>1, Building </para>
	/// <para>2, Floating Tile </para>
	/// 
	/// <para>Index [0] : Middle </para>
	/// <para>[1, 6] : Section3 </para>
	/// <para>[7, 18] : Section2 </para>
	/// <para>[19, 36] : Section1 </para>
	/// </summary>
	BYTE BuildingExist[TILE_MIDDLE_COUNT + TILE_SECTION1_COUNT + TILE_SECTION2_COUNT + TILE_SECTION3_COUNT];

	// 아이템 정보


};


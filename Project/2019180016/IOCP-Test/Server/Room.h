#pragma once

#include <array>
#include <atomic>
#include <vector>
#include <Windows.h>

constexpr int TILE_MIDDLE_COUNT = 1;
constexpr int TILE_SECTION3_COUNT = 6;
constexpr int TILE_SECTION2_COUNT = 12;
constexpr int TILE_SECTION1_COUNT = 18;

constexpr int BUILDING_MIDDLE_COUNT = 1;
constexpr int BUILDING_SECTION3_COUNT = 2;
constexpr int BUILDING_SECTION2_COUNT = 6;
constexpr int BUILDING_SECTION1_COUNT = 8;

constexpr int FLOATING_TILE_SECTION3_COUNT = 1;
constexpr int FLOATING_TILE_SECTION2_COUNT = 2;
constexpr int FLOATING_TILE_SECTION1_COUNT = 4;

// 한 Section에 포함되어있는 건물들
//struct TileInfo
//{
//	BYTE TileSumCount;
//	BYTE TileCount;
//	BYTE BuildingCount;
//	BYTE FloatingCount;
//	TileInfo(int t, int b, int f) : TileSumCount(t), BuildingCount(b), FloatingCount(f) {}
//};

class Room
{
	enum class ETEAM : BYTE {A, B};
	enum class ESETION : BYTE { MIDDLE, SECTION3, SECTION2, SECTION1 };
	enum class ETILETYPE : BYTE { NONTILE, BUILDING, FLOATINGTILE };

	// Section까지 포함된 타일과 관련된 개수들
	// static TileInfo Tiles[4];
public:
	Room();
	~Room() {}

	void AddKillCount(bool IsTeamA);
	BYTE* GetBuildingExist(int& size);

private:
	std::array<std::atomic<int>, 2> KillScore;

	// 건물 정보
	//std::array<bool, BUILDING_MIDDLE_COUNT + BUILDING_SECTION1_COUNT + BUILDING_SECTION2_COUNT + BUILDING_SECTION3_COUNT>BuildingExist;
	//BYTE BuildingLocation[3];
	
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


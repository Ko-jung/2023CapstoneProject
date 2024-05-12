#pragma once

#include <array>
#include <atomic>
#include <vector>
#include <Windows.h>
#include <chrono>
	
//#define ContiguousTiles

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

struct TileProperty
{
	BYTE TileType;
	BYTE SectionLevel;
	float PosX;
	float PosY;

	TileProperty() : TileType(0), SectionLevel(0), PosX(0.f), PosY(0.f) {}
	TileProperty(BYTE type, BYTE level, float x, float y) : TileType(type), SectionLevel(level), PosX(x), PosY(y) {}
};

class Room
{
	enum class ETEAM : BYTE {A, B};
	enum class ESETION : BYTE { MIDDLE, SECTION3, SECTION2, SECTION1 };
	enum class ETILETYPE : BYTE { NONBUILDING, BUILDING, FLOATINGTILE, SPAWNBUILDING_A, SPAWNBUILDING_B, BREAKTILE };
	static const int TileCount = TILE_MIDDLE_COUNT + TILE_SECTION1_COUNT + TILE_SECTION2_COUNT + TILE_SECTION3_COUNT;

public:
	Room();
	~Room() {}

	void IncreaseTileDropLevel() { ++TileDropLevel; }
	void AddKillCount(bool IsTeamA);
	void SetStartTime();

	BYTE GetTileDropLevel() { return TileDropLevel; }
	float GetRoomElapsedTime();			// 게임이 시작하고 경과시간
	int GetTileDropCenterIndex(int& CenterIndex);

	void GetTilePos(const int Index, float& X, float& Y);
	double Distance(float x1, float y1, float x2, float y2);

	void SpawnItem(std::vector<struct ItemInfo>& TileIndex);

private:
	std::array<std::atomic<int>, 2> KillScore;
	std::array<int, 3> CenterTileIndex;
	int TileDropLevel;
	std::chrono::system_clock::time_point RoomStartTime;
	int ItemSerial;

#ifdef ContiguousTiles
public:
	BYTE* GetBuildingExist(int& size);

private:
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

#else
public:
	const std::vector<TileProperty>& GetBuildingExist() { return BuildingExist; }

private:
	std::vector<TileProperty> BuildingExist;
	void CalculateLocation(const BYTE AngleCount, const BYTE Distance, float& x, float& y);
	TileProperty* GetLineTileFromAngleAndDistance(BYTE FindAngle, BYTE FindDistance,
							float FindTileLocationX, float FindTileLocationY, int& CenterIndex);
	void SpawnBuildings(const BYTE& SpawnCount, const BYTE& SectionLevel);
	void SpawnFloatingTiles(const BYTE& SpawnCount, const BYTE& SectionLevel);
	void SpawnTeamBuilding(const BYTE& SectionLevel);
#endif // ContiguousTiles



	// 아이템 정보


};


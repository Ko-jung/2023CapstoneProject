#include "Room.h"
#include "RandomUtil.h"

//TileInfo Room::Tiles[4] = { 
//	TileInfo(TILE_MIDDLE_COUNT,
//				BUILDING_MIDDLE_COUNT,
//				0),
//	TileInfo(TILE_MIDDLE_COUNT + TILE_SECTION3_COUNT,
//				BUILDING_SECTION3_COUNT,
//				FLOATING_TILE_SECTION3_COUNT),
//	TileInfo(TILE_MIDDLE_COUNT + TILE_SECTION3_COUNT + TILE_SECTION2_COUNT,
//				BUILDING_SECTION2_COUNT,
//				FLOATING_TILE_SECTION2_COUNT),
//	TileInfo(TILE_MIDDLE_COUNT + TILE_SECTION3_COUNT + TILE_SECTION2_COUNT + TILE_SECTION1_COUNT,
//				BUILDING_SECTION1_COUNT,
//				FLOATING_TILE_SECTION1_COUNT),
//};

Room::Room()
{
	KillScore[0] = KillScore[1] = 0;

	memset(BuildingExist, (BYTE)ETILETYPE::NONTILE, sizeof(BuildingExist));

	// Middle Section
	BuildingExist[0] = (BYTE)(BYTE)ETILETYPE::BUILDING;

	//for (int j = 0; j < 4; j++)
	//{
	//	auto RandInt = RandomUtil::RandUniqueInt(0, TILE_SECTION1_COUNT - 1, BUILDING_SECTION1_COUNT + FLOATING_TILE_SECTION1_COUNT);
	//	int i = 0;
	//	for (; i < BUILDING_SECTION1_COUNT; i++)	// Set BUILDING
	//	{
	//		BuildingExist[Tiles[j].TileSumCount + RandInt[i]] = (BYTE)ETILETYPE::BUILDING;
	//	}
	//	for (; i < FLOATING_TILE_SECTION1_COUNT; i++)	// Set FLOATING TILE
	//	{
	//		BuildingExist[Tiles[j].TileSumCount + RandInt[i]] = (BYTE)ETILETYPE::FLOATINGTILE;
	//	}
	//}

	// Section3
	auto RandInt = RandomUtil::RandUniqueInt(0, TILE_SECTION3_COUNT - 1, BUILDING_SECTION3_COUNT + FLOATING_TILE_SECTION3_COUNT);
	int i = 0;
	for (; i < BUILDING_SECTION3_COUNT; i++)	// Set BUILDING
	{
		BuildingExist[TILE_MIDDLE_COUNT + RandInt[i]] = (BYTE)ETILETYPE::BUILDING;
	}
	for (; i < BUILDING_SECTION3_COUNT + FLOATING_TILE_SECTION3_COUNT; i++)	// Set FLOATING TILE
	{
		BuildingExist[TILE_MIDDLE_COUNT + RandInt[i]] = (BYTE)ETILETYPE::FLOATINGTILE;
	}
	
	// Section2
	RandInt = RandomUtil::RandUniqueInt(0, TILE_SECTION2_COUNT - 1, BUILDING_SECTION2_COUNT + FLOATING_TILE_SECTION2_COUNT);
	i = 0; 
	for (; i < BUILDING_SECTION2_COUNT; i++)	// Set BUILDING
	{
		BuildingExist[TILE_MIDDLE_COUNT + TILE_SECTION3_COUNT + RandInt[i]] = (BYTE)ETILETYPE::BUILDING;
	}
	for (; i < BUILDING_SECTION2_COUNT + FLOATING_TILE_SECTION2_COUNT; i++)	// Set FLOATING TILE
	{
		BuildingExist[TILE_MIDDLE_COUNT + TILE_SECTION3_COUNT + RandInt[i]] = (BYTE)ETILETYPE::FLOATINGTILE;
	}

	// Section1
	RandInt = RandomUtil::RandUniqueInt(0, TILE_SECTION1_COUNT - 1, BUILDING_SECTION1_COUNT + FLOATING_TILE_SECTION1_COUNT);
	i = 0;
	for (; i < BUILDING_SECTION1_COUNT; i++)	// Set BUILDING
	{
		BuildingExist[TILE_MIDDLE_COUNT + TILE_SECTION3_COUNT + TILE_SECTION2_COUNT + RandInt[i]] = (BYTE)ETILETYPE::BUILDING;
	}
	for (; i < BUILDING_SECTION1_COUNT + FLOATING_TILE_SECTION1_COUNT; i++)	// Set FLOATING TILE
	{
		BuildingExist[TILE_MIDDLE_COUNT + TILE_SECTION3_COUNT + TILE_SECTION2_COUNT + RandInt[i]] = (BYTE)ETILETYPE::FLOATINGTILE;
	}
}

void Room::AddKillCount(bool IsTeamA)
{
	while (true)
	{
		if (IsTeamA)
		{
			int score = KillScore[(int)ETEAM::A];
			bool IsSucc = std::atomic_compare_exchange_strong(
				&KillScore[(int)ETEAM::A],
				&score,
				score + 1);

			if (IsSucc) return;
		}
		else
		{
			int score = KillScore[(int)ETEAM::B];
			bool IsSucc = std::atomic_compare_exchange_strong(
				&KillScore[(int)ETEAM::B],
				&score,
				score + 1);

			if (IsSucc) return;
		}
	}
}

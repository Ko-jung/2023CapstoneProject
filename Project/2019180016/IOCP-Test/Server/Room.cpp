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

	// SpawnBuilding의 한 위치를 잡아서 그 위치를 기준으로 4개 빌딩을 제작
	auto SpawnRand = RandomUtil::RandUniqueInt(0, TILE_SECTION3_COUNT - 1, 1);
	int APos = SpawnRand[0];
	int BPos;		// APos의 반대편

	// Section3
	BPos = (SpawnRand[0] + TILE_SECTION3_COUNT / 2) % TILE_SECTION3_COUNT;
	BuildingExist[TILE_MIDDLE_COUNT + APos] = (BYTE)ETILETYPE::SPAWNBUILDING_A;
	BuildingExist[TILE_MIDDLE_COUNT + BPos] = (BYTE)ETILETYPE::SPAWNBUILDING_B;

	auto RandInt = RandomUtil::RandUniqueInt(0, TILE_SECTION3_COUNT - 1, BUILDING_SECTION3_COUNT + FLOATING_TILE_SECTION3_COUNT,
												std::vector<int>{APos, BPos});
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
	BPos = (SpawnRand[0] + TILE_SECTION1_COUNT / 2) % TILE_SECTION1_COUNT;
	BuildingExist[TILE_MIDDLE_COUNT + TILE_SECTION3_COUNT + TILE_SECTION2_COUNT + APos] = (BYTE)ETILETYPE::SPAWNBUILDING_A;
	BuildingExist[TILE_MIDDLE_COUNT + TILE_SECTION3_COUNT + TILE_SECTION2_COUNT + BPos] = (BYTE)ETILETYPE::SPAWNBUILDING_B;
	RandInt = RandomUtil::RandUniqueInt(0, TILE_SECTION1_COUNT - 1, BUILDING_SECTION1_COUNT + FLOATING_TILE_SECTION1_COUNT,
								std::vector<int>{APos, BPos});
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
	//while (true)
	//{
		if (IsTeamA)
		{
			++KillScore[(int)ETEAM::A];
			//int score = KillScore[(int)ETEAM::A];
			//bool IsSucc = std::atomic_compare_exchange_strong(
			//	&KillScore[(int)ETEAM::A],
			//	&score,
			//	score + 1);

			//if (IsSucc) return;
		}
		else
		{
			++KillScore[(int)ETEAM::B];
			//int score = KillScore[(int)ETEAM::B];
			//bool IsSucc = std::atomic_compare_exchange_strong(
			//	&KillScore[(int)ETEAM::B],
			//	&score,
			//	score + 1);

			//if (IsSucc) return;
		}
	//}
}

BYTE* Room::GetBuildingExist(int& size)
{
	size = TILE_MIDDLE_COUNT + TILE_SECTION1_COUNT + TILE_SECTION2_COUNT + TILE_SECTION3_COUNT;
	return BuildingExist;
}

void Room::SpawnItem(int ItemCount)
{

}

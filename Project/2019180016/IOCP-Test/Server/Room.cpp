#include "Room.h"
#include "RandomUtil.h"
#include <cmath>

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
	TileDropLevel = 0;

	memset(BuildingExist, (BYTE)ETILETYPE::NONBUILDING, sizeof(BuildingExist));

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

void Room::SetStartTime()
{
	RoomStartTime = std::chrono::system_clock::now();
}

BYTE* Room::GetBuildingExist(int& size)
{
	size = TILE_MIDDLE_COUNT + TILE_SECTION1_COUNT + TILE_SECTION2_COUNT + TILE_SECTION3_COUNT;
	return BuildingExist;
}

float Room::GetRoomElapsedTime()
{
	auto Now = std::chrono::system_clock::now();

	return std::chrono::duration<float>(Now - RoomStartTime).count();
}

int Room::GetTileDropCenterIndex(int& CenterIndex)
{
	if (TileDropLevel == 0)
	{
		CenterIndex = RandomUtil::RandRange(0, 6);
		float CenterX, CenterY;
		GetTilePos(CenterIndex, CenterX, CenterY);

		// 깨진타일 -1 처리 중앙, 3구역은 절대로 걸릴일이 없다
		for (int i = 0; i < TILE_SECTION2_COUNT; i++)
		{
			float TargetX, TargetY;
			int TargetIndex = i + TILE_MIDDLE_COUNT + TILE_SECTION3_COUNT;
			GetTilePos(TargetIndex, TargetX, TargetY);

			double Dist = Distance(TargetX, TargetY, CenterX, CenterY);
			if (Dist > 6.25)
			{
				BuildingExist[TargetIndex] = (BYTE)ETILETYPE::BREAKTILE;
			}
		}
		for (int i = 0; i < TILE_SECTION1_COUNT; i++)
		{
			float TargetX, TargetY;
			int TargetIndex = i + TILE_MIDDLE_COUNT + TILE_SECTION3_COUNT + TILE_SECTION2_COUNT;
			GetTilePos(TargetIndex, TargetX, TargetY);

			double Dist = Distance(TargetX, TargetY, CenterX, CenterY);
			if (Dist > 6.25)
			{
				BuildingExist[TargetIndex] = (BYTE)ETILETYPE::BREAKTILE;
			}
		}
	}
	else if(TileDropLevel == 1)
	{
		std::vector<int> CenterCandidateTile;
		CenterCandidateTile.reserve(TILE_MIDDLE_COUNT + TILE_SECTION3_COUNT);
		float CenterX, CenterY;
		// Prev Center Pos
		GetTilePos(CenterTileIndex[TileDropLevel - 1], CenterX, CenterY);

		// Push Candidate Index
		for (int i = 0; i < TileCount; i++)
		{
			if (BuildingExist[i] == (BYTE)ETILETYPE::BREAKTILE) continue;

			float TargetX, TargetY;
			GetTilePos(i, TargetX, TargetY);

			double Dist = Distance(TargetX, TargetY, CenterX, CenterY);
			if (Dist < 2.25)
			{
				CenterCandidateTile.push_back(i);
			}
		}

		CenterIndex = RandomUtil::RandVector(CenterCandidateTile);
		// Current Center Pos
		GetTilePos(CenterIndex, CenterX, CenterY);
		for (int i = 0; i < TileCount; i++)
		{
			if (BuildingExist[i] == (BYTE)ETILETYPE::BREAKTILE) continue;

			float TargetX, TargetY;
			GetTilePos(i, TargetX, TargetY);

			double Dist = Distance(TargetX, TargetY, CenterX, CenterY);
			if (Dist > 2.25)
			{
				BuildingExist[i] = (BYTE)ETILETYPE::BREAKTILE;
			}
		}
	}
	else
	{
		std::vector<int> CenterCandidateTile;
		CenterCandidateTile.reserve(TILE_MIDDLE_COUNT + TILE_SECTION3_COUNT);
		for (int i = 0; i < TileCount; i++)
		{
			if (BuildingExist[i] == (BYTE)ETILETYPE::BREAKTILE) continue;

			CenterCandidateTile.push_back(i);
		}
		CenterIndex = RandomUtil::RandVector(CenterCandidateTile);
		for (int i : CenterCandidateTile)
		{
			BuildingExist[i] = (BYTE)ETILETYPE::BREAKTILE;
		}
	}

	CenterTileIndex[TileDropLevel] = CenterIndex;
	IncreaseTileDropLevel();
	return TileDropLevel;
}

void Room::GetTilePos(const int Index, float& X, float& Y)
{
	int Distance;
	int TileCount;
	int IndexInSection;

	// Get SectionLevel Use Index
	int SectionLevel;
	if (Index == 0)																		SectionLevel = 0;
	else if (Index < TILE_MIDDLE_COUNT + TILE_SECTION3_COUNT)							SectionLevel = 3;
	else if (Index < TILE_MIDDLE_COUNT + TILE_SECTION3_COUNT + TILE_SECTION2_COUNT)		SectionLevel = 2;
	else																				SectionLevel = 1;

	if (SectionLevel == 3)
	{
		Distance = 1;
		IndexInSection = Index - TILE_MIDDLE_COUNT;
		TileCount = TILE_SECTION3_COUNT;
	}
	else if (SectionLevel == 2)
	{
		Distance = 2;
		IndexInSection = Index - (TILE_MIDDLE_COUNT + TILE_SECTION3_COUNT);
		TileCount = TILE_SECTION2_COUNT;
	}
	else if (SectionLevel == 1)
	{
		Distance = 3;
		IndexInSection = Index - (TILE_MIDDLE_COUNT + TILE_SECTION3_COUNT + TILE_SECTION2_COUNT);
		TileCount = TILE_SECTION1_COUNT;
	}
	else
	{
		// MIDDLE SECTION
		X = 0.f;
		Y = 0.f;
		return;
	}

	X = Distance * cos((2 * 3.1415 / TileCount) * IndexInSection);
	Y = Distance * sin((2 * 3.1415 / TileCount) * IndexInSection);
}

double Room::Distance(float x1, float y1, float x2, float y2)
{
	return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}

void Room::SpawnItem(int ItemCount)
{

}

#include "Room.h"
#include "RandomUtil.h"
#include <cmath>

#include "../../../Common/Packet.h"

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

#ifdef ContiguousTiles
	memset(BuildingExist, (BYTE)ETILETYPE::NONBUILDING, sizeof(BuildingExist));

	// Middle Section
	BuildingExist[0] = (BYTE)(BYTE)ETILETYPE::BUILDING;	

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

#else
	BuildingExist.reserve(TileCount);
	BuildingExist.emplace_back((BYTE)ETILETYPE::NONBUILDING, 0, 0.f, 0.f);

	{	// Set Building Pos
		for (int angle = 0; angle < 6; ++angle)	// 각도 6부분 타일에 대해
		{
			for (int distance = 1; distance < 4; ++distance)	// 중앙 타일로부터의 거리
			{
				{//60도 방면 위치에 StaticMesh 추가
					float x, y;
					CalculateLocation(angle, distance, x, y);
					BuildingExist.emplace_back((BYTE)ETILETYPE::NONBUILDING, 4 - distance, x, y);
				}

				// 60도 방면 사이 위치에 Static Mesh 추가
				for (int midCount = 2; midCount < distance + 1; ++midCount)
				{
					float FirstX, FirstY, SecX, SecY;
					CalculateLocation(angle, distance, FirstX, FirstY);
					CalculateLocation(angle + 1, distance, SecX, SecY);

					float RelatLocX = ((FirstX - SecX) / (float)distance) * (midCount - 1) + SecX;
					float RelatLocY = ((FirstY - SecY) / (float)distance) * (midCount - 1) + SecY;

					BuildingExist.emplace_back((BYTE)ETILETYPE::NONBUILDING, 4 - distance, RelatLocX, RelatLocY);
				}
			}
		}
	}
	
	{	// 스폰 빌딩 생성
		SpawnTeamBuilding(3);
		SpawnTeamBuilding(1);
	}

	{	// 각 구역별 빌딩 생성
		SpawnBuildings(6, 1);
		SpawnBuildings(4, 2);
		SpawnBuildings(1, 0);
	}

	{	// 각 구역별 부유 타일 생성
		SpawnFloatingTiles(4, 1);
		SpawnFloatingTiles(2, 2);
		SpawnFloatingTiles(1, 3);
	}

#endif // ContiguousTiles
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

float Room::GetRoomElapsedTime()
{
	auto Now = std::chrono::system_clock::now();

	return std::chrono::duration<float>(Now - RoomStartTime).count();
}

void Room::SpawnItem(std::vector<ItemInfo>& TileIndex)
{
	int ItemCount = 5 - (TileDropLevel * 2);

	std::vector<BYTE> BuildTileIndex;
	BuildTileIndex.reserve(BuildingExist.size());

	for (int i = 0; i < BuildingExist.size(); i++)
	{
		if (BuildingExist[i].TileType != (BYTE)ETILETYPE::NONBUILDING)
		{
			BuildTileIndex.push_back(i);
		}
	}

	int SpawnCount = 0;
	while (SpawnCount < ItemCount)
	{
		int index = RandomUtil::RandRange(0, BuildTileIndex.size() - 1);
		int RarityRand = RandomUtil::RandRange(0, 9);
		int Rarity;
		int Effect = RandomUtil::RandRange(0, (BYTE)EItemEffect::COUNT - 1);

		if (RarityRand < 5)				Rarity = (BYTE)EItemRareLevel::Normal;
		else if (RarityRand < 8)		Rarity = (BYTE)EItemRareLevel::Rare;
		else						Rarity = (BYTE)EItemRareLevel::Legend;

		int floor;
		if (BuildingExist[BuildTileIndex[index]].SectionLevel == 0)			floor = RandomUtil::RandRange(0, 9 - 1);
		else if (BuildingExist[BuildTileIndex[index]].SectionLevel == 3)	floor = RandomUtil::RandRange(0, 7 - 1);
		else if (BuildingExist[BuildTileIndex[index]].SectionLevel == 2)	floor = RandomUtil::RandRange(0, 5 - 1);
		else	 															floor = RandomUtil::RandRange(0, 3 - 1);

		TileIndex.emplace_back(BuildTileIndex[index], floor, Effect, Rarity);
		BuildTileIndex.erase(BuildTileIndex.begin() + index);
		SpawnCount++;
	}

}

double Room::Distance(float x1, float y1, float x2, float y2)
{
	return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}

#ifdef ContiguousTiles

BYTE* Room::GetBuildingExist(int& size)
{
	size = TILE_MIDDLE_COUNT + TILE_SECTION1_COUNT + TILE_SECTION2_COUNT + TILE_SECTION3_COUNT;
	return BuildingExist;
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

#else
int Room::GetTileDropCenterIndex(int& CenterIndex)
{
	int CollapseDirectionAngle = RandomUtil::RandRange(0, 5);

	float CollapseRemainDistance{}, CenterX, CenterY;

	if (TileDropLevel == 0) 
	{
		CollapseRemainDistance = 2.5f;
		CenterX = BuildingExist[0].PosX;
		CenterY = BuildingExist[0].PosY;
	}
	else 
	{
		CollapseRemainDistance = 1.5f;
		CenterX = BuildingExist[CenterTileIndex[TileDropLevel - 1]].PosX;
		CenterY = BuildingExist[CenterTileIndex[TileDropLevel - 1]].PosY;
	}

	CenterX += sin((float)(CollapseDirectionAngle * 60 + 30) * (3.1415 / 180));
	CenterY += cos((float)(CollapseDirectionAngle * 60 + 30) * (3.1415 / 180));

	// Center Tile
	TileProperty* Property = GetLineTileFromAngleAndDistance(0, 0, CenterX, CenterY, CenterIndex);

	{
		//for (UChildActorComponent* Tile : Tiles)
		for (int i = 0; i < BuildingExist.size(); ++i)
		{
			float TileDistance = Distance(BuildingExist[i].PosX, BuildingExist[i].PosY,
				Property->PosX, Property->PosY);
			// 파괴 영역 체크
			if (TileDistance > CollapseRemainDistance)
			{
				BuildingExist.erase(BuildingExist.begin() + i);
				i -= 1;
			}
		}
	}

	IncreaseTileDropLevel();
	return TileDropLevel;
}

void Room::CalculateLocation(const BYTE AngleCount, const BYTE Distance, float& x, float& y)
{
	x = Distance * sin((float)(AngleCount * 60 + 30) * (3.1415 / 180));
	y = Distance * cos((float)(AngleCount * 60 + 30) * (3.1415 / 180));
}

TileProperty* Room::GetLineTileFromAngleAndDistance(BYTE FindAngle, BYTE FindDistance, float FindTileLocationX, float FindTileLocationY, int& CenterIndex)
{
	// (0, 0, 좌표) 입력시 해당 좌표의 타일 반환
	// (1, 3) 입력시 60도 방면의 Section1 타일 반환
		// 
	if (FindDistance != 0)
	{
		CalculateLocation(FindAngle, FindDistance, FindTileLocationX, FindTileLocationY);
	}

	CenterIndex = 0;
	for (TileProperty& Tile : BuildingExist)
	{
		// 모든 타일 중 해당 타일과의 거리를 비교하여 찾기
		if (Distance(Tile.PosX, Tile.PosY, FindTileLocationX, FindTileLocationY) < 1.f)
		{
			return &Tile;
		}
		++CenterIndex;
	}
	return nullptr;
}

void Room::SpawnBuildings(const BYTE& SpawnCount, const BYTE& SectionLevel)
{
	std::vector<TileProperty*> Tiles;
	//for (int i = 0; i < BuildingExist.size(); i++)
	//{
	//	if (BuildingExist[i].SectionLevel == SectionLevel)
	//		Tiles.emplace_back(&BuildingExist[i]);
	//}
	for (TileProperty& b : BuildingExist)
	{
		if (b.SectionLevel == SectionLevel)
			Tiles.emplace_back(&b);
	}

	int BuildingCount = 0;
	while (BuildingCount < SpawnCount)
	{
		int index = RandomUtil::RandRange(0, Tiles.size() - 1);
		TileProperty* Property = Tiles[index];

		if (Property->TileType == (BYTE)ETILETYPE::NONBUILDING)
		{
			Property->TileType = (BYTE)ETILETYPE::BUILDING;
			Tiles.erase(Tiles.begin() + index);
			++BuildingCount;
		}
	}
}

void Room::SpawnFloatingTiles(const BYTE& SpawnCount, const BYTE& SectionLevel)
{
	std::vector<TileProperty*> Tiles;
	for (TileProperty& b : BuildingExist)
	{
		if (b.SectionLevel == SectionLevel)
			Tiles.emplace_back(&b);
	}

	int BuildingCount = 0;
	while (BuildingCount < SpawnCount)
	{
		int index = RandomUtil::RandRange(0, Tiles.size() - 1);
		TileProperty* Property = Tiles[index];

		if (Property->TileType == (BYTE)ETILETYPE::NONBUILDING)
		{
			Property->TileType = (BYTE)ETILETYPE::FLOATINGTILE;
			Tiles.erase(Tiles.begin() + index);
			++BuildingCount;
		}
	}
}

void Room::SpawnTeamBuilding(const BYTE& SectionLevel)
{
	std::vector<TileProperty*> Tiles;
	for (TileProperty& b : BuildingExist)
	{
		if (b.SectionLevel == SectionLevel)
			Tiles.emplace_back(&b);
	}

	int index = RandomUtil::RandRange(0, Tiles.size() - 1);
	TileProperty *PropertyA, *PropertyB;
	PropertyA = Tiles[index];
	if (SectionLevel == 3)
	{
		PropertyB = Tiles[(index + 3) % 6];
	}
	else
	{
		PropertyB = Tiles[(index + 9) % 18];
	}
	PropertyA->TileType = (BYTE)ETILETYPE::SPAWNBUILDING_A;
	PropertyB->TileType = (BYTE)ETILETYPE::SPAWNBUILDING_B;
}

#endif // ContiguousTiles
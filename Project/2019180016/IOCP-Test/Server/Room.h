#pragma once

#include <array>
#include <atomic>

class Room
{
	enum class ETEAM {A, B};
public:
	Room();
	~Room() {}

	void AddKillCount(bool IsTeamA);

private:
	std::array<std::atomic<int>, 2> KillScore;

	// 건물 정보

	// 아이템 정보


};


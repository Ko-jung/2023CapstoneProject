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

	// �ǹ� ����

	// ������ ����


};


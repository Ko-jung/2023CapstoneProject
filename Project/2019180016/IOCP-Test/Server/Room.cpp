#include "Room.h"

Room::Room()
{
	KillScore[0] = KillScore[1] = 0;
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

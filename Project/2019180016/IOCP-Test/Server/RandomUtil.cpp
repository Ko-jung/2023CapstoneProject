#include "RandomUtil.h"

int RandomUtil::RandRange(int minInt, int maxInt)
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> IntUid(minInt, maxInt);

    return IntUid(mt);
}

std::vector<int> RandomUtil::RandUniqueInt(int minInt, int maxInt, int count)
{
	std::vector<int> ReturnVector;
	ReturnVector.reserve(count);

	while (ReturnVector.size() < count)
	{
		int RandInt = RandRange(minInt, maxInt);
		if (std::find(ReturnVector.begin(), ReturnVector.end(), RandInt) == ReturnVector.end())
		{
			ReturnVector.push_back(RandInt);
		}
	}

	return ReturnVector;
}

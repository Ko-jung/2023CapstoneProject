#pragma once

#include <random>
#include <vector>

class RandomUtil
{
public:
	RandomUtil() {}
	~RandomUtil() {}

	static int RandRange(int minInt, int maxInt);

	static std::vector<int> RandUniqueInt(int minInt, int maxInt, int count);

private:
	std::uniform_int_distribution<int> IntUid;
	std::uniform_real_distribution<double> DoubleUid;

};


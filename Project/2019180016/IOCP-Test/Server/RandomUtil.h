#pragma once

#include <random>
#include <vector>

class RandomUtil
{
public:
	RandomUtil() {}
	~RandomUtil() {}

	static int RandRange(int minInt, int maxInt);

	static std::vector<int> RandUniqueInt(const int& minInt, const int& maxInt, const int& count);
	static std::vector<int> RandUniqueInt(const int& minInt, const int& maxInt, const int& count, const std::vector<int>& IncludeInt);

private:
	std::uniform_int_distribution<int> IntUid;
	std::uniform_real_distribution<double> DoubleUid;

};


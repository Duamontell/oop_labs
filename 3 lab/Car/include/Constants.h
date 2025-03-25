#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <vector>

using Gears = std::vector<std::pair<int, std::pair<int, int>>>;
const std::string DIRECTION_FORWARD = "forward";
const std::string DIRECTION_BACKWARD = "backward";
const std::string DIRECTION_STANDING_STILL = "standing still";
const Gears GEARS = {
	{-1, {0, 20}},
	{0, {0, 150}},
	{1,{0,30}},
	{2,{20,50}},
	{3,{30, 60}},
	{4, {40, 90}},
	{5, {50, 150}}
};

#endif // CONSTANTS_H

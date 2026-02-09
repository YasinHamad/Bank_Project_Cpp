#pragma once

#include <cstdlib>
#include <ctime>

namespace generators
{
	// this function return a random number
	int RandomNumber(int From, int To)
	{
		int randNum = rand() % (To - From + 1) + From;
		return randNum;
	}
}
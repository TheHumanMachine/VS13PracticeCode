#pragma once
#include <string>
#include "Level.h"


using namespace std;

class GameSystem
{
public:
	GameSystem(string levelFileName);
	void playGame();

private:
	Level _level;

	
};


#include "GameSystem.h"
#include <iostream>
#include <conio.h>


GameSystem::GameSystem(string levelFileName)
{
	//Level, Health, Attack, Defense, Experience
	_level.load(levelFileName);
	
	system("PAUSE");
}

void GameSystem::playGame()
{
	bool isDone = false;

	while (isDone != true){

		_level.print();
		_level.update(); 
		_getch(); 
	}
}



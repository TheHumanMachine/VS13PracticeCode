#include <iostream>
#include <cstdlib>
#include <string>
#include <conio.h>
#include "GameSystem.h"



using namespace std;

int main()
{
	GameSystem gameSystem("levels.txt");

	gameSystem.playGame();



	system("PAUSE");
	return 0;
}
#include "Level.h"
#include <fstream>
#include <iostream>
#include <cstdio>

Level::Level()
{ 

}

void Level::load(string fileName, Player &player)
{
	ifstream file;

	file.open(fileName);
	if (file.fail()){
		perror(fileName.c_str());
		system("Pause");
		exit(1);
	}
	string line;

	while (getline(file, line)){
		_levelData.push_back(line);
	}
	file.close();
	
	//Process the level

	char tile;
	for (size_t i = 0; i < _levelData.size(); i++){
		for (size_t j = 0; j < _levelData.size(); j++){
			tile = _levelData[i][j];

			switch (tile){
			case '@': //Player
				player.setPosition(j, i);
				break;
			case 'S': //Snake
				_enemies.push_back(Enemy("Snake", tile, 1, 3, 2, 10, 50));
				_enemies.back().setPosition(j, i);
				break;
			case 'G': //Goblin
				_enemies.push_back(Enemy("Goblin", tile, 1, 3, 2, 50, 100));
				_enemies.back().setPosition(j, i);
				break;
			case 'O': //Ogre - Works
				_enemies.push_back(Enemy("Ogre", tile, 1, 3, 2, 75, 150));
				_enemies.back().setPosition(j, i);
				break;
			case 'B': //Bandit
				_enemies.push_back(Enemy("Bandit", tile, 4, 3, 2, 50, 150));
				_enemies.back().setPosition(j, i);
				break;
			case 'D': //Dragon
				_enemies.push_back(Enemy("Dragon", tile, 4, 3, 2, 100, 500));
				_enemies.back().setPosition(j, i);
				break;
			}
		}
	}


}

void Level::print()
{
	printf("%s", string(100, '\n').c_str());

	for (size_t i = 0; i < _levelData.size(); i++){
		printf("%s\n", _levelData[i].c_str());
	}
	printf("\n");
}

void Level::movePlayer(char input, Player &player)
{
	int playerX, playerY;

	player.getPosition(playerX, playerY);

	switch (input){
	case 'W': //up
	case 'w':
		processPlayerMove(player, playerX, playerY - 1);
		break;
	case 'S': //down
	case 's':
		processPlayerMove(player, playerX, playerY + 1);
		break;
	case 'A': //left
	case 'a':
		processPlayerMove(player, playerX - 1, playerY);
		break;
	case 'D': //right
	case 'd':
		processPlayerMove(player, playerX + 1, playerY);
		break;
	default:
		cout << "Invalid input";
		system("PAUSE");
		break;
	}
}

void Level::updateEnemies(Player &player)
{
	char aiMove;
	int playerX, playerY, enemyX, enemyY;


	
	player.getPosition(playerX, playerY);

	for (size_t i = 0; i < _enemies.size(); i++){
		aiMove = _enemies[i].getMove(playerX, playerY);
		_enemies[i].getPosition(enemyX, enemyY);

		switch (aiMove){
		case 'w'://up
			processEnemyMove(player, i, enemyX, enemyY - 1);
			break;
		case 's': //down
			processEnemyMove(player, i, enemyX, enemyY + 1);
			break;
		case 'a': //left
			processEnemyMove(player, i, enemyX - 1, enemyY);
			break;
		case 'd':  //right
			processEnemyMove(player, i, enemyX + 1, enemyY);
			break;
		}
	}
}

char Level::getTile(int x, int y)
{
	return _levelData[y][x];
	
}

void Level::setTile(int x, int y, char tile)
{
	_levelData[y][x] = tile; 
}

void Level::processPlayerMove(Player &player, int targetX, int targetY)
{
	int playerX, playerY;
	player.getPosition(playerX, playerY);

	char moveTile = getTile(targetX, targetY);
	
	switch (moveTile){
	case '.':
		player.setPosition(targetX, targetY);
		setTile(playerX, playerY, '.');
		setTile(targetX, targetY, '@');
		break;
	case '#':
		break;
	default:
		battleMonster(player, targetX, targetY);
		break;


	}
}

void Level::processEnemyMove(Player &player, int enemyIndex, int targetX, int targetY)
{
	int playerX, playerY, enemyX, enemyY;


	_enemies[enemyIndex].getPosition(enemyX, enemyY);
	player.getPosition(playerX, playerY);

	char moveTile = getTile(targetX, targetY);

	switch (moveTile){
	case '.':
		_enemies[enemyIndex].setPosition(targetX, targetY);
		setTile(enemyX, enemyY, '.'); 
		setTile(targetX, targetY, _enemies[enemyIndex].getTile());
		break;
	case '@':
		battleMonster(player, enemyX, enemyY);
		break;
	default:
		battleMonster(player, targetX, targetY);
		break;
	}
}


void Level::battleMonster(Player &player, int targetX, int targetY)
{
	int enemyX, enemyY, playerX, playerY, attackRoll, attackResult;
	string enemyName;


	player.getPosition(playerX, playerY);

	for (size_t i = 0; i < _enemies.size(); i++){

		_enemies[i].getPosition(enemyX, enemyY);

		enemyName = _enemies[i].getName(); 

		if (targetX == enemyX && targetY == enemyY){

			//Battle!
			attackRoll = player.attack();
			printf("\nPlayer attacked %s with a roll of %d\n", enemyName.c_str(), attackRoll);
			attackResult = _enemies[i].takeDamage(attackRoll);

			if (attackResult != 0){

				setTile(targetX, targetY, '.');
				print();
				printf("Monster died\n");

				_enemies[i] = _enemies.back();
				_enemies.pop_back();
				i--;

				system("PAUSE");
				player.addExperience(attackResult);

				return;
			}
			//Monster's turn
			attackRoll = _enemies[i].attack();
			printf("\n%s attacked player with a roll of %d\n", enemyName.c_str(), attackRoll);

			attackResult = player.takeDamage(attackRoll);

			if (attackResult != 0){

				setTile(playerX, playerY, 'x');
				print();
				printf("You've Died!\n");
				system("PAUSE");

				exit(0);
			}
			system("PAUSE");
			return;
		}
	}
}
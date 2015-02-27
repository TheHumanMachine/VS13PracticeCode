#include "Soldier.h"
#include <random>
#include <ctime>


Soldier::Soldier(string name, char tile, int level, int attack, int defense, int health, int army)
{
	_name = name;
	_tile = tile;
	_level = level;
	_attack = attack;
	_defense = defense; 
	_health = health;
	_army = army;
}


void Soldier::setPosition(int x, int y)
{
	_x = x;
	_y = y;
}

void Soldier::getPosition(int &x, int &y)
{
	x = _x;
	y = _y;

}

int Soldier::attack()
{
	static default_random_engine randomEngine(time(NULL));
	uniform_int_distribution<int> attackRoll(0, _attack);

	return attackRoll(randomEngine);
}

int Soldier::takeDamage(int attack)
{

	attack -= _defense;
	//check if the attack does damage
	if (attack > 0){
		_health -= attack;
		//check if he died
		if (_health <= 0){
			return 1;
		}
	}
	return 0;
}

char Soldier::getMove(vector<Soldier *> armies[], int numArmies){

	Soldier *closestSoldier = getClosestEnemy(armies, numArmies);

	if (closestSoldier == nullptr){
		return '.';
	}

	int soldierX, soldierY;

	closestSoldier->getPosition(soldierX, soldierY);

	int dX = _x - soldierX;
	int dY = _y - soldierY;

	int absoluteDistX = abs(dX);
	int absoluteDistY = abs(dY);

	if (absoluteDistX > absoluteDistY){
		if (dX > 0){
			return 'a';
		}else{
			return 'd';
		}
	}
	else{
		if (dY > 0){
			return 'w';
		}else{
			return 's';
		}
	}
	
}

Soldier *Soldier::getClosestEnemy(vector<Soldier *> armies[], int numArmies)
{
	Soldier *clostestSoldier = nullptr;
	int closestDistance = INT_MAX;
	int enemyX, enemyY, distance;
	for (int i = 0; i < numArmies; i++){
		if (i != _army){
			for (int j = 0; j < armies[i].size(); j++){
				armies[i][j]->getPosition(enemyX, enemyY);
				distance = abs(enemyX - _x) + abs(enemyY - _y);
				if (distance < closestDistance){
					clostestSoldier = armies[i][j];
					closestDistance = distance;
				}
			}
		}
	}
	return clostestSoldier;
}
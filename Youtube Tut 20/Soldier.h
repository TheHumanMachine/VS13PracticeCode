#pragma once
#include <string>
#include <vector>

using namespace std;

class Soldier
{
public:
	Soldier(string name, char tile, int level, int attack, int defense, int health, int army);
	
	//Setter
	void setPosition(int x, int y);
	//Getter
	void getPosition(int &x, int &y);
	string getName() { return _name; }
	char getTile(){ return _tile; } 
	int getArmy(){ return _army; }

	int attack();
	int takeDamage(int attack);

	//Gets AI move command
	char getMove(vector<Soldier *> armies[], int numArmies);

private:
	Soldier *getClosestEnemy(vector<Soldier *> armies[], int numArmies);

	string _name;
	char _tile;


	int _level;
	int _attack;
	int _defense;
	int _health;
	int _army;

	//positions
	int _x;
	int _y;
};


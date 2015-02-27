#pragma once
class Player
{
public:
	Player();
	void init(int level, int health, int attack, int defense, int experience);

	int attack();
	int takeDamage(int attack);
	//Setters
	void setPosition(int x, int y);
	void addExperience(int experience);
	//Getters
	void getPosition(int &x, int &y);
	int displayLevel(){ return _level; }
	

private:
	//Properties 
	int _level;
	int _health;
	int _attack;
	int _defense;
	int _experience;



	//positions
	int _x;
	int _y;	
};


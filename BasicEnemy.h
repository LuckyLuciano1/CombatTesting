#pragma once
#include "GameObject.h"
#include <iostream>
using namespace std;

class BasicEnemy : public GameObject
{
private:
	int health;
	int animationRow;

	double p_x;
	double p_y;
	double p_angle;
protected:
	bool ifPursue;
	bool ifShoot;
	bool ifMelee;

public:
	BasicEnemy();
	void Destroy();

	void Init(ALLEGRO_BITMAP *image, double copy_x, double copy_y);
	void Update();
	void Render();

	void ResetAnimation(int position);

	int GetHealth() { return health; }

	void TakeDamage() { health--; }

	void Collided(int objectID);

	bool GetPursue(){return ifPursue; }//basic enemy functions. speceific actions are descirbed in main
	void SetPursue(bool pursue){ BasicEnemy::ifPursue = pursue; }

	bool GetShoot(){ return ifShoot; }
	void SetShoot(bool shoot){ BasicEnemy::ifShoot = shoot; }

	bool GetMelee(){ return ifMelee; }
	void SetMelee(bool melee){ BasicEnemy::ifMelee = melee; }

	void PursueFunc(double p_x, double p_y, double angle);
	void ShootFunc(double p_x, double p_y);
	void MeleeFunc(double p_x, double p_y);

	void LogicFunc(double p_x, double p_y, double angle);
};
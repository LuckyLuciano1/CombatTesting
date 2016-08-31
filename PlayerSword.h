#pragma once

#include "GameObject.h"

class PlayerSword : public GameObject
{
private:
	int animationRow;
	double ObjMouseAngle;
	int RenderNum;

	double PlayerX;
	double PlayerY;

public:
	PlayerSword();
	void Destroy();
 
	void Init(ALLEGRO_BITMAP *playerSwordImage, double x, double y, double MouseAngle);
	void Update();
	void Render();

	void ResetAnimation(int position);

	void Collided(int objectID);
};
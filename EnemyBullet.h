#pragma once

#include "GameObject.h"

class EnemyBullet : public GameObject
{
private:
	int animationRow;
	double ObjMouseAngle;
	int RenderNum;

public:
	EnemyBullet();
	void Destroy();

	void Init(ALLEGRO_BITMAP *EnemyBulletImage, double x, double y, double MouseAngle);
	void Update();
	void Render();

	void ResetAnimation(int position);

	void Collided(int objectID);
};
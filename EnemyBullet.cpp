#include "EnemyBullet.h"
#include <iostream>
using namespace std;

EnemyBullet::EnemyBullet(){}

void EnemyBullet::Destroy()
{
	GameObject::Destroy();
}

void EnemyBullet::Init(ALLEGRO_BITMAP *image, double x, double y, double MouseAngle)
{
	GameObject::Init(x, y, 6, 6, 0, 0, 10, 12);

	SetID(ENEMYWEAPON);
	SetAlive(true);
	maxFrame = 3;
	curFrame = 0;
	RenderNum = 0;
	frameWidth = 46;
	frameHeight = 41;
	animationColumns = 3;
	animationDirection = 1;
	ObjMouseAngle = MouseAngle;
	if (image != NULL)
		EnemyBullet::image = image;
}

//atan2(mouse_y - y, mouse_x - x);

void EnemyBullet::Update()
{
	GameObject::Update();
	if (x < 0)
		x = 0;
	else if (x > SCREENW)
		x = SCREENW;

	if (y < 0)
		y = 0;
	else if (y > SCREENH)
		y = SCREENH;
}

void EnemyBullet::Render()
{
	GameObject::Render();
	RenderNum++;
	//animationRow++;
	int fx = (curFrame % animationColumns) * frameWidth;
	int fy = animationRow * frameHeight;
	al_draw_rotated_bitmap(image, 0, 0, x, y, ObjMouseAngle, 0);
	if (RenderNum == 5)
		SetAlive(false);
	else{/*cout << "Slashing" << endl;*/}
}
void EnemyBullet::ResetAnimation(int position)
{
	if (position == 1)
	{
		animationRow = 1;
		dirY = 0;
	}
	else
	{
		curFrame = 0;
		dirX = 0;
	}
}

void EnemyBullet::Collided(int objectID)
{
	if (objectID == PLAYER){}//enemy takes damage here
}
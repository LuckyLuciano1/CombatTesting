#include "PlayerSword.h"
#include <iostream>
using namespace std;

PlayerSword::PlayerSword(){}

void PlayerSword::Destroy()
{
	GameObject::Destroy();
}

void PlayerSword::Init(ALLEGRO_BITMAP *image, double x, double y, double MouseAngle)
{
	GameObject::Init(x, y, 6, 6, 0, 0, 50, 50);

	SetID(FRIENDLYWEAPON);
	SetAlive(true);

	PlayerX = x;
	PlayerY = y;

	maxFrame = 3;
	curFrame = 0;
	frameWidth = 50;
	frameHeight = 50;
	animationColumns = 3;
	animationDirection = 1;
	animationRow = 1;
	ObjMouseAngle = MouseAngle;
	RenderNum = 0;
	if (image != NULL)
		PlayerSword::image = image;
}

//atan2(mouse_y - y, mouse_x - x);

void PlayerSword::Update()
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

void PlayerSword::Render()
{
	GameObject::Render();
	RenderNum++;
	//animationRow++;
	int fx = (curFrame % animationColumns) * frameWidth;
	int fy = animationRow * frameHeight;
	al_draw_rotated_bitmap(image, 0, 0, univ_playerpos_x, univ_playerpos_y, ObjMouseAngle, 0);
	//al_draw_rotated_bitmap(image, 0, 0, x, y, ObjMouseAngle, 0);
	if (RenderNum == 6)
		SetAlive(false);
	else{/*cout << "Slashing" << endl;*/}
}

void PlayerSword::ResetAnimation(int position)
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

void PlayerSword::Collided(int objectID)
{}
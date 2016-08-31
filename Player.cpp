#include "Player.h"
#include<iostream>
using namespace std;

Player::Player(){}

void Player::Destroy()
{
	GameObject::Destroy();
}

void Player::Init(ALLEGRO_BITMAP *image)
{
	GameObject::Init(20, 200, 6, 6, 0, 0, 10, 12);

	SetID(PLAYER);
	SetAlive(true);

	health = 5;

	maxFrame = 3;
	curFrame = 0;
	frameWidth = 46;
	frameHeight = 41;
	animationColumns = 3;
	animationDirection = 1;

	animationRow = 1;

	if (image != NULL)
		Player::image = image;
}


void Player::Update()
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
void Player::Render()
{
	GameObject::Render();

	int fx = (curFrame % animationColumns) * frameWidth;
	int fy = animationRow * frameHeight;

	al_draw_bitmap_region(image, fx, fy, frameWidth, frameHeight, x - frameWidth / 2, y - frameHeight / 2, 0);
}

void Player::MoveUp()
{
	animationRow = 0;
	dirY = -1;
}
void Player::MoveDown()
{
	animationRow = 2;
	dirY = 1;
}
void Player::MoveLeft()
{
	curFrame = 2;
	dirX = -1;
}
void Player::MoveRight()
{
	curFrame = 1;
	dirX = 1;
}

void Player::Dash(double mouse_x, double mouse_y)
{
	double MouseAngle = atan2(mouse_y - y, mouse_x - x);
	double radius = 50;
		dirX = radius *cos(MouseAngle);
		dirY = radius *sin(MouseAngle);
}

void Player::ResetAnimation(int position)
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

void Player::Collided(int objectID)
{
	if (objectID == ENEMYWEAPON)
		health--;
}
#include "GameObject.h"

GameObject::GameObject()
{
	x = 0;
	y = 0;

	velX = 0;
	velY = 0;

	dirX = 0;
	dirY = 0;

	boundX = 0;
	boundY = 0;

	maxFrame = 0;
	curFrame = 0;
	frameCount = 0;
	frameDelay = 0;
	frameWidth = 0;
	frameHeight = 0;
	animationColumns = 0;
	animationDirection = 0;

	MouseAngle = 0;

	image = NULL;

	alive = true;
	collidable = true;
}

void GameObject::Destroy()
{}

void GameObject::Init(double x, double y, double velX, double velY, int dirX, int dirY, int boundX, int boundY)
{
	GameObject::x = x;
	GameObject::y = y;

	GameObject::velX = velX;
	GameObject::velY = velY;

	GameObject::dirX = dirX;
	GameObject::dirY = dirY;

	GameObject::boundX = boundX;
	GameObject::boundY = boundY;
}

void GameObject::Update()
{
	x += velX * dirX;
	y += velY * dirY;
}

void GameObject::Render()
{}

bool GameObject::CheckCollisions(GameObject *otherObject)
{
	double oX = otherObject->GetX();
	double oY = otherObject->GetY();

	int obX = otherObject->GetBoundX();
	int obY = otherObject->GetBoundY();

	if (x + boundX > oX - obX &&
		x - boundX < oX + obX &&
		y + boundY > oY - obY &&
		y - boundY < oY + obY)
		return true;
	else
		return false;
}

void GameObject::Collided(int objectID)
{}

bool GameObject::Collidable()
{
	return alive && collidable;
}
/*
void GiveValues(double v_1, double v_2, double v_3){
	univ_playerpos_x = v_1;
	univ_playerpos_y = v_2;
	univ_playerpos_angle = v_3;

}*/

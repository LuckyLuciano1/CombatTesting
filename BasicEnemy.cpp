#include "BasicEnemy.h"

BasicEnemy::BasicEnemy(){}

void BasicEnemy::Destroy()
{
	GameObject::Destroy();
}

void BasicEnemy::Init(ALLEGRO_BITMAP *image, double copy_x, double copy_y)
{
	GameObject::Init(copy_x, copy_y, 6, 6, 0, 0, 46, 41);
	SetID(BASICENEMY);
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
		BasicEnemy::image = image;
}

void BasicEnemy::Update()
{
	GameObject::Update();
	LogicFunc(univ_playerpos_x, univ_playerpos_y, univ_playerpos_angle);
	if (x < 0)
		x = 0;
	else if (x > SCREENW)
		x = SCREENW;

	if (y < 0)
		y = 0;
	else if (y > SCREENH)
		y = SCREENH;
}

void BasicEnemy::Render()
{
	GameObject::Render();

	int fx = (curFrame % animationColumns) * frameWidth;
	int fy = animationRow * frameHeight;

	al_draw_bitmap_region(image, fx, fy, frameWidth, frameHeight,
		x - frameWidth / 2, y - frameHeight / 2, 0);
}

void BasicEnemy::ResetAnimation(int position)
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

void BasicEnemy::Collided(int objectID)
{
	if (objectID == FRIENDLYWEAPON)
		SetAlive(false);
}

//defaults to pursue. uses trig to approach at any angle
void BasicEnemy::PursueFunc(double p_x, double p_y, double angle){
	
	dirX = -2 * cos(angle);
	dirY = -2 * sin(angle);

	double dif_x = p_x - GetX();
	double dif_y = p_y - GetY();	

	if (dirX <= -1)
		curFrame = 2;
	else if (dirX >= 1)
		curFrame = 2;
	else
		ResetAnimation(0);

	 if (dirY <= -1)
		animationRow = 0;
	else if (dirY >= 1)
		animationRow = 2;
	else
		ResetAnimation(1);
}
//randomly stops and shoots when pursuing
void BasicEnemy::ShootFunc(double p_x, double p_y){}
//if in range of target, attacks. for now (until enemy sword created) maybe just dashes backwards, and shoots?
void BasicEnemy::MeleeFunc(double p_x, double p_y){
	//dirX = 0;
	//dirY = 0;
}

void BasicEnemy::LogicFunc(double p_x, double p_y, double angle){
	if (GetX() < p_x + 80 &&//checks x and y perimeter, to see if in attack range
		GetX() > p_x - 80 &&
		GetY() < p_y + 80 &&
		GetY() > p_y - 80){
		SetMelee(true);

		MeleeFunc(p_x, p_y);
	}

	if (GetMelee() == false &&
		rand() % 100 == 1){
		SetShoot(true);

		ShootFunc(p_x, p_y);
	}

	if (GetShoot() == false &&//if nothing else, pursue
		GetMelee() == false){
		SetPursue(true);

		PursueFunc(p_x, p_y, angle);
	}

	SetPursue(false);//done with everything, so set everything to false
	SetMelee(false);
	SetShoot(false);
}

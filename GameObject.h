#pragma once

#include <iostream>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include "Globals.h"

class GameObject
{
private:
	int ID;
	int health;
	bool alive;
	bool collidable;

protected:
	double x;
	double y;

	double velX;
	double velY;

	int dirX;
	int dirY;

	int boundX;
	int boundY;

	int maxFrame;
	int curFrame;
	int frameCount;
	int frameDelay;
	int frameWidth;
	int frameHeight;
	int animationColumns;
	int animationDirection;

	double MouseAngle;

	ALLEGRO_BITMAP *image;
	
	double univ_playerpos_x;
	double univ_playerpos_y;
	double univ_playerpos_angle;

public:
	GameObject();
	void virtual Destroy();

	void Init(double x, double y, double velX, double velY, int dirX, int dirY, int boundX, int boundY);
	void virtual Update();
	void virtual Render();

	double GetX() { return x; }
	double GetY() { return y; }

	void SetX(double x) { GameObject::x = x; }
	void SetY(double y) { GameObject::y = y; }

	int GetBoundX() { return boundX; }
	int GetBoundY() { return boundY; }

	int GetID() { return ID; }
	void SetID(int ID) { GameObject::ID = ID; }

	bool GetAlive() { return alive; }
	void SetAlive(bool alive) { GameObject::alive = alive; }

	bool GetCollidable() { return collidable; }
	void SetCollidable(bool collidable) { GameObject::collidable = collidable; }

	bool CheckCollisions(GameObject *otherObject);
	void virtual Collided(int objectID);
	bool Collidable();

	void SetValues(double v_1, double v_2, double v_3){
		univ_playerpos_x = v_1;
		univ_playerpos_y = v_2;
		univ_playerpos_angle = v_3;
	}
};
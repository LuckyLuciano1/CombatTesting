#pragma once

#include "GameObject.h"

class Player : public GameObject
{
private:
	int health;
	int animationRow;

public:
	Player();
	void Destroy();

	void Init(ALLEGRO_BITMAP *image = NULL);
	void Update();
	void Render();

	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();

	void Dash(double mouse_x, double mouse_y);
	void Slash(double mouse_x, double mouse_y);
	void ResetAnimation(int position);

	int GetHealth() { return health; }

	void TakeDamage() { health--; }

	void Collided(int objectID);
};
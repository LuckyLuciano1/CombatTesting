#pragma once
const int SCREENH = 920, SCREENW = 1080;//console size

const double P_W = 30, P_H = 30;

const int SPEED = 2;
const int FPS = 60;

enum ID{ PLAYER, ENEMY, BULLET, BORDER, EXPLOSION, 
		ENEMYWEAPON, FRIENDLYWEAPON,  
		TERRAIN, DESTRUCTIBLE, 
		MISC,
		BASICENEMY
};
enum STATE{
	TITLE, PLAYING, LOST };
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <math.h>
#include <list>

#include "Globals.h"
#include "GameObject.h"
#include "Player.h"
#include "PlayerSword.h"
#include "BasicEnemy.h"

#define PI 3.14159265
#define DEGREES(x) int((x)/360.0*0xFFFFFF)
#define RADIANS(x) int((x)/2/M_PI*0xFFFFFF)

using namespace std;

double FindAngle(double X_1, double Y_1, double X_2, double Y_2);
void BasicEnemyAI(BasicEnemy *enemy);

bool keys[] = { false, false, false, false, false, false, false };
enum KEYS{ UP, DOWN, LEFT, RIGHT, SPACE, MOUSE_BUTTON, DASH };

//globals
Player *player;
PlayerSword *playersword;
BasicEnemy *basicenemy;
std::list<GameObject *> objects;
std::list<GameObject *>::iterator iter;
std::list<GameObject *>::iterator iter2;

ALLEGRO_SAMPLE_INSTANCE *songInstance;

//todo
void __cdecl TakeLife();

int main()
{

	//==============================================
	//SHELL VARIABLES
	//==============================================
	bool redraw = true;
	bool doexit = false;
	//double MouseAngle = 0;
	double angle = 0;
	int mousex = 0;
	int mousey = 0;
	bool render = false;

	double gameTime = 0;
	int frames = 0;
	int gameFPS = 0;

	//int Overlay[SCREENH / 10][SCREENW / 10] = {};//matrix to handle rudimentary physics, synthetic depth, terrain layering, etc.
	double secondtimer = 0;//for timer setup
	double seconds = 0;//for timer setup
	int fivesecondtimer = 0;
	double DashTime = 0;
	//==============================================
	//PROJECT VARIABLES
	//==============================================
	player = new Player();

	int state = 1;

	ALLEGRO_BITMAP *playerImage = NULL;
	ALLEGRO_BITMAP *playerSwordImage = NULL;
	ALLEGRO_BITMAP *basicEnemyImage = NULL;
	//==============================================
	//ALLEGRO VARIABLES
	//==============================================
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_FONT *font18;

	//==============================================
	//ALLEGRO INIT FUNCTIONS
	//==============================================
	if (!al_init())										//initialize Allegro
		return -1;

	display = al_create_display(SCREENW, SCREENH);			//create our display object

	if (!display)										//test display object
		return -1;

	//==============================================
	//ADDON INSTALL
	//==============================================
	al_install_keyboard();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();
	al_install_audio();
	al_init_acodec_addon();
	al_install_mouse();

	//==============================================
	//PROJECT INIT
	//==============================================
	//insert font types, images, sounds, state images, etc
	font18 = al_load_font("pricedown bl.ttf", 18, 0);
	al_reserve_samples(15);

	playerImage = al_load_bitmap("spaceship_by_arboris.png");
	al_convert_mask_to_alpha(playerImage, al_map_rgb(255, 0, 255));
	player->Init(playerImage);
	objects.push_back(player);

	basicEnemyImage = al_load_bitmap("spaceship_by_arboris.png");
	al_convert_mask_to_alpha(basicEnemyImage, al_map_rgb(255, 0, 255));

	playerSwordImage = al_load_bitmap("CustomSetSlash.png");
	al_convert_mask_to_alpha(playerSwordImage, al_map_rgb(255, 255, 255));

	//change state can be here
	srand(time(NULL));
	//==============================================
	//TIMER INIT AND STARTUP
	//==============================================
	event_queue = al_create_event_queue();
	timer = al_create_timer(1.000 / FPS);

	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_mouse_event_source());

	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_flip_display();
	al_start_timer(timer);
	bool toggle = false;

	while (!doexit)
	{

		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		secondtimer++;

		if (secondtimer == 60){
			seconds++;
			fivesecondtimer++;
			secondtimer = 0;			
		}

		if (fivesecondtimer == 2){
			fivesecondtimer = 0;
			BasicEnemy *basicenemy = new BasicEnemy();
			basicenemy->Init(basicEnemyImage, SCREENW / 2, SCREENH / 2);
			objects.push_back(basicenemy);
		}

		//==============================================
		//INPUT
		//==============================================

		if (ev.type == ALLEGRO_EVENT_MOUSE_AXES){

			mousex = ev.mouse.x;
			mousey = ev.mouse.y;//creates variables for mouse to use later in class and dash function
			/*
			PlayerSword *playersword = new PlayerSword();//BLUR EFFECT (for sword, could work with dash)
			playersword->Init(playerSwordImage, player->GetX(), player->GetY(), FindAngle(player->GetX(), player->GetY(), ev.mouse.x, ev.mouse.y) - 45);
			objects.push_back(playersword);*/
		}

		if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				doexit = true;
				break;
			case ALLEGRO_KEY_A:
				keys[LEFT] = true;
				break;
			case ALLEGRO_KEY_D:
				keys[RIGHT] = true;
				break;
			case ALLEGRO_KEY_W:
				keys[UP] = true;
				break;
			case ALLEGRO_KEY_S:
				keys[DOWN] = true;
				break;
			case ALLEGRO_KEY_LSHIFT:
				keys[DASH] = true;
				break;
			}
		}

		else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
			keys[MOUSE_BUTTON] = true;
			PlayerSword *playersword = new PlayerSword();
			playersword->Init(playerSwordImage, player->GetX(), player->GetY(), FindAngle(player->GetX(), player->GetY(), ev.mouse.x, ev.mouse.y) - 45);
			objects.push_back(playersword);
		}

		else if (ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				doexit = true;
				break;
			case ALLEGRO_KEY_A:
				keys[LEFT] = false;
				break;
			case ALLEGRO_KEY_D:
				keys[RIGHT] = false;
				break;
			case ALLEGRO_KEY_W:
				keys[UP] = false;
				break;
			case ALLEGRO_KEY_S:
				keys[DOWN] = false;
				break;
			case ALLEGRO_KEY_SPACE:
				keys[SPACE] = false;
				break;
			case ALLEGRO_KEY_LSHIFT:
				keys[DASH] = false;
				break;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
			keys[MOUSE_BUTTON] = false;
			//if (playersword->GetAlive() == false){}
			//playersword->SetAlive(false);
		}
		
		//==============================================
		//GAME UPDATE
		//==============================================
		else if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			render = true;
			
			//UPDATE FPS===========
			frames++;
			if (al_current_time() - gameTime >= 1)
			{
				gameTime = al_current_time();
				gameFPS = frames;
				frames = 0;
			}
			//=====================
			if (state == PLAYING)//if playing, recieve movement
			{
				if (keys[UP]){
					player->MoveUp();
				}
				else if (keys[DOWN]){
					player->MoveDown();
				}

				else{
					player->ResetAnimation(1);
				}

				if (keys[LEFT]){
					player->MoveLeft();
				}
				else if (keys[RIGHT]){
					player->MoveRight();
				}
				else{
					player->ResetAnimation(0);//idle anim
				}

				if (keys[DASH] && (seconds > (DashTime + 1))){
					player->Dash(mousex, mousey);//calculates mouse angle before dash
					DashTime = seconds;//records dash time for use in next dash
				}
				//cout << FindAngle(player->GetX(), player->GetY(), ev.mouse.x, ev.mouse.y) << endl;
				//update
				for (iter = objects.begin(); iter != objects.end(); ++iter){
					if ((*iter)->GetID() == BASICENEMY ||
						(*iter)->GetID() == FRIENDLYWEAPON){//gives player variables to created objects that need it.
						(*iter)->SetValues(player->GetX(), player->GetY(), FindAngle(player->GetX(), player->GetY(), (*iter)->GetX(), (*iter)->GetY()));
					}
						(*iter)->Update();
				}

				for (iter = objects.begin(); iter != objects.end(); ++iter)
				{
					if (!(*iter)->Collidable()) continue;

					for (iter2 = iter; iter2 != objects.end(); ++iter2)
					{
						if (!(*iter2)->Collidable()) continue;
						if ((*iter)->GetID() == (*iter2)->GetID()) continue;

						if ((*iter)->CheckCollisions((*iter2)))
						{
							(*iter)->Collided((*iter2)->GetID());
							(*iter2)->Collided((*iter)->GetID());
						}
					}
				}
				if (player->GetHealth() <= 0){}//checks for death here
				//ChangeState(state, LOST);

			}
			//cull the dead
			for (iter = objects.begin(); iter != objects.end();)
			{
				if (!(*iter)->GetAlive())
				{
					delete (*iter);
					iter = objects.erase(iter);
				}
				else
					iter++;
			}
		}
		//==============================================
		//RENDER
		//==============================================
		if (render && al_is_event_queue_empty(event_queue))
		{
			render = false;

			//BEGIN PROJECT RENDER================
			for (iter = objects.begin(); iter != objects.end(); ++iter){
				(*iter)->Render();
			}

			//FLIP BUFFERS========================
			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));
		}
	}//end gameloop

	//==============================================
	//DESTROY PROJECT OBJECTS
	//==============================================
	for (iter = objects.begin(); iter != objects.end();)
	{
		(*iter)->Destroy();
		delete (*iter);
		iter = objects.erase(iter);
	}

	//titleScreen->Destroy();
	//lostScreen->Destroy();
	//delete titleScreen;
	//delete lostScreen;
	//al_destroy_bitmap(playerImage);
	//al_destroy_bitmap(playerSwordImage);

	//SHELL OBJECTS=================================
	al_destroy_font(font18);
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);
	al_destroy_display(display);

	return 0;
}
/*
double FindAngle(double X_1, double Y_1, double X_2, double Y_2){
	//double MouseAngle = atan2((ev.mouse.y - player->GetY()), (ev.mouse.x - player->GetX()))*180/PI;
	
	int lesser_x = 0, lesser_y = 0;
	int greater_x = 0, greater_y = 0;

	if (X_2 > X_1)
		lesser_x = X_1, greater_x = X_2;
	if (X_2 < X_1)
		lesser_x = X_2, greater_x = X_1;

	if (Y_2 > Y_1)
		lesser_y = Y_1, greater_y = Y_2;
	if (Y_2 < Y_1)
		lesser_y = Y_2, greater_y = Y_1;

	double dif_x = greater_x - lesser_x;
	double dif_y = greater_y - lesser_y;
	
	double Angle = atan(Y_2 - Y_1 / X_2 - X_1) *180 / PI;
	
	if (X_2 > X_1 &&//mouse to right
		Y_2 < Y_1//mouse above
		)//quadrant I
		Angle += 90;
	if (X_2 < X_1 &&//mouse to left
		Y_2 < Y_1//mouse above
		)//quadrant II
		Angle += 90;

	if (X_2 < X_1 &&//mouse to left
		Y_2 > Y_1//mouse below
		)//quadrant III
		Angle += 270;
	if (X_2 > X_1 &&//mouse to right
		Y_2 > Y_1//mouse below
		)//quadrant IV
		Angle += 270;
	
	Angle += 45;

	//Angle *= (ALLEGRO_PI / 180);//converts to "allegro degrees"
	cout << Angle << endl;
	return Angle;
}*/

double FindAngle(double X_1, double Y_1, double X_2, double Y_2){
	return atan2(Y_2 - Y_1, X_2 - X_1);
}

void BasicEnemyAI(BasicEnemy *enemy){

	if (enemy->GetX() < player->GetX() + 80 &&//checks x and y perimeter, to see if in attack range
		enemy->GetX() > player->GetX() - 80 &&
		enemy->GetY() < player->GetY() + 80 &&
		enemy->GetY() > player->GetY() - 80){
		enemy->SetMelee(true);

		enemy->MeleeFunc(player->GetX(), player->GetY());
	}

	if (enemy->GetMelee() == false &&
		rand() % 100 == 1){
		enemy->SetShoot(true);

		enemy->ShootFunc(player->GetX(), player->GetY());
	}

	if (enemy->GetShoot() == false &&//if nothing else, pursue
		enemy->GetMelee() == false){
		enemy->SetPursue(true);

		enemy->PursueFunc(player->GetX(), player->GetY(), FindAngle(enemy->GetX(), enemy->GetY(), player->GetX(), player->GetY()));
	}

	enemy->SetPursue(false);//done with everything, so set everything to false
	enemy->SetMelee(false);
	enemy->SetShoot(false);
}
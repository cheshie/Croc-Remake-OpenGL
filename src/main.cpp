#include "stdafx.h"
#include <string.h>

void OnRender();
void OnReshape(int, int);
void OnKeyPress(unsigned char, int, int);
void OnKeyDown(unsigned char, int, int);
void OnKeyUp(unsigned char, int, int);
void OnTimer(int);
void OnMouseMove(int, int);
void OnMouseClick(int, int, int, int);
void loadtextures();
void Render_level1();
void Render_level2();
void Render_level3();
void Render_level4();

void Initialize_level1();
void Initialize_level2();
void Initialize_level3();
void Initialize_level4();
void Render_lights();
void dropdiamonds();
void checkandrenderdiamonds(int start, int end);
void checkandrenderspecialdiamonds(int index);
void checkandrenderhearts(int start, int end);
void initializediamonds(int howmanydiamonds);


// // // // // LEVEL 1 DECLARATIONS // // // // // 
Sphere  * movableSphere;
Terrain * Level1_floor;
Terrain * Level1_rock;
Terrain * Level1_walls;
Enemy   * Level1_enemy;
Terrain * Level1_well1_walls;
Terrain * Level1_doors_right;
Terrain * Level1_doors_frame;
Terrain * Level1_doors_left;
Terrain * Level1_pool;
Terrain * Level1_teleportbox;
Scene scene;
Blackbox *trunk1;
Camera * camera;
Player * player;
NormalBox * box1;
Diamond * diamond;
Key * key;
Platform * Level1_platform1;
Platform * Level1_platform2;
Platform * Level1_well1_cover;
Platform * Level1_well1_teleport;
Friend  * Level1_friend1;

Well1 * well1;
Wood * wood;
cLava * Level1_lava;

Heart * heart;
vec3 * hearts_coords;
bool * hearts_taken;

vec3 * diamonds_coords;
bool * diamonds_taken;

int window_width, window_height;
vec3 mousePosition;
float diam_rot = 0.0f;
bool captureMouse;

bool light1state = true;
bool light2state = true;
bool light3state = false;
bool lavalightstate = true;
bool goldentrunkstate = true;

bool jump = 0;
bool started_game = 0;
float jump_height = 3.5f;
float jump_temp = 0.0f;
float time_since_start = 0.f;
vec3 * box_coords;
vec3 * trunks_position;
Sphere *playerS;
// // // // // LEVEL 1 DECLARATIONS // // // // // 

// // // // // LEVEL 2 DECLARATIONS // // // // // 
Terrain * Level2_floor1;
Terrain * Level2_arch;
Terrain * Level2_kopula;
Terrain * Level2_wall1;
Terrain * Level2_floor2;
Terrain * Level2_getbacktolevel1;
Terrain * Level2_getbacktolevel1wall;
Terrain * Level2_teleportboxto1;
Terrain * Level2_floor3;
Terrain * Level2_lastwall;

Terrain * Level2_doorsright1;
Terrain * Level2_doorsleft1;
Terrain * Level2_doorsright2;
Terrain * Level2_doorsleft2;
Terrain * Level2_arch2;
Terrain * Level2_teleportboxfinal;

Platform * Level2_movingplatform1;
Platform * Level2_movingplatform2;
Friend  * Level2_friend1;
Terrain * Level2_finalgong;



cLava   * Level2_lava;

// // // // // LEVEL 2 DECLARATIONS // // // // // 

// // // // // LEVEL 3 DECLARATIONS // // // // // 
Terrain * Level3_floor1;
Terrain * Level3_floor2;
Well1 * Level3_well1;

Platform * Level3_well1_teleport;
Platform * Level3_fallingplatform1;
Platform * Level3_fallingplatform2;
Platform * Level3_fallingplatform3;
bool light4state = 0;
float angle_diamonds;
Enemy * Level3_BIGENEMY;
Enemy * Level3_smallenemy;
vec3 * smallenemy_coords;
bool * smallenemy_isalive;
Friend * Level3_friend1;




// // // // // LEVEL 3 DECLARATIONS // // // // // 

// // // // // LEVEL 4 DECLARATIONS // // // // //
Terrain * Level4_floor1;
Terrain * Level4_walls;
Terrain * Level4_floor2;

Terrain * Level4_floor_moving1;
Terrain * Level4_floor_moving2;
Terrain * Level4_floor_moving3;
Terrain * Level4_floor_moving4;

Terrain * Level4_floor_moving5;
Terrain * Level4_floor_moving6;
Terrain * Level4_floor_moving7;
Terrain * Level4_floor_moving9;

Terrain * Level4_grid1;
Terrain * Level4_grid2;
Terrain * Level4_hempisphere;




Platform * Level4_platform1;
Platform * Level4_platform2;
Platform * Level4_platform3;
Platform * Level4_platform4;
Platform * Level4_platform5;
Platform * Level4_platform6;
Platform * Level4_platform7;
Platform * Level4_platform8;

Well1 * Level4_well1;
Platform * Level4_teleport;

Friend * Level4_friend;


cLava * Level4_lava;


// // // // // LEVEL 4 DECLARATIONS // // // // //  


// MISC // 
float diamonds_drop = 0;
bool dropping = 0;
vec3 * dropped_coords;
bool * dropped_state;
float * dropped_size;
Diamond * DDiam;
// MISC //


// MAIN MENU // 

bool ismainMenuActive = 1;

//MAIN MENU //

Terrain * daniotest;
Terrain * torus;
Terrain * croc_corpse;
Terrain * croc_eyes;
Terrain * croc_backpack;






// / // / / / / // / / / / / / // / 

//Pytania do prowadzacego: 
// Kamera - jak zrobic to plynnne obracanie
// Swiatla - dlaczego na 3 lvl nie dzialaja z ta latarka? 
// skompilowac kod na windows
// dzwiek - nie dziala openal
//Textury w blenderze - jak tutaj je wrzucic?

// / // / / / / // / / / / / / // / 



float T = 0;

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);

	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	glutCreateWindow("Croc: Gobbos Tribute");

	glutDisplayFunc(OnRender);
	glutReshapeFunc(OnReshape);
	glutKeyboardFunc(OnKeyPress);
	glutKeyboardUpFunc(OnKeyUp);
	glutTimerFunc(17, OnTimer, 0);
	glutPassiveMotionFunc(OnMouseMove);
	glutMotionFunc(OnMouseMove);
	glutMouseFunc(OnMouseClick);

	glClearColor(0.1f, 0.2f, 0.3f, 0.0);

	glEnable(GL_DEPTH_TEST);

	float gl_amb[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, gl_amb);

	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	FreeConsole();


	// Camera and player initialization
	player = new Player(vec3(2.5f, 1.f, 0.f), vec3(1.f, 0.f, 0.f), vec3(0.f, 0.f, 0.f), vec3(0.01f, 0.01f, 0.01f), 0.f);
	player->Load("../Resources/Models/Diamond.obj");
	player->textureName = "nope";
	scene.AddObject(player);

	croc_corpse = new Terrain(vec3(-0.6f, 0.f, 0.f), vec3(0.03, 0.03, 0.03), 180.f, vec3(0.6, 0.2, 0.8));
	croc_corpse->load("../Resources/Models/croc_corpse.obj");
	croc_corpse->textureName = "croc_corpse";

	croc_eyes = new Terrain(vec3(-0.6f, 0.f, 0.f), vec3(0.03, 0.03, 0.03), 180.f, vec3(0.6, 0.2, 0.8));
	croc_eyes->load("../Resources/Models/croc_eyes.obj");
	croc_eyes->textureName = "croc_eyes";

	croc_backpack = new Terrain(vec3(-0.6f, 0.f, 0.f), vec3(0.03, 0.03, 0.03), 180.f, vec3(0.6, 0.2, 0.8));
	croc_backpack->load("../Resources/Models/croc_backpack.obj");
	croc_backpack->textureName = "croc_backpack";

	camera = new Camera(vec3(player->pos.x, player->pos.y, 0.f), vec3(-1.0f, -.5f, 0.0f), vec3(0.f, 0.f, 0.f), 0.f);
	scene.AddObject(camera);

	torus = new Terrain(vec3(player->pos.x, player->pos.y, 0.f), vec3(0.6, 0.6, 0.6), 0.f, vec3(0.2, 0.6, 0.8));
	torus->load("../Resources/Models/Torus_tapniecie.obj");
	torus->textureName = "torus";

	//Angle diamonds
	angle_diamonds = 0.f;

	//Initialization of levels
	Initialize_level1();
	Initialize_level2();
	Initialize_level3();
	Initialize_level4();

	loadtextures();

	
	//starting position
	player->pos.x = 2.f;
	player->pos.y = 0.8f;
	player->pos.z = 0.f;

	glutMainLoop();

	return 0;
}

bool keystate[256];

void OnKeyPress(unsigned char key, int x, int y) {
	if (!keystate[key]) {
		OnKeyDown(key, x, y);
	}
	//else
	//OnKeyUp(key,x,y);

	keystate[key] = true;
}

void OnKeyDown(unsigned char key, int x, int y) {
	if (key == 27) {

		if(ismainMenuActive == 1)
		exit(0);

		//glutLeaveMainLoop();
		if (ismainMenuActive == 0)
			ismainMenuActive = 1;
		//else


		glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
		captureMouse = false;
	}
	if (key == 'o')
	{
		if (ismainMenuActive == 1)
		if (started_game == 0)
		{
			////printf("New Game\n");
			glutSetCursor(GLUT_CURSOR_NONE);
			captureMouse = true;
			glutWarpPointer(window_width / 2, window_height / 2);
			player->currentlevel = 1;
			ismainMenuActive = 0;
			started_game = 1;
		}
	}
	if (key == 'p')
	{
		if (ismainMenuActive == 1)
		if (started_game == 1)
		{
			////printf("Continue\n");
			glutSetCursor(GLUT_CURSOR_NONE);
			captureMouse = true;
			glutWarpPointer(window_width / 2, window_height / 2);
			ismainMenuActive = 0;
		}

	}
	if (key == 'f')
	{
		player->flyingMode = !player->flyingMode;
	}
	if (key == '1')
	{
		light1state = !light1state;
	}

	if (key == '2')
	{
		light2state = !light2state;
	}
	if (key == '3')
	{
		light3state = !light3state;
	}
	if (key == '4')
	{
		player->stop = 1;
		//////printf("stop!\n");
	}
	//Skok - spacja
	if (key == 32)
	{
		//player->onground = 0;
		if (player->jumping == 0)
		{
			player->maxrelativeheight = player->pos.y;
			player->makejump();
			player->doublejump = 0;
			player->falling = 1;
		}
		if (player->jumping && player->doublejump == 0 && fabs(player->pos.y - player->maxrelativeheight) >= 1.0f && player->timetonextjump == 0.f)
		{
			player->timetonextjump = 300.f;
			player->doublejump = 1;
		}
	}
	if (key == 'c' || player->doublejump == 1)
	{		
		if (sqrt((player->pos.x - Level1_enemy->pos.x)*(player->pos.x - Level1_enemy->pos.x) + (player->pos.z - Level1_enemy->pos.z)*(player->pos.z - Level1_enemy->pos.z)) < 0.4)
		{
			Level1_enemy->isAlive = 0;
			player->showtorus =1;
			//Level1_enemy->dissapearanimation();
		}

		for (int i = 0; i<10; i++)
		{
			if (sqrt((player->pos.x - smallenemy_coords[i].x)*(player->pos.x - smallenemy_coords[i].x) + (player->pos.z - smallenemy_coords[i].z)*(player->pos.z - smallenemy_coords[i].z)) < 0.5)
			{
				smallenemy_isalive[i] = 0;
				dropping = 1;
				player->showtorus =1;			
			}
		}

		if(sqrt((player->pos.x - Level2_finalgong->pos.x)*(player->pos.x - Level2_finalgong->pos.x) + (player->pos.z - Level2_finalgong->pos.z)*(player->pos.z - Level2_finalgong->pos.z)) < 0.25 && player->iWonTheGame == 0 && player->specialdiamonds[0] == 1 && player->specialdiamonds[1] == 1 && player->specialdiamonds[2] == 1)
		{
			player->iWonTheGame = 1;
			ismainMenuActive = 0;
		}
		
	}

	if(key == 'c')
	{
		player->turn = 1;
	}
	if (key == 'x')
	{
		player->direction *= -1;
	}
}

void OnKeyUp(unsigned char key, int x, int y) {
	keystate[key] = false;
}

void OnMouseMove(int x, int y)
{
	mousePosition.x = x;
	mousePosition.y = y;
}

void OnMouseClick(int button, int state, int x, int y)
{
	if (ismainMenuActive == 1)
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			//.	glutInitWindowSize(800, 600);
			//
			// if (mousePosition.x > 202 * glutGet(GLUT_WINDOW_WIDTH) / 800 && mousePosition.x * glutGet(GLUT_WINDOW_WIDTH) / 800 < 560 && mousePosition.y * glutGet(GLUT_INIT_WINDOW_HEIGHT) / 600 > 301 && mousePosition.y * glutGet(GLUT_INIT_WINDOW_HEIGHT) / 600 < 352)
			if (mousePosition.x > glutGet(GLUT_WINDOW_WIDTH)/4 && mousePosition.x < (glutGet(GLUT_WINDOW_WIDTH)/2 + glutGet(GLUT_WINDOW_WIDTH)/6) && mousePosition.y > glutGet(GLUT_WINDOW_HEIGHT)/2 && mousePosition.y < (glutGet(GLUT_WINDOW_HEIGHT)/2 + glutGet(GLUT_WINDOW_HEIGHT)/12) )
			
			{
				if (started_game == 0)
				{

					////printf("New Game\n");
					glutSetCursor(GLUT_CURSOR_NONE);
					captureMouse = true;
					glutWarpPointer(window_width / 2, window_height / 2);
					player->currentlevel = 1;
					ismainMenuActive = 0;
				}
			}

			//if (mousePosition.x > 202 && mousePosition.x < 560 && mousePosition.y > 393 && mousePosition.y < 446)
			if (mousePosition.x > glutGet(GLUT_WINDOW_WIDTH)/4 && mousePosition.x < (glutGet(GLUT_WINDOW_WIDTH)/2 + glutGet(GLUT_WINDOW_WIDTH)/6) && mousePosition.y > glutGet(GLUT_WINDOW_HEIGHT)/1.5 && mousePosition.y < (glutGet(GLUT_WINDOW_HEIGHT)/1.5 + glutGet(GLUT_WINDOW_HEIGHT)/12) )			
			{
				if (started_game == 1)
				{
					////printf("Continue\n");
					glutSetCursor(GLUT_CURSOR_NONE);
					captureMouse = true;
					glutWarpPointer(window_width / 2, window_height / 2);
					ismainMenuActive = 0;
				}
			}


			//if (mousePosition.x > 202 && mousePosition.x < 560 && mousePosition.y > 482 && mousePosition.y < 541)
			if (mousePosition.x > glutGet(GLUT_WINDOW_WIDTH)/4 && mousePosition.x < (glutGet(GLUT_WINDOW_WIDTH)/2 + glutGet(GLUT_WINDOW_WIDTH)/6) && mousePosition.y > glutGet(GLUT_WINDOW_HEIGHT)/1.2 && mousePosition.y < (glutGet(GLUT_WINDOW_HEIGHT)/1.2 + glutGet(GLUT_WINDOW_HEIGHT)/12) )						
			{
				////printf("Exit\n");
				delete[] smallenemy_coords;
				delete[] smallenemy_isalive;
				delete[] hearts_coords;
				delete[] hearts_taken;
				delete[] diamonds_coords;
				delete[] diamonds_taken;

				delete[] dropped_coords;
				delete[] dropped_state;
				delete[] dropped_size;	

				delete movableSphere;
				delete Level1_floor;
				delete Level1_rock;
				delete Level1_walls;
				delete Level1_enemy;

				delete Level1_well1_walls;
				delete Level1_doors_right;
				delete Level1_doors_frame;
				delete Level1_doors_left;
				delete Level1_pool;
				delete Level1_teleportbox;
				delete trunk1;
				delete camera;
				delete player;
				delete box1;
				delete diamond;
				delete key;
				delete Level1_platform1;
				delete Level1_platform2;
				delete Level1_well1_cover;
				delete Level1_well1_teleport;
				delete Level1_friend1;

				delete well1;
				delete wood;
				delete Level1_lava;

				delete heart;
				delete box_coords;
				delete trunks_position;
				delete playerS;
				// // // // // LEVEL 1 DECLARATIONS // // // // // 

				// // // // // LEVEL 2 DECLARATIONS // // // // // 
				delete Level2_floor1;
				delete Level2_arch;
				delete Level2_kopula;
				delete Level2_wall1;
				delete Level2_floor2;
				delete Level2_getbacktolevel1;
				delete Level2_getbacktolevel1wall;
				delete Level2_teleportboxto1;
				delete Level2_floor3;
				delete Level2_lastwall;

				delete Level2_doorsright1;
				delete Level2_doorsleft1;
				delete Level2_doorsright2;
				delete Level2_doorsleft2;
				delete Level2_arch2;
				delete Level2_teleportboxfinal;

				delete Level2_movingplatform1;
				delete Level2_movingplatform2;

				delete Level2_lava;

				// // // // // LEVEL 2 DECLARATIONS // // // // // 

				// // // // // LEVEL 3 DECLARATIONS // // // // // 
				delete Level3_floor1;
				delete Level3_floor2;
				delete Level3_well1;

				delete Level3_well1_teleport;
				delete Level3_fallingplatform1;
				delete Level3_fallingplatform2;
				delete Level3_fallingplatform3;
				delete Level3_BIGENEMY;
				delete Level3_smallenemy;
				delete smallenemy_coords;
				delete smallenemy_isalive;

				// // // // // LEVEL 3 DECLARATIONS // // // // // 

				// // // // // LEVEL 4 DECLARATIONS // // // // //
				delete Level4_floor1;
				delete Level4_walls;
				delete Level4_floor2;

				delete Level4_floor_moving1;
				delete Level4_floor_moving2;
				delete Level4_floor_moving3;
				delete Level4_floor_moving4;

				delete Level4_floor_moving5;
				delete Level4_floor_moving6;
				delete Level4_floor_moving7;
				delete Level4_floor_moving9;

				delete Level4_platform1;
				delete Level4_platform2;
				delete Level4_platform3;
				delete Level4_platform4;
				delete Level4_lava;



				exit(0);
			}
		}
	}
}

void OnTimer(int id) {

	float kierunek_horizontal = (float)atan2(player->dir.z, player->dir.x);
	float kierunek_vertical = (float)atan2(player->dir.z, player->dir.y);

	bool isplayerinmoveu = 0;
	bool isplayerinmoved = 0;
	bool isplayerinmovel = 0;
	bool isplayerinmover = 0;


	if (ismainMenuActive == 0)
	{
		if (keystate['w'] && player->iWonTheGame != 1) {
			player->pos = player->pos - (player->dir * player->speed);
		}

		if (keystate['s'] && player->iWonTheGame != 1) {

			player->pos = player->pos + (player->dir * player->speed);
		}
		if (keystate['a'] && player->iWonTheGame != 1 && player->direction != -1) {
			
			player->rotate += 1.2 * player->direction;
			//isplayerinmovel = 1;

		}
		if (keystate['d']&& player->iWonTheGame != 1 && player->direction != -1) {
			//player->velocity_horizontal = 1;
			player->rotate -= 1.2 * player->direction;
			//isplayerinmover = 1;
		}
		if (keystate['q']) {
			//player->velocity_horizontal = -1;
			//player->rotate -= 0.8;
			//isplayerinmover = 1;
		}
		if (keystate['e']) {
			
			//player->velocity_horizontal = 1;
			//player->rotate -= 0.8;
			//isplayerinmover = 1;
		}


		if (isplayerinmoveu || isplayerinmoved || isplayerinmovel || isplayerinmover)
			player->ismoving = 1;
		else
			player->ismoving = 0;
	}

	if (captureMouse)
	{
		glutWarpPointer(window_width / 2, window_height / 2);
	}
	if (keystate['e']) {
		player->rotate += 0.8;
	}

	if (keystate['q']) {
		player->rotate -= 0.8;
	}
	if (keystate['o'])
	{

	}


	scene.Update();

	glutTimerFunc(17, OnTimer, 0);
}

void OnRender() {

	float time_since_start_new = glutGet(GLUT_ELAPSED_TIME);
	player->deltatime = time_since_start_new - time_since_start;
	camera->deltatime = time_since_start_new - time_since_start;

	time_since_start = time_since_start_new;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//scene.CokolwiekDisplay();

	if (ismainMenuActive == 0 && player->iWonTheGame == 0)
	{
		scene.DiamondDisplay();
		scene.Diamond1Display(*player);
		scene.Diamond2Display(*player);
		scene.Diamond3Display(*player);

		scene.LifeDisplay();
		scene.KeyDisplay(*player);
		scene.NumberofDiamondsDisplayd1(*player);
		scene.NumberofDiamondsDisplayd2(*player);
		scene.NumberofLivesDisplayd1(*player);
		scene.NumberofLivesDisplayd2(*player);

		scene.FriendDisplay();
		scene.NumberoffriendsDisplayd1(*player);
		scene.NumberoffriendsDisplayd2(*player);

	}
	
	if (ismainMenuActive == 1 && player->iWonTheGame == 0)
	{

		scene.mainMenuNewGame();
		scene.mainMenuContinue();
		scene.mainMenuExit();

		scene.mainMenuCover();
	}

	
	if ( player->iWonTheGame == 1 )
	{
		scene.mainMenuConGratulations();
		scene.ResultDiamond();
		scene.ResultDisplayd1(player->diamonds_counter,0);
		scene.ResultDisplayd2(player->diamonds_counter,0);

		scene.ResultFriend();
		scene.ResultDisplayd1(player->friendscounter,20);
		scene.ResultDisplayd2(player->friendscounter,20);

		scene.ResultLife();
		scene.ResultDisplayd1(player->lives_counter,40);
		scene.ResultDisplayd2(player->lives_counter,40);
	}

	camera->myUpdate(*player, scene.boundaryMax, scene.boundaryMin);
	//player->test_sphere();
	player->Render();
	croc_corpse->Render("croc_corpse",*player);
	croc_backpack->Render("croc_backpack",*player);
	croc_eyes->Render("croc_eyes",*player);	

	player->Update();

	if (player->timetoblink == 0 && player->timesblink > 0)
	{
		player->timetoblink = 10.f;
		player->timesblink--;
	}


	if (player->currentlevel == 1)
		Render_level1();

	if (player->currentlevel == 2)
		Render_level2();

	if (player->currentlevel == 3)
		Render_level3();

	if (player->currentlevel == 4)
		Render_level4();

	Render_lights();

	if (player->iWonTheGame == 1)
		ismainMenuActive = 1;

	angle_diamonds += 4;
	angle_diamonds = fmod(angle_diamonds, 350.f);

	diamonds_drop = fmod(diamonds_drop, 300.f);

	if(player->endurance == 1)
	player->dropalldiamonds = 1;

	if(player->dropalldiamonds == 1 || player->dropalldiamonds == 2)
	dropdiamonds();

	if(player->showtorus == 1)
	{
		torus->pos = player->pos;
		torus->pos.y = player->pos.y;
		torus->Render("torus",*player);
		player->torussize+=0.5;

		if(player->torussize > 4.f)
		player->showtorus = 0;
	}
	else
	player->torussize = 0.6;

	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
}

void OnReshape(int width, int height) {

	window_width = width;
	window_height = height;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, width, height);
	gluPerspective(60.0f, (float)width / height, .01f, 250.0f);
}


void loadtextures(){

	TextureManager::getInstance()->LoadTexture("level1_floor", "../Resources/Textures/level1_floor_grass.png", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST, GL_BGRA_EXT);
	TextureManager::getInstance()->LoadTexture("level1_rock", "../Resources/Textures/clay.jpg", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST, GL_BGR_EXT);
	TextureManager::getInstance()->LoadTexture("level1_well1_walls", "../Resources/Textures/moss_stone.jpg", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST, GL_BGR_EXT);
	TextureManager::getInstance()->LoadTexture("level1_walls", "../Resources/Textures/level1_walls.png", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST, GL_BGRA_EXT);
	TextureManager::getInstance()->LoadTexture("level1_wood", "../Resources/Textures/wood1.jpg", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST, GL_BGR_EXT);
	TextureManager::getInstance()->LoadTexture("level1_well1_cover", "../Resources/Textures/wood1.jpg", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST, GL_BGR_EXT);
	TextureManager::getInstance()->LoadTexture("skydome", "../Resources/Textures/skydome.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST, GL_BGR_EXT);
	TextureManager::getInstance()->LoadTexture("trunk", "../Resources/Textures/Przydatne/BR_PMT_RGBA_4444/CRYSTAL1.png", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST, GL_BGRA_EXT);
	TextureManager::getInstance()->LoadTexture("diamond_counter_0", "../Resources/Textures/SCORE_0.png", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST, GL_BGRA_EXT);
	TextureManager::getInstance()->LoadTexture("diamond_counter_1", "../Resources/Textures/SCORE_1.png", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST, GL_BGRA_EXT);
	TextureManager::getInstance()->LoadTexture("diamond_counter_2", "../Resources/Textures/SCORE_2.png", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST, GL_BGRA_EXT);
	TextureManager::getInstance()->LoadTexture("diamond_counter_3", "../Resources/Textures/SCORE_3.png", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST, GL_BGRA_EXT);
	TextureManager::getInstance()->LoadTexture("diamond_counter_4", "../Resources/Textures/SCORE_4.png", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST, GL_BGRA_EXT);
	TextureManager::getInstance()->LoadTexture("diamond_counter_5", "../Resources/Textures/SCORE_5.png", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST, GL_BGRA_EXT);
	TextureManager::getInstance()->LoadTexture("diamond_counter_6", "../Resources/Textures/SCORE_6.png", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST, GL_BGRA_EXT);
	TextureManager::getInstance()->LoadTexture("diamond_counter_7", "../Resources/Textures/SCORE_7.png", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST, GL_BGRA_EXT);
	TextureManager::getInstance()->LoadTexture("diamond_counter_8", "../Resources/Textures/SCORE_8.png", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST, GL_BGRA_EXT);
	TextureManager::getInstance()->LoadTexture("diamond_counter_9", "../Resources/Textures/SCORE_9.png", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST, GL_BGRA_EXT);
	TextureManager::getInstance()->LoadTexture("heart", "../Resources/Textures/CRYSTAL1.png", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST, GL_BGRA_EXT);
	TextureManager::getInstance()->LoadTexture("croclife", "../Resources/Textures/CROCLIFE.png", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST, GL_BGRA_EXT);
	TextureManager::getInstance()->LoadTexture("questionbox", "../Resources/Textures/questionbox.jpg", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST, GL_BGR_EXT);
	TextureManager::getInstance()->LoadTexture("platform_green", "../Resources/Textures/platform_green.png", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST, GL_BGRA_EXT);
	TextureManager::getInstance()->LoadTexture("goldkey", "../Resources/Textures/KEY.png", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST, GL_BGRA_EXT);
	TextureManager::getInstance()->LoadTexture("sdiamond1", "../Resources/Textures/sdiamond1.png", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST, GL_BGRA_EXT);
	TextureManager::getInstance()->LoadTexture("sdiamond2", "../Resources/Textures/sdiamond2.png", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST, GL_BGRA_EXT);
	TextureManager::getInstance()->LoadTexture("sdiamond3", "../Resources/Textures/sdiamond3.png", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST, GL_BGRA_EXT);
	TextureManager::getInstance()->LoadTexture("woodendoor", "../Resources/Textures/wooden_plank_door.jpg", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST, GL_BGR_EXT);
	TextureManager::getInstance()->LoadTexture("lava", "../Resources/Textures/lava.png", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST, GL_BGRA_EXT);
	TextureManager::getInstance()->LoadTexture("level1_well1_teleport", "../Resources/Textures/Level1_well1_teleport.png", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST, GL_BGRA_EXT);
	TextureManager::getInstance()->LoadTexture("mainMenuCover", "../Resources/Textures/mainMenuCover.png", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST, GL_BGRA_EXT);
	TextureManager::getInstance()->LoadTexture("mainMenuNewGame", "../Resources/Textures/New_game.png", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST, GL_BGRA_EXT);
	TextureManager::getInstance()->LoadTexture("mainMenuContinue", "../Resources/Textures/Continue.png", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST, GL_BGRA_EXT);
	TextureManager::getInstance()->LoadTexture("mainMenuExit", "../Resources/Textures/Exit.png", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST, GL_BGRA_EXT);
	TextureManager::getInstance()->LoadTexture("mainMenuConGratulations", "../Resources/Textures/ConGratulations.png", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST, GL_BGRA_EXT);
	TextureManager::getInstance()->LoadTexture("level2_floor1", "../Resources/Textures/Level2_floor1.jpg", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST, GL_BGR_EXT);
	TextureManager::getInstance()->LoadTexture("diamonds_normal", "../Resources/Textures/diamond.png", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST, GL_BGRA_EXT);
	TextureManager::getInstance()->LoadTexture("level2_arch", "../Resources/Textures/Level2_floor1.jpg", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST, GL_BGR_EXT);
	TextureManager::getInstance()->LoadTexture("specialdoorsleft", "../Resources/Textures/specialdoorleft.jpg", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST, GL_BGR_EXT);
	TextureManager::getInstance()->LoadTexture("specialdoorsright", "../Resources/Textures/specialdoorright.jpg", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST, GL_BGR_EXT);
	TextureManager::getInstance()->LoadTexture("level3_floor1", "../Resources/Textures/sand.jpg", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST, GL_BGR_EXT);
	TextureManager::getInstance()->LoadTexture("desertbox", "../Resources/Textures/desertbox.jpg", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST, GL_BGR_EXT);
	TextureManager::getInstance()->LoadTexture("level3_well", "../Resources/Textures/brick.jpg", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST, GL_BGR_EXT);
	TextureManager::getInstance()->LoadTexture("level2_box", "../Resources/Textures/level2_box.jpg", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST, GL_BGR_EXT);
	TextureManager::getInstance()->LoadTexture("level3platform", "../Resources/Textures/Level3_platform.jpg", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST, GL_BGR_EXT);
	TextureManager::getInstance()->LoadTexture("friend", "../Resources/Textures/friend.png", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST, GL_BGR_EXT);
	TextureManager::getInstance()->LoadTexture("Level4_floor1", "../Resources/Textures/snow1.png", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST, GL_BGRA_EXT);
	TextureManager::getInstance()->LoadTexture("Level4_walls", "../Resources/Textures/icewalls1.png", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST, GL_BGRA_EXT);
	TextureManager::getInstance()->LoadTexture("Level1_goldenchest", "../Resources/Textures/golden_chest.jpg", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST, GL_BGR_EXT);
	TextureManager::getInstance()->LoadTexture("Level4_lavawater", "../Resources/Textures/icewater.png", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST, GL_BGRA_EXT);
	TextureManager::getInstance()->LoadTexture("level4platform", "../Resources/Textures/iceplatform.png", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST, GL_BGRA_EXT);
	TextureManager::getInstance()->LoadTexture("Level4_well", "../Resources/Textures/Level4_well.png", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST, GL_BGRA_EXT);
	TextureManager::getInstance()->LoadTexture("Level4_box", "../Resources/Textures/snowbox.jpg", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST, GL_BGR_EXT);
	TextureManager::getInstance()->LoadTexture("Level4_grid", "../Resources/Textures/grid1.png", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST, GL_BGRA_EXT);
	TextureManager::getInstance()->LoadTexture("Level4_hemisphere", "../Resources/Textures/hemisphere.jpg", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST, GL_BGR_EXT);
	TextureManager::getInstance()->LoadTexture("finalgong", "../Resources/Textures/gongend.png", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST, GL_BGRA_EXT);
	TextureManager::getInstance()->LoadTexture("croc_corpse", "../Resources/Textures/croc_corpse.jpg", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST, GL_BGR_EXT);
	TextureManager::getInstance()->LoadTexture("croc_eyes", "../Resources/Textures/eyes.jpg", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST, GL_BGR_EXT);
	TextureManager::getInstance()->LoadTexture("croc_backpack", "../Resources/Textures/backpack.jpg", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST, GL_BGR_EXT);
	TextureManager::getInstance()->LoadTexture("monkey", "../Resources/Textures/monkey.png", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST, GL_BGRA_EXT);

}

void Render_level1()
{
	if(started_game == 0)
	{
		started_game = 1;
		player->pos.x = 3.39f;
		player->pos.y = 0.2f;
		player->pos.z = 0.4f;
		player->makejump(4.f);
	}
	//daniotest->Render("Danio", *player);

	scene.boundaryMin = vec3(-8.5f, -2, -6.5f);
	scene.boundaryMax = vec3(5.8f, 3.5, 4.5f);

	diamonds_coords[1] = vec3(0.4f, 1.2f, 2.6f);
	diamonds_coords[0] = vec3(5.4f, 0.2f, 2.55f);
	diamonds_coords[2] = vec3(0.80f, 1.1f, -1.f);


	light4state = 0;
	light1state = 1;
	box1->textureName = "questionbox";

	scene.Render();

	Level1_floor->Render("floor", *player);
	Level1_rock->Render("rock", *player);
	Level1_walls->Render("walls", *player);
	Level1_doors_right->Render("Level1_wooden_door_right", *player);
	Level1_doors_left->Render("Level1_wooden_door_left", *player);
	Level1_doors_right->WoodenDoorOpen(*player);
	Level1_doors_left->WoodenDoorOpen(*player);
	Level1_teleportbox->Render("Level1_teleportbox", *player);
	Level1_pool->Render("pool", *player);
	Level1_enemy->Render(*player);


	Level1_friend1->Render(*player);

	wood->Render(*player);
	well1->Render(*player);

	Level1_platform1->Render(*player, 0);
	Level1_platform2->Render(*player, 1);
	Level1_well1_cover->Render(*player, 2);
	Level1_well1_teleport->Render(*player, 3);


	trunk1->Paint(trunks_position[0], *player, 0);

	Level1_lava->Draw(*player);

	for (int i = 0; i<1; i++)
	{
		box1->Render(*player, box_coords[i], i);
	}
	
	checkandrenderdiamonds(3,6);
	checkandrenderspecialdiamonds(0);
	checkandrenderhearts(1,2);
	
}

void Initialize_level1()
{
	//daniotest = new Terrain(vec3(0.0f, 0.5f, 0.f), vec3(0.8, 0.6, 0.6), 0.f, vec3(0.6, 0.2, 0.8));
	//daniotest->load("../Resources/Models/Danio2.obj");

	box1 = new NormalBox(vec3(.80f, 0.3f, 1.6f));
	box1->Load("../Resources/Models/Level1_testbox.obj");
	box1->textureName = "questionbox";

	diamond = new Diamond(vec3(-.80f, 0.1f, 1.0f));
	diamond->Load("../Resources/Models/Diamond.obj");
	diamond->textureName = "diamonds_normal";

	DDiam = new Diamond(vec3(-.80f, 100.1f, 1.0f));
	DDiam->Load("../Resources/Models/Diamond.obj");
	DDiam->textureName = "diamonds_normal";

	heart = new Heart(vec3(-.80f, 0.1f, 1.0f));
	heart->Load("../Resources/Models/Heart.obj");

	box_coords = new vec3[9];
	box_coords[0] = vec3(vec3(1.8f, 0.3f, 3.0f));
	box_coords[1] = vec3(vec3(100.9f, 100.3f, 2.6f));
	box_coords[2] = vec3(vec3(100.9f, 100.3f, 2.2f));

	diamonds_coords = new vec3[44];
	diamonds_taken = new bool[44];

	diamonds_coords[31] = vec3(-2.80f, 100.1f, -1.f);

	diamonds_coords[3] = vec3(.20f, 0.1f, 0.0f);
	diamonds_coords[4] = vec3(.80f, 0.1f, .0f);
	diamonds_coords[5] = vec3(1.40f, 0.1f, 0.f);

	for (int i = 0; i<26; i++)
		diamonds_taken[i] = 0;

	hearts_coords = new vec3[3];
	hearts_taken = new bool[3];

	hearts_coords = new vec3[3];
	hearts_taken = new bool[3];

	hearts_coords[0] = vec3(-1.8f, 0.4f, 1.0f);
	hearts_coords[1] = vec3(1.8f, 0.4f, 3.0f);
	hearts_coords[2] = vec3(-1.8f, 0.4f, -1.f);

	for (int i = 0; i<3; i++)
		hearts_taken[i] = 0;

	Level1_platform1 = new Platform(vec3(-.35f, 1.4f, 1.39f), 1, 1.f);
	Level1_platform1->Load("../Resources/Models/Platform.obj");
	Level1_platform1->textureName = "platform_green";

	Level1_platform2 = new Platform(vec3(-.35f, 1.4f, -.2f), 2, 1.f);
	Level1_platform2->Load("../Resources/Models/Platform.obj");
	Level1_platform2->textureName = "platform_green";

	Level1_well1_cover = new Platform(vec3(-0.35f, 0.4f, 2.9f), 5, 1.f);
	Level1_well1_cover->Load("../Resources/Models/Platform.obj");
	Level1_well1_cover->textureName = "level1_well1_cover";

	Level1_well1_teleport = new Platform(vec3(-0.35f, 0.01f, 2.9f), 6, 1.f);
	Level1_well1_teleport->Load("../Resources/Models/Level1_well1_teleport.obj");
	Level1_well1_teleport->textureName = "level1_well1_teleport";


	Level1_floor = new Terrain(vec3(-0.6f, 0.f, 0.f), vec3(0.6, 0.6, 0.6), 0.f, vec3(0.6, 0.2, 0.8));
	Level1_floor->load("../Resources/Models/Level1_floor1.obj");
	Level1_floor->textureName = "level1_floor";

	Level1_walls = new Terrain(vec3(-0.8f, 0, 0), vec3(0.6, 0.6, 0.6), 0.f, vec3(0.2, 0.6, 0.8));
	Level1_walls->load("../Resources/Models/Level1_walls.obj");
	Level1_walls->textureName = "level1_walls";

	Level1_pool = new Terrain(vec3(-4.5f, -0.8f, 0), vec3(0.6, 0.6, 0.8), 0.f, vec3(0.2, 0.6, 0.8));
	Level1_pool->load("../Resources/Models/Level1_pool.obj");
	Level1_pool->textureName = "level1_walls";

	Level1_rock = new Terrain(vec3(4.4, 0.1, -3.7), vec3(0.7, 0.7, 0.5), 0.f, vec3(0.2, 0.6, 0.8));
	Level1_rock->load("../Resources/Models/Level1_rock.obj");
	Level1_rock->textureName = "level1_rock";

	well1 = new Well1(vec3(-0.35f, 0.2f, 2.9f));
	well1->Load("../Resources/Models/Level1_well1_walls.obj");
	well1->textureName = "level1_well1_walls";

	Level1_doors_frame = new Terrain(vec3(0, 0, 0), vec3(0.5, 0.5, 0.5), 0.f, vec3(0.2, 0.6, 0.8));
	Level1_doors_frame->load("../Resources/Models/Level1_doors_frame.obj");

	Level1_doors_right = new Terrain(vec3(-7.53f, 0.0f, -0.65f), vec3(1.3, 0.8, 0.71), 0.f, vec3(0.2, 0.6, 0.8));
	Level1_doors_right->load("../Resources/Models/Level1_doors_right.obj");
	Level1_doors_right->textureName = "woodendoor";

	//Level1_doors_left = new Terrain(vec3(-7.60f, 0.0f, 1.10f), vec3(0.9,0.8,0.71), 180.f ,vec3(0.2,0.6,0.8));
	Level1_doors_left = new Terrain(vec3(-7.60f, 0.0f, 1.10f), vec3(0.9, 0.8, 0.71), 180.f, vec3(0.2, 0.6, 0.8));
	Level1_doors_left->load("../Resources/Models/Level1_doors_right.obj");
	Level1_doors_left->textureName = "woodendoor";

	Level1_teleportbox = new Terrain(vec3(-8.8f, 1.3f, 0.0f), vec3(0.1, 0.8, 0.71), 0.f, vec3(0.8, 0.8, 0.8));
	Level1_teleportbox->load("../Resources/Models/Level1_teleportbox.obj");

	Level1_lava = new cLava(2.f, "level1_lava", vec3(-6.5f, 0.f, -8.f));

	trunk1 = new Blackbox();
	trunk1->load();
	trunk1->load2();
	trunk1->textureName = "trunk";

	trunks_position = new vec3[1];
	trunks_position[0] = vec3(5.5f, 0.f, 2.4f);

	wood = new Wood(vec3(-4.4f, 0.0f, .0));
	wood->Load("../Resources/Models/Level1_wood.obj");

	Level1_enemy = new Enemy(vec3(-2.0f, 0.2f, 1.5f), vec3(1.f, 0.f, 1.f), vec3(0.f, 0.f, 0.f), vec3(0.09f, 0.09f, 0.09f), 0.f);

	Level1_friend1 = new Friend(vec3(1.8f, 0.6f, 3.0f), vec3(0.002, 0.002, 0.002), vec3(0.2, 0.2, 0.2), vec3(0.1, 0.1, 0.1), 0.f);
	Level1_friend1->Load("../Resources/Models/bunny.obj");

}

void Initialize_level2()
{


	key = new Key(vec3(-17.4f, 0.2f, 1.0f));
	key->Load("../Resources/Models/Key.obj");


	Level2_friend1 = new Friend(vec3(-6.5f, 0.6f, -2.5f), vec3(0.002, 0.002, 0.002), vec3(0.2, 0.2, 0.2), vec3(0.1, 0.1, 0.1), 0.f);
	Level2_friend1->Load("../Resources/Models/bunny.obj");


	Level2_floor1 = new Terrain(vec3(0.0f, 0.0f, 0.f), vec3(1.0, 0.6, 0.6), 90.f, vec3(0.6, 0.2, 0.8));
	Level2_floor1->load("../Resources/Models/Level2_floor1.obj");
	Level2_floor1->textureName = "level2_floor1";

	Level2_arch = new Terrain(vec3(-4.8f, 0.f, 0.f), vec3(0.6, 0.6, 0.6), 90.f, vec3(0.6, 0.2, 0.8));
	Level2_arch->load("../Resources/Models/Level2_arch.obj");
	Level2_arch->textureName = "level2_arch";

	Level2_kopula = new Terrain(vec3(-4.8f, -1.9f, 0.f), vec3(5.6, 1.8, 0.8), 0.f, vec3(0.6, 0.2, 0.8));
	Level2_kopula->load("../Resources/Models/Level2_kopula.obj");
	Level2_kopula->textureName = "level2_arch";

	Level2_wall1 = new Terrain(vec3(-4.8f, 0.0f, 0.f), vec3(0.6, 0.6, 0.6), 90.f, vec3(0.6, 0.2, 0.8));
	Level2_wall1->load("../Resources/Models/Level2_wall1.obj");
	Level2_wall1->textureName = "level2_arch";

	Level2_floor2 = new Terrain(vec3(-6.0f, 0.0f, 0.f), vec3(1.4, 0.6, 1.2), 0.f, vec3(0.6, 0.2, 0.8));
	Level2_floor2->load("../Resources/Models/Level2_floor2.obj");
	Level2_floor2->textureName = "level2_arch";

	Level2_floor3 = new Terrain(vec3(-18.0f, 0.0f, 0.f), vec3(1.4, 0.6, 2.2), 0.f, vec3(0.6, 0.2, 0.8));
	Level2_floor3->load("../Resources/Models/Level2_floor2.obj");
	Level2_floor3->textureName = "level2_arch";

	Level2_lastwall = new Terrain(vec3(-20.0f, 0.0f, 0.f), vec3(0.6, 1.2, 1.2), 0.f, vec3(0.6, 0.2, 0.8));
	Level2_lastwall->load("../Resources/Models/Level2_lastwall.obj");
	Level2_lastwall->textureName = "level2_arch";

	Level2_getbacktolevel1 = new Terrain(vec3(5.0f, 0.0f, .0f), vec3(0.3, 0.4, 0.1), 90.f, vec3(0.6, 0.2, 0.8));
	Level2_getbacktolevel1->load("../Resources/Models/Level2_getbacktolevel1.obj");
	Level2_getbacktolevel1->textureName = "level2_arch";

	Level2_getbacktolevel1wall = new Terrain(vec3(5.0f, 0.0f, .0f), vec3(0.7, 0.41, 0.1), 90.f, vec3(0.6, 0.2, 0.8));
	Level2_getbacktolevel1wall->load("../Resources/Models/Level2_getbacktolevel1wall.obj");
	Level2_getbacktolevel1wall->textureName = "level2_arch";

	Level2_teleportboxto1 = new Terrain(vec3(5.8f, .2f, 0.0f), vec3(0.7, 0.8, 0.6), 180.f, vec3(0.6, 0.2, 0.8));
	Level2_teleportboxto1->load("../Resources/Models/Level1_teleportbox.obj");
	

	//Level2_doorsright1 = new Terrain(vec3(-7.53f, 0.0f, -0.65f), vec3(1.3,0.8,0.71), 0.f ,vec3(0.2,0.6,0.8));
	Level2_doorsright1 = new Terrain(vec3(4.40f, 0.0f, -.65f), vec3(1.3, 0.8, 0.71), 0.f, vec3(0.2, 0.6, 0.8));
	Level2_doorsright1->load("../Resources/Models/Level1_doors_right.obj");
	Level2_doorsright1->textureName = "woodendoor";

	//Level2_doorsleft1 = new Terrain(vec3(-7.60f, 0.0f, 1.10f), vec3(0.9,0.8,0.71), 180.f ,vec3(0.2,0.6,0.8));
	Level2_doorsleft1 = new Terrain(vec3(4.50f, 0.0f, 1.05f), vec3(1.3, 0.8, 0.71), 180.f, vec3(0.2, 0.6, 0.8));
	Level2_doorsleft1->load("../Resources/Models/Level1_doors_right.obj");
	Level2_doorsleft1->textureName = "woodendoor";

	//Level2_doorsright1 = new Terrain(vec3(-7.53f, 0.0f, -0.65f), vec3(1.3,0.8,0.71), 0.f ,vec3(0.2,0.6,0.8));
	Level2_doorsright2 = new Terrain(vec3(-18.10f, 0.0f, -.65f), vec3(1.3, 0.8, 0.71), 0.f, vec3(0.2, 0.6, 0.8));
	Level2_doorsright2->load("../Resources/Models/Level1_doors_right.obj");
	Level2_doorsright2->textureName = "specialdoorsright";

	//Level2_doorsleft1 = new Terrain(vec3(-7.60f, 0.0f, 1.10f), vec3(0.9,0.8,0.71), 180.f ,vec3(0.2,0.6,0.8));
	Level2_doorsleft2 = new Terrain(vec3(-18.20f, 0.0f, 1.10f), vec3(1.3, 0.8, 0.71), 180.f, vec3(0.2, 0.6, 0.8));
	Level2_doorsleft2->load("../Resources/Models/Level1_doors_right.obj");
	Level2_doorsleft2->textureName = "specialdoorsleft";

	Level2_arch2 = new Terrain(vec3(-20.2f, 0.0f, 0.3f), vec3(0.4, 0.5, 0.3), 90.f, vec3(0.6, 0.2, 0.8));
	Level2_arch2->load("../Resources/Models/Level2_getbacktolevel1.obj");
	Level2_arch2->textureName = "level2_arch";

	// Level2_teleportboxfinal = new Terrain(vec3(-18.9f, .5f, 0.3f), vec3(0.3, 0.4, 0.3), 0.f, vec3(0.6, 0.2, 0.8));
	// Level2_teleportboxfinal->load("../Resources/Models/Level1_teleportbox.obj");

	Level2_movingplatform1 = new Platform(vec3(-9.85f, 0.3f, 1.0f), 3, 1.f);
	Level2_movingplatform1->Load("../Resources/Models/Platform.obj");
	Level2_movingplatform1->textureName = "level2_arch";

	Level2_movingplatform2 = new Platform(vec3(-12.55f, 0.3f, -1.0f), 3, -1.4f);
	Level2_movingplatform2->Load("../Resources/Models/Platform.obj");
	Level2_movingplatform2->textureName = "level2_arch";

	//Level2_teleportboxto1 = new Terrain(vec3(5.8f, .2f, 0.0f), vec3(0.7, 0.8, 0.6), 180.f, vec3(0.6, 0.2, 0.8));
	//Level2_teleportboxto1->load("../Resources/Models/Level1_teleportbox.obj");
	Level2_finalgong = new Terrain(vec3(-18.9f, .4f, 0.3f), vec3(0.3, 0.3, 0.3), 90.f, vec3(0.6, 0.2, 0.8));
	Level2_finalgong->load("../Resources/Models/gong.obj");
	Level2_finalgong->textureName = "finalgong";


	Level2_lava = new cLava(64.f, "level2_lava", vec3(-32.0f, -0.6f, -12.0f));
}

void Render_level2()
{

	box1->textureName = "level2_box";

	Level2_floor1->Render("Level2_floor1", *player);
	Level2_arch->Render("Level2_arch", *player);
	Level2_kopula->Render("Level2_kopula", *player);
	Level2_wall1->Render("Level2_wall1", *player);
	Level2_floor2->Render("Level2_floor2", *player);
	Level2_lava->Draw(*player);
	Level2_getbacktolevel1->Render("Level2_getbacktolevel1", *player);
	Level2_getbacktolevel1wall->Render("Level2_getbacktolevel1wall", *player);
	Level2_teleportboxto1->Render("Level2_teleportboxto1", *player);
	Level2_floor3->Render("Level2_floor3", *player);
	Level2_lastwall->Render("Level2_lastwall", *player);
	Level2_friend1->Render(*player);


	Level2_doorsright1->Render("Level2_wooden_door_right", *player);
	Level2_doorsleft1->Render("Level2_wooden_door_left", *player);
	Level2_doorsright1->WoodenDoorOpen(*player);
	Level2_doorsleft1->WoodenDoorOpen(*player);

	Level2_doorsright2->Render("Level2specialdoorsright", *player);
	Level2_doorsleft2->Render("Level2specialdoorsleft", *player);
	Level2_doorsright2->WoodenDoorOpen(*player);
	Level2_doorsleft2->WoodenDoorOpen(*player);


	Level2_arch2->Render("Level2_arch2", *player);
	Level2_movingplatform1->Render(*player, 4);
	Level2_movingplatform2->Render(*player, 5);
	key->Render(*player, Level2_movingplatform2->pos);

	Level2_finalgong->Render("finalgong",*player);

	//Level2_teleportboxfinal->Render("Level2_teleportboxfinal", *player);

	//if(diamonds_taken[6] == 0 || diamonds_taken[7] == 0 ||diamonds_taken[8] == 0 )

	// diamonds_coords[0] = vec3( .40f, 100.201f, 0.f);
	// diamonds_coords[1] = vec3( - 0.8f, 100.202f, .0f);
	// diamonds_coords[2] = vec3( - 2.10f, 100.202f, 0.f);

	diamonds_coords[6] = vec3(.40f, 0.201f, 0.f);
	diamonds_coords[7] = vec3(-0.8f, 0.202f, .0f);
	diamonds_coords[8] = vec3(-2.10f, 0.202f, 0.f);

	diamonds_coords[9] = vec3(-6.6f, 0.2f, -2.35f);
	diamonds_coords[10] = vec3(-6.35f, 0.2f, -2.35f);
	diamonds_coords[11] = vec3(-6.5f, 0.2f, -2.5f);

	diamonds_coords[12] = vec3(-6.6f, 0.2f, 2.35f);
	diamonds_coords[13] = vec3(-6.35f, 0.2f, 2.35f);
	diamonds_coords[14] = vec3(-6.5f, 0.2f, 2.5f);

	box_coords[1] = vec3(vec3(-6.5f, 0.3f, -2.5f));
	box_coords[2] = vec3(vec3(-6.5f, 0.3f, 2.5f));

	for (int i = 1; i<3; i++)
	{
		box1->Render(*player, box_coords[i], i);
	}

	if (player->specialdiamonds[0] == 1 && player->specialdiamonds[1] == 1 && player->specialdiamonds[2] == 1)
	{
		scene.boundaryMin = vec3(-19.1f, -2, -20.5f);
		scene.boundaryMax = vec3(20.8f, 3.5, 20.5f);
	}
	else
	{
		scene.boundaryMin = vec3(-18.10f, -2, -20.5f);
		scene.boundaryMax = vec3(20.8f, 3.5, 20.5f);
	}

	checkandrenderdiamonds(6,15);
}

void Initialize_level3()
{
	Level3_floor1 = new Terrain(vec3(0.0f, 0.0f, 0.f), vec3(1.0, 0.6, 0.6), 0.f, vec3(0.6, 0.2, 0.8));
	Level3_floor1->load("../Resources/Models/Level3_floor1.obj");
	Level3_floor1->textureName = "level3_floor1";

	Level3_floor2 = new Terrain(vec3(-33.0f, 0.5f, 0.f), vec3(0.8, 0.6, 0.8), 0.f, vec3(0.6, 0.2, 0.8));
	Level3_floor2->load("../Resources/Models/Level3_floor2.obj");
	Level3_floor2->textureName = "level3_floor1";

	Level3_well1 = new Well1(vec3(-33.0f, 1.1f, 0.f));
	Level3_well1->Load("../Resources/Models/Level1_well1_walls.obj");
	Level3_well1->textureName = "level3_well";

	Level3_well1_teleport = new Platform(vec3(-33.0f, 1.0f, 0.f), 6, 1.f);
	Level3_well1_teleport->Load("../Resources/Models/Level1_well1_teleport.obj");
	Level3_well1_teleport->textureName = "level1_well1_teleport";

	Level3_fallingplatform1 = new Platform(vec3(-29.0f, 0.5f, 0.0f), 4, 1.f);
	Level3_fallingplatform1->Load("../Resources/Models/Platform.obj");
	Level3_fallingplatform1->textureName = "level3platform";

	Level3_fallingplatform2 = new Platform(vec3(-27.0f, 0.5f, 0.0f), 4, 1.f);
	Level3_fallingplatform2->Load("../Resources/Models/Platform.obj");
	Level3_fallingplatform2->textureName = "level3platform";

	Level3_fallingplatform3 = new Platform(vec3(-24.3f, 0.5f, 0.0f), 4, 1.f);
	Level3_fallingplatform3->Load("../Resources/Models/Platform.obj");
	Level3_fallingplatform3->textureName = "level3platform";

	Level3_BIGENEMY = new Enemy(vec3(21.5f, 0.9f, 6.f), vec3(1.f, 0.f, 1.f), vec3(0.f, 0.f, 0.f), vec3(1.2f, 1.2f, 1.2f), 0.f);
	Level3_BIGENEMY->Load("../Resources/Models/enemy_monkey.obj");
	Level3_BIGENEMY->textureName = "monkey";

	Level3_smallenemy = new Enemy(vec3(21.5f, 0.3f, -1.f), vec3(1.f, 0.f, 1.f), vec3(0.f, 0.f, 0.f), vec3(0.3f, 0.3f, 0.3f), 0.f);
	Level3_smallenemy->Load("../Resources/Models/enemy_monkey.obj");
	Level3_smallenemy->textureName = "monkey";
	Level3_smallenemy->dirmove = 4;

	smallenemy_coords = new vec3[10];
	smallenemy_isalive = new bool[10];

	Level3_friend1 = new Friend(vec3(18.9f, 0.6f, 2.6f), vec3(0.002, 0.002, 0.002), vec3(0.2, 0.2, 0.2), vec3(0.1, 0.1, 0.1), 0.f);
	Level3_friend1->Load("../Resources/Models/bunny.obj");

	for (int i = 0; i<10; i++)
	{
		smallenemy_isalive[i] = 0;
	}
}

void Render_level3()
{
	box1->textureName = "desertbox";

	//glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

	Level3_BIGENEMY->bigRender(*player);

	if (player->lost == 1)
	{
		for (int i = 0; i<10; i++)
		{
			smallenemy_isalive[i] = 0;
		}

		player->lost = 0;
		Level3_BIGENEMY->timer_stop2 = 150.f;
	}


	if (Level3_BIGENEMY->timer_stop2 == 0)
	{
		for (int i = 0; i<10; i++)
		{
			if (smallenemy_isalive[i] == 0)
			{
				smallenemy_coords[i] = Level3_BIGENEMY->pos;
				smallenemy_isalive[i] = 1;
				Level3_BIGENEMY->timer_stop2 = 100.f;
				smallenemy_coords[i].y = 0.3f;
				////printf("ENEMY DEPLOYED\n");
				break;
			}
		}
		// if(smallenemy_index < 10)
		// smallenemy_index ++;
		// else
		// smallenemy_index = 0;
	}


	if (player->pos.x < -15.f || Level3_BIGENEMY->pos.x >= player->pos.x)
		Level3_BIGENEMY->timer_stop2 = 100.f;

	////printf("TIME: %f\n",Level3_BIGENEMY->timer_stop2);

	Level3_friend1->Render(*player);

	for (int i = 0; i<10; i++)
	{
		if (smallenemy_isalive[i] == 1)
		{
			Level3_smallenemy->smallRender(*player, smallenemy_coords[i], smallenemy_isalive[i]);
		}
	}

	Level3_floor1->Render("Level3_floor1", *player);
	Level3_floor2->Render("Level3_floor2", *player);
	Level3_well1->Render(*player);
	Level3_well1_teleport->Render(*player, 1);

	Level3_fallingplatform1->Render(*player, 6);
	Level3_fallingplatform2->Render(*player, 7);
	Level3_fallingplatform3->Render(*player, 8);

	box_coords[3] = vec3(vec3(18.9f, 0.3f, 2.6f));
	box_coords[4] = vec3(vec3(14.9f, 0.3f, 2.6f));
	box_coords[5] = vec3(vec3(18.9f, 0.3f, -2.6f));
	box_coords[6] = vec3(vec3(14.9f, 0.3f, -2.6f));

	diamonds_coords[0] = vec3(-33.0f, 1000.5f, 0.f);
	diamonds_coords[1] = vec3(-33.0f, 1.5f, 0.f);
	diamonds_coords[2] = vec3(-33.0f, 1000.5f, 0.f);


	diamonds_coords[14] = vec3(18.9f, 0.2f, 2.45f);
	diamonds_coords[15] = vec3(18.75f, 0.2f, 2.45f);
	diamonds_coords[16] = vec3(18.7f, 0.2f, 2.6f);

	diamonds_coords[17] = vec3(14.9f, 0.2f, 2.45f);
	diamonds_coords[18] = vec3(14.75f, 0.2f, 2.45f);
	diamonds_coords[19] = vec3(14.7f, 0.2f, 2.6f);

	diamonds_coords[20] = vec3(18.9f, 0.2f, -2.45f);
	diamonds_coords[21] = vec3(18.75f, 0.2f, -2.45f);
	diamonds_coords[22] = vec3(18.7f, 0.2f, -2.45f);

	diamonds_coords[23] = vec3(14.9f, 0.2f, -2.45f);
	diamonds_coords[24] = vec3(14.75f, 0.2f, -2.45f);
	diamonds_coords[25] = vec3(14.7f, 0.2f, -2.6f);


	diamonds_coords[26] = vec3(-32.0f, 1.1f, 1.45f);
	diamonds_coords[27] = vec3(-32.5f, 1.1f, 1.45f);
	diamonds_coords[28] = vec3(-33.0f, 1.1f, 1.6f);

	diamonds_coords[29] = vec3(-32.0f, 1.1f, -1.45f);
	diamonds_coords[30] = vec3(-32.5f, 1.1f, -1.45f);

	hearts_coords[0] = vec3(-33.0f, 1.5f, 2.f);


	for (int i = 3; i<7; i++)
	{
		box1->Render(*player, box_coords[i], i);
	}

	scene.boundaryMin = vec3(-40.10f, -10, -20.5f);
	scene.boundaryMax = vec3(25.0f, 3.5, 20.5f);

	checkandrenderdiamonds(14,32);
	checkandrenderspecialdiamonds(1);
	checkandrenderhearts(0,1);

	//glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
}

void Initialize_level4()
{
	////printf("INIT\n");

	Level4_floor1 = new Terrain(vec3(2.0f, 0.6f, 0.f), vec3(1.5, 0.5, 3.5), 0.f, vec3(0.6, 0.2, 0.8));
	Level4_floor1->load("../Resources/Models/Level4_floor1.obj");
	Level4_floor1->textureName = "Level4_floor1";

	Level4_floor2 = new Terrain(vec3(-23.0f, 0.6f, 0.f), vec3(1.5, 0.5, 3.5), 0.f, vec3(0.6, 0.2, 0.8));
	Level4_floor2->load("../Resources/Models/Level4_floor1.obj");
	Level4_floor2->textureName = "Level4_floor1";

	Level4_floor_moving1 = new Terrain(vec3(-2.5f, 0.6f, -10.f), vec3(0.6, 0.5, 0.2), 0.f, vec3(0.5, 0.5, 0.5));
	Level4_floor_moving1->load("../Resources/Models/Level4_floor1.obj");
	Level4_floor_moving1->textureName = "Level4_floor1";

	Level4_floor_moving2 = new Terrain(vec3(-2.5f, 0.6f, -5.f), vec3(0.6, 0.5, 0.2), 0.f, vec3(0.5, 0.5, 0.5));
	Level4_floor_moving2->load("../Resources/Models/Level4_floor1.obj");
	Level4_floor_moving2->textureName = "Level4_floor1";

	Level4_floor_moving3 = new Terrain(vec3(-2.5f, 0.6f, 0.f), vec3(0.6, 0.5, 0.2), 0.f, vec3(0.5, 0.5, 0.5));
	Level4_floor_moving3->load("../Resources/Models/Level4_floor1.obj");
	Level4_floor_moving3->textureName = "Level4_floor1";

	Level4_floor_moving4 = new Terrain(vec3(-2.5f, 0.6f, 5.f), vec3(0.6, 0.5, 0.2), 0.f, vec3(0.5, 0.5, 0.5));
	Level4_floor_moving4->load("../Resources/Models/Level4_floor1.obj");
	Level4_floor_moving4->textureName = "Level4_floor1";

	Level4_floor_moving5 = new Terrain(vec3(-5.5f, 0.6f, -10.f), vec3(0.6, 0.5, 0.2), 0.f, vec3(0.5, 0.5, 0.5));
	Level4_floor_moving5->load("../Resources/Models/Level4_floor1.obj");
	Level4_floor_moving5->textureName = "Level4_floor1";

	Level4_floor_moving6 = new Terrain(vec3(-5.5f, 0.6f, -5.f), vec3(0.6, 0.5, 0.2), 0.f, vec3(0.5, 0.5, 0.5));
	Level4_floor_moving6->load("../Resources/Models/Level4_floor1.obj");
	Level4_floor_moving6->textureName = "Level4_floor1";

	Level4_floor_moving7 = new Terrain(vec3(-5.5f, 0.6f, 0.f), vec3(0.6, 0.5, 0.2), 0.f, vec3(0.5, 0.5, 0.5));
	Level4_floor_moving7->load("../Resources/Models/Level4_floor1.obj");
	Level4_floor_moving7->textureName = "Level4_floor1";

	Level4_floor_moving9 = new Terrain(vec3(-5.5f, 0.6f, 5.f), vec3(0.6, 0.5, 0.2), 0.f, vec3(0.5, 0.5, 0.5));
	Level4_floor_moving9->load("../Resources/Models/Level4_floor1.obj");
	Level4_floor_moving9->textureName = "Level4_floor1";

	Level4_walls = new Terrain(vec3(-12.2f, 0.0f, 0.f), vec3(1.5, 2.5, 1.5), 0.f, vec3(0.6, 0.2, 0.8));
	Level4_walls->load("../Resources/Models/Level4_walls.obj");
	Level4_walls->textureName = "Level4_walls";

	Level4_lava = new cLava(64.f, "Level4_lavawater", vec3(-32.0f, -0.6f, -12.0f));

	Level4_platform1 = new Platform(vec3(-8.f, 0.4f, -4.0f), 1, 1.f);
	Level4_platform1->Load("../Resources/Models/Platform.obj");
	Level4_platform1->textureName = "level4platform";

	Level4_platform2 = new Platform(vec3(-9.5f, 0.4f, -3.0f), 1, 1.f);
	Level4_platform2->Load("../Resources/Models/Platform.obj");
	Level4_platform2->textureName = "level4platform";

	Level4_platform3 = new Platform(vec3(-11.f, 0.4f, -2.0f), 1, 1.f);
	Level4_platform3->Load("../Resources/Models/Platform.obj");
	Level4_platform3->textureName = "level4platform";

	Level4_platform4 = new Platform(vec3(-12.5f, 0.4f, -1.0f), 1, 1.f);
	Level4_platform4->Load("../Resources/Models/Platform.obj");
	Level4_platform4->textureName = "level4platform";

	Level4_platform5 = new Platform(vec3(-14.0f, 0.4f, 0.0f), 1, 1.f);
	Level4_platform5->Load("../Resources/Models/Platform.obj");
	Level4_platform5->textureName = "level4platform";

	Level4_platform6 = new Platform(vec3(-16.f, 0.4f, -1.0f), 1, 1.f);
	Level4_platform6->Load("../Resources/Models/Platform.obj");
	Level4_platform6->textureName = "level4platform";

	Level4_platform7 = new Platform(vec3(-17.3f, 0.4f, -2.0f), 1, 1.f);
	Level4_platform7->Load("../Resources/Models/Platform.obj");
	Level4_platform7->textureName = "level4platform";

	Level4_platform8 = new Platform(vec3(-19.f, 0.4f, -3.0f), 1, 1.f);
	Level4_platform8->Load("../Resources/Models/Platform.obj");
	Level4_platform8->textureName = "level4platform";

	Level4_teleport = new Platform(vec3(2.0,0.7,4.f), 18,1.f);
	Level4_teleport->Load("../Resources/Models/Platform.obj");
	Level4_teleport->textureName = "level1_well1_teleport";

	Level4_well1 = new Well1(vec3(2.0f, 0.8f, 4.f));
	Level4_well1->Load("../Resources/Models/Level1_well1_walls.obj");
	Level4_well1->textureName = "Level4_well";

	Level4_grid1 = new Terrain(vec3(-12.2f, 3.2f, 8.f), vec3(0.6, 0.6, 0.6), 0.f, vec3(0.6, 0.6, 0.6));
	Level4_grid1->load("../Resources/Models/Level4_grid.obj");
	Level4_grid1->textureName = "Level4_grid";

	Level4_grid2 = new Terrain(vec3(-7.2f, 3.2f, 8.f), vec3(0.6, 0.6, 0.6), 0.f, vec3(0.6, 0.6, 0.6));
	Level4_grid2->load("../Resources/Models/Level4_grid.obj");
	Level4_grid2->textureName = "Level4_grid";

	Level4_hempisphere = new Terrain(vec3(-21.7f, 0.6f, 7.6f), vec3(0.4, 0.2, 0.4), 0.f, vec3(0.6, 0.6, 0.6));
	Level4_hempisphere->load("../Resources/Models/Level4_hemisphere.obj");
	Level4_hempisphere->textureName = "Level4_hemisphere";

	Level4_friend = new Friend(vec3(-7.8f, 3.3f, 8.f), vec3(0.002, 0.002, 0.002), vec3(0.2, 0.2, 0.2), vec3(0.1, 0.1, 0.1), 0.f);
	Level4_friend->Load("../Resources/Models/bunny.obj");
}

void Render_level4()
{
	box1->textureName = "Level4_box";
	Level4_walls->textureName = "Level4_walls";

	// player->standat = 1.f;
	// player->pos.y = 1.f;

	hearts_coords[2] = vec3(2.0f, 1.4f, 4.f);

	scene.boundaryMin = vec3(-40.10f, -10, -10.5f);
	scene.boundaryMax = vec3(3.8f, 20.5, 10.5f);

	Level4_floor1->Render("Level4_floor1", *player);
	Level4_floor2->Render("Level4_floor2", *player);

	Level4_floor_moving1->Render("Level4_floor_moving1", *player);
	Level4_floor_moving2->Render("Level4_floor_moving2", *player);
	Level4_floor_moving3->Render("Level4_floor_moving3", *player);
	Level4_floor_moving4->Render("Level4_floor_moving4", *player);

	Level4_floor_moving5->Render("Level4_floor_moving5", *player);
	Level4_floor_moving6->Render("Level4_floor_moving6", *player);
	Level4_floor_moving7->Render("Level4_floor_moving7", *player);
	Level4_floor_moving9->Render("Level4_floor_moving9", *player);

	Level4_well1->Render(*player);
	Level4_teleport->Render(*player,17);

	Level4_walls->Render("Level4_walls", *player);
	Level4_lava->Draw(*player);

	Level4_platform1->Render(*player, 9);
	Level4_platform2->Render(*player, 10);
	Level4_platform3->Render(*player, 11);
	Level4_platform4->Render(*player, 12);


	Level4_platform5->Render(*player, 13);
	Level4_platform6->Render(*player, 14);
	Level4_platform7->Render(*player, 15);
	Level4_platform8->Render(*player, 16);

	diamonds_coords[32] = vec3(2.f, 1.f, -2.45f);
	diamonds_coords[33] = vec3(2.f, 1.f, -4.45f);
	diamonds_coords[34] = vec3(2.f, 1.f, -6.45f);

	diamonds_coords[35] = vec3(-22.9f, 1.f, 2.45f);
	diamonds_coords[36] = vec3(-22.75f, 1.f, 4.45f);
	diamonds_coords[37] = vec3(-22.7f, 1.f, 6.6f);

	diamonds_coords[2] = vec3(-22.7f, 1.f, 8.6f);
	diamonds_coords[0] = vec3(-22.7f, 1000.f, 8.6f);
	diamonds_coords[1] = vec3(-22.7f, 1000.f, 8.6f);


	diamonds_coords[38] = vec3(2.2f, 0.9f, -8.45f);
	diamonds_coords[39] = vec3(2.5f, 0.9f, -8.45f);
	diamonds_coords[40] = vec3(2.3f, 0.9f, -8.50f);

	diamonds_coords[41] = vec3(-21.75f, 1.f, -10.41f);
	diamonds_coords[42] = vec3(-21.75f, 1.f, -10.42f);
	diamonds_coords[43] = vec3(-21.75f, 1.f, -10.45f);

	box_coords[7] = vec3(vec3(2.4f, 0.9f, -8.46f));
	box_coords[8] = vec3(vec3(-22.75f, 0.9f, -8.6f));

	Level4_grid1->Render("Level4_grid1", *player);
	Level4_grid2->Render("Level4_grid2", *player);
	Level4_hempisphere->Render("Level4_hemisphere", *player);
	Level4_friend->Render(*player);


	for (int i = 7; i<9; i++)
	{
		box1->Render(*player, box_coords[i], i);
	}

	checkandrenderdiamonds(32,43);
	checkandrenderspecialdiamonds(2);
	checkandrenderhearts(2,3);

	////printf("INIT2\n");
}

void Render_lights()
{
	if (light1state)
	{
		GLfloat l0_ambient[] = { 0.2f, 0.2f, 0.2f };
		GLfloat l0_diffuse[] = { 1.0f, 1.0f, 1.0 };
		GLfloat l0_specular[] = { 0.5f, 0.5f, 0.5f };
		GLfloat l0_position[] = { 2.f, 2.f, 2.f, 0.0f };

		glEnable(GL_LIGHT0);
		glLightfv(GL_LIGHT0, GL_AMBIENT, l0_ambient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, l0_diffuse);
		glLightfv(GL_LIGHT0, GL_SPECULAR, l0_specular);
		glLightfv(GL_LIGHT0, GL_POSITION, l0_position);
		glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0);
		glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.2);
		glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0);
	}
	else
	{
		glDisable(GL_LIGHT0);
	}

	if (light2state)
	{
		GLfloat l0_ambient[] = { 0.0f, 0.0f, 0.0f };
		GLfloat l0_diffuse[] = { 0.5f, 0.5f, 0.5 };
		GLfloat l0_specular[] = { 0.2f, 0.2f, 0.2f };
		GLfloat l0_position[] = { -player->dir.x, -player->dir.y, -player->dir.z, 0.0f };

		glEnable(GL_LIGHT1);
		glLightfv(GL_LIGHT1, GL_AMBIENT, l0_ambient);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, l0_diffuse);
		glLightfv(GL_LIGHT1, GL_SPECULAR, l0_specular);
		glLightfv(GL_LIGHT1, GL_POSITION, l0_position);
		glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 0);
		glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.2);
		glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0);
	}
	else
	{
		glDisable(GL_LIGHT1);
	}
	if (light3state)
	{

		GLfloat l2_ambient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
		GLfloat l2_diffuse[] = { 1.0f, 1.0f, 1.0 };
		GLfloat l2_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		GLfloat l2_position[] = { player->pos.x, player->pos.y, player->pos.z, 1.0f };
		GLfloat l2_direction[] = { player->dir.x, player->dir.y, player->dir.z };


		glLightfv(GL_LIGHT2, GL_DIFFUSE, l2_ambient);
		glLightfv(GL_LIGHT2, GL_SPECULAR, l2_specular);
		glLightfv(GL_LIGHT2, GL_POSITION, l2_position);
		glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, l2_direction);

		glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 20.0f);
		glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 0.f);
		glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, .2f);
		glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.f);

		glEnable(GL_LIGHT2);
	}
	else
	{
		glDisable(GL_LIGHT2);
	}
	if (!goldentrunkstate)
	{
		GLfloat l0_ambient[] = { 0.2f, 0.2f, 0.2f };
		GLfloat l0_diffuse[] = { 1.0f, 1.0f, 1.0 };
		GLfloat l0_specular[] = { 0.5f, 0.5f, 0.5f };
		GLfloat l0_position[] = { 5.5f, 0.f, 2.4f, 1.0f };

		glEnable(GL_LIGHT3);
		glLightfv(GL_LIGHT3, GL_AMBIENT, l0_ambient);
		glLightfv(GL_LIGHT3, GL_DIFFUSE, l0_diffuse);
		glLightfv(GL_LIGHT3, GL_SPECULAR, l0_specular);
		glLightfv(GL_LIGHT3, GL_POSITION, l0_position);
		glLightf(GL_LIGHT3, GL_CONSTANT_ATTENUATION, 0);
		glLightf(GL_LIGHT3, GL_LINEAR_ATTENUATION, 0.2);
		glLightf(GL_LIGHT3, GL_QUADRATIC_ATTENUATION, 0);
	}
	else
	{
		glDisable(GL_LIGHT4);
	}
	if (light4state)
	{
		GLfloat l4_ambient[] = { 0.2f, 0.2f, 0.2f };
		GLfloat l4_diffuse[] = { 1.0f, 1.0f, 1.0 };
		GLfloat l4_specular[] = { 0.5f, 0.5f, 0.5f };
		GLfloat l4_position[] = { player->pos.x + 0.5f, player->pos.y + 0.5f, player->pos.z, 1.0f };

		glEnable(GL_LIGHT4);
		glLightfv(GL_LIGHT4, GL_AMBIENT, l4_ambient);
		glLightfv(GL_LIGHT4, GL_DIFFUSE, l4_diffuse);
		glLightfv(GL_LIGHT4, GL_SPECULAR, l4_specular);
		glLightfv(GL_LIGHT4, GL_POSITION, l4_position);
		glLightf(GL_LIGHT4, GL_CONSTANT_ATTENUATION, 0);
		glLightf(GL_LIGHT4, GL_LINEAR_ATTENUATION, 0.4);
		glLightf(GL_LIGHT4, GL_QUADRATIC_ATTENUATION, 0);
	}
	else
	{
		glDisable(GL_LIGHT4);
	}
}

void checkandrenderdiamonds(int start, int end)
{
	for (int i = start; i<end; i++)
	{
		if (sqrt((player->pos.x - diamonds_coords[i].x)*(player->pos.x - diamonds_coords[i].x) + (player->pos.z - diamonds_coords[i].z)*(player->pos.z - diamonds_coords[i].z)) <= 0.3 && diamonds_taken[i] == 0 && player->pos.y < diamonds_coords[i].y + 0.1)
		{
			diamonds_taken[i] = 1;
			if (i >= 3)
			{
				player->diamonds_counter += 1; player->endurance = 2;
			}
		}

		diamond->Render(*player, diamonds_coords[i], diamonds_taken[i], i, angle_diamonds,0);
	}
}

void checkandrenderspecialdiamonds(int index)
{
	if (sqrt((player->pos.x - diamonds_coords[index].x)*(player->pos.x - diamonds_coords[index].x) + (player->pos.z - diamonds_coords[index].z)*(player->pos.z - diamonds_coords[index].z)) <= 0.3 && diamonds_taken[index] == 0)
	{
		if(index == 0 && player->keys_counter == -1)
		diamonds_taken[index] = 1; player->specialdiamonds[index] = 1;

		if(index == 2 || index == 1)
		diamonds_taken[index] = 1; player->specialdiamonds[index] = 1;		
	}

	if (player->specialdiamonds[index] != 1)
		diamond->Render(*player, diamonds_coords[index], diamonds_taken[index], index, angle_diamonds,0);
}

void checkandrenderhearts(int start, int end)
{
	for (int i = start; i<end; i++)
	{
		if (sqrt((player->pos.x - hearts_coords[i].x)*(player->pos.x - hearts_coords[i].x) + (player->pos.z - hearts_coords[i].z)*(player->pos.z - hearts_coords[i].z)) <= 0.25 && hearts_taken[i] == 0 && player->pos.y < hearts_coords[i].y + 0.1)
		{
			hearts_taken[i] = 1;
			player->lives_counter += 1;
		}
		heart->Render(*player, hearts_coords[i], hearts_taken[i]);
	}
}

void dropdiamonds()
{
	//printf("DROPPING\n");
	//printf(" %d \n",player->dropalldiamonds);

	if (player->diamonds_counter > 0 && player->dropalldiamonds == 1)
	{
		//printf("DROPPING\n");
		dropped_coords = new vec3[player->diamonds_counter];
		dropped_state =  new bool[player->diamonds_counter];

		for (int i = 0; i<player->diamonds_counter; i++)
		{
			diamonds_drop += 32.f;			
			float rotX = (float)cos((diamonds_drop) * 3.14 / 180);
			float rotZ = (float)sin((diamonds_drop) * 3.14 / 180);

			if(fabs(player->pos.x - (player->pos.x + rotX) > 0.4f ))
			rotX/= 2;

			if(fabs(player->pos.x - (player->pos.x - rotZ) > 0.4f ))
			rotZ/= 2;

			dropped_coords[i] = vec3(player->pos.x + rotX, player->pos.y, player->pos.z - rotZ);
			dropped_state[i] = 0;
		}

		player->howmanyweredropped = player->diamonds_counter;
		player->dropalldiamonds = 2;
		player->diamonds_counter = 0;
	}

	if (player->dropalldiamonds == 2)
	{
		for (int i = 0; i<player->howmanyweredropped; i++)
		{
			 //printf("&& %d\n",dropped_state[i]);
			if (sqrt((player->pos.x - dropped_coords[i].x)*(player->pos.x - dropped_coords[i].x) + (player->pos.z - dropped_coords[i].z)*(player->pos.z - dropped_coords[i].z)) <= 0.15 && dropped_state[i] == 0 && player->droppedscale > 0.01f)
			{
				dropped_state[i] = 1;
				player->diamonds_counter += 1; player->endurance = 2;
			}
			

			if(player->droppedscale > 0.03f)			
			DDiam->Render(*player, dropped_coords[i], dropped_state[i], 4, angle_diamonds, 1);
			else
			dropped_state[i] = 1;
			
		}
	}

	//printf("DROPPED: %d\n",player->dropalldiamonds);

	if(player->dropalldiamonds == 2)
	{
		bool gate = 0;

		for (int i = 0; i<player->howmanyweredropped; i++)
		{
			if(dropped_state[i] == 0)
			gate = 1;
		}

		if(gate == 0 && player->howmanyweredropped != 0)
		{
			//printf("DONE\n");
			player->dropalldiamonds = 0;
			player->howmanyweredropped = 0;
			player->droppedscale = 0.3f;
			diamonds_drop = 0.f;

			delete[] dropped_coords;
			delete[] dropped_state;
		}
	}
}
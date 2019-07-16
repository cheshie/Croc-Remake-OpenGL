#pragma once
#include "SceneObject.h"
class Player :
	public SceneObject
{
public:
	Player(vec3 pos, vec3 dir, vec3 force, vec3 scale, float angle);
	~Player();

	void Render();
	void Update();
	int makejump();
	int makejump(float);
	bool Load(std::string filename);
	void test_sphere();
	int endjump();
	void beginafterliveloss();
	void checkpointlevel2();
	void checkpointlevel4();
	void checkpointlevel3();
	
	
	vec3 color;
	vec3 dir;
	vec3 scale;
	vec3 oldpos;
	float speed;
	bool stop;

	float tmprotate;
	float droppedscale;
	float rotate;
	float angle;
	float velocity_vertical;
	float velocity_horizontal;
	bool  jumping;
	float jump_maximal_height;
	float jump_temporary_height;
	bool  falling;
	float velocity_jump;
	float jump_credit;
	float gravity;
	float onground;
	int   action;
	float deltatime;
	float maxrelativeheight;
	float standat;
	bool doublejump;
	bool isplayerunderplatform;
	bool youcantgethigher;
	float blockposition;
	bool * platformstop;
	bool * specialdiamonds;
	bool rock_collision;
	bool * trunk_stop;
	bool floor_collision;
	int endurance;
	float waitfornextjump;
	float stopforamoment;
	float waitbeforedie;
	bool wyrzucilem_diamenty;
	float stop_falling;
	bool goldenkey;
	bool iWonTheGame;
	int currentlevel;

	bool * box_stop;
	bool stopwell1;
	bool stopWood;

	int diamonds_counter;
	int lives_counter;
	int keys_counter;

	bool flyingMode;

	std::string textureName;
	float energy;
	float maxEnergy;
	float gravity_jump;
	int boxnumber;

	//Blinking
	float timetoblink;
	int   timesblink;

	//Level2
	bool * Level2_collisions;
	int    Level2_numberofobjects;
	float  counter;
	int platformnumber;
	bool ismoving;

	//Level3
	int Level3_numberofobjects;
	bool * Level3_collisions;
	float timetofall;
	int friendscounter;
	bool lost;
	float timetoshowup;

	int  showorblink;
	int  showorblinktimer;

	//Level4
	int Level4_numberofobjects;
	bool * Level4_collisions;
	float direction;


	//Various
	int dropalldiamonds;
	int howmanyweredropped;
	float timetonextjump;
	bool showtorus;
	float torussize;
	bool turn;

	std::vector<vec3> vertices;
	std::vector<vec3> normals;
	std::vector<vec3> uvs;
};


#pragma once
#include "stdafx.h"

#define PI 3.14159265359
#define LEVEL2_FLOOR1 0
#define LEVEL2_FLOOR2 1
#define LEVEL3_FLOOR1 0
#define LEVEL3_FLOOR2 1

#define LEVEL4_FLOOR1 0
#define LEVEL4_FLOOR2 1
#define LEVEL4_GRID1 2
#define LEVEL4_GRID2 3


#define LEVEL4_FLOOR_MOVING1 1


class Terrain
{
public:
	Terrain(vec3 pos, vec3 scale, float rotate, vec3 color);
	~Terrain(void);

	vec3 pos;
    vec3 scale;
    float rotate;
	float woodenDoorRotation;
	float * keepdistancex;
	float * keepdistancez;
	float myrot_start;
	float myrot;
	//float radius;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

    std::string textureName;

	std::vector<vec3> vertices;
	std::vector<vec3> normals;
	std::vector<vec3> uvs;

	//bool isAlive;
    bool load(std::string filename);
	void Render(std::string, Player &);
	void Update();
	void WoodenDoorOpen(Player &player);
	void RockCollision(Player &player);
	void floor_level1_Collision(Player &player);
	void Checkplayerfinishedlevel1( Player &player );
	void floor1_level2_Collision(Player &player);
	void floor2_level2_Collision(Player &player);
	void floor1_level3_Collision(Player &player);
	void floor2_level3_Collision(Player &player);
	void checkpointlevel3(Player &player);
	void Checkplayerfinishedlevel2( Player &player );
	void Checkplayerfinishedgame( Player &player);
	void floor1_level4_Collision(Player &);
	void floor2_level4_Collision(Player &);
	void grid_level4_Collision(Player &, std::string);
	void hemisphere_level4_Collision(Player &);
	void finalgong(Player &);
	
	
	void floor_moving1_level4_Collision(Player &, std::string);
	
};


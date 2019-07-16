#pragma once
#include "stdafx.h"
#define NORMAL_NOTMOVING 1
#define MAGIC_TELEPORT 2 
#define NORMAL_MOVING 3
#define NORMAL_DISSAP 4
#define WELL_PLATFORM 5
#define WELL_TELEPORT 6


#define PI 3.14159265359

class Platform
{
public:
	Platform(vec3 pos, int, float);
	~Platform(void);
    bool Load(std::string);

	vec3 pos;
    vec3 color;

	vec3 force;
	float weight;
	float radius;
    float height;
    float width;    
	float * keepdistancex;
	float * keepdistancez;
    float rotation;
    bool  isplayerunder;
	int typeofplatform;
	int magic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
    std::string textureName;

	bool isAlive;
	bool stopmagic;
	float prot;
	float direction_rotating;

	std::vector<vec3> vertices;
	std::vector<vec3> normals;
	std::vector<vec3> uvs;

	//level3
	float timetofall;
	bool startfalling;
	float timetoresp;
	float originalpos;

	void Render(Player &player, int );
	void Update(Player &player, int );
	void Teleporttolevel3( Player &player );
};

#pragma once
#include "SceneObject.h"
#include "stdafx.h"
class Friend
{
public:
	Friend(vec3 pos, vec3 dir, vec3 force, vec3 scale, float angle);
	~Friend();

	void Render(Player &);
	void Update( Player &);
	bool Load(std::string filename);
	
	vec3 pos;
	vec3 color;
	vec3 dir;
	vec3 scale;

	std::vector<vec3> vertices;
	std::vector<vec3> normals;
	std::vector<vec3> uvs;

	float angle;
	float force;
	bool left;
	bool normal;
	bool isAlive;
};


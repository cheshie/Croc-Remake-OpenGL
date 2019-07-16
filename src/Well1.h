#pragma once
#include "stdafx.h"

#define PI 3.14159265359

class Well1
{
public:
	Well1(vec3 pos);
	~Well1(void);
    bool Load(std::string);

	vec3 pos;
    vec3 color;

	vec3 force;
	float weight;
	float radius;
    float height;
    float width;    
	float keepdistancex;
	float keepdistancez;
    float rotation;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
    std::string textureName;

	bool isAlive;

	std::vector<vec3> vertices;
	std::vector<vec3> normals;
	std::vector<vec3> uvs;

	void Render(Player &);
	void Update(Player &);
};

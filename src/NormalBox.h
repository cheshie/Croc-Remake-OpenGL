#pragma once

#define PI 3.14159265359

class NormalBox
{
public:
	NormalBox(vec3 pos);
	~NormalBox(void);
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
	bool * is_destroyed;

	GLuint DisplayListIndex;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
    std::string textureName;

	bool isAlive;

	std::vector<vec3> vertices;
	std::vector<vec3> normals;
	std::vector<vec3> uvs;

	void Render(Player &player, vec3, int);
	void Update(Player &player, int);
};


#pragma once
#include "SceneObject.h"
class Enemy
{
public:
	Enemy(vec3 pos, vec3 dir, vec3 force, vec3 scale, float angle);
	~Enemy();

	void Render(Player &);
	void Update( Player &);
	void makejump(float );	
	bool Load(std::string filename);
	void bigRender(Player &);
	void bigUpdate(Player &);
	void smallRender(Player &, vec3 &, bool &);
	void smallUpdate(Player &, vec3 &, bool &);
	

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
	float angle_right;
	float gravity_jump;
	float velocity_jump;
	float timer_stop2;

	vec3 ldc;
	vec3 rdc;
	
	vec3 luc;
	vec3 ruc;
	float timer_stop;
	
	int dirmove;

	GLuint DisplayListIndex;
	
	string textureName;

};


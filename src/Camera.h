#pragma once
#include "SceneObject.h"
#include "Player.h"
class Camera : public SceneObject
{
public:
	Camera(vec3 pos, vec3 dir, vec3 force, float angle);
	~Camera();

	void Render();
	void Update();
	void myUpdate(Player &, vec3, vec3);
	vec3 dir;
	vec3 pos;
	vec3 force;

	float angle;
	float speed;
	float deltatime;

	float velocity_vertical;
	float velocity_horizontal;
	bool flyingMode;
};


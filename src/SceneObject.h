#pragma once

#define PI 3.14159265359

class SceneObject
{
public:
	SceneObject(void);
	~SceneObject(void);

	vec3 pos;
	vec3 prevPos;

	vec3 force;
	float weight;
	float radius;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	bool isAlive;

	virtual void Render() = 0;
	virtual void Update() = 0;
};


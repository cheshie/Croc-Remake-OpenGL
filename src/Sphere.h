#pragma once

#include "SceneObject.h"

class Sphere : public SceneObject
{
public:
	Sphere(vec3 pos, vec3 color, float radius, float weight);
	~Sphere(void);

	void Render();
	void Update();
	void makejump();

	bool  jumping;
	float jump_maximal_height;
	float jump_temporary_height;
	bool  falling;

	float radiusChangePerUpdate;
};

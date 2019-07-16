#include "stdafx.h"
#include "SceneObject.h"


SceneObject::SceneObject(void)
{
	ambient = vec3(0.0f, 0.0f, 0.0f);
	diffuse = vec3(0.3f, 0.3f, 0.3f);
	specular = vec3(0.1f, 0.1f, 0.1f);

	weight = 1;

	isAlive = true;
}


SceneObject::~SceneObject(void)
{
}
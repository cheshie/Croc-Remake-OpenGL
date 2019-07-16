#pragma once
#include "stdafx.h"
#include "SceneObject.h"
#include <string>
#include <cmath>
using namespace std;

class Blackbox : public SceneObject
{

    public: 
        Blackbox();//vec3 pos, vec3 color);
        ~Blackbox();

	bool load();
	bool load2();
	

	void Render();
	void setup();
	void Update();
	void Paint(vec3, Player &, int);
	void UpdateCollision(vec3, Player &, int);
	float  * trunk_open;
	float * angle1;
	float * angle2;
	bool  * trunk_state;
	float * keepdistancex;
	float * keepdistancez;

	//vec3 pos;
    std::string textureName;
    //float radius;
    //float size;
	//vec3 color;
	//vec3 pos;
	GLuint DisplayListIndex;
	GLuint DisplayListIndex2;
	
};
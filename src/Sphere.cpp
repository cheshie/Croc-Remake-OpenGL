#include "stdafx.h"
#include "Sphere.h"


Sphere::Sphere(vec3 pos, vec3 color, float radius, float weight)
{
	this->pos = pos;
	this->diffuse = color;
	this->radius = radius;
	this->weight = weight;

	radiusChangePerUpdate = 0;
}


Sphere::~Sphere(void)
{
}

void Sphere::Render()
{
	glMaterialfv(GL_FRONT, GL_AMBIENT, &ambient.x);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, &diffuse.x);
	glMaterialfv(GL_FRONT, GL_SPECULAR, &specular.x);

	glPushMatrix();
	glTranslatef(pos.x, pos.y, pos.z);
	glScalef(0.8f,0.8f,0.8f);
	glutSolidSphere(radius, 24, 24);
	glPopMatrix();
}

void Sphere::Update()
{
	pos.x += force.x / weight;
	pos.y += force.y / weight;
	pos.z += force.z / weight;

	force.x /= 1.2;
	force.y /= 1.2;
	force.z /= 1.2;

	// radius += radiusChangePerUpdate;

	// if (radius <= 0)
	// {
	// 	isAlive = false;
	// }

	makejump();


}

void Sphere::makejump()
{
	if(this->jumping && this->jump_temporary_height == this->jump_maximal_height)
	{ this->jumping = 0; this->falling = 1;}

	if(this->falling && this->jump_temporary_height == 0)
	{ this->falling = 0;}

	if(this->jumping)
	{
		this->jump_temporary_height += 0.5f;
		this->force.y = 2.f;
		this->pos.y += 0.25;
	}
	else if(this->falling)
	{
		this->jump_temporary_height -= 0.5f;
		this->pos.y -= 0.25f;
	}
	//else if(this->falling)
	//{
	//	this->jump_temporary_height -= 0.5f;
	//	this->pos.x -= 0.5f;
	//}
}
#include "stdafx.h"
#include "Camera.h"


Camera::Camera(vec3 pos, vec3 dir, vec3 force, float angle)
{
	this->pos = pos;
	this->dir = dir;
	this->angle = angle;
	this->force = force;
	this->radius = 0.2f;
	this->weight = 4;
	this->force = 1.f;
	this->deltatime = 0.f;
	this->speed = 0.1f;

	//pos.x = 0.0f;
	//pos.y = 1.75f;
	//pos.z = 0.0f;
	

	//dir.x = 2.0f;
	//dir.y = 0.0f;
	//dir.z = -1.0f;

	//speed = 0.1f;

	//velocity_horizontal = 0;
	//velocity_vertical = 0;

	flyingMode = false;
}


Camera::~Camera()
{
}


void Camera::Render()
{

}

void Camera::Update()
{

}

void Camera::myUpdate(Player &player, vec3 boundaryMax, vec3 boundaryMin)
{

		float rotX = (float)cos(player.rotate * 3.14 / 180) * 1.8f;
		float rotZ = (float)sin(player.rotate * 3.14 / 180) * 1.8f;

		this->dir.x  = player.pos.x - 0.2f - rotX;
		this->dir.z  = player.pos.z  + rotZ;
		this->dir.y  = 0.1f + pos.y * 0.7;

		bool ismovingX = 0;
		bool ismovingZ = 0;

		prevPos = pos;

		vec3 newpos = player.pos - pos;
		float length = sqrt((player.pos.x - pos.x)*(player.pos.x - pos.x)+(player.pos.y - pos.y)*(player.pos.y - pos.y)+(player.pos.z - pos.z)*(player.pos.z - pos.z));
	
		newpos.x = newpos.x / length * 0.3;
		newpos.y = newpos.y / length * 0.3;
		newpos.z = newpos.z / length * 0.3;

		this->pos.x = player.pos.x + rotX;
		this->pos.z = player.pos.z - rotZ;	

		float distMXx = fabs(pos.x + radius - boundaryMax.x);
		float distMNx = fabs(pos.x + radius - boundaryMin.x);

		float distMXz = fabs(pos.z + radius - boundaryMax.z);
		float distMNz = fabs(pos.z + radius - boundaryMin.z);

		if(distMXx <= 0.5)
		{
			pos.x = boundaryMax.x - 0.45f;
		}

		if(distMNx <= 0.5)
		{
			pos.x = boundaryMin.x + 0.45f;
		}

		if(distMXz <= 0.5)
		{
			pos.z = boundaryMax.z - 0.45f;			
		}
		if(distMNz <= 0.5)
		{
			pos.z = boundaryMin.z + 0.45f;			
		}
	

		float closest_wall;

		// if ((pos.x + radius) < boundaryMax.x && (pos.x - radius) > boundaryMin.x)
		// {
		// 	this->pos.x = player.pos.x + rotX;
		// 	ismovingX = 1;
		// }
		// else
		// {
		// 	 this->pos.x += 0.02f * direction;		
		// }
				
		// if ((pos.z + radius) < boundaryMax.z && (pos.z - radius) > boundaryMin.z)
		// {
		// 	this->pos.z = player.pos.z - rotZ;	
		// 	ismovingZ = 1;
		// }
		// else
		// {
		// 	 this->pos.z += 0.2f * direction;	
		// }

		//if (ismovingX == 0)
	   	//this->pos.x += newpos.x * 0.2f;
		//this->pos.x = prevPos.x;
		
		//if(ismovingZ == 0)
		//this->pos.z += newpos.z * 0.2;
		//this->pos.z = prevPos.z;



		this->pos.y = player.pos.y + 0.5;
	
		gluLookAt(
			this->pos.x, this->pos.y, this->pos.z,
			this->dir.x, this->dir.y, this->dir.z,
			0.0f, 1.0f, 0.0f
		);

}


/*

void Camera::Update()
{

}

void Camera::myUpdate(Player *player, vec3 boundaryMax, vec3 boundaryMin)
{
		//if(obj->radius = 5.f)
		//printf("raduus\n");

		float rotX = (float)cos(player.rotate * 3.14 / 180) * 1.8f;
		float rotZ = (float)sin(player.rotate * 3.14 / 180) * 1.8f;

		bool ismovingX = 0;
		bool ismovingZ = 0;

		prevPos = pos;

		if ((pos.x + radius) > boundaryMax.x || (pos.x - radius) < boundaryMin.x)
		{
			pos.x = prevPos.x;
		}
		else
		{
			this->pos.x = player.pos.x + rotX;
			//prevPos.x = pos.x;
		}

		if ((pos.y + radius) > boundaryMax.y || (pos.y - radius) < boundaryMin.y)
		{
			pos.y = prevPos.y;	
		}
		else
		{
			this->pos.y = player.pos.y +  0.5f;
			//prevPos.y = pos.y;		
			
		}

		if ((pos.z + radius) > boundaryMax.z || (pos.z - radius) < boundaryMin.z)
		{
			pos.z = prevPos.z;
			
		}
		else
		{
			this->pos.z = player.pos.z - rotZ;
// /			prevPos.z = pos.z;
		}

	

	//vec3 newpos = player.pos - pos;
	//float length = sqrt((player.pos.x - pos.x)*(player.pos.x - pos.x)+(player.pos.y - pos.y)*(player.pos.y - pos.y)+(player.pos.z - pos.z)*(player.pos.z - pos.z));
	
	//newpos.x = newpos.x / length * 0.3;
	//newpos.y = newpos.y / length * 0.3;
	//newpos.z = newpos.z / length * 0.3;

	//this->pos.x += newpos.x * 0.1f;
	//this->pos.y += newpos.y * 0.1f;
	//this->pos.z += newpos.z * 0.1f;
	
		gluLookAt(
			this->pos.x, this->pos.y, this->pos.z,
			player.pos.x - 0.2f - rotX,  1.4f, player.pos.z + rotZ,
			0.0f, 1.0f, 0.0f
		);

	  

}


*/
/* NON DEBUG

	float rotX = (float)cos(player.rotate * 3.14 / 180) * 1.8f;
	float rotZ = (float)sin(player.rotate * 3.14 / 180) * 1.8f;

	this->pos.x = player.pos.x + rotX;
	this->pos.y = player.pos.y +  1.5f;
	this->pos.z = player.pos.z - rotZ;

	vec3 newpos = player.pos - pos;
	float length = sqrt((player.pos.x - pos.x)*(player.pos.x - pos.x)+(player.pos.y - pos.y)*(player.pos.y - pos.y)+(player.pos.z - pos.z)*(player.pos.z - pos.z));
	newpos.x = newpos.x / length;
	newpos.y = newpos.y / length;
	newpos.z = newpos.z / length;

	this->pos.x += newpos.x * 0.1f;
	this->pos.y += newpos.y * 0.1f;
	this->pos.z += newpos.z * 0.1f;
	

	gluLookAt(
		this->pos.x, this->pos.y, this->pos.z,
		player.pos.x - 0.2f - rotX, 0.5f, player.pos.z + rotZ,
		0.0f, 1.0f, 0.0f
	);


*/
#include "stdafx.h"
#include "vec3.h"

vec3::vec3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

vec3::~vec3(void)
{
}

float vec3::distance(vec3 v1, vec3 v2)
{
	return (v1 - v2).length();
}

vec3 vec3::cross(vec3 v1, vec3 v2)
{
	vec3 v;

	v.x = v1.y * v2.z - v2.y * v1.z;
	v.y = v1.z * v2.x - v2.z * v1.x;
	v.z = v1.x * v2.y - v2.x * v1.y;

	return v;
}

float vec3::dot(vec3 v1, vec3 v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

vec3 vec3::normalized()
{
	vec3 v;
	float d = length();

	if (d == 0) return vec3(0, 0, 0);

	v.x = x / d;
	v.y = y / d;
	v.z = z / d;

	return v;
}

float vec3::length()
{
	return sqrt(x * x + y * y + z * z);
}

vec3 vec3::operator+(vec3 v)
{
	vec3 newV;

	newV.x = x + v.x;
	newV.y = y + v.y;
	newV.z = z + v.z;

	return newV;
}

vec3 vec3::operator-(vec3 v)
{
	vec3 newV;

	newV.x = x - v.x;
	newV.y = y - v.y;
	newV.z = z - v.z;

	return newV;
}

vec3 vec3::operator*(float v)
{
	vec3 newV;

	newV.x = x * v;
	newV.y = y * v;
	newV.z = z * v;

	return newV;
}

void vec3::print()
{
	printf("%f %f %f\n", x, y, z);
}
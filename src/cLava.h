#pragma once

#include "stdafx.h"

#define FLOW_SPEED 0.6f
#define LAVA_HEIGHT_MAX -.4f
#define LAVA_HEIGHT_MIN -0.8f

class cLava
{
public:
	cLava(float, std::string, vec3);
	~cLava();
	void Load();
	void Draw(Player &);
	float GetHeight();
	float GetHeightMax();
	void Update(Player &);
	vec3 pos;

private:
	int id_Lava;
	float height,ang;
	bool up;
	float terrain_size;
	float stream_left;
	bool left;
	std::string lavaID;
};
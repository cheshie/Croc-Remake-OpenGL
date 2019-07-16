#include "cLava.h"
#include <iostream>
#include "stdafx.h"

cLava::cLava(float terrain_size, string name, vec3 pos)
{
	height = (LAVA_HEIGHT_MAX + LAVA_HEIGHT_MIN)/2;
	ang = 0.0f;
	up = true;
	this-> terrain_size = terrain_size;
	stream_left = 0.f;
	left = 1;
	this->pos = pos;
	this->lavaID= name;

	Load();
}
cLava::~cLava(){}

void cLava::Load()
{
	id_Lava=glGenLists(1);
	glNewList(id_Lava,GL_COMPILE);

	glBegin(GL_QUADS); 
		glTexCoord2f(0.0f,    1.0f*16); glVertex3f(terrain_size, 0.0f, 0.0f        );
		glTexCoord2f(1.0f*16, 1.0f*16); glVertex3f(0.0f,         0.0f, 0.0f        );
		glTexCoord2f(1.0f*16,    0.0f); glVertex3f(0.0f,         0.0f, terrain_size);
		glTexCoord2f(0.0f,       0.0f); glVertex3f(terrain_size, 0.0f, terrain_size);
	glEnd();

	glEndList();
}


void cLava::Draw(Player &player)
{
	glDisable(GL_LIGHTING);

	glDisable(GL_DEPTH_TEST); //desactivo el depth test para que el jugador no vea como el skymap corta con el escenario
	//Skybox.Draw(Data->GetID(IMG_SKYBOX),playerPos.x,playerPos.y,playerPos.z);
	glEnable(GL_DEPTH_TEST);

	glPushMatrix();
	glTranslatef(0.0f,height,0.0f);

	glDisable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);
	//glBindTexture(GL_TEXTURE_2D,"lava");
	glTranslatef(pos.x, pos.y, pos.z + stream_left);
	glScalef(3.f,1.f,10.f);

		if(lavaID == "Level4_lavawater")
		{
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		TextureManager::getInstance()->BindTexture("Level4_lavawater");
		
		}
		else
		{
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		TextureManager::getInstance()->BindTexture("lava");
		}
	glCallList(id_Lava);
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
	glEnable(GL_CULL_FACE);

	glEnable(GL_LIGHTING);
	Update(player);
	
}

float cLava::GetHeight()
{
	return height;
}

float cLava::GetHeightMax()
{
	return LAVA_HEIGHT_MAX;
}

void cLava::Update(Player &player)
{
	if(lavaID == "level1_lava")
	if((player.pos.y) <= -0.4 && player.pos.x < -3.22f &&  player.pos.x > -5.8f)
	{
		player.makejump(5.2);
		player.endurance--;
	}

	if(lavaID == "level2_lava" || "Level4_lavawater")
	if((player.pos.y ) <= -0.9)
	{
		player.makejump(5.2);
		player.endurance--;

		if(player.endurance == 0 )

		if(lavaID == "level2_lava")
		player.checkpointlevel2();
		if(lavaID == "Level4_lavawater")
		player.checkpointlevel4();
	}

	if(up)
	{
		ang = fmod(ang+FLOW_SPEED,360);
		height = ((LAVA_HEIGHT_MAX - LAVA_HEIGHT_MIN)/2.0f)*sin(ang*(PI/180)) + (LAVA_HEIGHT_MAX + LAVA_HEIGHT_MIN)/2.0f;
		up = (height < LAVA_HEIGHT_MAX);
	}
	else
	{
		ang = fmod(ang-FLOW_SPEED,360);
		height = ((LAVA_HEIGHT_MAX - LAVA_HEIGHT_MIN)/2.0f)*sin(ang*(PI/180)) + (LAVA_HEIGHT_MAX + LAVA_HEIGHT_MIN)/2.0f;
		up = (height <= LAVA_HEIGHT_MIN);
	}
	if(left)
	{
		stream_left += 0.005;
		if( stream_left >= 1.f)
		left = !left;
	}
	else
	{
		stream_left -= 0.005f;
		if(stream_left <= 0.f)
		left = !left;
	}

}
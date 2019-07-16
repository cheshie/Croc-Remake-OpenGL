#include "stdafx.h"
#include "Terrain.h"
#define SCIANY 0
#define PODLOGA 1
#define BASEN 2
#define ROCK 3


Terrain::Terrain(vec3 pos, vec3 scale, float rotate, vec3 color)
{
	this->pos = pos;
    this->scale = scale;
    this->diffuse = color;
	this->rotate = rotate;
	this->woodenDoorRotation = 0.f;

	keepdistancex = new float[4];
	keepdistancez = new float[4];
}

Terrain::~Terrain()
{
	delete[] keepdistancex;
	delete[] keepdistancez;
	
}

	struct SFace {
		int v[3];
		int n[3];
		int uv[3];
	};

bool Terrain::load(std::string filename)
{


	FILE * fp = fopen(filename.c_str(), "r");

	if (fp == NULL) {
		////printf("Nie wczytano pliku %s\n", filename.c_str());
		return false;
	}

	vertices.clear();

	std::vector<vec3> loaded_vertices;
	std::vector<vec3> loaded_normals;
	std::vector<vec3> loaded_uvs;
	std::vector<SFace> loaded_faces;

	char buf[256];

	while (fgets(buf, 256, fp)) {
		if (buf[0] == 'v' && buf[1] == ' ') {
			vec3 vertex;
			sscanf(buf, "v %f %f %f", &vertex.x, &vertex.y, &vertex.z);
			loaded_vertices.push_back(vertex);
		}
		if (buf[0] == 'v' && buf[1] == 'n') {
			vec3 normal;
			sscanf(buf, "vn %f %f %f", &normal.x, &normal.y, &normal.z);
			loaded_normals.push_back(normal);
		}
		if (buf[0] == 'v' && buf[1] == 't') {
			vec3 vertex;
			sscanf(buf, "vt %f %f %f", &vertex.x, &vertex.y, &vertex.z);
			loaded_uvs.push_back(vertex);
		}
		if (buf[0] == 'f' && buf[1] == ' ') {
			SFace face;
			sscanf(buf, "f %d/%d/%d %d/%d/%d %d/%d/%d", 
				&face.v[0], &face.uv[0], &face.n[0],
				&face.v[1], &face.uv[1], &face.n[1], 
				&face.v[2], &face.uv[2], &face.n[2]);
			loaded_faces.push_back(face);
		}
	}

	fclose(fp);

	vec3 minVertex = loaded_vertices[0];
	vec3 maxVertex = loaded_vertices[1];

	for (int i = 0; i < loaded_faces.size(); ++i) {
		for (int j = 0; j < 3; ++j) {

			int idxV = loaded_faces[i].v[j] - 1;
			int idxN = loaded_faces[i].n[j] - 1;
			int idxUV = loaded_faces[i].uv[j] - 1;

			vertices.push_back(loaded_vertices[idxV]);
			normals.push_back(loaded_normals[idxN]);
			uvs.push_back(loaded_uvs[idxUV]);

			if (loaded_vertices[idxV].x < minVertex.x)
				minVertex.x = loaded_vertices[idxV].x;

			if (loaded_vertices[idxV].x > maxVertex.x)
				maxVertex.x = loaded_vertices[idxV].x;


			if (loaded_vertices[idxV].y < minVertex.y)
				minVertex.y = loaded_vertices[idxV].y;

			if (loaded_vertices[idxV].y > maxVertex.y)
				maxVertex.y = loaded_vertices[idxV].y;


			if (loaded_vertices[idxV].z < minVertex.z)
				minVertex.z = loaded_vertices[idxV].z;

			if (loaded_vertices[idxV].z > maxVertex.z)
				maxVertex.z = loaded_vertices[idxV].z;
		}
	}

	return true;
}

void Terrain::Render(std::string objectname, Player &player)
{
	if (!textureName.empty())
	{
		// glEnable(GL_TEXTURE_2D);
		// TextureManager::getInstance()->BindTexture(textureName);

        glEnable(GL_TEXTURE_2D);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		TextureManager::getInstance()->BindTexture(textureName);
	}

	if(objectname == "torus")
	glDisable(GL_LIGHTING);

	float mat_ambient[] = { 0.0f, 0.0f, 0.0f };
	float mat_diffuse[] = { 1.f, 1.f,1.f };
	float mat_specular[] = { 0.1f, 0.1f, 0.1f };

	if(objectname == "Level1_teleportbox" || objectname == "Level2_teleportboxto1" || objectname == "Level2_teleportboxfinal")
	{
		mat_diffuse[0] = 0.f;
		mat_diffuse[1] = 0.f;
		mat_diffuse[2] = 0.f;
	}

	if(objectname == "level3_floor1" || objectname == "Level4_walls")
	{
		mat_diffuse[0] = 0.1f;
		mat_diffuse[1] = 0.1f;
		mat_diffuse[2] = 0.1f;
	}

	if(objectname == "Level4_walls")
	glDisable(GL_LIGHTING);


	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);

	// if( !(objectname == "Level4_walls"))
	glDisable(GL_CULL_FACE);
	
	glPushMatrix();

		if(objectname == "croc_corpse" || objectname == "croc_eyes" || objectname == "croc_backpack")
		{
			myrot_start = player.rotate;
			
			if(player.turn == 0)
			myrot = player.rotate;

			if( player.turn == 1)
			{
				if(player.pos.y == player.standat)
				player.makejump(1.f);

				if(myrot <= myrot_start + 360.f)
				myrot+=26;

				if(myrot >= myrot_start + 360.f)
				player.turn = 0;
			}

			glTranslatef(player.pos.x, player.pos.y - 0.08, player.pos.z);	
			glRotatef(myrot, 0.0f, 1.0f, 0.0f);

		}
		else
		glTranslatef(pos.x, pos.y, pos.z);


		glRotatef(rotate, 0.0f, 1.0f, 0.0f);

		if(objectname != "torus")
		glScalef(scale.x, scale.y, scale.z);

		if(objectname == "Level1_wooden_door_left" || objectname == "Level2_wooden_door_left")
        glRotatef(woodenDoorRotation, 0.0f, 1.0f, 0.0f);

		if(objectname == "Level1_wooden_door_right" || objectname == "Level2_wooden_door_right")
        glRotatef(-woodenDoorRotation, 0.0f, 1.0f, 0.0f);

		if(objectname == "Level2specialdoorsright" && player.specialdiamonds[0] == 1 && player.specialdiamonds[1] == 1 && player.specialdiamonds[2] == 1 )
        { glRotatef(woodenDoorRotation, 0.0f, 1.0f, 0.0f);} 

		if(objectname == "Level2specialdoorsleft" && player.specialdiamonds[0] == 1 && player.specialdiamonds[1] == 1 && player.specialdiamonds[2] == 1)
        glRotatef(-woodenDoorRotation, 0.0f, 1.0f, 0.0f);

		if(objectname == "torus")
		{
			//glColor3f()
			glScalef(player.torussize,0.6,player.torussize);
		}
		
		if(player.timetoblink <= 15.f && player.timetoblink > 0 && (objectname == "croc_corpse" || objectname == "croc_eyes" || objectname == "croc_backpack") || (objectname != "croc_corpse" && objectname != "croc_eyes" & objectname != "croc_backpack"))
		{

		glBegin(GL_TRIANGLES);
		for (int i = 0; i < vertices.size(); i++)
		{
			glNormal3f(normals[i].x, normals[i].y, normals[i].z);
			glTexCoord2f(uvs[i].x, uvs[i].y);
			glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
		}
		glEnd();

		}


	glPopMatrix();	

	if(objectname == "rock")
	RockCollision(player);

	if(objectname == "floor")
	floor_level1_Collision(player);

	if(objectname == "torus")
	glEnable(GL_LIGHTING);

	if(objectname == "Level1_teleportbox")
	Checkplayerfinishedlevel1(player);

	if(objectname == "Level2_teleportboxto1")
	Checkplayerfinishedlevel2(player);

	if(objectname == "Level2_teleportboxfinal")
	Checkplayerfinishedgame(player);

	if(objectname == "Level2_floor1")
	floor1_level2_Collision(player);

	if(objectname == "Level3_floor1")
	floor1_level3_Collision(player);	

	if(objectname == "Level2_floor2" || objectname == "Level2_floor3")
	floor2_level2_Collision(player);

	if(objectname == "Level3_floor2" )
	floor2_level3_Collision(player);

	if(objectname == "Level4_floor1" )
	floor1_level4_Collision(player);

	if(objectname == "Level4_floor2" )
	floor2_level4_Collision(player);
	
	if(objectname == "Level4_walls")
	glEnable(GL_LIGHTING);
	//if( !(objectname == "Level4_walls"))

	//if(objectname == "finalgong")
	//finalgong(player);

	if(objectname == "Level4_floor_moving1" || objectname == "Level4_floor_moving2" || objectname == "Level4_floor_moving3" || objectname == "Level4_floor_moving4")
	floor_moving1_level4_Collision(player, objectname);

	if(objectname == "Level4_floor_moving5" || objectname == "Level4_floor_moving6" || objectname == "Level4_floor_moving7" || objectname == "Level4_floor_moving9")
	floor_moving1_level4_Collision(player, objectname);

	
	if(objectname == "Level4_grid1" || objectname == "Level4_grid2")
	grid_level4_Collision(player, objectname);

	if(objectname == "Level4_hemisphere")
	hemisphere_level4_Collision(player);

	glEnable(GL_CULL_FACE);
	glDisable(GL_TEXTURE_2D);
}

void Terrain::finalgong(Player &player)
{

}

void Terrain::hemisphere_level4_Collision(Player &player)
{
	if(sqrt((player.pos.x - pos.x)*(player.pos.x - pos.x) + (player.pos.z - pos.z)*(player.pos.z - pos.z)) <= 0.3f)
    {


		if( fabs(player.pos.y -  pos.y) < 0.2f && player.pos.y > pos.y)
        {	
			player.makejump(20.f);
		}
    }
}

void Terrain::grid_level4_Collision(Player &player, string objectname)
{
	int index = 0;

	if(objectname == "Level4_grid1")
	index = LEVEL4_GRID1;
	if(objectname == "Level4_grid2")
	index = LEVEL4_GRID2;

	if( fabs( player.pos.z - pos.z ) < 0.4f && fabs(player.pos.x - pos.x) < 1.6f && fabs(player.pos.y - pos.y) < 0.3f)
	{
		player.Level4_collisions[index] = 1;
		player.standat = pos.y + 0.2;
		player.maxrelativeheight = pos.y + 0.2;
		
		if( fabs(player.pos.y - pos.y) < 0.4f)
		player.jumping = 0;
		player.waitbeforedie = 100.f;
		
	}
	else
	{
		////printf(":%f\n",player.waitbeforedie);
		player.Level4_collisions[index] = 0;	
		player.maxrelativeheight = 0.0;
	}

}

void Terrain::floor_moving1_level4_Collision(Player &player, string objectname)
{
	if(objectname == "Level4_floor_moving1" || objectname == "Level4_floor_moving2" || objectname == "Level4_floor_moving3" || objectname == "Level4_floor_moving4")
	{
		pos.z += 0.02;

		if(pos.z >= 12.f)
		pos.z = -12.f;
	}
	if(objectname == "Level4_floor_moving5" || objectname == "Level4_floor_moving6" || objectname == "Level4_floor_moving7" || objectname == "Level4_floor_moving9")
	{
		pos.z -= 0.02;

		if(pos.z <= -12.f)
		pos.z = 12.f;
	}

	int index = 0;

	if(objectname == "Level4_floor_moving1")
	index = 4;
	if(objectname == "Level4_floor_moving2")
	index = 5;
	if(objectname == "Level4_floor_moving3")
	index = 6;
	if(objectname == "Level4_floor_moving4")
	index = 7;
	if(objectname == "Level4_floor_moving5")
	index = 8;
	if(objectname == "Level4_floor_moving6")
	index = 9;
	if(objectname == "Level4_floor_moving7")
	index = 10;
	if(objectname == "Level4_floor_moving9")
	index = 11;
	

	if( fabs( player.pos.z - pos.z ) < 0.8f && fabs(player.pos.x - pos.x) < 0.8f && fabs(player.pos.y - pos.y) < 0.3f)
	{
		player.Level4_collisions[index] = 1;
		player.standat = pos.y + 0.1;
		player.maxrelativeheight = pos.y + 0.1;
		
		if( fabs(player.pos.y - pos.y) < 0.2f)
		{player.jumping = 0;
		player.waitbeforedie = 20.f;}
		
		
		if(objectname == "Level4_floor_moving1" || objectname == "Level4_floor_moving2" || objectname == "Level4_floor_moving3" || objectname == "Level4_floor_moving4")
		player.pos.z += 0.02;
		else
		player.pos.z -= 0.02;
		
	}
	else
	{
		////printf(":%f\n",player.waitbeforedie);
		player.Level4_collisions[index] = 0;	
		player.maxrelativeheight = 0.0;
	}
}

void Terrain::floor1_level4_Collision(Player &player)
{
	//Level2_floor1 = new Terrain(vec3(-0.6f,1.5f,0.f), vec3(0.6,0.6,0.6), 90.f ,vec3(0.6,0.2,0.8));
	// printf("pos: %f <> %f\n",fabs(player.pos.x - pos.x) ,fabs( player.pos.z - pos.z ));


	if( fabs( player.pos.z - pos.z ) < 11.f && fabs(player.pos.x - pos.x) < 2.0f)
	{
		player.Level4_collisions[LEVEL4_FLOOR1] = 1;
		player.standat = pos.y + 0.1;
		player.maxrelativeheight = pos.y + 0.1;
		
		if( fabs(player.pos.y - pos.y) < 0.2f)
		player.jumping = 0;
		player.waitbeforedie = 100.f;
		////printf("stop\n");
	}
	else
	{
		////printf(":%f\n",player.waitbeforedie);
		player.Level4_collisions[LEVEL4_FLOOR1] = 0;	
		player.maxrelativeheight = 0.0;
		player.standat = -3.0f;
		//player.checkpointlevel4();
	}
}

void Terrain::floor2_level4_Collision(Player &player)
{
	//Level2_floor1 = new Terrain(vec3(-0.6f,1.5f,0.f), vec3(0.6,0.6,0.6), 90.f ,vec3(0.6,0.2,0.8));
	// printf("pos: %f <> %f\n",fabs(player.pos.x - pos.x) ,fabs( player.pos.z - pos.z ));

	if( fabs( player.pos.z - pos.z ) < 11.f && fabs(player.pos.x - pos.x) < 2.0f)
	{
		player.Level4_collisions[LEVEL4_FLOOR2] = 1;
		player.standat = pos.y + 0.1;
		player.maxrelativeheight = pos.y + 0.1;
		
		if( fabs(player.pos.y - pos.y) < 0.2f)
		player.jumping = 0;
		player.waitbeforedie = 100.f;
		////printf("stop\n");
	}
	else
	{
		////printf(":%f\n",player.waitbeforedie);
		player.Level4_collisions[LEVEL4_FLOOR2] = 0;	
		player.maxrelativeheight = 0.0;
		//player.standat = -3.0f;
		//player.checkpointlevel4();
	}
}

void Terrain::Update()
{

}

void Terrain::floor2_level3_Collision(Player &player)
{
	////printf("pos: %f ? %f\n",pos.z,pos.x);
	if( fabs( player.pos.z - pos.z ) < 3.0f && fabs(player.pos.x - pos.x) < 3.00f)
	{
		////printf("COLL\n");
		player.Level3_collisions[LEVEL3_FLOOR2] = 1;
		player.standat = pos.y + 0.50;
		player.maxrelativeheight = pos.y + 050;
		
		if( fabs(player.pos.y - pos.y) < 0.70f)
		player.jumping = 0;
		player.waitbeforedie = 100.f;
		////printf("stop\n");
	}
	else
	{
		////printf(":%f\n",player.waitbeforedie);
		player.Level3_collisions[LEVEL3_FLOOR2] = 0;	
		player.maxrelativeheight = 0.0;
	}
}

void Terrain::floor1_level2_Collision(Player &player)
{
	//Level2_floor1 = new Terrain(vec3(-0.6f,1.5f,0.f), vec3(0.6,0.6,0.6), 90.f ,vec3(0.6,0.2,0.8));

	if( fabs( player.pos.z - pos.z ) < 1.20f && fabs(player.pos.x - pos.x) < 6.f)
	{

		player.Level2_collisions[LEVEL2_FLOOR1] = 1;
		player.standat = pos.y + 0.1;
		player.maxrelativeheight = pos.y + 0.1;
		
		if( fabs(player.pos.y - pos.y) < 0.2f)
		player.jumping = 0;
		player.waitbeforedie = 100.f;
		////printf("stop\n");
	}
	else
	{
		////printf(":%f\n",player.waitbeforedie);
		player.Level2_collisions[LEVEL2_FLOOR1] = 0;	
		player.maxrelativeheight = 0.0;
		player.standat = -3.0f;

		if(player.pos.y < -0.5f)
		{
			player.checkpointlevel2();
		}
	}
}

void Terrain::floor2_level2_Collision(Player &player)
{
	//Level2_floor1 = new Terrain(vec3(-0.6f,1.5f,0.f), vec3(0.6,0.6,0.6), 90.f ,vec3(0.6,0.2,0.8));

	if( fabs( player.pos.z - pos.z ) < 4.5f && fabs(player.pos.x - pos.x) < 1.80f && player.currentlevel == 2)
	{

		player.Level2_collisions[LEVEL2_FLOOR2] = 1;
		player.standat = pos.y + 0.11;
		player.maxrelativeheight = pos.y + 0.1;
		
		if( fabs(player.pos.y - pos.y) < 0.2f)
		player.jumping = 0;
		player.waitbeforedie = 100.f;
		////printf("stop\n");
	}
	else
	{
		////printf(":%f\n",player.waitbeforedie);
		player.Level2_collisions[LEVEL2_FLOOR2] = 0;	
		player.maxrelativeheight = 0.0;
	}
}

void Terrain::WoodenDoorOpen(Player &player)
{
    if(sqrt((player.pos.x - pos.x)*(player.pos.x - pos.x) + (player.pos.z - pos.z)*(player.pos.z - pos.z)) <= 1.1 )
    {
		if(woodenDoorRotation < 90.f)
		woodenDoorRotation += 1.f;
    }
	else
	{
		if(woodenDoorRotation > 0.f)
		woodenDoorRotation -= 1.f;
	}

}

void Terrain::RockCollision(Player &player)
{
 	//////printf("STOP!: %d\n",stop);
    if(sqrt((player.pos.x - pos.x)*(player.pos.x - pos.x) + (player.pos.z - pos.z)*(player.pos.z - pos.z)) <= 0.421 )
    {
			//////printf("not falling: %f\n",radius);
			// ////printf("Player: %f : %f \n",player.pos.x, player.pos.z);
			// ////printf("Box: %f : %f \n",pos.x, pos.z);
			// ////printf("Distance: %f  \n", sqrt((player.pos.x - pos.x)*(player.pos.x - pos.x) + (player.pos.z - pos.z)*(player.pos.z - pos.z)) );
			// ////printf("Height: %f and jump %d and stop %d\n",player.maxrelativeheight, player.jumping, player.stop);

        if(player.pos.y - (pos.y + 0.221) <= 0.1 && ((pos.y + 0.221) < player.pos.y))
        {

			//////printf("STOP2!: %d\n",stop);
			player.rock_collision = 1;		
			player.standat = pos.y + 0.221;
			player.maxrelativeheight = pos.y + 0.221;
			player.jumping = 0;
			//////printf("max: %f %d\n",player.maxrelativeheight,player.jumping);	
			//////printf("stop!\n");
		}
		if (((pos.y + 0.221) > player.pos.y))
		{
			//////printf("not falling: %f\n",radius);
			//////printf("Player: %f : %f \n",player.pos.x, player.pos.z);
			//////printf("Box: %f : %f \n",pos.x, pos.z);
			//////printf("Distance: %f  \n", sqrt((player.pos.x - pos.x)*(player.pos.x - pos.x) + (player.pos.z - pos.z)*(player.pos.z - pos.z)) );
		
				player.pos.x = keepdistancex[ROCK];
				player.pos.z = keepdistancez[ROCK];
		}

    }
    else
    {
		keepdistancex[ROCK] = player.pos.x;
		keepdistancez[ROCK] = player.pos.z;
		player.rock_collision = 0;
		player.maxrelativeheight = 0.1;
	}

}

void Terrain::floor_level1_Collision(Player &player)
{
	//scene.boundaryMin = vec3(-8.5f, -2, -4.5f);
	//scene.boundaryMax = vec3(5.8f, 3.5, 4.5f);

	//for scene number 1 only!
	if( (player.pos.x < -5.5 && player.pos.x >= -8.5f || player.pos.x > -3.22f &&  player.pos.x < 5.8f ) && player.pos.z <= 4.5f && player.pos.z > -4.5f)
    {
			// //////printf("not falling: %f\n",radius);
			// //printf("Player: %f : %f \n",player.pos.x, player.pos.z);
			// ////printf("Box: %f : %f \n",pos.x, pos.z);
			// ////printf("Distance: %f  \n", sqrt((player.pos.x - pos.x)*(player.pos.x - pos.x) + (player.pos.z - pos.z)*(player.pos.z - pos.z)) );
			// ////printf("Height: %f and jump %d and stop %d\n",player.maxrelativeheight, player.jumping, player.stop);
		if(player.pos.y < 0.2f)
		{
			player.floor_collision = 1;		
			player.standat = pos.y + 0.1;
			player.maxrelativeheight = pos.y + 0.1 ;

					
			//player.velocity_jump = 0;
			////printf("co jest\n");
			player.jumping = 0;
		}
		else
		{
			player.floor_collision = 0;
		}

	}
	else
	{
		player.floor_collision = 0;
		player.maxrelativeheight = 0.0;


		if(player.pos.y < -0.25f)
		{
			player.beginafterliveloss();
		}
	}


	if( player.pos.x <= -5.5 && (player.pos.z >= 1.3f || player.pos.z <= -1.1f))
	{
		//////printf("NIE WOLNO\n");

		player.pos.x = keepdistancex[PODLOGA];
		player.pos.z = keepdistancez[PODLOGA];
	}
	else
	{
		//////printf("TERAZ WOLNO\n");

		keepdistancex[PODLOGA] = player.pos.x;
		keepdistancez[PODLOGA] = player.pos.z;
	}


}

void Terrain::floor1_level3_Collision( Player &player) 
{
	//Level2_floor1 = new Terrain(vec3(-0.6f,1.5f,0.f), vec3(0.6,0.6,0.6), 90.f ,vec3(0.6,0.2,0.8));

	if( fabs( player.pos.z - pos.z ) < 8.8f && fabs(player.pos.x - pos.x) < 23.0f && player.currentlevel == 3)
	{

		player.Level3_collisions[LEVEL3_FLOOR1] = 1;
		player.standat = pos.y + 0.11;
		player.maxrelativeheight = pos.y + 0.1;
		
		if( fabs(player.pos.y - pos.y) < 0.2f)
		player.jumping = 0;
		player.waitbeforedie = 100.f;
		////printf("stop\n");
	}
	else
	{
		if(player.pos.y < -5.f)
		player.checkpointlevel3();

		////printf(":%f\n",player.waitbeforedie);
		player.Level3_collisions[LEVEL3_FLOOR1] = 0;	
		player.maxrelativeheight = 0.0;
		player.standat = -10.f;
	}

}

void Terrain::Checkplayerfinishedlevel1( Player &player )
{
	if(sqrt((player.pos.x - pos.x)*(player.pos.x - pos.x) + (player.pos.z - pos.z)*(player.pos.z - pos.z)) <= 0.821 )
    {
		player.currentlevel=2;
		player.pos.x = 2.6f;
		player.pos.z = 0.2f;
		player.pos.y = pos.y + 0.1;
		
		player.makejump(3.f);
	//	//printf("TELEPORT %d\n",player.currentlevel);
	}
}

void Terrain::Checkplayerfinishedlevel2( Player &player)
{
	if(sqrt((player.pos.x - pos.x)*(player.pos.x - pos.x) + (player.pos.z - pos.z)*(player.pos.z - pos.z)) <= 0.821 )
    {
		player.currentlevel=1;
		player.pos.x = -7.0f;
		player.pos.z = 0.1f;
		player.pos.y = pos.y + 0.1;
		player.makejump(3.f);
	//	//printf("TELEPORT %d\n",player.currentlevel);
	}
}

void Terrain::Checkplayerfinishedgame( Player &player)
{
	if(sqrt((player.pos.x - pos.x)*(player.pos.x - pos.x) + (player.pos.z - pos.z)*(player.pos.z - pos.z)) <= 0.821 )
    {
		player.currentlevel=0;
		player.iWonTheGame = 1;
		
	//	//printf("TELEPORT %d\n",player.currentlevel);
	}
}


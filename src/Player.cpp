#include "stdafx.h"
#include "Player.h"
#define jump 1
#define fall 2
#define stand 3
#define move 4


Player::Player(vec3 pos, vec3 dir, vec3 force, vec3 scale, float angle)
{
	this->pos = pos;
	this->dir = dir;
	this->angle = angle;
	this->force = force;
	this->scale = scale;
	this->rotate = 0;
	this->isplayerunderplatform = 0;
	this->youcantgethigher = 0;
	this->endurance = 2;
	this->waitbeforedie = 0.f;
	this->wyrzucilem_diamenty = 0;
	this->iWonTheGame = 0;
	this->goldenkey = 0;
	this->currentlevel = 0;
	this->friendscounter = 0;
	this->lost = 0;
	this->tmprotate = 0;
//this->diam_rotation = 0;

	this->showorblink = 0;
	this->showorblinktimer = 50.f;
	
	//Blinkin of player when resp
	this->timetoblink = 15.f;
	this->timesblink = 0;
	this->timetoshowup = 50.f;

	diamonds_counter = 0;
	lives_counter = 3;
	keys_counter = 0;
	
	trunk_stop = new bool[1];
	trunk_stop[0] = 0;

	// pos.x = 0.0f;
	// pos.y = 1.75f;
	// pos.z = 0.0f;


	// dir.x = 2.0f;
	// dir.y = 0.0f;
	// dir.z = -1.0f;

	speed = 0.05f;
	radius = .1f;
	stop = 0;
	stopwell1 = 0;
	stopWood = 0;

	jumping  = 0;
	falling  = 0;
	jump_maximal_height = 2.f;
	jump_temporary_height = 0.f;
	turn = 0;

	velocity_horizontal = 0;
	velocity_vertical = 0;
	velocity_jump = 0.0f;
	gravity_jump = -9.81f;
	onground = true;
	deltatime = 0.f;
	maxrelativeheight = 0.1f;
	doublejump = 0;
	rock_collision = 0;
	floor_collision = 0;
	platformnumber = 22;
	boxnumber = 10;
	timetofall = 100.f;
	direction = 1.f;

	specialdiamonds = new bool[3];
	specialdiamonds[0] = 0;
	specialdiamonds[1] = 0;
	specialdiamonds[2] = 0;
	
	box_stop = new bool [boxnumber];
	platformstop = new bool[platformnumber];

	for(int i=0; i<platformnumber; i++)
	platformstop[i] = 0;

	for(int i=0; i<boxnumber; i++)
	box_stop[i] = 0;

	textureName = "playertex";
	flyingMode = false;

	weight = 4;

	//Level2

	Level2_numberofobjects = 3;
	
	Level2_collisions = new bool[Level2_numberofobjects];
	
	for(int i=0; i<Level2_numberofobjects; i++)
	Level2_collisions[i] = 0;

	this->ismoving = 0;

	//Level3
	Level3_numberofobjects = 3;
	Level3_collisions = new bool[Level3_numberofobjects];

	for(int i=0; i<Level3_numberofobjects; i++)
	Level3_collisions[i] = 0;

	//Level4
	Level4_numberofobjects = 26;
	Level4_collisions = new bool[Level4_numberofobjects];

	for(int i=0; i<Level4_numberofobjects; i++)
	Level4_collisions[i] = 0;

	//Various
	this->dropalldiamonds = 0;
	this->howmanyweredropped = 0;
	this->droppedscale = 0.3f;
	this->timetonextjump = 0.f;

	showtorus = 0;
	torussize = 0.6f;

}


Player::~Player()
{
	delete[] box_stop;
	delete[] trunk_stop;
	delete[] specialdiamonds;
	delete[] platformstop;

	delete[] Level2_collisions;
	delete[] Level3_collisions;
	delete[] Level4_collisions;
	
}

	struct SFace {
		int v[3];
		int n[3];
		int uv[3];
	};


bool Player::Load(std::string filename)
{


	FILE * fp = fopen(filename.c_str(), "r");

	if (fp == NULL) {
		//printf("Nie wczytano pliku %s\n", filename.c_str());
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

	float diffX = maxVertex.x - minVertex.x;
	float diffY = maxVertex.y - minVertex.y;
	float diffZ = maxVertex.z - minVertex.z;

	if (diffX < diffY)
	{
		if (diffY < diffZ)
		{
			radius = diffZ;
		}
		else
		{
			radius = diffY;
		}
	}
	else
	{
		if (diffX < diffZ)
		{
			radius = diffZ;
		}
		else
		{
			radius = diffX;
		}
	}

    radius /= 2;
	//weight = radius;

	return true;
}

void Player::Render()
{

	if(timetoblink <= 15.f && timetoblink > 0)
	{
	// glMaterialfv(GL_FRONT, GL_AMBIENT, &ambient.x);
	// glMaterialfv(GL_FRONT, GL_DIFFUSE, &diffuse.x);
	// glMaterialfv(GL_FRONT, GL_SPECULAR, &specular.x);

	// glPushMatrix();
	// glTranslatef(pos.x, pos.y, pos.z);
	// //glRotatef(rotate.x, rotate.y, rotate.z);
	// glScalef(scale.x,scale.y,scale.z);
	// glutSolidSphere(radius, 24, 24);
	// glPopMatrix();

	if (!textureName.empty())
	{
		glEnable(GL_TEXTURE_2D);
		TextureManager::getInstance()->BindTexture(textureName);
	}

	float mat_ambient[] = { 0.0f, 0.0f, 0.0f };
	float mat_diffuse[] = { color.x, color.y, color.z };
	float mat_specular[] = { 0.1f, 0.1f, 0.1f };

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);

	glPushMatrix();

		glTranslatef(pos.x, pos.y, pos.z);
		glScalef(scale.x,scale.y,scale.z);

		//glTranslatef(modelTranslation.x, modelTranslation.y, modelTranslation.z);
		//glScalef(modelScale.x, modelScale.y, modelScale.z);

		glBegin(GL_TRIANGLES);
		for (int i = 0; i < vertices.size(); i++)
		{
			glNormal3f(normals[i].x, normals[i].y, normals[i].z);
			glTexCoord2f(uvs[i].x, uvs[i].y);
			glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
		}
		glEnd();

	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	}

}

void Player::Update()
{
	//printf("SPECIAL: %d %d %d <> %d \n",specialdiamonds[0],specialdiamonds[1],specialdiamonds[2],keys_counter);
	//printf("D: %d\n",dropalldiamonds);
	//printf("")
	//printf("doublejump: %d\n",jumping);
	//printf("maxrelative: %f\n",maxrelativeheight);
	// printf("pos.x: %f\n",pos.x);
	// printf("pos.y: %f\n",pos.y);
	// printf("pos.z: %f\n",pos.z);
	
	//printf("standat: %f\n",standat);
	
	//printf("velocity.y: %f\n",velocity_jump);
		//else
	//velocity_jum = 0;
	
	// printf("velocity : %f \n",velocity_jump);
	// printf("gravity : %f \n",gravity_jump);

	// printf("TRACE: SHOW: %f <> BLINK %f, TIMES: %d\n",timetoshowup,timetoblink,timesblink);

	// if(showorblinktimer > 0)
	// {
	// 	showorblinktimer --;
	// }

	// if(showorblink == 1)
	// {
	// 	showorblinktimer = 50.f;
	// }

	if(showorblink == 1 && timetoblink == 0 && timesblink > 0)
	{
		timetoblink = 30.f;
		timesblink--;
	}

	if(timesblink == 0)
	{
		showorblink = 0;
		timetoblink = 15.f;
	}

	// printf("K: %d\n",endurance);

	
	oldpos = pos;
	

	if(dropalldiamonds == 2)
	droppedscale -= 0.0005f;

	if((pos.y > maxrelativeheight))
	{jumping = true; }
	else
	jumping  = false;

	if(direction == 1)
	{
		tmprotate = rotate + 180.f;
	}
	else
	{
		if(fabs(tmprotate - rotate) > 0.1f)
		rotate+=4;
		else
		direction = 1;
	}


	float rotX = (float)cos(rotate * 3.14 / 180) * 1.8f;
	float rotZ = (float)sin(rotate * 3.14 / 180) * 1.8f;

	dir.x += rotX;
	dir.z -= rotZ;

	float dlugosc = sqrt(dir.x * dir.x + dir.z * dir.z + dir.y * dir.y);

	dir.x = dir.x/dlugosc;
	dir.z = dir.z/dlugosc;
	dir.y = dir.y/dlugosc;

	deltatime = deltatime * 0.001;
	pos.y += velocity_jump * deltatime;
	
	bool stop_available = 0;
	for(int i=0; i<7; i++)
	{
		if(box_stop[i] == 1 )
		{stop_available = 1; break;}
	}

	for(int i=0; i<platformnumber; i++)
	{
		if(platformstop[i] == 1 )
		{stop_available = 1; break;}
	}

	//if(currentlevel == 2)
	for(int i=0; i<Level2_numberofobjects; i++)
	{
		if(Level2_collisions[i] == 1)
		{stop_available = 1; break;}
	}

	//if(currentlevel == 3)
	for(int i=0; i<Level3_numberofobjects; i++)
	{
		if(Level3_collisions[i] == 1)
		{stop_available = 1; break;}
	}

	//if(currentlevel == 4)
	for(int i=0; i<Level4_numberofobjects; i++)
	{
		if(Level4_collisions[i] == 1)
		{stop_available = 1; break;}
	}


	if(stop_available == 1 || stopwell1 == 1 || stopWood == 1 || rock_collision || trunk_stop[0] || floor_collision ) 
	//if( stopwell1 == 1 || stopWood == 1 || rock_collision || trunk_stop[0] || floor_collision) 
	//if(floor_collision) 
	{
		///printf("> %f ?? %f\n",pos.y, standat);
		if(pos.y < standat )
		pos.y = standat;
	}

	//if(velocity_jump <= 0.01)
	//{
	//	pos.y -= 1.f * deltatime;
	//}

	if(doublejump == 1 && pos.y >= 0.2 )
    makejump(-8.f);


	if(waitbeforedie > 0)
	{
		waitbeforedie --;
	}
	if(timetofall > 0)
	{
		timetofall--;
	}
	if(timetoblink > 0 && showorblink == 1)
	{
		timetoblink--;
	}
	if(timetonextjump > 0 )
	{
		timetonextjump--;
	}

	if(velocity_jump <= -9.81)
	velocity_jump = -9.81;


	velocity_jump += gravity_jump * deltatime;
	velocity_vertical /= 1.2;
	velocity_horizontal /= 1.2;
}

int Player::makejump()
{
	velocity_jump = 5.2f;

	return 1;
}

int Player::makejump(float jmp)
{
	velocity_jump = jmp;

	return 1;
}

void Player::test_sphere()
{
	// if(timetoblink <= 15.f && timetoblink > 0)
	// {
	// //glDisable(GL_LIGHTING);
	// float mat_ambient[] = { 0.0f, 0.0f, 0.0f };
	// float mat_diffuse[] = { 0.f, 1.f, 0.f };
	// float mat_specular[] = { 0.1f, 0.1f, 0.1f };

	// glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	// glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	// glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);

	// glPushMatrix();
	// glTranslatef(pos.x, pos.y, pos.z);
	// //glRotatef(rotate.x, rotate.y, rotate.z);
	// glScalef(scale.x,scale.y,scale.z);
	// glutSolidSphere(radius, 24, 24);
	// glPopMatrix();
	// //glEnable(GL_LIGHTING);
	// }
}

void Player::checkpointlevel3()
{
	if(waitbeforedie == 0 && pos.y < -0.2f && diamonds_counter == 0)
	{
		lives_counter--;
		diamonds_counter = 0;
		endurance = 2;
		pos.x = 22.2f;
		pos.z = 0.2f;
		pos.y = 0.2f;
		
	    makejump(3.f);
		

		if(lives_counter < 0 )
		exit(0);
		//printf("TELEPORT %d\n",player->currentlevel);
		return;
	}
	if(diamonds_counter == 0)
	{
		lives_counter--;
		diamonds_counter = 0;
		endurance = 2;
		pos.x = 22.2f;
		pos.z = 0.2f;
		pos.y = 0.2f;
		lost = 1;

		timesblink = 20;
		showorblink = 1;
		
	    makejump(3.f);
		

		if(lives_counter < 0 )
		exit(0);
		//printf("TELEPORT %d\n",player->currentlevel);
		return;
	}

	dropalldiamonds = 1;
}

void Player::checkpointlevel2()
{
	if(diamonds_counter == 0)
	{
		lives_counter--;
		endurance = 2;

		pos.x = 4.2f;
		pos.z = 0.2f;
		pos.y = 2.4f;
		//printf("TELEPORT %d\n",currentlevel);

		timesblink = 20;
		showorblink = 1;
		
	    makejump(3.f);

		if(lives_counter < 0 )
		exit(0);
		//printf("TELEPORT %d\n",player->currentlevel);
	}

	dropalldiamonds = 1;
}

void Player::checkpointlevel4()
{

	if(diamonds_counter == 0)
	{
		
		lives_counter--;
		endurance = 2;

			pos.x = 2.0f;
			pos.z = 0.0f;
			pos.y = 0.1f;

		timesblink = 20;
		showorblink = 1;
		
	    makejump(3.f);

		if(lives_counter < 0 )
		exit(0);
	}

	dropalldiamonds = 1;
}

void Player::beginafterliveloss()
{
	if ( diamonds_counter == 0 )
	{
		pos.x = 2.f;
		pos.y = 0.8f;
		pos.z = 0.f;

		lives_counter --;
		endurance = 2;

		timesblink = 20;
		showorblink = 1;

		makejump(3.f);

		if(lives_counter < 0 )
		exit(0);

		//And play sound!
	}

	dropalldiamonds = 1;
}
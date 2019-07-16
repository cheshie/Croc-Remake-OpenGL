#include "stdafx.h"
#include "Enemy.h"
#define jump 1
#define fall 2
#define stand 3
#define move 4


Enemy::Enemy(vec3 pos, vec3 dir, vec3 force, vec3 scale, float angle)
{

	this->pos = pos;
	this->dir = dir;
	this->angle = angle;
	this->scale = scale;
	this->angle_right = 0.f;

	this->left = true;
	this->normal = 1;
	this->isAlive = 1;
	this->DisplayListIndex = glGenLists(1);
	

	this->ldc = vec3(22.f, 0.9f, 8.11f);
	this->rdc = vec3(22.f, 0.9f, -7.11f);
	
	this->luc = vec3(-22.f, 0.9f, 8.11f);
	this->ruc = vec3(-22.f, 0.9f, -7.11f);
	this->timer_stop = 20.f;
	this->timer_stop2 = 100.f;
	
	this->dirmove = 0;
	this->velocity_jump = 0.0f;
	this->gravity_jump = -9.81f;
}


Enemy::~Enemy()
{
	//delete[] box_stop;
}

	struct SFace {
		int v[3];
		int n[3];
		int uv[3];
	};


bool Enemy::Load(std::string filename)
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

		glNewList(DisplayListIndex, GL_COMPILE);

		glBegin(GL_TRIANGLES);
		for (int i = 0; i < vertices.size(); i++)
		{
			glNormal3f(normals[i].x, normals[i].y, normals[i].z);
			glTexCoord2f(uvs[i].x, uvs[i].y);
			glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
		}
		glEnd();

		glEndList();

	return true;
}

void Enemy::smallRender(Player &player, vec3 &translation, bool &aliver)
{
	if(isAlive == 1)
	{

	if (!textureName.empty())
	{
		glEnable(GL_TEXTURE_2D);
		TextureManager::getInstance()->BindTexture(textureName);
	}

	float mat_ambient[] = { 0.0f, 0.0f, 0.0f };
	//float mat_diffuse[] = { 1.f, 1.f, 1.f };
	float mat_diffuse[] = { 1.f,1.f,1.f };	
	float mat_specular[] = { 0.1f, 0.1f, 0.1f };

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);


	//pos = boxposition;

	glPushMatrix();


		glTranslatef(translation.x, translation.y, translation.z);
		//glTranslatef(modelTranslation.x, modelTranslation.y, modelTranslation.z);
		glScalef(scale.x, scale.y, scale.z);
        glRotatef(angle_right, 0.f, 1.f, 0.f);
		glCallList(DisplayListIndex);
		//printf("angle: %f\n",angle);
		//glBegin(GL_TRIANGLES);
		//for (int i = 0; i < vertices.size(); i++)
		//{
		//	glNormal3f(normals[i].x, normals[i].y, normals[i].z);
		//	glTexCoord2f(uvs[i].x, uvs[i].y);
		//	glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
		//}
		//glEnd();

	glPopMatrix();
	}

	smallUpdate(player, translation, aliver);
}


void Enemy::smallUpdate(Player &player, vec3 &translation, bool &aliver)
{
	//printf("CORDS: %f  <>  %f\n",translation.x,translation.z);
	vec3 step;
	float length;
	int dirmove_temp = dirmove;

	//player.deltatime = player.deltatime;
	//printf("JUMP: %f\n",velocity_jump * player.deltatime);
	
	translation.y += velocity_jump * player.deltatime;

		step = player.pos - translation;
		length = sqrt((step.x)*(step.x)+(step.z)*(step.z));		

		if(length <= 0.15f && fabs(pos.y - player.pos.y) < 0.65)
		{
			aliver = 0;
			player.timesblink = 20;
			player.showorblink = 1;
			player.makejump(2.f);
			player.checkpointlevel3();
		}

		if(translation.y <= 0.3f)
		{
			translation.y = 0.3f;
		}

		if(velocity_jump <= -9.81)
		velocity_jump = -9.81;

		if(timer_stop >= 0)
		{
			timer_stop--;
		}

		if(timer_stop == 0 && pos.y <= 0.3f)
		{
			timer_stop = 30.f;
			makejump(2.f);
		//	printf("jump!\n");
		}


		step.x = step.x/length;
		//step.y = step.y/length;
		step.z = step.z/length;
		
		translation.x += step.x * 0.08;
		//pos.y += step.y * 0.18;
		translation.z += step.z * 0.08;

		velocity_jump += gravity_jump * player.deltatime;
		//printf("velocity: %f\n",velocity_jump);
		
}


void Enemy::bigRender(Player &player)
{
	if(isAlive == 1)
	{

	if (!textureName.empty())
	{
		glEnable(GL_TEXTURE_2D);
		TextureManager::getInstance()->BindTexture(textureName);
	}

	float mat_ambient[] = { 0.0f, 0.0f, 0.0f };
	//float mat_diffuse[] = { 1.f, 1.f, 1.f };
	float mat_diffuse[] = { 1.f,1.f,1.f };	
	float mat_specular[] = { 0.1f, 0.1f, 0.1f };

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);


	//pos = boxposition;

	glPushMatrix();


		glTranslatef(pos.x, pos.y, pos.z);
		//glTranslatef(modelTranslation.x, modelTranslation.y, modelTranslation.z);
		glScalef(scale.x, scale.y, scale.z);
        glRotatef(angle_right, 0.f, 1.f, 0.f);
		glCallList(DisplayListIndex);
		//printf("angle: %f\n",angle);
		//glBegin(GL_TRIANGLES);
		//for (int i = 0; i < vertices.size(); i++)
		//{
		//	glNormal3f(normals[i].x, normals[i].y, normals[i].z);
		//	glTexCoord2f(uvs[i].x, uvs[i].y);
		//	glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
		//}
		//glEnd();

	glPopMatrix();
	}

	bigUpdate(player);
}

void Enemy::bigUpdate(Player &player)
{
	vec3 step;
	float length;
	int dirmove_temp = dirmove;

	//player.deltatime = player.deltatime;
	//printf("JUMP: %f\n",velocity_jump * player.deltatime);
	pos.y += velocity_jump * player.deltatime;

	if(pos.y <= 0.9f)
	{
		pos.y = 0.9f;
	}
	if (pos.y >= 3.9f)
	{
		pos.y = 0.9f;
	}

	if(this->dirmove == 0)
	{
		step = ldc - pos;
		length = sqrt((step.x)*(step.x)+(step.z)*(step.z));

		if(length <= 0.4f)
		{this->dirmove = 1; }
	}
	if(this->dirmove == 1)
	{
		step = luc - pos;
		length = sqrt((step.x)*(step.x)+(step.z)*(step.z));

		if(length <= 0.4f)
		{this->dirmove = 2; }
	}
	if(this->dirmove == 2)
	{
		step = ruc - pos;
		length = sqrt((step.x)*(step.x)+(step.z)*(step.z));

		if(length <= 0.4f)
		{this->dirmove = 3; }
	}
	if(this->dirmove == 3)
	{
		step = rdc - pos;
		length = sqrt((step.x)*(step.x)+(step.z)*(step.z));

		if(length <= 0.4f)
		{this->dirmove = 0;}
	}


		if(dirmove_temp != dirmove)
		this->angle_right-= 90.f;

		if(dirmove == 0 || dirmove == 1 || dirmove == 2 ||dirmove == 3)
		{
		step.x = step.x/length;
		//step.y = step.y/length;
		step.z = step.z/length;
		
		pos.x += step.x * 0.18;
		//pos.y += step.y * 0.18;
		pos.z += step.z * 0.18;
		}

		if(velocity_jump <= -9.81)
		velocity_jump = -9.81;

		if(timer_stop >= 0)
		{
			timer_stop--;
		}

		if(timer_stop2 >= 0)
		{
			timer_stop2--;
		}

		if(timer_stop == 0 && pos.y <= 0.9)
		{
			timer_stop = 100.f;
			makejump(6.f);
			// printf("jump!\n");
		}

		velocity_jump += gravity_jump * player.deltatime;
		//printf("velocity: %f\n",velocity_jump);

		if(sqrt((player.pos.x - pos.x)*(player.pos.x - pos.x) + (player.pos.z - pos.z)*(player.pos.z - pos.z)) < 0.4f)
		{
	//	printf("Life loss: \n");
		player.endurance--;
		this->normal = 0;
			if(player.diamonds_counter == 0)
			player.checkpointlevel3();
			else
			player.dropalldiamonds = 1;
		}
}

void Enemy::makejump(float high)
{
	velocity_jump = high;
}

void Enemy::Render(Player &player)
{
	if(isAlive == 1)
	{
	//glDisable(GL_LIGHTING);

	float mat_ambient[] = { 0.0f, 0.0f, 0.0f };
	float mat_diffuse[] = { 1.f, 0.f, 0.f };
	float mat_specular[] = { 0.1f, 0.1f, 0.1f };

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);

	glPushMatrix();
	glTranslatef(pos.x, pos.y, pos.z);
	//glColor3f(0.8f, .0f, 0.0f);
	//glRotatef(rotate.x, rotate.y, rotate.z);
	glScalef(scale.x,scale.y,scale.z);
	glutSolidSphere(1.2, 24, 24);
	glPopMatrix();
	//glEnable(GL_LIGHTING);
	Update(player);
	}
	//pos.y+= 0.01;
}

void Enemy::Update(Player &player)
{

	//dir.x += rotX;
	//dir.z -= rotZ;

	//float dlugosc = sqrt(dir.x * dir.x + dir.z * dir.z + dir.y * dir.y);

	if(this->normal == 1)
	{
		if(this->left == 1)
		{
			pos.z += 0.02f;
			pos.x = -2.f;
		}
		else
		{
			pos.z -= 0.02f;
			pos.x = -2.f;		
		}

	//printf("POSX: %f || %d\n",pos.z,normal);

		if(pos.z > 1.2f )
		{
			this->left = 0;
		}
		if(pos.z < -1.2f )
		{
			this->left = 1;
		}

	}

    if(sqrt((player.pos.x - pos.x)*(player.pos.x - pos.x) + (player.pos.z - pos.z)*(player.pos.z - pos.z)) <= 1.2f)
	{
		this->normal = 0;
	}

	else
	{
		this->normal = 1;
	}
	
	if(this->normal == 0)
	{
		vec3 step = player.pos - pos;
		float length = sqrt((player.pos.x - pos.x)*(player.pos.x - pos.x)+(player.pos.y - pos.y)*(player.pos.y - pos.y)+(player.pos.z - pos.z)*(player.pos.z - pos.z));
		step.x = step.x/length;
		step.y = step.y/length;
		step.z = step.z/length;
		
		pos.x += step.x * 0.02;
		pos.y = 0.2;
		pos.z += step.z * 0.02;
	}

	if(sqrt((player.pos.x - pos.x)*(player.pos.x - pos.x) + (player.pos.z - pos.z)*(player.pos.z - pos.z)) < 0.2f)
	{
		
		
		isAlive = 0;
		player.timesblink = 20;
		player.showorblink = 1;
		player.makejump(2.f);
		player.beginafterliveloss();
		this->normal = 0;
	}

	//dir.x = dir.x/dlugosc;
	//dir.z = dir.z/dlugosc;
	//dir.y = dir.y/dlugosc;


}
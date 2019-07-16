#include "stdafx.h"
#include "Diamond.h"


Diamond::Diamond(vec3 pos) 
{
    this->pos = pos;

    ambient = vec3(0.0f, 0.0f, 0.0f);
	diffuse = vec3(0.3f, 0.3f, 0.3f);
	specular = vec3(0.1f, 0.1f, 0.1f);
    height = 0.3f;
    width = 0.4;
	weight = 1;
	DisplayListIndex = glGenLists(1);
    rotation = 0.f;
	timetodisappear = 0.f;

	isAlive = true;
}


Diamond::~Diamond(void)
{ 
}
    	struct SFace {
		int v[3];
		int n[3];
		int uv[3];
	};

bool Diamond::Load(std::string filename)
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

void Diamond::Render(Player &player, vec3 boxposition, bool taken, int special, float angle, bool isdropped)
{
    if(taken == 0)
    {

	if(special == 0)
	{
		glEnable(GL_TEXTURE_2D);
		TextureManager::getInstance()->BindTexture("sdiamond1");
	}
	else if(special == 1)
	{
		glEnable(GL_TEXTURE_2D);
		TextureManager::getInstance()->BindTexture("sdiamond2");
	}
	else if(special == 2)
	{
		glEnable(GL_TEXTURE_2D);
		TextureManager::getInstance()->BindTexture("sdiamond3");
	}
	else
	{
    if (!textureName.empty())
	{
		glEnable(GL_TEXTURE_2D);
		TextureManager::getInstance()->BindTexture(textureName);
	}
	}

	float mat_ambient[] = { 0.0f, 0.0f, 0.0f };
	//float mat_diffuse[] = { 1.f, 1.f, 1.f };
	float mat_diffuse[] = { 1.f,1.f,1.f };	
	float mat_specular[] = { 0.1f, 0.1f, 0.1f };

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);

	pos = boxposition;

	glPushMatrix();

		glTranslatef(boxposition.x, boxposition.y, boxposition.z);
		//glTranslatef(modelTranslation.x, modelTranslation.y, modelTranslation.z);

		if(isdropped == 1)
		glScalef(player.droppedscale,player.droppedscale,player.droppedscale);
        else
		glScalef(0.3f, 0.3f, 0.3f);
		
		glRotatef(angle, 0.f, 1.f, 1.f);
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

	glDisable(GL_TEXTURE_2D);


    Update(player, boxposition, angle);
	glDisable(GL_TEXTURE_2D);
    }
}

void Diamond::Update(Player &player, vec3 pos, float angle)
{
    
    

    //  if(sqrt((player.pos.x - pos.x)*(player.pos.x - pos.x) + (player.pos.z - pos.z)*(player.pos.z - pos.z)) <= 0.2 )
    //  {
    //      ////printf("znikaj!\n");
    //      taken = 1;
    //      player.diamonds_counter ++;
    //  }

    // if(sqrt((player.pos.x - pos.x)*(player.pos.x - pos.x) + (player.pos.z - pos.z)*(player.pos.z - pos.z)) <= 0.391 )
    // {
	// 		////printf("not falling: %f\n",radius);
	// 		////printf("Player: %f : %f \n",player.pos.x, player.pos.z);
	// 		////printf("Box: %f : %f \n",pos.x, pos.z);
	// 		////printf("Distance: %f  \n", sqrt((player.pos.x - pos.x)*(player.pos.x - pos.x) + (player.pos.z - pos.z)*(player.pos.z - pos.z)) );
	// 		////printf("Height: %f and jump %d and stop %d\n",player.maxrelativeheight, player.jumping, player.stop);

    //     if(player.pos.y - (pos.y + 0.391) <= 0.1 && ((pos.y + 0.391) < player.pos.y))
    //     {
	// 		player.stop = 1;		
	// 		player.standat = pos.y + 0.393;
	// 		player.maxrelativeheight = pos.y + 0.393;
	// 		player.jumping = 0;
	// 		//////printf("max: %f %d\n",player.maxrelativeheight,player.jumping);	
	// 		//////printf("stop!\n");

	// 		//Possible issue: I cant jump when I jump from box to ground: solution? 
	// 		if(player.doublejump == 1)
	// 		////printf("niszczymy!\n");
	// 	}
	// 	if (((pos.y + 0.391) > player.pos.y))
	// 	{
	// 		//////printf("not falling: %f\n",radius);
	// 		//////printf("Player: %f : %f \n",player.pos.x, player.pos.z);
	// 		//////printf("Box: %f : %f \n",pos.x, pos.z);
	// 		//////printf("Distance: %f  \n", sqrt((player.pos.x - pos.x)*(player.pos.x - pos.x) + (player.pos.z - pos.z)*(player.pos.z - pos.z)) );
		
	// 		if(player.stop == 0)
	// 		{
	// 			player.pos.x = keepdistancex;
	// 			player.pos.z = keepdistancez;
	// 		}
	// 	}
	// 	// if(player.pos.x - pos.x <= 0.391 || -player.pos.x + pos.x <= 0.391)
	// 	// {
	// 	// 	////printf("stop x!\n");
	// 	// }
	// 	// if(player.pos.z - pos.z <= 0.391 || -player.pos.z + pos.z <= 0.391)
	// 	// {
	// 	// 	////printf("stop z!\n");
	// 	// }
    // }
    // else
    // {
	// 	keepdistancex = player.pos.x;
	// 	keepdistancez = player.pos.z;
	// 	player.stop = 0;
	// 	player.maxrelativeheight = 0.1;
	// }
	
	//player.stop = 0;

	//Petla sprawdza kolizje miedzy obiektami
	// for (int i = 0; i < DiamondObjects.size(); i++)
	// {
	// 	for (int j = i + 1; j < DiamondObjects.size(); j++)
	// 	{
	// 		DiamondObject* obj1 = DiamondObjects[i];
	// 		DiamondObject* obj2 = DiamondObjects[j];

	// 		float r = vec3::distance(obj1->pos, obj2->pos);

	// 		float d = (obj1->radius + obj2->radius) - r;

	// 		if (d > 0)
	// 		{
	// 			vec3 v1 = obj1->pos - obj2->pos;
	// 			vec3 v2 = obj2->pos - obj1->pos;

	// 			v1 = v1.normalized();
	// 			v2 = v2.normalized();

	// 			obj1->pos = obj1->pos + v1 * (d / 2) * 1.2f;
	// 			obj2->pos = obj2->pos + v2 * (d / 2) * 1.2f;

	// 			float total_force = obj1->force.length() + obj2->force.length();

	// 			obj1->force = v1 * total_force * 0.5f;
	// 			obj2->force = v2 * total_force * 0.5;
	// 		}
	// 	}
	// }
}
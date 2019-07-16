#include "stdafx.h"
#include "Wood.h"


Wood::Wood(vec3 pos) 
{
    this->pos = pos;

    ambient = vec3(0.0f, 0.0f, 0.0f);
	diffuse = vec3(0.3f, 0.3f, 0.3f);
	specular = vec3(0.1f, 0.1f, 0.1f);
    height = 0.3f;
    width = 0.4;
	weight = 1;
    rotation = 0.f;
	isAlive = true;
}


Wood::~Wood(void)
{ 
}
    	struct SFace {
		int v[3];
		int n[3];
		int uv[3];
	};

bool Wood::Load(std::string filename)
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

void Wood::Render(Player &player)
{
    //if(taken != 1)
    //{

		glEnable(GL_TEXTURE_2D);
		TextureManager::getInstance()->BindTexture("level1_wood");

	float mat_ambient[] = { 0.0f, 0.0f, 0.0f };
	float mat_diffuse[] = {1.f, 1.f, 1.f };
    float mat_specular[] = { 0.1f, 0.1f, 0.1f };

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);


	glPushMatrix();

		glTranslatef(pos.x, pos.y, pos.z);
		//glTranslatef(modelTranslation.x, modelTranslation.y, modelTranslation.z);
		glScalef(.45f, .3f, .3f);
        glRotatef(rotation, 0.f, 1.f, 0.f);
        //glColorf()
		glBegin(GL_TRIANGLES);
		for (int i = 0; i < vertices.size(); i++)
		{
			glNormal3f(normals[i].x, normals[i].y, normals[i].z);
			glTexCoord2f(uvs[i].x, uvs[i].y);
			glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
		}
		glEnd();
		//glBegin(GL_TRIANGLES);
		//for (int i = 0; i < vertices.size(); i++)
		//{
		//	glNormal3f(normals[i].x, normals[i].y, normals[i].z);
		//	glTexCoord2f(uvs[i].x, uvs[i].y);
		//	glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
		//}
		//glEnd();

	glPopMatrix();

	//glDisable(GL_TEXTURE_2D);


    Update(player);
	glDisable(GL_TEXTURE_2D);
    //}
}

void Wood::Update(Player &player)
{
    // if(rotation <= 360.f)
    // rotation += 1.f;
    // else
    // rotation = 0.f;

	
    if(sqrt((player.pos.x - pos.x)*(player.pos.x - pos.x) + (player.pos.z - pos.z)*(player.pos.z - pos.z)) <= 1.9f && pos.z - player.pos.z <= 0.3 && pos.z + player.pos.z <= 0.4)
    {



        if(player.pos.y - (pos.y ) <= 0.35 && ((pos.y ) < player.pos.y))
        {

			player.stopWood = 1;		
			player.standat = pos.y + 0.35f;
			player.maxrelativeheight = pos.y + 0.35f;
			player.jumping = 0;

              // //printf("Player: %f : %f \n",player.pos.y, player.pos.z);
			   ////printf("Box: %f : %f \n",pos.y, pos.z);

		}
		if (((pos.y) > player.pos.y))
		{
			////printf("not falling: %f\n",radius);
			////printf("Player: %f : %f \n",player.pos.x, player.pos.z);
			////printf("Box: %f : %f \n",pos.x, pos.z);
			////printf("Distance: %f  \n", sqrt((player.pos.x - pos.x)*(player.pos.x - pos.x) + (player.pos.z - pos.z)*(player.pos.z - pos.z)) );
		
			if(player.stop == 0)
			{
				player.pos.x = keepdistancex;
				player.pos.z = keepdistancez;
			}
		}
    }
    else
    {
		keepdistancex = player.pos.x;
		keepdistancez = player.pos.z;
		player.stopWood = 0;
		player.standat = 0.1f;
		player.maxrelativeheight = 0.1;
	}

}
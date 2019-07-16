#include "stdafx.h"
#include "Friend.h"
#define jump 1
#define fall 2
#define stand 3
#define move 4


Friend::Friend(vec3 pos, vec3 dir, vec3 force, vec3 scale, float angle)
{

	this->pos = pos;
	this->dir = dir;
	this->angle = angle;
	this->scale = scale;

	this->left = true;
	this->normal = 1;
	this->isAlive = 1;

}


Friend::~Friend()
{
	//delete[] box_stop;
}

	// struct SFace {
	// 	int v[3];
	// 	int n[3];
	// 	int uv[3];
	// };	
    
    struct SFace {
		int v[3];
		int n[3];
	};


bool Friend::Load(std::string filename)
{

	FILE * fp = fopen(filename.c_str(), "r");

	if (fp == NULL) {
		printf("Nie wczytano pliku %s\n", filename.c_str());
		return false;
	}

	vertices.clear();

	std::vector<vec3> loaded_vertices;
	std::vector<vec3> loaded_normals;
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
		if (buf[0] == 'f' && buf[1] == ' ') {
			SFace face;
			sscanf(buf, "f %d//%d %d//%d %d//%d", 
				&face.v[0], &face.n[0], &face.v[1], &face.n[1], &face.v[2], &face.n[2]);
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

			vertices.push_back(loaded_vertices[idxV]);
			normals.push_back(loaded_normals[idxN]);

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

	return true;
}

void Friend::Render(Player &player)
{

    if(isAlive == 1)
    {
	float mat_ambient[] = { 0.1f, 1.0f, 0.3f };
	float mat_diffuse[] = { 0.3, 0.6, 0.3 };
	float mat_specular[] = { 0.5f, 0.5f, 0.5f };

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);

	//glColor3f(0, 1, 1);
    
	glPushMatrix();

		glTranslatef(pos.x, pos.y, pos.z);
        glScalef(scale.x,scale.y,scale.z);
        glRotatef(180.f,0.0f,1.f,0.f);

		glBegin(GL_TRIANGLES);
		for (int i = 0; i < vertices.size(); i++)
		{
			glNormal3f(normals[i].x, normals[i].y, normals[i].z);
			glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
		}
		glEnd();
	glPopMatrix();
    Update(player);
    }
}

void Friend::Update(Player &player)
{


    if(sqrt((player.pos.x - pos.x)*(player.pos.x - pos.x) + (player.pos.z - pos.z)*(player.pos.z - pos.z)) <= 0.2f)
	{
		this->isAlive = 0;
        player.friendscounter++;
	}

}
#include "stdafx.h"
#include "NormalBox.h"


NormalBox::NormalBox(vec3 pos) 
{
    this->pos = pos;

    ambient = vec3(0.0f, 0.0f, 0.0f);
	diffuse = vec3(0.3f, 0.3f, 0.3f);
	specular = vec3(0.1f, 0.1f, 0.1f);
    height = 0.3f;
    width = 0.4;
	weight = 1;
	DisplayListIndex = glGenLists(1);
	rotation = 0;

	keepdistancex = new float[10];
	keepdistancez = new float[10];
	is_destroyed = new bool[10];

	for(int i=0; i<10; i++)
	is_destroyed[i] = 0;

	isAlive = true;
}


NormalBox::~NormalBox(void)
{ 
	delete[] keepdistancex;
	delete[] keepdistancez;
	delete[] is_destroyed;
	
}
    	struct SFace {
		int v[3];
		int n[3];
		int uv[3];
	};

bool NormalBox::Load(std::string filename)
{

	FILE * fp = fopen(filename.c_str(), "r");

	if (fp == NULL) {
		printf("Nie wczytano pliku %s\n", filename.c_str());
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

void NormalBox::Render(Player &player, vec3 boxposition, int intex)
{
    float size = 1.f;

	if( is_destroyed[intex] == 0)
	{
    if (!textureName.empty())
	{
		glEnable(GL_TEXTURE_2D);
		TextureManager::getInstance()->BindTexture(textureName);
	}

	//float mat_ambient[] = { 0.0f, 0.0f, 0.0f };
	//float mat_diffuse[] = { 1.f, 1.f, 1.f };
	//float mat_specular[] = { 0.1f, 0.1f, 0.1f };

	//glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	//glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);

	pos = boxposition;

	glDisable(GL_LIGHTING);
	glPushMatrix();

		glColor3f(1.f,1.f,1.f);		
		glTranslatef(boxposition.x, boxposition.y, boxposition.z);
		//glTranslatef(modelTranslation.x, modelTranslation.y, modelTranslation.z);
		glScalef(0.3f, 0.3f, 0.3f);
		glRotatef(-90.f,0.f,0.f,1.f);	
		//glRotatef(rotation++,0.f,1.f,0.f);
		glCallList(DisplayListIndex);
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

	
    Update(player, intex);
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	}
}
 
void NormalBox::Update(Player &player, int i)
{
	//printf("STOP!: %d\n",stop);
    if(sqrt((player.pos.x - pos.x)*(player.pos.x - pos.x) + (player.pos.z - pos.z)*(player.pos.z - pos.z)) <= 0.391 )
    {

				if(fabs(player.pos.y - pos.y) < 0.4 && player.doublejump == 1)
				{
					player.doublejump = 0;
					player.makejump(3.f);
					player.showtorus = 1;
					player.box_stop[i] = 0;
					player.maxrelativeheight = 0.1;
					is_destroyed[i] = 1; 
					return;	
				}

        if(player.pos.y - (pos.y + 0.391) <= 0.1 && ((pos.y + 0.391) < player.pos.y))
        {
			//Possible issue: I cant jump when I jump from box to ground: solution? 
			if(player.doublejump == 1)
			{ 

				// player.makejump(2.f);
				// player.doublejump = 0;
				// player.box_stop[i] = 0;
				// player.maxrelativeheight = 0.1;
				// is_destroyed[i] = 1; 
				// player.showtorus =1;
				

				// return;
			}

			player.box_stop[i] = 1;		
			player.standat = pos.y + 0.393;
			player.maxrelativeheight = pos.y + 0.393;
			player.jumping = 0;
		}
		if (((pos.y + 0.391) > player.pos.y))
		{
				player.pos.x = keepdistancex[i];
				player.pos.z = keepdistancez[i];
		}
    }
    else
    {
		//bool comp  = player.box_stop[i];
		keepdistancex[i] = player.pos.x;
		keepdistancez[i] = player.pos.z;
		player.box_stop[i] = 0;

		player.maxrelativeheight = 0.1;
	}
}
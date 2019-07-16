#include "stdafx.h"
#include "Platform.h"


Platform::Platform(vec3 pos, int type, float dir) 
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
	typeofplatform = type;
	magic = 0;
	stopmagic = 0;
	prot = 0.f;
	this->direction_rotating = dir;

	timetofall = 100.f;
	startfalling = 0;

	keepdistancex = new float[25];
	keepdistancez = new float[25];

}


Platform::~Platform(void)
{ 
	delete[] keepdistancex;
	delete[] keepdistancez;
}
    	struct SFace {
		int v[3];
		int n[3];
		int uv[3];
	};

bool Platform::Load(std::string filename)
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

	return true;
}

void Platform::Render(Player &player, int index)
{
    if(isAlive == 1)
    {

    if (!textureName.empty())
	{
		glEnable(GL_TEXTURE_2D);
		TextureManager::getInstance()->BindTexture(textureName);
	}

	if(typeofplatform != 6)
	{
	float mat_ambient[] = { 0.0f, 0.0f, 0.0f };
	float mat_diffuse[] = {1.f, 1.f, 1.f };
    float mat_specular[] = { 0.1f, 0.1f, 0.1f };

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	}

	glPushMatrix();

		glTranslatef(pos.x, pos.y, pos.z);
		//glTranslatef(modelTranslation.x, modelTranslation.y, modelTranslation.z);
		if(index > 8 && index <= 16 && player.currentlevel == 4)
		glScalef(.2f, .5f, .2f);
		else
		glScalef(.5f, .5f, .5f);
		

		
        glRotatef(rotation, 0.f, 1.f, 0.f);

			if(typeofplatform == 6)
			{	
				glColor3f(1.0f, 0.0f, 0.0f);
			}

        //glColorf()
		glBegin(GL_TRIANGLES);
		for (int i = 0; i < vertices.size(); i++)
		{
			glNormal3f(normals[i].x, normals[i].y, normals[i].z);
			glTexCoord2f(uvs[i].x, uvs[i].y);
			glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
		}
		glEnd();

	glPopMatrix();

	//glDisable(GL_TEXTURE_2D);


    Update(player, index);
	glDisable(GL_TEXTURE_2D);
    }
}

void Platform::Teleporttolevel3( Player &player )
{
		player.currentlevel=3;
		player.pos.x = 22.6f;
		//player.pos.x = -35.0f;
		
		player.pos.z = 0.3f;
		player.pos.y = 0.8f;
		
		player.makejump(3.f);
}

void Platform::Update(Player &player, int i) 
{
	float rotX = (float)cos((prot + 20.0) * 3.14 / 180);
	float rotZ = (float)sin((prot + 20.0) * 3.14 / 180);

	if(typeofplatform == 3)
	{
		prot+= 0.8;

		

		pos.x += rotX * 0.02; 
		pos.z -= rotZ * 0.02 * direction_rotating;

		//printf("POSITION: %f :: %f \n",pos.x,pos.z);
		
	}


	if(typeofplatform == 6 && player.currentlevel == 1)
	{
		if(sqrt((player.pos.x - pos.x)*(player.pos.x - pos.x) + (player.pos.z - pos.z)*(player.pos.z - pos.z)) <= 0.60 && player.pos.y - pos.y <= 0.3)
		{
			//player.pos = vec3(-22.7f,1.f,7.6f);
			player.currentlevel=4;
			player.pos.x = 2.0f;
			player.pos.z = 0.0f;
			player.pos.y = 0.8f;
			//player.makejump(3.f);
			return;
		}
	}
	
	if(typeofplatform == 6 && player.currentlevel == 3)
	{
		if(sqrt((player.pos.x - pos.x)*(player.pos.x - pos.x) + (player.pos.z - pos.z)*(player.pos.z - pos.z)) <= 0.30 && player.pos.y - pos.y <= 0.3)
		{

			player.currentlevel=1;
			player.pos.x = 2.5f;
			player.pos.z = 1.0f;
			player.pos.y = pos.y + 0.1;
			player.makejump(3.f);
			return;
			//	printf("TELEPORT %d\n",player.currentlevel);
			//Do_teleport_to_cave
			//printf("Tep to cave!\n");
			//
		}
	}

	if(typeofplatform == 18 && player.currentlevel == 4)
	{
		if(sqrt((player.pos.x - pos.x)*(player.pos.x - pos.x) + (player.pos.z - pos.z)*(player.pos.z - pos.z)) <= 0.30 && player.pos.y - pos.y <= 0.3)
		{

			player.currentlevel=1;
			player.pos.x = 2.5f;
			player.pos.z = 1.0f;
			player.pos.y = pos.y + 0.1;
			player.makejump(3.f);
			return;
			//	printf("TELEPORT %d\n",player.currentlevel);
			//Do_teleport_to_cave
			//printf("Tep to cave!\n");
			
		}
	}

		if(typeofplatform == NORMAL_DISSAP)
		{
			if(timetofall <= 0)
			pos.y -= 0.5;

			if(startfalling == 1)
			timetofall --;

			if(timetoresp <= 0)
			{startfalling = 0; timetofall = 100.f; }//printf("OK\n");}

			if(startfalling == 1)
			timetoresp--;

			//printf("TIME: %f\n",timetoresp);
			//printf("pos: %f\n",originalpos);
			//printf("pos: %f\n",pos.y);
			
		}

	float distance;

	if(i < 9)
	distance = 0.58;
	else
	distance = 0.2;
	

    if(sqrt((player.pos.x - pos.x)*(player.pos.x - pos.x) + (player.pos.z - pos.z)*(player.pos.z - pos.z)) <= distance)
    {



			if(typeofplatform == 3 && fabs(player.pos.y -  pos.y) <= 0.28f && player.ismoving == 0)
			{
				
				//vec3 step =  pos - player.pos;
				//float length = sqrt((step.x)*(step.x)+(step.y)*(step.y)+(step.z)*(step.z));
				//step.x = step.x/length;
				//step.y = step.y/length;
				//step.z = step.z/length;
		
				if(player.ismoving == 0)
				{
					player.pos.x += rotX * 0.02;
					player.pos.z -= rotZ * 0.02 * direction_rotating;
				}
				else
				{
				//player.pos.x += step.x * 0.02;
				//player.pos.y += step.y * 0.02;
				//player.pos.z += step.z * 0.02;
				}
			}
		    //printf("Player: %f : %f \n",player.pos.y, pos.y);
			//printf("a\n");
			//printf("a\n");
			if(player.doublejump == 1)
			{ 
				if(typeofplatform == WELL_PLATFORM && fabs(player.pos.y - pos.y) < 0.2)
				{
					//player.makejump(2.f);
					//player.doublejump = 0;
					player.doublejump = 0;
					player.makejump(3.f);
					player.showtorus = 1;
					//player.box_stop[i] = 0;
					player.maxrelativeheight = 0.1;
					//is_destroyed[i] = 1; 
					player.platformstop[i] = 0;
					//player.maxrelativeheight = 0.1;
					//player.makejump(10.f);
					isAlive = 0;
					return;
					
				}
				if(typeofplatform == MAGIC_TELEPORT)
				{
					if(magic == 30)
					{
						//do_teleport();
						magic = 5;
						Teleporttolevel3( player );									
						return;
						stopmagic = 1;					
					}


					if(stopmagic == 0)
					magic++;
				}

			}

			
		if(fabs(player.pos.y - pos.y) <= 0.1f)
		{
			player.pos.x = keepdistancex[i];
			player.pos.z = keepdistancez[i];
		}
		else
		{
			keepdistancex[i] = player.pos.x;
			keepdistancez[i] = player.pos.z;
		}

		if( fabs(player.pos.y -  pos.y) < 0.2f)
        {
			if(player.pos.y < pos.y - 0.1f)
			{
				player.makejump(-3.f);
			}
			else
			{
				player.platformstop[i] = 1;		
				player.standat = pos.y + 0.16f;
				player.maxrelativeheight = pos.y + 0.16f;
				player.jumping = 0;

				if(typeofplatform == NORMAL_DISSAP && startfalling == 0)
				{timetofall == 100.f; startfalling = 1; timetoresp = 300.f; originalpos = pos.y; }
			}


		}
    }
    else
    {
		keepdistancex[i] = player.pos.x;
		keepdistancez[i] = player.pos.z;
		player.platformstop[i] = 0;
		player.maxrelativeheight = 0.1;

		if(typeofplatform == NORMAL_DISSAP)
		if(timetoresp <= 0)
		pos.y = 0.5f;
	}

}
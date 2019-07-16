#include "stdafx.h"
#include "BlackBox.h"


Blackbox::Blackbox()//vec3 pos, vec3 color)
{
	//this->pos = pos;
	//this->color = color;
	this->DisplayListIndex = glGenLists(1);
	this->DisplayListIndex2 = glGenLists(1);
   // this->size = 5;
    //this->radius = sqrt(3) * size / 2;

	trunk_open = new float[1];
	trunk_open[0] = 0;

	trunk_state = new bool[1];
	trunk_state[0] = 0;

	angle1 = new float[1];
	angle2 = new float[1];

	angle1[0] = 0.f;
	angle2[0] = 90.f;

	keepdistancex = new float[1];
	keepdistancez = new float[1];
}

Blackbox::~Blackbox()
{

}
	struct SFace {
		int v[3];
		int n[3];
		int t[3];
	};

bool Blackbox::load()
{	

	// Create the circle in the coordinates origin
	const int sides = 9;  // The amount of segment to create the circle
	const double eradius = 0.2; // The radius of the circle
	const int angle = 180;

	int STEPS = 7;
	float DELTA = 3.1415/STEPS;
	float half_height = 0.5f;
	float radius = .2f;

	//glRotatef(spinch, 0.0, 0.0, 1.0);
	//glTranslatef(150, 95, 0.0);

	//glColor3f(color.x, color.y, color.z);
    //glTranslatef(pos.x, pos.y, pos.z);
    //glScalef(0.3f,0.3f,0.3f);
	
	glNewList(DisplayListIndex, GL_COMPILE);
	glRotatef(-90.f,1.f,0.f,0.f);
	glRotatef(90.f,0.f,0.f,1.f);
	glTranslatef(0.50f,-0.2f,0.f);

	glBegin(GL_POLYGON);
	for(int step=0; step<=STEPS; ++step) {
   		float angle = step*DELTA;
  		 glVertex3f(half_height,radius*cos(angle),radius*sin(angle));
	}
	glEnd();

	// rendering of bottom cap; one corner per iteration
	glBegin(GL_POLYGON);
	for(int step=0; step<=STEPS; ++step) {
   		float angle = step*DELTA;
   		glVertex3f(-half_height,radius*cos(angle),radius*sin(angle));
	}
	glEnd();

	// rendering of "mantle"; one quad per iteration
	glBegin(GL_QUADS);
	for(int step=0; step<STEPS; ++step) { // notice the < only
   		float angle1 = step*DELTA; // at this angle the quad starts
   		float angle2 = (step+1)*DELTA; // look ahead of next angle: at this angle the quad ends
   		float rsine1 = radius*sin(angle1);
   		float rcosine1 = radius*cos(angle1);
   		float rsine2 = radius*sin(angle2);
   		float rcosine2 = radius*cos(angle2);
   		glVertex3f(half_height,rcosine1,rsine1);
   		glVertex3f(half_height,rcosine2,rsine2);
   		glVertex3f(-half_height,rcosine2,rsine2);
   		glVertex3f(-half_height,rcosine1,rsine1);
	}
	
	glEnd();

	// rendering of closing of "mantle"
	glBegin(GL_QUADS);
	glVertex3f(half_height,radius,0);
	glVertex3f(half_height,-radius,radius);
	glVertex3f(-half_height,-radius,radius);
	glVertex3f(-half_height,radius,0);
	glEnd();

	// glNewList(DisplayListIndex, GL_COMPILE);

	// glBegin(GL_POLYGON);
	
	// for(float j = 0.f; j >= -1.0; j-= 0.001)
  	// for (int ar = 0; ar <= angle; ar += angle / sides)
 	// {
	//     double heading = ar * M_PI / 180;
	//     glVertex3f(cos(heading) * eradius + 0.2, sin(heading) * eradius, j);
  	// }
	// glEnd();
	

	glEndList();

	return true;
}

bool Blackbox::load2()
{
	glNewList(DisplayListIndex2, GL_COMPILE);

	glBegin(GL_QUADS);

    // front
	
	glNormal3f(0.0f, -1.0f, 0.0f);
    //glColor3f(1.0f,0.2f,0.2f);
    glTexCoord2f(0, 1);
	glVertex3f(0.0f, 0.001f, 0.0f);
    glTexCoord2f(0, 0);
    glVertex3f(.4f, 0.001f, 0.0f);
    glTexCoord2f(1, 0);
    glVertex3f(.4f, .4f, 0.0f);
    glTexCoord2f(1, 1);
    glVertex3f(0.0f, .4f, 0.0f);
    // back

	glNormal3f(0.0f, 0.0f, -1.0f);
    glTexCoord2f(0, 1);
    glVertex3f(0.0f, 0.001f, -1.0f);
    glTexCoord2f(0, 0);
    glVertex3f(.4f, 0.001f, -1.0f);
    glTexCoord2f(1, 0);
    glVertex3f(.4f, .4f, -1.0f);
    glTexCoord2f(1, 1);
    glVertex3f(0.0f, .4f, -1.0f);
    // right

	glNormal3f(1.0f, 0.0f, 0.0f);
    //glColor3f(1.0f,0.2f,0.2f);	
    glTexCoord2f(0,0);
    glVertex3f(.4f, 0.001f, 0.0f);
    glTexCoord2f(1, 0);
    glVertex3f(.4f, 0.001f, -1.0f);
    glTexCoord2f(1, 1);
    glVertex3f(.4f, .4f, -1.0f);
    glTexCoord2f(0, 1);
    glVertex3f(.4f, .4f, 0.0f);
    // left

	glNormal3f(-1.0f, 0.0f, 0.0f);
    glTexCoord2f(1, 1);
    glVertex3f(0.0f, 0.001f, 0.0f);
    glTexCoord2f(0, 1);
    glVertex3f(0.0f, 0.001f, -1.0f);
    glTexCoord2f(0, 0);
    glVertex3f(0.0f, .4f, -1.0f);
    glTexCoord2f(1, 0);
    glVertex3f(0.0f, .4f, 0.0f);
    // top
	// glColor3f(.0, 1.0, 0.0);
    // glVertex3f(0.0f, .4f, 0.0f);
    // glVertex3f(.4f, .4f, 0.0f);
    // glVertex3f(.4f, .4f, -1.0f);
    // glVertex3f(0.0f, .4f, -1.0f);



    // // bottom
	glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(1, 1);
    glVertex3f(0.0f, 0.001f, 0.0f);
    glTexCoord2f(0, 1);
    glVertex3f(.4f, 0.001f, 0.0f);
    glTexCoord2f(0, 0);
    glVertex3f(.4f, 0.001f, -1.0f);
    glTexCoord2f(1, 0);
    glVertex3f(0.0f, 0.001f, -1.0f);


	glEnd();

	glEndList();

	return true;
}



void Blackbox::Render()
{

}

void Blackbox::Update()
{

}

void Blackbox::Paint(vec3 posa, Player &player, int i)
{

	float mat_ambient[] = { 0.3f, 0.3f, 0.f };
	float mat_diffuse[] = { 255.f / 256.f, 250.f / 256.f, 0.f / 255.f };
    float mat_specular[] = { 0.1f, 0.1f, 0.1f };

	glEnable(GL_TEXTURE_2D);
	TextureManager::getInstance()->BindTexture("Level1_goldenchest");

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glDisable(GL_LIGHTING);
    glDisable(GL_CULL_FACE);
	glPushMatrix();

		//glColor3f(0.7f, .4f,.2f);
		glColor3f( 255.f / 256.f, 250.f / 256.f, 0.f / 255.f);				
		glTranslatef(posa.x, posa.y, posa.z);
		glRotatef(90.f,0.f,-1.f,0.f);
		glRotatef(angle2[i],0.f,-1.f,0.f);
		glCallList(DisplayListIndex2);
		

		angle1[i] = trunk_open[i];
		
		//glColor3f( 255.f / 256.f, 250.f / 256.f, 0.f / 255.f);
		glTranslatef(0.f, 0.4f, 0.f);
		glRotatef(angle1[i],0.f,0.f,1.f);
		
		glPushMatrix();
			//glColor3f(1.0f,0.0f,0.2f);	

			glEnable(GL_TEXTURE_2D);
			TextureManager::getInstance()->BindTexture("Level1_goldenchest");
			glCallList(DisplayListIndex);

		glPopMatrix();

	glPopMatrix();

	UpdateCollision(posa, player, i);

    glDisable(GL_TEXTURE_2D);
    glEnable(GL_CULL_FACE);
	glDisable(GL_LIGHTING);
	
}

void Blackbox::UpdateCollision(vec3 pos, Player &player, int i )
{
		////printf("STOP!: %d\n",stop);
    if(sqrt((player.pos.x - pos.x)*(player.pos.x + .35f -  pos.x) + (player.pos.z - 0.5f - pos.z)*(player.pos.z - pos.z)) <= 0.4 )
    {

			if(!trunk_state[i])
			{
					if(player.keys_counter == 1)
					{
					trunk_state[i] = !trunk_state[i];
					player.keys_counter = -1;
					//BUG -> diamond doesnt dissapear?
					//player.specialdiamonds[0] = 1;
					}
			}
			////printf("not falling: %f\n",radius);
			//printf("Player: %f : %f \n",player.pos.x, player.pos.z);
			//printf("Box: %f : %f \n",pos.x, pos.z);
			//printf("Distance: %f  \n", sqrt((player.pos.x - pos.x)*(player.pos.x - pos.x) + (player.pos.z - pos.z)*(player.pos.z - pos.z)) );
			//printf("Height: %f and jump %d and stop %d\n",player.maxrelativeheight, player.jumping, player.stop);

		if ( fabs(pos.x - player.pos.x) <= 0.5f && fabs(pos.z - player.pos.z) <= 1.f && trunk_state[i] == 0)
		{
			////printf("not falling: %f\n",radius);
			////printf("Player: %f : %f \n",player.pos.x, player.pos.z);
			////printf("Box: %f : %f \n",pos.x, pos.z);
			////printf("Distance: %f  \n", sqrt((player.pos.x - pos.x)*(player.pos.x - pos.x) + (player.pos.z - pos.z)*(player.pos.z - pos.z)) );
		
			//if(stop == 0)
			//{
				player.pos.x = keepdistancex[i];
				player.pos.z = keepdistancez[i];

			if(player.pos.y - (pos.y + 0.291) <= 0.1 && ((pos.y + 0.291) < player.pos.y) )
        	{
			////printf("STOP2!: %d\n",stop);
			player.trunk_stop[i] = 1;		
			player.standat = pos.y + 0.292;
			player.maxrelativeheight = pos.y + 0.292;
			player.jumping = 0;
			////printf("max: %f %d\n",player.maxrelativeheight,player.jumping);	
			////printf("stop!\n");
		}

			//}
		}
		// if(player.pos.x - pos.x <= 0.391 || -player.pos.x + pos.x <= 0.391)
		// {
		// 	//printf("stop x!\n");
		// }
		// if(player.pos.z - pos.z <= 0.391 || -player.pos.z + pos.z <= 0.391)
		// {
		// 	//printf("stop z!\n");
		// }
    }
    else
    {
		keepdistancex[i] = player.pos.x;
		keepdistancez[i] = player.pos.z;
		player.trunk_stop[i] = 0;
		player.maxrelativeheight = 0.1;
	}

	if(trunk_state[i])
	{
		if(trunk_open[i] >= 70.f)
		{
			return;
		}
		

		trunk_open[i] += 1.f;
	}

}
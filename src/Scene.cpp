#include "stdafx.h"
#include "Scene.h"


Scene::Scene(void)
{
	skydome = new Skydome(150, "skydome");
}


Scene::~Scene(void)
{
	for(unsigned int i = 0 ; i < sceneObjects.size() ; i++)
		delete sceneObjects[i];

	sceneObjects.clear();
}

void Scene::AddObject(SceneObject *object)
{
	sceneObjects.push_back(object);
}


void renderBitmapString(float x, float y, char* text) {
	char *c; 
	glRasterPos3f(x, y, 0);
	for (c = text; *c != '\0'; c++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
	}
}

void Scene::AddTriangleCollider(vec3 v1, vec3 v2, vec3 v3, vec3 uv1, vec3 uv2, vec3 uv3, std::string textureName)
{
	Triangle t;

	t.v1 = v1;
	t.v2 = v2;
	t.v3 = v3;

	t.uv1 = uv1;
	t.uv2 = uv2;
	t.uv3 = uv3;

	t.textureName = textureName;

	t.n = vec3::cross(v1 - v3, v2 - v1);
	t.n = t.n.normalized();

	t.A = t.n.x;
	t.B = t.n.y;
	t.C = t.n.z;
	t.D = -(t.A * v1.x + t.B * v1.y + t.C*v1.z);

	collisionTriangles.push_back(t);
}

void Scene::Diamond1Display(Player &player)
{
	if(player.specialdiamonds[0] == 1)
	{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, 100, 0, 100);
	glDisable(GL_LIGHTING);
	glDisable(GL_CULL_FACE);
	glEnable(GL_BLEND);

		glEnable(GL_TEXTURE_2D);
		glClearColor(0.0f,0.0f,0.0f,0.0f);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		TextureManager::getInstance()->BindTexture("sdiamond1");

	//glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE);
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	//glClearColor(0.0f,0.0f,0.0f,0.0f);
	glTexCoord2f(0, 0);
	glVertex2f(40, 95);
	glTexCoord2f(1, 0);	
	glVertex2f(40, 90);

	glTexCoord2f(1, 1);	
	glVertex2f(45, 90);
	glTexCoord2f(0, 1); 	
	glVertex2f(45, 95);

	//glColor3f(0, 0.3, 0);
	glEnd();

	glDisable(GL_TEXTURE_2D);

	glEnable(GL_LIGHTING);
	glEnable(GL_CULL_FACE);
	glDisable(GL_BLEND);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	}

}

void Scene::Diamond2Display(Player &player)
{
	if(player.specialdiamonds[1] == 1)
	{	
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, 100, 0, 100);
	glDisable(GL_LIGHTING);
	glDisable(GL_CULL_FACE);
	glEnable(GL_BLEND);

		glEnable(GL_TEXTURE_2D);
		glClearColor(0.0f,0.0f,0.0f,0.0f);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		TextureManager::getInstance()->BindTexture("sdiamond2");

	//glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE);
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	//glClearColor(0.0f,0.0f,0.0f,0.0f);
	glTexCoord2f(0, 0);
	glVertex2f(45, 95);
	glTexCoord2f(1, 0);	
	glVertex2f(45, 90);

	glTexCoord2f(1, 1);	
	glVertex2f(50, 90);
	glTexCoord2f(0, 1); 	
	glVertex2f(50, 95);

	//glColor3f(0, 0.3, 0);
	glEnd();

	glDisable(GL_TEXTURE_2D);

	glEnable(GL_LIGHTING);
	glEnable(GL_CULL_FACE);
	glDisable(GL_BLEND);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	}

}

void Scene::Diamond3Display(Player &player)
{
	if(player.specialdiamonds[2] == 1)
	{	
		
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, 100, 0, 100);
	glDisable(GL_LIGHTING);
	glDisable(GL_CULL_FACE);
	glEnable(GL_BLEND);

		glEnable(GL_TEXTURE_2D);
		glClearColor(0.0f,0.0f,0.0f,0.0f);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		TextureManager::getInstance()->BindTexture("sdiamond3");

	//glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE);
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	//glClearColor(0.0f,0.0f,0.0f,0.0f);
	glTexCoord2f(0, 0);
	glVertex2f(50, 95);
	glTexCoord2f(1, 0);	
	glVertex2f(50, 90);

	glTexCoord2f(1, 1);	
	glVertex2f(55, 90);
	glTexCoord2f(0, 1); 	
	glVertex2f(55, 95);

	//glColor3f(0, 0.3, 0);
	glEnd();

	glDisable(GL_TEXTURE_2D);

	glEnable(GL_LIGHTING);
	glEnable(GL_CULL_FACE);
	glDisable(GL_BLEND);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	}
}

void Scene::CokolwiekDisplay()
{
		
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, 100, 0, 100);
	glDisable(GL_LIGHTING);
	glDisable(GL_CULL_FACE);
	glEnable(GL_BLEND);

		glEnable(GL_TEXTURE_2D);
		glClearColor(0.0f,0.0f,0.0f,0.0f);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		TextureManager::getInstance()->BindTexture("diamenciki");

	//glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE);
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	//glClearColor(0.0f,0.0f,0.0f,0.0f);
	glTexCoord2f(0, 0);
	glVertex2f(2, 3);
	glTexCoord2f(1, 0);	
	glVertex2f(2, 1);

	glTexCoord2f(1, 1);	
	glVertex2f(3, 3);
	glTexCoord2f(0, 1); 	
	glVertex2f(3, 1);

	//glColor3f(0, 0.3, 0);
	glEnd();

	glDisable(GL_TEXTURE_2D);

	glEnable(GL_LIGHTING);
	glEnable(GL_CULL_FACE);
	glDisable(GL_BLEND);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

}

void Scene::KeyDisplay(Player &player)
{
	if(player.keys_counter == 1)
	{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, 100, 0, 100);
	glDisable(GL_LIGHTING);
	glDisable(GL_CULL_FACE);
	glEnable(GL_BLEND);

		glEnable(GL_TEXTURE_2D);
		glClearColor(0.0f,0.0f,0.0f,0.0f);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		TextureManager::getInstance()->BindTexture("goldkey");


	//glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE);
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	//glClearColor(0.0f,0.0f,0.0f,0.0f);
	glTexCoord2f(0, 0);
	glVertex2f(2, 75);
	glTexCoord2f(1, 0);	
	glVertex2f(2, 70);

	glTexCoord2f(1, 1);	
	glVertex2f(9, 70);
	glTexCoord2f(0, 1); 	
	glVertex2f(9, 75);

	//glColor3f(0, 0.3, 0);
	glEnd();

	glDisable(GL_TEXTURE_2D);

	glEnable(GL_LIGHTING);
	glEnable(GL_CULL_FACE);
	glDisable(GL_BLEND);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	}
}

void Scene::LifeDisplay()
{
	
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, 100, 0, 100);
	glDisable(GL_LIGHTING);
	glDisable(GL_CULL_FACE);
	glEnable(GL_BLEND);

		glEnable(GL_TEXTURE_2D);
		glClearColor(0.0f,0.0f,0.0f,0.0f);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		TextureManager::getInstance()->BindTexture("croclife");


	//glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE);
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	//glClearColor(0.0f,0.0f,0.0f,0.0f);
	glTexCoord2f(0, 0);
	glVertex2f(90, 95);
	glTexCoord2f(1, 0);	
	glVertex2f(90, 85);

	glTexCoord2f(1, 1);	
	glVertex2f(98, 85);
	glTexCoord2f(0, 1); 	
	glVertex2f(98, 95);

	//glColor3f(0, 0.3, 0);
	glEnd();

	glDisable(GL_TEXTURE_2D);

	glEnable(GL_LIGHTING);
	glEnable(GL_CULL_FACE);
	glDisable(GL_BLEND);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void Scene::NumberofDiamondsDisplayd1(Player &player)
{
		
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, 100, 0, 100);
	glDisable(GL_LIGHTING);
	glDisable(GL_CULL_FACE);
	glEnable(GL_BLEND);

		glEnable(GL_TEXTURE_2D);
		glClearColor(0.0f,0.0f,0.0f,0.0f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	int dzielnik = 1;
	
	if(player.diamonds_counter >= 10)
	dzielnik = 10;

	if(player.diamonds_counter/dzielnik == 0)
	TextureManager::getInstance()->BindTexture("diamond_counter_0");
	if(player.diamonds_counter/dzielnik == 1)
	TextureManager::getInstance()->BindTexture("diamond_counter_1");
	if(player.diamonds_counter/dzielnik == 2)
	TextureManager::getInstance()->BindTexture("diamond_counter_2");
	if(player.diamonds_counter/dzielnik == 3)
	TextureManager::getInstance()->BindTexture("diamond_counter_3");
	if(player.diamonds_counter/dzielnik == 4)
	TextureManager::getInstance()->BindTexture("diamond_counter_4");
	if(player.diamonds_counter/dzielnik == 5)
	TextureManager::getInstance()->BindTexture("diamond_counter_5");
	if(player.diamonds_counter/dzielnik == 6)
	TextureManager::getInstance()->BindTexture("diamond_counter_6");
	if(player.diamonds_counter/dzielnik == 7)
	TextureManager::getInstance()->BindTexture("diamond_counter_7");
	if(player.diamonds_counter/dzielnik == 8)
	TextureManager::getInstance()->BindTexture("diamond_counter_8");
	if(player.diamonds_counter/dzielnik == 9)
	TextureManager::getInstance()->BindTexture("diamond_counter_9");
	

	//glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE);

	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	//glClearColor(0.0f,0.0f,0.0f,0.0f);
	//glRotate2f(90.f,1.0f,0.f);
	glTexCoord2f(0, 0);
	glVertex2f(10, 95);
	glTexCoord2f(1, 0);	
	glVertex2f(10, 91);

	glTexCoord2f(1, 1);	
	glVertex2f(14, 91);
	glTexCoord2f(0, 1); 	
	glVertex2f(14, 95);

	//glColor3f(0, 0.3, 0);
	glEnd();

	glDisable(GL_TEXTURE_2D);

	glEnable(GL_LIGHTING);
	glEnable(GL_CULL_FACE);
	glDisable(GL_BLEND);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

}

void Scene::NumberofDiamondsDisplayd2(Player &player)
{
	if(player.diamonds_counter >= 10)
	{	
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, 100, 0, 100);
	glDisable(GL_LIGHTING);
	glDisable(GL_CULL_FACE);
	glEnable(GL_BLEND);

		glEnable(GL_TEXTURE_2D);
		glClearColor(0.0f,0.0f,0.0f,0.0f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	if(player.diamonds_counter%10 == 0)
	TextureManager::getInstance()->BindTexture("diamond_counter_0");
	if(player.diamonds_counter%10 == 1)
	TextureManager::getInstance()->BindTexture("diamond_counter_1");
	if(player.diamonds_counter%10 == 2)
	TextureManager::getInstance()->BindTexture("diamond_counter_2");
	if(player.diamonds_counter%10 == 3)
	TextureManager::getInstance()->BindTexture("diamond_counter_3");
	if(player.diamonds_counter%10 == 4)
	TextureManager::getInstance()->BindTexture("diamond_counter_4");
	if(player.diamonds_counter%10 == 5)
	TextureManager::getInstance()->BindTexture("diamond_counter_5");
	if(player.diamonds_counter%10 == 6)
	TextureManager::getInstance()->BindTexture("diamond_counter_6");
	if(player.diamonds_counter%10 == 7)
	TextureManager::getInstance()->BindTexture("diamond_counter_7");
	if(player.diamonds_counter%10 == 8)
	TextureManager::getInstance()->BindTexture("diamond_counter_8");
	if(player.diamonds_counter%10 == 9)
	TextureManager::getInstance()->BindTexture("diamond_counter_9");

	//glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE);

	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	//glClearColor(0.0f,0.0f,0.0f,0.0f);
	glTexCoord2f(0, 0);
	glVertex2f(14, 95);
	glTexCoord2f(1, 0);	
	glVertex2f(14, 91);

	glTexCoord2f(1, 1);	
	glVertex2f(18, 91);
	glTexCoord2f(0, 1); 	
	glVertex2f(18, 95);

	//glColor3f(0, 0.3, 0);
	glEnd();

	glDisable(GL_TEXTURE_2D);

	glEnable(GL_LIGHTING);
	glEnable(GL_CULL_FACE);
	glDisable(GL_BLEND);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	}

}

void Scene::NumberofLivesDisplayd1(Player &player)
{
		
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, 100, 0, 100);
	glDisable(GL_LIGHTING);
	glDisable(GL_CULL_FACE);
	glEnable(GL_BLEND);

		glEnable(GL_TEXTURE_2D);
		glClearColor(0.0f,0.0f,0.0f,0.0f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	int dzielnik = 1;
	
	if(player.lives_counter >= 10)
	dzielnik = 10;

	if(player.lives_counter/dzielnik == 0)
	TextureManager::getInstance()->BindTexture("diamond_counter_0");
	if(player.lives_counter/dzielnik == 1)
	TextureManager::getInstance()->BindTexture("diamond_counter_1");
	if(player.lives_counter/dzielnik == 2)
	TextureManager::getInstance()->BindTexture("diamond_counter_2");
	if(player.lives_counter/dzielnik == 3)
	TextureManager::getInstance()->BindTexture("diamond_counter_3");
	if(player.lives_counter/dzielnik == 4)
	TextureManager::getInstance()->BindTexture("diamond_counter_4");
	if(player.lives_counter/dzielnik == 5)
	TextureManager::getInstance()->BindTexture("diamond_counter_5");
	if(player.lives_counter/dzielnik == 6)
	TextureManager::getInstance()->BindTexture("diamond_counter_6");
	if(player.lives_counter/dzielnik == 7)
	TextureManager::getInstance()->BindTexture("diamond_counter_7");
	if(player.lives_counter/dzielnik == 8)
	TextureManager::getInstance()->BindTexture("diamond_counter_8");
	if(player.lives_counter/dzielnik == 9)
	TextureManager::getInstance()->BindTexture("diamond_counter_9");
	

	//glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE);

	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	//glClearColor(0.0f,0.0f,0.0f,0.0f);
	//glRotate2f(90.f,1.0f,0.f);
	glTexCoord2f(0, 0);
	glVertex2f(82, 95);
	glTexCoord2f(1, 0);	
	glVertex2f(82, 91);

	glTexCoord2f(1, 1);	
	glVertex2f(86, 91);
	glTexCoord2f(0, 1); 	
	glVertex2f(86, 95);

	//glColor3f(0, 0.3, 0);
	glEnd();

	glDisable(GL_TEXTURE_2D);

	glEnable(GL_LIGHTING);
	glEnable(GL_CULL_FACE);
	glDisable(GL_BLEND);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

}

void Scene::DiamondDisplay()
{
	
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, 100, 0, 100);
	glDisable(GL_LIGHTING);
	glDisable(GL_CULL_FACE);
	glEnable(GL_BLEND);

		glEnable(GL_TEXTURE_2D);
		glClearColor(0.0f,0.0f,0.0f,0.0f);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		TextureManager::getInstance()->BindTexture("diamonds_normal");

	//glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex2f(2, 95);
	glTexCoord2f(1, 0);	
	glVertex2f(2, 85);

	glTexCoord2f(1, 1);	
	glVertex2f(10, 85);
	glTexCoord2f(0, 1); 	
	glVertex2f(10, 95);

	//glColor3f(0, 0.3, 0);
	glEnd();
 
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_LIGHTING);
	glEnable(GL_CULL_FACE);
	glDisable(GL_BLEND);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void Scene::NumberofLivesDisplayd2(Player &player)
{
	if(player.lives_counter >= 10)
	{	
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, 100, 0, 100);
	glDisable(GL_LIGHTING);
	glDisable(GL_CULL_FACE);
	glEnable(GL_BLEND);

		glEnable(GL_TEXTURE_2D);
		glClearColor(0.0f,0.0f,0.0f,0.0f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	if(player.lives_counter%10 == 0)
	TextureManager::getInstance()->BindTexture("diamond_counter_0");
	if(player.lives_counter%10 == 1)
	TextureManager::getInstance()->BindTexture("diamond_counter_1");
	if(player.lives_counter%10 == 2)
	TextureManager::getInstance()->BindTexture("diamond_counter_2");
	if(player.lives_counter%10 == 3)
	TextureManager::getInstance()->BindTexture("diamond_counter_3");
	if(player.lives_counter%10 == 4)
	TextureManager::getInstance()->BindTexture("diamond_counter_4");
	if(player.lives_counter%10 == 5)
	TextureManager::getInstance()->BindTexture("diamond_counter_5");
	if(player.lives_counter%10 == 6)
	TextureManager::getInstance()->BindTexture("diamond_counter_6");
	if(player.lives_counter%10 == 7)
	TextureManager::getInstance()->BindTexture("diamond_counter_7");
	if(player.lives_counter%10 == 8)
	TextureManager::getInstance()->BindTexture("diamond_counter_8");
	if(player.lives_counter%10 == 9)
	TextureManager::getInstance()->BindTexture("diamond_counter_9");

	//glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE);

	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	//glClearColor(0.0f,0.0f,0.0f,0.0f);
	glTexCoord2f(0, 0);
	glVertex2f(86, 95);
	glTexCoord2f(1, 0);	
	glVertex2f(86, 91);

	glTexCoord2f(1, 1);	
	glVertex2f(90, 91);
	glTexCoord2f(0, 1); 	
	glVertex2f(90, 95);

	//glColor3f(0, 0.3, 0);
	glEnd();

	glDisable(GL_TEXTURE_2D);

	glEnable(GL_LIGHTING);
	glEnable(GL_CULL_FACE);
	glDisable(GL_BLEND);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	}

}

void Scene::FriendDisplay()
{
	
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, 100, 0, 100);
	glDisable(GL_LIGHTING);
	glDisable(GL_CULL_FACE);
	glEnable(GL_BLEND);

		glEnable(GL_TEXTURE_2D);
		glClearColor(0.0f,0.0f,0.0f,0.0f);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		TextureManager::getInstance()->BindTexture("friend");


	//glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE);
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	//glClearColor(0.0f,0.0f,0.0f,0.0f);
	glTexCoord2f(0, 0);
	glVertex2f(90, 75);
	glTexCoord2f(1, 0);	
	glVertex2f(90, 65);

	glTexCoord2f(1, 1);	
	glVertex2f(98, 65);
	glTexCoord2f(0, 1); 	
	glVertex2f(98, 75);

	//glColor3f(0, 0.3, 0);
	glEnd();

	glDisable(GL_TEXTURE_2D);

	glEnable(GL_LIGHTING);
	glEnable(GL_CULL_FACE);
	glDisable(GL_BLEND);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void Scene::NumberoffriendsDisplayd1(Player &player)
{
		
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, 100, 0, 100);
	glDisable(GL_LIGHTING);
	glDisable(GL_CULL_FACE);
	glEnable(GL_BLEND);

		glEnable(GL_TEXTURE_2D);
		glClearColor(0.0f,0.0f,0.0f,0.0f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	int dzielnik = 1;
	
	if(player.friendscounter >= 10)
	dzielnik = 10;

	if(player.friendscounter/dzielnik == 0)
	TextureManager::getInstance()->BindTexture("diamond_counter_0");
	if(player.friendscounter/dzielnik == 1)
	TextureManager::getInstance()->BindTexture("diamond_counter_1");
	if(player.friendscounter/dzielnik == 2)
	TextureManager::getInstance()->BindTexture("diamond_counter_2");
	if(player.friendscounter/dzielnik == 3)
	TextureManager::getInstance()->BindTexture("diamond_counter_3");
	if(player.friendscounter/dzielnik == 4)
	TextureManager::getInstance()->BindTexture("diamond_counter_4");
	if(player.friendscounter/dzielnik == 5)
	TextureManager::getInstance()->BindTexture("diamond_counter_5");
	if(player.friendscounter/dzielnik == 6)
	TextureManager::getInstance()->BindTexture("diamond_counter_6");
	if(player.friendscounter/dzielnik == 7)
	TextureManager::getInstance()->BindTexture("diamond_counter_7");
	if(player.friendscounter/dzielnik == 8)
	TextureManager::getInstance()->BindTexture("diamond_counter_8");
	if(player.friendscounter/dzielnik == 9)
	TextureManager::getInstance()->BindTexture("diamond_counter_9");
	

	//glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE);

	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	//glClearColor(0.0f,0.0f,0.0f,0.0f);
	//glRotate2f(90.f,1.0f,0.f);
	glTexCoord2f(0, 0);
	glVertex2f(82, 75);
	glTexCoord2f(1, 0);	
	glVertex2f(82, 71);

	glTexCoord2f(1, 1);	
	glVertex2f(86, 71);
	glTexCoord2f(0, 1); 	
	glVertex2f(86, 75);

	//glColor3f(0, 0.3, 0);
	glEnd();

	glDisable(GL_TEXTURE_2D);

	glEnable(GL_LIGHTING);
	glEnable(GL_CULL_FACE);
	glDisable(GL_BLEND);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

}


void Scene::NumberoffriendsDisplayd2(Player &player)
{
	if(player.friendscounter >= 10)
	{	
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, 100, 0, 100);
	glDisable(GL_LIGHTING);
	glDisable(GL_CULL_FACE);
	glEnable(GL_BLEND);

		glEnable(GL_TEXTURE_2D);
		glClearColor(0.0f,0.0f,0.0f,0.0f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	if(player.friendscounter%10 == 0)
	TextureManager::getInstance()->BindTexture("diamond_counter_0");
	if(player.friendscounter%10 == 1)
	TextureManager::getInstance()->BindTexture("diamond_counter_1");
	if(player.friendscounter%10 == 2)
	TextureManager::getInstance()->BindTexture("diamond_counter_2");
	if(player.friendscounter%10 == 3)
	TextureManager::getInstance()->BindTexture("diamond_counter_3");
	if(player.friendscounter%10 == 4)
	TextureManager::getInstance()->BindTexture("diamond_counter_4");
	if(player.friendscounter%10 == 5)
	TextureManager::getInstance()->BindTexture("diamond_counter_5");
	if(player.friendscounter%10 == 6)
	TextureManager::getInstance()->BindTexture("diamond_counter_6");
	if(player.friendscounter%10 == 7)
	TextureManager::getInstance()->BindTexture("diamond_counter_7");
	if(player.friendscounter%10 == 8)
	TextureManager::getInstance()->BindTexture("diamond_counter_8");
	if(player.friendscounter%10 == 9)
	TextureManager::getInstance()->BindTexture("diamond_counter_9");

	//glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE);

	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	//glClearColor(0.0f,0.0f,0.0f,0.0f);
	glTexCoord2f(0, 0);
	glVertex2f(86, 75);
	glTexCoord2f(1, 0);	
	glVertex2f(86, 71);

	glTexCoord2f(1, 1);	
	glVertex2f(90, 71);
	glTexCoord2f(0, 1); 	
	glVertex2f(90, 75);

	//glColor3f(0, 0.3, 0);
	glEnd();

	glDisable(GL_TEXTURE_2D);

	glEnable(GL_LIGHTING);
	glEnable(GL_CULL_FACE);
	glDisable(GL_BLEND);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	}

}

void Scene::mainMenuCover()
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, 100, 0, 100);
	glDisable(GL_LIGHTING);
	glDisable(GL_CULL_FACE);
	glEnable(GL_BLEND);

	glEnable(GL_TEXTURE_2D);
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	TextureManager::getInstance()->BindTexture("mainMenuCover");

	glBegin(GL_QUADS);
		glColor3f(1, 1, 1);
		glTexCoord2f(0, 0);
		glVertex2f(0, 100);
		glTexCoord2f(1, 0);	
		glVertex2f(0, 0);

		glTexCoord2f(1, 1);	
		glVertex2f(100, 0);
		glTexCoord2f(0, 1); 	
		glVertex2f(100, 100);
	glEnd();

	glDisable(GL_TEXTURE_2D);

	glEnable(GL_LIGHTING);
	glEnable(GL_CULL_FACE);
	glDisable(GL_BLEND);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

}

void Scene::mainMenuNewGame()
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, 100, 0, 100);
	glDisable(GL_LIGHTING);
	glDisable(GL_CULL_FACE);
	glEnable(GL_BLEND);

	glEnable(GL_TEXTURE_2D);
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	TextureManager::getInstance()->BindTexture("mainMenuNewGame");

	glBegin(GL_QUADS);
		glColor3f(1, 1, 1);
		glTexCoord2f(0, 0);
		glVertex2f(25, 50);
		glTexCoord2f(1, 0);	
		glVertex2f(25, 40);

		glTexCoord2f(1, 1);	
		glVertex2f(70, 40);
		glTexCoord2f(0, 1); 	
		glVertex2f(70, 50);
	glEnd();

	glDisable(GL_TEXTURE_2D);

	glEnable(GL_LIGHTING);
	glEnable(GL_CULL_FACE);
	glDisable(GL_BLEND);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

}

void Scene::mainMenuContinue()
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, 100, 0, 100);
	glDisable(GL_LIGHTING);
	glDisable(GL_CULL_FACE);
	glEnable(GL_BLEND);

	glEnable(GL_TEXTURE_2D);
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	TextureManager::getInstance()->BindTexture("mainMenuContinue");

	glBegin(GL_QUADS);
		glColor3f(1, 1, 1);
		glTexCoord2f(0, 0);
		glVertex2f(25, 35);
		glTexCoord2f(1, 0);	
		glVertex2f(25, 25);

		glTexCoord2f(1, 1);	
		glVertex2f(70, 25);
		glTexCoord2f(0, 1); 	
		glVertex2f(70, 35);
	glEnd();

	glDisable(GL_TEXTURE_2D);

	glEnable(GL_LIGHTING);
	glEnable(GL_CULL_FACE);
	glDisable(GL_BLEND);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

}
void Scene::mainMenuExit()
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, 100, 0, 100);
	glDisable(GL_LIGHTING);
	glDisable(GL_CULL_FACE);
	glEnable(GL_BLEND);

	glEnable(GL_TEXTURE_2D);
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	TextureManager::getInstance()->BindTexture("mainMenuExit");

	glBegin(GL_QUADS);
		glColor3f(1, 1, 1);
		glTexCoord2f(0, 0);
		glVertex2f(25, 20);
		glTexCoord2f(1, 0);	
		glVertex2f(25, 10);

		glTexCoord2f(1, 1);	
		glVertex2f(70, 10);
		glTexCoord2f(0, 1); 	
		glVertex2f(70, 20);
	glEnd();

	glDisable(GL_TEXTURE_2D);

	glEnable(GL_LIGHTING);
	glEnable(GL_CULL_FACE);
	glDisable(GL_BLEND);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

}

void Scene::mainMenuConGratulations()
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, 100, 0, 100);
	glDisable(GL_LIGHTING);
	glDisable(GL_CULL_FACE);
	glEnable(GL_BLEND);

	glEnable(GL_TEXTURE_2D);
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	TextureManager::getInstance()->BindTexture("mainMenuConGratulations");

	glBegin(GL_QUADS);
		glColor3f(1, 1, 1);
		glTexCoord2f(0, 0);
		glVertex2f(25, 90);
		glTexCoord2f(1, 0);	
		glVertex2f(25, 80);

		glTexCoord2f(1, 1);	
		glVertex2f(70, 80);
		glTexCoord2f(0, 1); 	
		glVertex2f(70, 90);
	glEnd();

	glDisable(GL_TEXTURE_2D);

	glEnable(GL_LIGHTING);
	glEnable(GL_CULL_FACE);
	glDisable(GL_BLEND);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

}

void Scene::ResultDiamond()
{
	
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, 100, 0, 100);
	glDisable(GL_LIGHTING);
	glDisable(GL_CULL_FACE);
	glEnable(GL_BLEND);

		glEnable(GL_TEXTURE_2D);
		glClearColor(0.0f,0.0f,0.0f,0.0f);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		TextureManager::getInstance()->BindTexture("diamonds_normal");

	//glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex2f(25, 65);
	glTexCoord2f(1, 0);	
	glVertex2f(25, 55);

	glTexCoord2f(1, 1);	
	glVertex2f(33, 55);
	glTexCoord2f(0, 1); 	
	glVertex2f(33, 65);

	//glColor3f(0, 0.3, 0);
	glEnd();
 
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_LIGHTING);
	glEnable(GL_CULL_FACE);
	glDisable(GL_BLEND);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void Scene::ResultFriend()
{
	
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, 100, 0, 100);
	glDisable(GL_LIGHTING);
	glDisable(GL_CULL_FACE);
	glEnable(GL_BLEND);

		glEnable(GL_TEXTURE_2D);
		glClearColor(0.0f,0.0f,0.0f,0.0f);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		TextureManager::getInstance()->BindTexture("friend");

	//glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex2f(45, 65);
	glTexCoord2f(1, 0);	
	glVertex2f(45, 55);

	glTexCoord2f(1, 1);	
	glVertex2f(53, 55);
	glTexCoord2f(0, 1); 	
	glVertex2f(53, 65);

	//glColor3f(0, 0.3, 0);
	glEnd();
 
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_LIGHTING);
	glEnable(GL_CULL_FACE);
	glDisable(GL_BLEND);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void Scene::ResultLife()
{
	
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, 100, 0, 100);
	glDisable(GL_LIGHTING);
	glDisable(GL_CULL_FACE);
	glEnable(GL_BLEND);

		glEnable(GL_TEXTURE_2D);
		glClearColor(0.0f,0.0f,0.0f,0.0f);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		TextureManager::getInstance()->BindTexture("croclife");

	//glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex2f(65, 65);
	glTexCoord2f(1, 0);	
	glVertex2f(65, 55);

	glTexCoord2f(1, 1);	
	glVertex2f(73, 55);
	glTexCoord2f(0, 1); 	
	glVertex2f(73, 65);

	//glColor3f(0, 0.3, 0);
	glEnd();
 
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_LIGHTING);
	glEnable(GL_CULL_FACE);
	glDisable(GL_BLEND);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void Scene::ResultDisplayd1(int number1, int offsety)
{
		
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, 100, 0, 100);
	glDisable(GL_LIGHTING);
	glDisable(GL_CULL_FACE);
	glEnable(GL_BLEND);

		glEnable(GL_TEXTURE_2D);
		glClearColor(0.0f,0.0f,0.0f,0.0f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	int dzielnik = 1;
	
	if(number1 >= 10)
	dzielnik = 10;

	if(number1/dzielnik == 0)
	TextureManager::getInstance()->BindTexture("diamond_counter_0");
	if(number1/dzielnik == 1)
	TextureManager::getInstance()->BindTexture("diamond_counter_1");
	if(number1/dzielnik == 2)
	TextureManager::getInstance()->BindTexture("diamond_counter_2");
	if(number1/dzielnik == 3)
	TextureManager::getInstance()->BindTexture("diamond_counter_3");
	if(number1/dzielnik == 4)
	TextureManager::getInstance()->BindTexture("diamond_counter_4");
	if(number1/dzielnik == 5)
	TextureManager::getInstance()->BindTexture("diamond_counter_5");
	if(number1/dzielnik == 6)
	TextureManager::getInstance()->BindTexture("diamond_counter_6");
	if(number1/dzielnik == 7)
	TextureManager::getInstance()->BindTexture("diamond_counter_7");
	if(number1/dzielnik == 8)
	TextureManager::getInstance()->BindTexture("diamond_counter_8");
	if(number1/dzielnik == 9)
	TextureManager::getInstance()->BindTexture("diamond_counter_9");
	

	//glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE);

	// 	glTexCoord2f(0, 0);
	// glVertex2f(25, 65);
	// glTexCoord2f(1, 0);	
	// glVertex2f(25, 55);

	// glTexCoord2f(1, 1);	
	// glVertex2f(33, 55);
	// glTexCoord2f(0, 1); 	
	// glVertex2f(33, 65);

	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	//glClearColor(0.0f,0.0f,0.0f,0.0f);
	//glRotate2f(90.f,1.0f,0.f);
	glTexCoord2f(0, 0);
	glVertex2f(21 + offsety, 45);
	glTexCoord2f(1, 0);	
	glVertex2f(21 + offsety, 35);

	glTexCoord2f(1, 1);	
	glVertex2f(29 + offsety, 35);
	glTexCoord2f(0, 1); 	
	glVertex2f(29 + offsety, 45);

	//glColor3f(0, 0.3, 0);
	glEnd();

	glDisable(GL_TEXTURE_2D);

	glEnable(GL_LIGHTING);
	glEnable(GL_CULL_FACE);
	glDisable(GL_BLEND);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

}

void Scene::ResultDisplayd2(int number1, int offsety)
{
	if(number1 >= 10)
	{	
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, 100, 0, 100);
	glDisable(GL_LIGHTING);
	glDisable(GL_CULL_FACE);
	glEnable(GL_BLEND);

		glEnable(GL_TEXTURE_2D);
		glClearColor(0.0f,0.0f,0.0f,0.0f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	if(number1%10 == 0)
	TextureManager::getInstance()->BindTexture("diamond_counter_0");
	if(number1%10 == 1)
	TextureManager::getInstance()->BindTexture("diamond_counter_1");
	if(number1%10 == 2)
	TextureManager::getInstance()->BindTexture("diamond_counter_2");
	if(number1%10 == 3)
	TextureManager::getInstance()->BindTexture("diamond_counter_3");
	if(number1%10 == 4)
	TextureManager::getInstance()->BindTexture("diamond_counter_4");
	if(number1%10 == 5)
	TextureManager::getInstance()->BindTexture("diamond_counter_5");
	if(number1%10 == 6)
	TextureManager::getInstance()->BindTexture("diamond_counter_6");
	if(number1%10 == 7)
	TextureManager::getInstance()->BindTexture("diamond_counter_7");
	if(number1%10 == 8)
	TextureManager::getInstance()->BindTexture("diamond_counter_8");
	if(number1%10 == 9)
	TextureManager::getInstance()->BindTexture("diamond_counter_9");

	//glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE);

	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	//glClearColor(0.0f,0.0f,0.0f,0.0f);
	glTexCoord2f(0, 0);
	glVertex2f(29 + offsety, 45);
	glTexCoord2f(1, 0);	
	glVertex2f(29 + offsety, 35);

	glTexCoord2f(1, 1);	
	glVertex2f(37 + offsety, 35);
	glTexCoord2f(0, 1); 	
	glVertex2f(37 + offsety, 45);

	//glColor3f(0, 0.3, 0);
	glEnd();

	glDisable(GL_TEXTURE_2D);

	glEnable(GL_LIGHTING);
	glEnable(GL_CULL_FACE);
	glDisable(GL_BLEND);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	}

}

void Scene::Render()
{
	for(unsigned int i = 0 ; i < sceneObjects.size() ; i++)
		sceneObjects[i]->Render();

	for (unsigned int i = 0 ; i < collisionTriangles.size() ; i++)
	{
		if (!collisionTriangles[i].textureName.empty())
		{
			glEnable(GL_TEXTURE_2D);
			TextureManager::getInstance()->BindTexture(collisionTriangles[i].textureName);
		}

		float ambient[] = { 0.5f, 0.5f, 0.5f };
		float diffuse[] = { 1.0f, 1.0f, 1.0f };
		float specular[] = { 0.0f, 0.0f, 0.0f };

		glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
		glBegin(GL_TRIANGLES);
		glNormal3f(collisionTriangles[i].n.x, collisionTriangles[i].n.y, collisionTriangles[i].n.z);
		glTexCoord2f(collisionTriangles[i].uv1.x, collisionTriangles[i].uv1.y);
		glVertex3f(collisionTriangles[i].v1.x, collisionTriangles[i].v1.y, collisionTriangles[i].v1.z);
		glTexCoord2f(collisionTriangles[i].uv2.x, collisionTriangles[i].uv2.y);
		glVertex3f(collisionTriangles[i].v2.x, collisionTriangles[i].v2.y, collisionTriangles[i].v2.z);
		glTexCoord2f(collisionTriangles[i].uv3.x, collisionTriangles[i].uv3.y);
		glVertex3f(collisionTriangles[i].v3.x, collisionTriangles[i].v3.y, collisionTriangles[i].v3.z);
		glEnd();

		glDisable(GL_TEXTURE_2D);
	}

	skydome->Render();
}

void Scene::Update()
{

	//Petla sprawdza kolizje obiektow z ustawionymi granicami sceny
	for (int i = 0; i < sceneObjects.size(); i++)
	{
		SceneObject* obj = sceneObjects[i];

		//if(obj->radius = 5.f)
		//printf("raduus\n");

		obj->prevPos = obj->pos;

		obj->pos.y -= 0.01f;

		if ((obj->pos.x + obj->radius) > boundaryMax.x)
			obj->pos.x = boundaryMax.x - obj->radius;

		if ((obj->pos.y + obj->radius) > boundaryMax.y)
			obj->pos.y = boundaryMax.y - obj->radius;

		if ((obj->pos.z + obj->radius) > boundaryMax.z)
			obj->pos.z = boundaryMax.z - obj->radius;

		if ((obj->pos.x - obj->radius) < boundaryMin.x)
			obj->pos.x = boundaryMin.x + obj->radius;

		if ((obj->pos.y - obj->radius) < boundaryMin.y)
			obj->pos.y = boundaryMin.y + obj->radius;

		if ((obj->pos.z - obj->radius) < boundaryMin.z)
			obj->pos.z = boundaryMin.z + obj->radius;
	}
	////////////////////////////////////////////////////


	//Petla sprawdza kolizje miedzy obiektami
	for (int i = 0; i < sceneObjects.size(); i++)
	{
		for (int j = i + 1; j < sceneObjects.size(); j++)
		{
			SceneObject* obj1 = sceneObjects[i];
			SceneObject* obj2 = sceneObjects[j];

			float r = vec3::distance(obj1->pos, obj2->pos);

			float d = (obj1->radius + obj2->radius) - r;

			if (d > 0)
			{
				vec3 v1 = obj1->pos - obj2->pos;
				vec3 v2 = obj2->pos - obj1->pos;

				v1 = v1.normalized();
				v2 = v2.normalized();

				obj1->pos = obj1->pos + v1 * (d / 2) * 1.2f;
				obj2->pos = obj2->pos + v2 * (d / 2) * 1.2f;

				float total_force = obj1->force.length() + obj2->force.length();

				obj1->force = v1 * total_force * 0.5f;
				obj2->force = v2 * total_force * 0.5;
			}
		}
	}
	////////////////////////////////////////////////////

	for(unsigned int i = 0 ; i < sceneObjects.size() ; i++)
		sceneObjects[i]->Update();

	// for (unsigned int i = 0; i < sceneObjects.size(); i++)
	// {
	// 	SceneObject* obj = sceneObjects[i];

	// 	for (int j = 0; j < collisionTriangles.size(); j++)
	// 	{
	// 		Triangle tr = collisionTriangles[j];

	// 		float currDist = tr.A * obj->pos.x + tr.B * obj->pos.y + tr.C * obj->pos.z + tr.D;
	// 		float prevDist = tr.A * obj->prevPos.x + tr.B * obj->prevPos.y + tr.C * obj->prevPos.z + tr.D;

	// 		if ((currDist * prevDist < 0) || abs(currDist) < obj->radius)
	// 		{
	// 			// Rzut pozycji obiektu na plaszczyzne
	// 			vec3 p = obj->pos - tr.n * currDist;

	// 			// Przesuniecie punktu do srodka trojkata o dlugosc promienia kolidera
	// 			vec3 r = (tr.v1 + tr.v2 + tr.v3) * (1.0f / 3.0f) - p;
	// 			r = r.normalized();
	// 			p = p + r * obj->radius;

	// 			// Obliczenie v, w, u - wspolrzednych barycentrycznych
	// 			vec3 v0 = tr.v2 - tr.v1, v1 = tr.v3 - tr.v1, v2 = p - tr.v1;
	// 			float d00 = vec3::dot(v0, v0);
	// 			float d01 = vec3::dot(v0, v1);
	// 			float d11 = vec3::dot(v1, v1);
	// 			float d20 = vec3::dot(v2, v0);
	// 			float d21 = vec3::dot(v2, v1);
	// 			float denom = d00 * d11 - d01 * d01;

	// 			float v = (d11 * d20 - d01 * d21) / denom;
	// 			float w = (d00 * d21 - d01 * d20) / denom;
	// 			float u = 1.0f - v - w;

	// 			// Sprawdzenie czy punkt jest w srodku trojkata
	// 			if (v >= 0 && w >= 0 && (v + w) <= 1)
	// 			{
	// 				float d = obj->radius - currDist;

	// 				obj->pos = obj->pos + tr.n * d;

	// 				obj->force = obj->force - tr.n * vec3::dot(tr.n, obj->force) * 2;
	// 			}
	// 		}
	// 	}
	// }

	// for (std::vector<SceneObject*>::iterator it = sceneObjects.begin(); it != sceneObjects.end();)
	// {
	// 	if ((*it)->isAlive)
	// 	{
	// 		it++;
	// 	}
	// 	else
	// 	{
	// 		it = sceneObjects.erase(it);
	// 	}
	// }

	skydome->Update();
}
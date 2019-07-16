#include "stdafx.h"
#include "Skydome.h"


Skydome::Skydome(float radius, std::string textureName)
{
	this->radius = radius;
	this->textureName = textureName;
	frameCounter = 0;
}


Skydome::~Skydome(void)
{
}

void Skydome::Update(void)
{
	frameCounter++;
}

void Skydome::Render(void)
{
	if (!textureName.empty())
	{
		glEnable(GL_TEXTURE_2D);
		TextureManager::getInstance()->BindTexture(textureName);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	}

	glPushMatrix();
	
	glTranslatef(position.x, position.y, position.z);
	glRotatef(0.1f * frameCounter, 0.0f, 1.0f, 0.0f);

	int Np = 36;

	glBegin(GL_QUAD_STRIP);
	for (int j = -1; j < Np / 2; ++j) {
		for (int i = 0; i <= Np; ++i) {

			float t1 = PI * j / Np - PI / 2;
			float t2 = PI * (j + 1) / Np - PI / 2;
			float p = PI * 2.0f * i / Np;

			float tx1 = sin(t1) * cos(p);
			float tx2 = sin(t2) * cos(p);
			float tz1 = sin(t1) * sin(p);
			float tz2 = sin(t2) * sin(p);
			float ty1 = cos(t1);
			float ty2 = cos(t2);

			float tr1 = -sin(t1);
			float tr2 = -sin(t2);

			float x1 = radius * tx1;
			float x2 = radius * tx2;
			float z1 = radius * tz1;
			float z2 = radius * tz2;
			float y1 = radius * ty1;
			float y2 = radius * ty2;

			glTexCoord2f(.5f + .5f * tr2 * tx2, .5f + .5f * tr2 * tz2);
			glNormal3f(x2, y2, z2);
			glVertex3f(x2, y2, z2);

			glTexCoord2f(.5f + .5f * tr1 * tx1, .5f + .5f * tr1 * tz1);
			glNormal3f(x1, y1, z1);
			glVertex3f(x1, y1, z1);

		}
	}
	glEnd();

	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}

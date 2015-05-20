#include "Effects.h"


Effects::Effects()
{
}


Effects::~Effects()
{
}

void Effects::smoke(GLfloat x, GLfloat z)
{
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glColor4f(1.0, 1.0, 1.0, smokeAlpha);
	glTranslatef(x, 2.8, z);
	glRotatef(90, 0.0, 1.0, 0.0);
	glutSolidSphere(0.5, 30, 30);
	glPopMatrix();
	glEnable(GL_LIGHTING);
	/*if (smokeAlpha >= 0)
		smokeAlpha -= 0.01;*/
}
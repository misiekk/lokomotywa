#include "Effects.h"

const GLfloat SmokeAmbient[4] = { 0.25, 0.25, 0.25, 1.0 };
const GLfloat SmokeDiffuse[4] = { 0.400000, 0.400000, 0.400000, 1.0 };
const GLfloat SmokeSpecular[4] = { 0.77, 0.77, 0.77, 1.0 };
const GLfloat SmokeShininess = 0;


const GLfloat * ambientS = SmokeAmbient;
const GLfloat * diffuseS = SmokeDiffuse;
const GLfloat * specularS = SmokeSpecular;
GLfloat shininessS = SmokeShininess;


Effects::Effects()
{
}


Effects::~Effects()
{
}

void Effects::smoke(GLfloat x, GLfloat z)
{
	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambientS);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuseS);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specularS);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininessS);
	//glDisable(GL_LIGHTING);
	glColor4f(1.0, 1.0, 1.0, smokeAlpha);
	glTranslatef(x, this->y, z);
	glutSolidSphere(R, 30, 30);
	glPopMatrix();
	//glEnable(GL_LIGHTING);
	if (smokeAlpha >= 0 && smokeDown)
	{
		smokeAlpha -= 0.01;
		y += 0.01;
		R += 0.01;
		if (smokeAlpha < 0) smokeUp = true;
	}
	if (smokeUp)
	{
		smokeDown = false;
		smokeAlpha += 0.01;
		if (smokeAlpha > 1.0)
		{
			smokeDown = true;
			smokeUp = false;
		}
	}
	
}
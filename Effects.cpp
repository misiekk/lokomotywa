#include "Effects.h"

const GLfloat SmokeAmbient[4] = { 0.25, 0.25, 0.25, 0.5 };
const GLfloat SmokeDiffuse[4] = { 0.40, 0.40, 0.40, 1.0 };
const GLfloat SmokeSpecular[4] = { 0.0, 0.0, 0.0, 0.0 };
const GLfloat SmokeShininess = 0;


const GLfloat * ambientS = SmokeAmbient;
const GLfloat * diffuseS = SmokeDiffuse;
const GLfloat * specularS = SmokeSpecular;
GLfloat shininessS = SmokeShininess;

enum {
	X, Y, Z, W
};

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
		R += 0.005;
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



void Effects::generateShadowMatrix(GLfloat shadow[4][4], GLfloat plane[4], GLfloat light[4])
{
	GLfloat is;

	// iloczyn skalarny
	is = plane[X] * light[X] +
		plane[Y] * light[Y] +
		plane[Z] * light[Z] +
		plane[W] * light[W];

	shadow[0][0] = is - light[X] * plane[X];
	shadow[1][0] = 0.f - light[X] * plane[Y];
	shadow[2][0] = 0.f - light[X] * plane[Z];
	shadow[3][0] = 0.f - light[X] * plane[W];

	shadow[X][1] = 0.f - light[Y] * plane[X];
	shadow[1][1] = is - light[Y] * plane[Y];
	shadow[2][1] = 0.f - light[Y] * plane[Z];
	shadow[3][1] = 0.f - light[Y] * plane[W];

	shadow[X][2] = 0.f - light[Z] * plane[X];
	shadow[1][2] = 0.f - light[Z] * plane[Y];
	shadow[2][2] = is - light[Z] * plane[Z];
	shadow[3][2] = 0.f - light[Z] * plane[W];

	shadow[X][3] = 0.f - light[W] * plane[X];
	shadow[1][3] = 0.f - light[W] * plane[Y];
	shadow[2][3] = 0.f - light[W] * plane[Z];
	shadow[3][3] = is - light[W] * plane[W];
}
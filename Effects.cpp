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
	glTranslatef(x, this->y, z);

	glutSolidSphere(R, 30, 30);
	glPopMatrix();
	glEnable(GL_LIGHTING);
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
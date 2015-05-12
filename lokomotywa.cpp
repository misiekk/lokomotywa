#include "lokomotywa.h"

Lokomotywa::Lokomotywa()
{
	std::cout << "Lokomotywa loading...";
}

void Lokomotywa::draw()
{
	GLUquadricObj *obj = gluNewQuadric();
	GLfloat torus_diffuse[] = { 0.0, 1.0, 0.0, 1.0 };
	glPushMatrix();
	glRotatef(this->alfa, 0.0, 1.0, 0.0);
	glTranslatef(x, 1.0, z);		// wstepne przesuniecie modelu

	// komin-------------
		glPushMatrix();
		//glRotatef((GLfloat)(frameNum), 0.0, 1.0, 0.0);
		//glTranslatef(-0.80, 0.35, 0.0); //0.35
		//glRotatef(100.0, 1.0, 0.0, 0.0);
		//glRotatef((GLfloat)(frameNum), 1.0, 0.0, 0.0);
		//glScalef((GLfloat)frameNum / 180, 1.0, (GLfloat)frameNum / 180);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, torus_diffuse);
		//glColor3f(1.0, 0.1, 0.1);
		//glTranslatef(2.0, 2.0, 1.0);
		glRotatef(90, 1.0, 0.0, 0.0);
		glTranslatef(0.0, 0.0, -1.0);
		gluCylinder(obj, 0.2, 0.2, 0.8, 30, 30);

		glPopMatrix();
		// end --- komin-------------

	// prostopadloscian--------------
		glPushMatrix();
		glMaterialfv(GL_FRONT, GL_DIFFUSE, torus_diffuse);
		
		glTranslatef(0.0, -0.5, 0.0);
		glScalef(2.0, 1.0, 1.0);
		glutSolidCube(1.0);
		glPopMatrix();

	// kolo
		glPushMatrix();
		glMaterialfv(GL_FRONT, GL_DIFFUSE, torus_diffuse);
		glTranslatef(1.0, -1.0, 0.45);
		//gluDisk(obj, 0.2, 0.3, 20, 20);
		gluCylinder(obj, 0.1, 0.1, 0.05, 20, 20);
		glPopMatrix();

	glPopMatrix();

}


void Lokomotywa::move()
{
	// jedziemy po okregu
	// x = rcosFI
	// z = rsinFI
	x = R*sin(alfa);
	z = R*cos(alfa);
	alfa += 0.1;
	if (alfa >= 360.0) alfa = 0.0;

}


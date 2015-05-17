#include "lokomotywa.h"
#define M_PI 3.1415

Lokomotywa::Lokomotywa()
{
	std::cout << "Lokomotywa loading...";
}

void Lokomotywa::draw()
{
	//std::cout << "draw \n";
	GLUquadricObj *obj = gluNewQuadric();
	GLfloat torus_diffuse[] = { 0.0, 1.0, 0.0, 1.0 };
	glPushMatrix();
	
	glTranslatef(x, 1.0, z);		// przesuniecie modelu
	glRotatef(this->alfa, 0.0, 1.0, 0.0);
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

	// kola
		glPushMatrix();
		
		drawWheel(1.0, -1.0, 0.45, 0.4, 0.5);
		glPopMatrix();
	glPopMatrix();

}

void Lokomotywa::drawWheel(GLfloat x, GLfloat y, GLfloat z, GLdouble innerradius, GLdouble outerradius)
{
	GLUquadricObj *obj = gluNewQuadric();
	glPushMatrix();
	
	glTranslatef(x, y, z);
	glRotatef(-this->alfa * 3, 0.0, 0.0, 1.0);
	glDisable(GL_LIGHTING);
	for (int i = 0; i < 4; i++)
	{
		GLfloat x = getNextWheelXCord(i, innerradius);
		GLfloat y = getNextWheelYCord(i, innerradius);
		glBegin(GL_LINES);
		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(-x, -y, 0.05);
		glVertex3f(x, y, 0.05);
		glEnd();
	}
	glColor3f(0.0, 0.0, 0.0);
	gluCylinder(obj, innerradius+0.01, innerradius+0.01, 0.1, 20, 20);
	//gluDisk(obj, innerradius, outerradius, 20, 20);
	glEnable(GL_LIGHTING);
	glPopMatrix();
}


void Lokomotywa::move()
{
	//std::cout << "move \n";
	// jedziemy po okregu
	// x = rcosFI
	// z = rsinFI
	x = (GLfloat)R*sin(M_PI*alfa/180.0);
	z = (GLfloat)R*cos(M_PI*alfa / 180.0);
	alfa += 1.0;
	if (alfa >= 360.0) alfa = 0.0;

	// w��czenie efektu mg�y
	glEnable(GL_FOG);

	// wskaz�wki jako�ci generacji mg�y
	glHint(GL_FOG_HINT, fog_hint);

	// kolor mg�y
	GLfloat fog_color[4] = { 0.9, 0.9, 0.9, 1.0 };
	glFogfv(GL_FOG_COLOR, fog_color);

	// g�sto�� mg�y
	glFogf(GL_FOG_DENSITY, fog_density);

	// rodzaj mg�y
	glFogf(GL_FOG_MODE, fog_mode);

	// pocz�tek i koniec oddzia�ywania mg�y liniowej
	glFogf(GL_FOG_START, fog_start);
	glFogf(GL_FOG_END, fog_end);
	
	/*glBegin(GL_TRIANGLES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(5.0, 5.0, 0.0);
	glVertex3f(8.0, 8.0, 8.0);
	glEnd();*/
	glDisable(GL_FOG);
	//glutSolidSphere(3.0, 30, 30);
}

GLfloat Lokomotywa::getNextWheelXCord(int i, GLfloat radius)
{
	GLfloat cordX;
	GLfloat dFI = 45;
	cordX = (GLfloat)radius*cos(M_PI*i*dFI / 180.0);
	return cordX;
}

GLfloat Lokomotywa::getNextWheelYCord(int i, GLfloat radius)
{
	GLfloat cordY;
	GLfloat dFI = 45;
	cordY = (GLfloat)radius*sin(M_PI*i*dFI / 180.0);
	return cordY;
}
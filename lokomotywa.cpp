#include "lokomotywa.h"
#define M_PI 3.1415

const GLfloat ChromeAmbient[4] = { 0.25, 0.25, 0.25, 1.0 };
const GLfloat ChromeDiffuse[4] = { 0.40, 0.40, 0.40, 1.0 };
const GLfloat ChromeSpecular[4] = {	0.77, 0.77, 0.77, 1.0 };
const GLfloat ChromeShininess = 76.0;


const GLfloat * ambient = ChromeAmbient;
const GLfloat * diffuse = ChromeDiffuse;
const GLfloat * specular = ChromeSpecular;
GLfloat shininess = ChromeShininess;

GLfloat plane[4] = { 0, 1, 0, -0.01},
	light[] = { 2.0, 5.0, 10.0, 0.5 },
	shadow_matrix[4][4];

Lokomotywa::Lokomotywa()
{
	std::cout << "Lokomotywa loading...";
	effect = new Effects();
}

void Lokomotywa::draw()
{
	//std::cout << "draw \n";
	GLUquadricObj *obj = gluNewQuadric();

	effect->generateShadowMatrix(shadow_matrix, plane, light);

	glDisable(GL_LIGHTING);
	glColor3f(0.2f, 0.2f, 0.2f); // kolor cienia
	
	glPushMatrix();
		glMultMatrixf((GLfloat *)shadow_matrix);
		generateLoco(1);
	glPopMatrix();

	glEnable(GL_LIGHTING);

	glPushMatrix();
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
		generateLoco(0);
	glPopMatrix();
	
}
void Lokomotywa::generateLoco(bool shadow)
{
	//std::cout << "generating loco...\n";
	GLUquadricObj *obj = gluNewQuadric();

	//wymiary czesci skladowych
	//prostopadloscian podstawy lokomotywy
	GLfloat xProst = 2.0,
		yProst = 0.5,
		zProst = 1.0;

	// stozek
	GLfloat stozekR = 0.5,
		stozekH = 0.6;

	// walec poziomy
	GLfloat walecR1 = 0.5,
		walecR2 = 0.5,
		walecH = 1.8;

	// komin
	GLfloat kominR1 = 0.2,
		kominR2 = 0.2,
		kominH = 0.8;
	if (shadow)
	{
		glDisable(GL_LIGHTING);
		glColor3f(0.2f, 0.2f, 0.2f); // kolor cienia
	}

	glPushMatrix();

	glTranslatef(x, 1.0, z);		// przesuniecie modelu
	glRotatef(this->alfa, 0.0, 1.0, 0.0);

	// komin-------------
	glPushMatrix();
	glRotatef(90, 1.0, 0.0, 0.0);
	glTranslatef(0.0, 0.0, -1.5);
	gluCylinder(obj, kominR1, kominR2, kominH, 30, 30);
	glPopMatrix();
	

	// walec
	glPushMatrix();
	glTranslatef(-1.0, 0.2, 0.0);
	glRotatef(90, 0.0, 1.0, 0.0);
	gluCylinder(obj, walecR1, walecR2, walecH, 30, 30);
	glPopMatrix();

	// stozek na przodzie
	glPushMatrix();
	glTranslatef(0.8, 0.2, 0.0);
	glRotatef(90, 0.0, 1.0, 0.0);
	glutSolidCone(stozekR, stozekH, 30, 30);
	glPopMatrix();

	// dysk zamykajacy ciuchcie
	glPushMatrix();
	glTranslatef(-1.0, 0.2, 0.0);
	glRotatef(90, 0.0, 1.0, 0.0);
	gluDisk(obj, 0, 0.5, 30, 2);
	glPopMatrix();

	// prostopadloscian--------------
	glPushMatrix();
	glTranslatef(0.0, -0.5, 0.0);
	glScalef(xProst, yProst, zProst);
	glutSolidCube(1.0);
	glPopMatrix();

	// kola
	glPushMatrix();
	// prawa strona
	drawWheel(1.0, -0.58, 0.50, 0.4, shadow);
	drawWheel(0.1, -0.58, 0.50, 0.4, shadow);
	drawWheel(-0.8, -0.58, 0.50, 0.4, shadow);

	// lewa strona
	drawWheel(1.0, -0.58, -0.6, 0.4, shadow);
	drawWheel(0.1, -0.58, -0.6, 0.4, shadow);
	drawWheel(-0.8, -0.58, -0.6, 0.4, shadow);
	glPopMatrix();

	glPopMatrix();
	if (shadow)
	{
		glEnable(GL_LIGHTING);
	}
}
void Lokomotywa::drawWheel(GLfloat x, GLfloat y, GLfloat z, GLdouble innerradius, bool shadow)
{
	GLUquadricObj *obj = gluNewQuadric();
	glPushMatrix();
	
	glTranslatef(x, y, z);
	glRotatef(-this->alfa * 4, 0.0, 0.0, 1.0);
	glDisable(GL_LIGHTING);
	for (int i = 0; i < 4; i++)
	{
		GLfloat x = getNextWheelXCord(i, innerradius);
		GLfloat y = getNextWheelYCord(i, innerradius);
		glBegin(GL_LINES);
		if (shadow)
			glColor3f(0.2f, 0.2f, 0.2f); // kolor cienia
		else
			glColor3f(1.0, 0.0, 0.0);
		glVertex3f(-x, -y, 0.05);
		glVertex3f(x, y, 0.05);
		glEnd();
	}
	if (shadow)
		glColor3f(0.2f, 0.2f, 0.2f); // kolor cienia
	else
		glColor3f(0.0, 0.0, 0.0);
	gluCylinder(obj, innerradius+0.01, innerradius+0.01, 0.1, 20, 20);
	//gluDisk(obj, innerradius, outerradius, 20, 20);
	glEnable(GL_LIGHTING);
	glPopMatrix();
}


void Lokomotywa::move()
{
	x = (GLfloat)R*sin(M_PI*alfa/180.0);
	z = (GLfloat)R*cos(M_PI*alfa / 180.0);
	alfa += dalfa;
	if (alfa >= 360.0)
	{
		alfa = 0.0;
		lapNumber++;
		lapsToGo--;
	}

	if (lapNumber == 2 || lap)
	{
		lap = true;
		
		if (effect->getsmokeNumber() < 5)
		{
			if (nextSmoke)
			{
				xSmoke = this->getChimneyX();
				zSmoke = this->getChimneyZ();
				nextSmoke = false;
			}
			effect->smoke(xSmoke, zSmoke);
			if (effect->getSmokeAlpha() <= 0.05)
			{
				effect->incrementsmokeNumber();
				effect->setSmokeAlphaToOne();
				effect->setDefaultYSmoke();
				effect->setDefaultRSmoke();
				nextSmoke = true;
			}
		}
		else
		{
			lap = false;
			lapNumber = 0;
			effect->setsmokeNumber();
		}
	}
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

#include "lokomotywa.h"
#define M_PI 3.1415

Lokomotywa::Lokomotywa()
{
	std::cout << "Lokomotywa loading...";
	effect = new Effects();
}

void Lokomotywa::draw()
{
	//std::cout << "draw \n";
	GLUquadricObj *obj = gluNewQuadric();
	GLfloat torus_diffuse[] = { 0.0, 1.0, 0.0, 1.0 };


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

	glPushMatrix();
	
	glTranslatef(x, 1.0, z);		// przesuniecie modelu
	glRotatef(this->alfa, 0.0, 1.0, 0.0);
	// komin-------------
		glPushMatrix();
		glMaterialfv(GL_FRONT, GL_DIFFUSE, torus_diffuse);
		glRotatef(90, 1.0, 0.0, 0.0);
		glTranslatef(0.0, 0.0, -1.5);
		gluCylinder(obj, kominR1, kominR2, kominH, 30, 30);

		glPopMatrix();
		// end --- komin-------------

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
		glMaterialfv(GL_FRONT, GL_DIFFUSE, torus_diffuse);
		
		glTranslatef(0.0, -0.5, 0.0);
		glScalef(xProst, yProst, zProst);
		glutSolidCube(1.0);
		glPopMatrix();

	// kola
		glPushMatrix();
		
		// prawa strona
		drawWheel(1.0, -0.5, 0.45, 0.4);
		drawWheel(0.1, -0.5, 0.45, 0.4);
		drawWheel(-0.8, -0.5, 0.45, 0.4);
		
		// lewa strona
		drawWheel(1.0, -0.5, -0.6, 0.4);
		drawWheel(0.1, -0.5, -0.6, 0.4);
		drawWheel(-0.8, -0.5, -0.6, 0.4);
		
		glPopMatrix();
	glPopMatrix();

}

void Lokomotywa::drawWheel(GLfloat x, GLfloat y, GLfloat z, GLdouble innerradius)
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
	if (alfa >= 360.0)
	{
		alfa = 0.0;
		lapNumber++;
	}

	if (lapNumber == 2 || lap)
	{
		lap = true;
		
		if (effect->getsmokeNumber() < 5)
		{
			//std::cout << "jestem1 \n";
			effect->smoke(this->getChimneyX(), this->getChimneyZ());
			if (effect->getSmokeAlpha() <= 0.05)
			{
				//std::cout << "jestem2 \n";
				effect->incrementsmokeNumber();
				effect->setSmokeAlphaToOne();
				effect->setDefaultYSmoke();
				effect->setDefaultRSmoke();
			}
		}
		else
		{
			//std::cout << "else \n";
			lap = false;
			lapNumber = 0;
			effect->setsmokeNumber();
		}
	}
		/*if (effect->getCounter() < -10000)
		{
			effect->smoke(this->getChimneyX(), this->getChimneyZ());
			effect->incrementCounter();
		}
		//if (effect->getCounter() >= 10000) effect->incrementsmokeNumber();
	}

		//}
		//lapNumber = 0;
	//}
	/*
	// w³¹czenie efektu mg³y
	glEnable(GL_FOG);

	// wskazówki jakoœci generacji mg³y
	glHint(GL_FOG_HINT, fog_hint);

	// kolor mg³y
	GLfloat fog_color[4] = { 0.9, 0.9, 0.9, 1.0 };
	glFogfv(GL_FOG_COLOR, fog_color);

	// gêstoœæ mg³y
	glFogf(GL_FOG_DENSITY, fog_density);

	// rodzaj mg³y
	glFogf(GL_FOG_MODE, fog_mode);

	// pocz¹tek i koniec oddzia³ywania mg³y liniowej
	glFogf(GL_FOG_START, fog_start);
	glFogf(GL_FOG_END, fog_end);
	
	/*glBegin(GL_TRIANGLES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(5.0, 5.0, 0.0);
	glVertex3f(8.0, 8.0, 8.0);
	glEnd();
	glDisable(GL_FOG);
	//glutSolidSphere(3.0, 30, 30);
	*/
	
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

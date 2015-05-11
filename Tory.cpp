#include "Tory.h"


Tory::Tory()
{
	
}


void Tory::Lines()
{
	// generowanie punktow
	GLUquadricObj *obj = gluNewQuadric();
	glPushMatrix();
	
	glDisable(GL_LIGHTING);
	glColor3f(0.0, 0.0, 0.0);
	glRotatef(90, 1, 0, 0);
	gluDisk(obj, 5.0, 5.1, 30, 30);
	gluDisk(obj, 6.0, 6.1, 30, 30);
	glPopMatrix();

	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(0, 1, 0);
	glVertex3f(10, 1, 0);
	glVertex3f(10, 1, 2);
	glVertex3f(0, 1, 2);
	/*
	glVertex2f(0, 485);
	glVertex2f(1000, 485);
	glVertex2f(0, 486);
	glVertex2f(1000, 486);*/
	/*while (c != 1000)
	{
	glVertex2f(c, d);
	glVertex2f(c, d - 15);
	c += 10;
	}*/
	glEnd();
	glEnable(GL_LIGHTING);


	glBegin(GL_LINES);
	for (int i = 0; i < size/2; i++)
	{
		glVertex3fv(tory_xyz  );
	}
	glEnd();
}

Tory::~Tory()
{
}

void Tory::drawTory()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, tory_xyz);
	glDisableClientState(GL_VERTEX_ARRAY);
}
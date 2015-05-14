#include "Tory.h"


Tory::Tory()
{
	fillVertexArray(this->R1, this->R2);
	
}


Tory::~Tory()
{
}

void Tory::drawTory()
{
	GLUquadricObj *obj = gluNewQuadric();
	glPushMatrix();

	glDisable(GL_LIGHTING);
	glColor3f(0.0, 0.0, 0.0);
	glRotatef(90, 1, 0, 0);
	gluDisk(obj, this->R1, this->R1 + 0.1, 30, 30);
	gluDisk(obj, this->R2, this->R2 + 0.1, 30, 30);
	glPopMatrix();
	
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, tory_xyz);
	glColor3f(0.0, 0.0, 0.0);
	glDrawArrays(GL_LINES, 0, size);

	glDisableClientState(GL_VERTEX_ARRAY);
	glEnable(GL_LIGHTING);
}

void Tory::fillVertexArray(GLdouble pr1, GLdouble pr2)
{
	double deltaFi = 0.0;		// kat o jaki rysowane sa kolejne linie miedzy okregami
	for (int i = 0; i < size; i++)
	{
		tory_xyz[6 * i + 0] = pr1*sin(M_PI*deltaFi / 180.0);			//x1
		tory_xyz[6 * i + 1] = 0.0;										//y1
		tory_xyz[6 * i + 2] = pr1*cos(M_PI*deltaFi / 180.0);			//z1

		tory_xyz[6 * i + 3] = pr2*sin(M_PI*deltaFi / 180.0);			//x2
		tory_xyz[6 * i + 4] = 0.0;										//y2
		tory_xyz[6 * i + 5] = pr2*cos(M_PI*deltaFi / 180.0);			//z2

		deltaFi += 15.0;
	}
}
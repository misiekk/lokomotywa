#include <Windows.h>
#include "GLUT.H"
#include <gl\GL.h>
#include "lokomotywa.h"

Lokomotywa *lok;

void init()			// devil/openil (obsluga tesktur), glm  (matematyka), glulookat (sterowanie polem widzenia)
{
	lok = new Lokomotywa();
	GLfloat mat_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_position[] = { 0.0, 0.0, 10.0, 1.0 };
	GLfloat lm_ambient[] = { 0.4, 0.4, 0.4, 1.0 };

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, 50.0);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lm_ambient);

	//glLightf(GL_LIGHT0, GL_AMBIENT, 0.0);

	glShadeModel(GL_SMOOTH);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);

	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
}


void displayLokomotywa()
{
	lok->draw();
}

void displayObjects(int frameNum)
{
	
}

void display()
{
	static int frameNumber = 0;
	if (frameNumber < 360)
	{
		frameNumber++;
	}
	else if (frameNumber == 360)
	{
		frameNumber = 0;
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.9, 0.5);

	glMatrixMode(GL_PROJECTION);
	
	glPushMatrix();
	//glTranslatef(0.1, 0.1, 0.5);
	//glRotatef((GLfloat)frameNumber, 0.0, 1.0, 0.0);
	
	glMatrixMode(GL_MODELVIEW);
	//displayObjects(frameNumber);
	glRotatef(5, 0.0, 1.0, 0.0);
	glTranslatef(0.1, 0.0, 0.0);
	displayLokomotywa();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glFlush();
	glutSwapBuffers();
}

void reshape(GLsizei w, GLsizei h)
{
	if (h > 0 && w > 0) {
		glViewport(0, 0, w, h);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		if (w <= h) {
			glOrtho(-2.25, 2.25, -2.25*h / w, 2.25*h / w, -10.0, 10.0);
			//glFrustum(-1.5, 1.5, -1.5*h / w, 1.5*w / h, 1.0, 10.0);
		}
		else {
			glOrtho(-2.25*w / h, 2.25*w / h, -2.25, 2.25, -10.0, 10.0);
			//glFrustum(-1.5*w / h, 1.5*w / h, -1.5, 1.5 + h, 1.0, 10.0);
		}
		glTranslatef(0.0, 0.0, 0.5);
		glMatrixMode(GL_MODELVIEW);
	}
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 800);

	glutCreateWindow("Lokomotywa");

	//Lokomotywa *lok = new Lokomotywa;

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(display);


	init();

	glutMainLoop();

	return 0;
}

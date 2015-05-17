#include <Windows.h>
#include <time.h>
#include "GLUT.H"
#include <gl\GL.h>
#include "lokomotywa.h"
#include "Tory.h"

Lokomotywa *lok;
Tory *tory;
int width, height;

// polozenie obserwatora
GLdouble eyex = 0;
GLdouble eyey = 5;
GLdouble eyez = 5;

// punkt w ktorego kierunku jest zwrocony obserwator
GLdouble centerx = 0;
GLdouble centery = 0;
GLdouble centerz = 0;

bool readyToGo = false;

void sleep(unsigned int mseconds)
{
	clock_t goal = mseconds + clock();
	while (goal > clock());
}


void init()			// devil/openil (obsluga tesktur), glm  (matematyka), glulookat (sterowanie polem widzenia)
{
	lok = new Lokomotywa();
	tory = new Tory();
	GLfloat mat_ambient[] = { 1.0, 1.0, 1.0, 0.5 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_position[] = { 0.0, 5.0, 10.0, 0.5 };
	GLfloat lm_ambient[] = { 0.4, 0.4, 0.4, 1.0 };

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, 20.0);
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
	lok->move();
	
}

void sky()
{
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glBegin(GL_POLYGON);
	glColor3f(0, 1, 1);
	glVertex3f(100, 1, -10);
	glVertex3f(100, 100, -10);
	glVertex3f(-100, 100, -10);
	glVertex3f(-100, 1, -10);
	glEnd();
	glEnable(GL_LIGHTING);
	glPopMatrix();
}

void displayObjects(int frameNum)
{
	
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.5, 0.0, 0.5);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(120, (GLfloat)width / (GLfloat)height, 0.1, 100.0);
	
	glPushMatrix(); 
	gluLookAt(eyex, eyey, eyez,
		centerx, centery, centerz,
		0, 1, 0);

	//glTranslatef(0.1, 0.1, 0.5);
	//glRotatef((GLfloat)frameNumber, 0.0, 1.0, 0.0);
	
	glMatrixMode(GL_MODELVIEW);
	
	// jazda po kole
	/*if (readyToGo)
	{
		glRotatef(1, 0.0, 1.0, 0.0);
		glTranslatef(0.1, 0.0, 0.0);
	}*/
	sky();
	displayLokomotywa();
	tory->drawTory();
	
	
	glMatrixMode(GL_PROJECTION);
	
	glPopMatrix();

	glFlush();
	glutSwapBuffers();
}

void displayIdle()
{

}

void reshape(GLsizei w, GLsizei h)
{
	if (h > 0 && w > 0) 
	{
		width = w;
		height = h;
		glViewport(0, 0, w, h);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		
		gluPerspective(90, (GLfloat)w / (GLfloat)h, 0.1, 1000.0);
		/*
		if (w <= h) {
			glOrtho(-12.25, 12.25, -12.25*h / w, 12.25*h / w, -10.0, 100.0);
			//glFrustum(-1.5, 1.5, -1.5*h / w, 1.5*w / h, -10.0, 10.0);
		}
		else {
			glOrtho(-12.25*w / h, 12.25*w / h, -12.25, 12.25, -10.0, 100.0);
			//glFrustum(-1.5*w / h, 1.5*w / h, -1.5, 1.5 + h, -10.0, 10.0);
		}*/
		glTranslatef(0.0, 0.0, 0.5);
		glMatrixMode(GL_MODELVIEW);
	}
}
/*
Start/zatrzymanie animacji
*/
void keyboardStart(unsigned char key, int x, int y)
{
	if (key == 32 && !readyToGo) readyToGo = true;
	else if (key == 32 && readyToGo) readyToGo = false;
	
	// sterowanie kamera
	// TODO: ograniczenia
	if (key == 'w')
	{
		eyey += 0.1;
	}
	if (key == 's')
	{
		eyey -= 0.1;
	}
	if (key == 'a')
	{
		eyex -= 0.1;
	}
	if (key == 'd')
	{
		eyex += 0.1;
	}
	if (key == 'z')
	{
		eyez += 0.1;
	}
	if (key == 'x')
	{
		eyez -= 0.1;
	}

	// odrysowanie okna
	reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 800);

	glutCreateWindow("Lokomotywa - GKOM, Piotr Misiowiec");
	
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(display);
	glutKeyboardFunc(keyboardStart);

	init();

	glutMainLoop();

	return 0;
}

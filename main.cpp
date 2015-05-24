#include <Windows.h>
#include <time.h>
#include "GLUT.H"
#include <gl\GL.h>
#include "lokomotywa.h"
#include "Tory.h"
#include "devil-1.7.8\include\IL\il.h"

GLint tex_list[1];
ilInit();
ilLoadImage("sky.jpg");
#define SKYTEX tex_list[0]


GLubyte tekstura[8][8][3] =
{
	{
		{ 250, 0, 0 }, { 250, 0, 0 }, { 250, 0, 0 }, { 250, 0, 0 },
		{ 230, 230, 230 }, { 230, 230, 230 }, { 230, 230, 230 }, { 230, 230, 230 }
	},
	{
		{ 250, 0, 0 }, { 250, 0, 0 }, { 250, 0, 0 }, { 250, 0, 0 },
		{ 230, 230, 230 }, { 230, 230, 230 }, { 230, 230, 230 }, { 230, 230, 230 }
	},
	{
		{ 250, 0, 0 }, { 250, 0, 0 }, { 250, 0, 0 }, { 250, 0, 0 },
		{ 230, 230, 230 }, { 230, 230, 230 }, { 230, 230, 230 }, { 230, 230, 230 }
	},
	{
		{ 250, 0, 0 }, { 250, 0, 0 }, { 250, 0, 0 }, { 250, 0, 0 },
		{ 230, 230, 230 }, { 230, 230, 230 }, { 230, 230, 230 }, { 230, 230, 230 }
	},
	{
		{ 0, 250, 0 }, { 0, 250, 0 }, { 0, 250, 0 }, { 0, 250, 0 },
		{ 0, 0, 250 }, { 0, 0, 250 }, { 0, 0, 250 }, { 0, 0, 250 }
	},
	{
		{ 0, 250, 0 }, { 0, 250, 0 }, { 0, 250, 0 }, { 0, 250, 0 },
		{ 0, 0, 250 }, { 0, 0, 250 }, { 0, 0, 250 }, { 0, 0, 250 }
	},
	{
		{ 0, 250, 0 }, { 0, 250, 0 }, { 0, 250, 0 }, { 0, 250, 0 },
		{ 0, 0, 250 }, { 0, 0, 250 }, { 0, 0, 250 }, { 0, 0, 250 }
	},
	{
		{ 0, 250, 0 }, { 0, 250, 0 }, { 0, 250, 0 }, { 0, 250, 0 },
		{ 0, 0, 250 }, { 0, 0, 250 }, { 0, 0, 250 }, { 0, 0, 250 }
	}
};

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

bool readyToGo = true;

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

	glNewList(SKYTEX, GL_COMPILE);
		skyTexture();
	glEndList();
}

void displayLokomotywa()
{
	lok->draw();
	if (readyToGo)
	{
		lok->move();
	}
	
	
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

void skyTexture()
{
	/*GLint texture;
	texture = SOIL_load_OGL_texture
		(
		"sky.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		);*/
	
	GLint
		s_vec[4] = { 200, 0, 0, 0 },
		t_vec[4] = { 0, 0, 200, 0 };

	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);

	glTexGeniv(GL_S, GL_OBJECT_PLANE, s_vec);
	glTexGeniv(GL_T, GL_OBJECT_PLANE, t_vec);

	//glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, white_amb_col);
	//glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, white_dif_col);
	glEnable(GL_TEXTURE_2D);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 8, 8, 0, GL_RGB, GL_UNSIGNED_BYTE, tekstura);
	glCallList(SKYTEX);
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 1);
	glVertex3f(1, 0, 1);
	glVertex3f(1, 0, 0);
	glEnd();
	//glBindTexture(GL_TEXTURE_2D, texture);
	glDisable(GL_TEXTURE_2D);

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
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
	
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(display);
	glutKeyboardFunc(keyboardStart);
	
	
	init();

	glutMainLoop();

	return 0;
}

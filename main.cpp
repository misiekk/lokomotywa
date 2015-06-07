#include <Windows.h>
#include <time.h>
#include "GLUT.H"
#include <gl\GL.h>
#include "lokomotywa.h"
#include "Tory.h"
#include "il.h"

GLuint texture[2];
GLfloat light_position[] = { 2.0, 5.0, 10.0, 0.5 };

Lokomotywa *lok;
Tory *tory;
int width, height;


// polozenie obserwatora
GLdouble eyex = 0;
GLdouble eyey = 3;
GLdouble eyez = 7;

// punkt w ktorego kierunku jest zwrocony obserwator
GLdouble centerx = 0;
GLdouble centery = 0;
GLdouble centerz = 0;

bool readyToGo = true;


void init()			// devil/openil (obsluga tesktur), glm  (matematyka), glulookat (sterowanie polem widzenia)
{
	lok = new Lokomotywa();
	tory = new Tory();

	GLfloat lm_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat fog[4] = { 0.9, 0.9, 0.9, 1 };

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lm_ambient);
	
	glShadeModel(GL_SMOOTH);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);

	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	
	glEnable(GL_FOG);
	glFogf(GL_FOG_DENSITY, 0.02);
	glFogi(GL_FOG_MODE, GL_EXP);
	glFogfv(GL_FOG_COLOR, fog);
	glHint(GL_FOG_HINT, GL_NICEST);
	
}

void displayLokomotywa()
{
	lok->draw();
	if (readyToGo && lok->getLapsToGo() > 0)
	{
		lok->move();
	}
	if (lok->getLapsToGo() == 0)
		readyToGo = false;
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

GLuint loadImage(const char* filename)
{
	ILuint texid; /* ILuint is a 32bit unsigned integer.
				  Variable texid will be used to store image name. */
	ILboolean success;
	GLuint image;
	int finished;
	if (ilGetInteger(IL_VERSION_NUM) < IL_VERSION)
	{
		std::cout << "IL VERSION PROBLEM! \n";
		return -1;
	}

	ilInit();
	ilGenImages(1, &texid); /* Generation of one image name */
	ilBindImage(texid); /* Binding of image name */
	success = ilLoadImage((const ILstring)filename); 
	if (success) 
	{
		success = ilConvertImage(IL_RGB, IL_UNSIGNED_BYTE); /* Convert every colour component into
															unsigned byte. If your image contains alpha channel you can replace IL_RGB with IL_RGBA */
		if (!success)
		{
			std::cout << "Texture error! \n";
			return -1;
		}

		glGenTextures(1, &image); /* Texture name generation */
		glBindTexture(GL_TEXTURE_2D, image); /* Binding of texture name */
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), ilGetInteger(IL_IMAGE_WIDTH),
			ilGetInteger(IL_IMAGE_HEIGHT), 0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE,
			ilGetData()); 
	}
	else
	{
		std::cout << "Texture error! \n";
		return -1;
	}
	ilDeleteImages(1, &texid); /* Because we have already copied image data into texture data
							   we can release memory used by image. */
	
	return image;
}

void skyTexture()
{
	glPushMatrix();
	//glRotatef(90, 0.0, 0.0, 1.0);
	glTranslatef(-100.0, 0.0, 0.0);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glTexCoord2i(0, 0); glVertex3i(-200, 0, -20);
	glTexCoord2i(0, 1); glVertex3i(-200, 133, -20);
	glTexCoord2i(1, 1); glVertex3i(200, 133, -20);
	glTexCoord2i(1, 0); glVertex3i(200, 0, -20);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void groundTexture()
{
	glPushMatrix();
	//glRotatef(90, 0.0, 0.0, 1.0);
	glTranslatef(-65.0, 0.0, -47.5);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glTexCoord2i(0, 0); glVertex3f(-160, -0.1, 0);
	glTexCoord2i(0, 1); glVertex3f(-160, -0.1, 125);
	glTexCoord2i(1, 1); glVertex3f(160, -0.1, 125);
	glTexCoord2i(1, 0); glVertex3f(160, -0.1, 0);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}


void textureSkyInit()
{
	const char* fileSky = "sky.jpg";
	texture[0] = loadImage(fileSky);
}

void textureGroundInit()
{
	const char* fileGround = "zwir2.jpg";
	texture[1] = loadImage(fileGround);
}

void textureInit()
{
	textureGroundInit();
	textureSkyInit();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glutInitDisplayMode(GLUT_RGBA | GLUT_ALPHA);
	glClearColor(0.77, 0.77, 0.77, 1.0);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(120, (GLfloat)width / (GLfloat)height, 0.1, 100.0);
	
	glPushMatrix(); 
	gluLookAt(eyex, eyey, eyez,
		centerx, centery, centerz,
		0, 1, 0);

	glMatrixMode(GL_MODELVIEW);

	displayLokomotywa();
	tory->drawTory();
	skyTexture();
	groundTexture();
	
	glMatrixMode(GL_PROJECTION);
	
	glPopMatrix();
	glFlush();
	glutSwapBuffers();
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

void keyboardStart(unsigned char key, int x, int y)
{
	// q
	if (key == 113 && !readyToGo)
	{
		readyToGo = true;
		if (lok->getLapsToGo() == 0)
			lok->setLapsToGo(4);
	}
	else if (key == 113 && readyToGo)
		readyToGo = false;

	
	// sterowanie kamera
	if (key == 'w')
	{
		if (eyey < 4)
			eyey += 0.1;
	}
	if (key == 's')
	{
		if (eyey > 1)
			eyey -= 0.1;
	}
	if (key == 'a')
	{
		if (eyex > 0.0)
			eyex -= 0.1;
	}
	if (key == 'd')
	{
		if (eyex < 1.0)
			eyex += 0.1;
	}
	if (key == 'z')
	{
		if (eyez < 7.5)
			eyez += 0.1;
	}
	if (key == 'x')
	{
		if (eyez > 6.5)
			eyez -= 0.1;
	}
	// odrysowanie okna
	reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
}

void setVelocity(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		if (lok->getdAlfa() < 2.0)
			lok->incrementAlfa();
		break;

	case GLUT_KEY_DOWN:
		if (lok->getdAlfa() >= 0.0)
			lok->decrementAlfa();
		break;
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);// | GLUT_ALPHA);

	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 800);

	glutCreateWindow("Lokomotywa - GKOM, Piotr Misiowiec");
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(display);
	glutKeyboardFunc(keyboardStart);
	glutSpecialFunc(setVelocity);
	textureInit();

	init();
	glutMainLoop();

	return 0;
}


/*
plik DevIL.dll do C:\Windows\SysWOW64 i wtedy dziala

#pragma comment(lib, "DevIL.lib")
#pragma comment(lib, "ILU.lib")
#pragma comment(lib, "ILUT.lib")
*/
#include <Windows.h>
#include <time.h>
#include "GLUT.H"
#include <gl\GL.h>
#include "lokomotywa.h"
#include "Tory.h"
#include "il.h"

GLuint texture[2];

Lokomotywa *lok;
Tory *tory;
int width, height;



// polozenie obserwatora
GLdouble eyex = 2;
GLdouble eyey = 4;
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
	GLfloat mat_ambient[] = { 1.0, 1.0, 1.0, 0.5 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_position[] = { 2.0, 5.0, 5.0, 0.5 };
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
	if (readyToGo && lok->getLapsToGo() > 0)
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
			glTexCoord2i(0, 0); glVertex3i(0, 0, -20);
			glTexCoord2i(0, 1); glVertex3i(0, 133, -20);
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
	glTexCoord2i(0, 0); glVertex3f(0, -0.1, 0);
	glTexCoord2i(0, 1); glVertex3f(0, -0.1, 95);
	glTexCoord2i(1, 1); glVertex3f(130, -0.1, 95);
	glTexCoord2i(1, 0); glVertex3f(130, -0.1, 0);
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
	glClearColor(0.0, 0.0, 0.0, 1.0);
	
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
	//sky();
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
	glutSpecialFunc(setVelocity);
	textureInit();

	init();
	glutMainLoop();

	return 0;
}


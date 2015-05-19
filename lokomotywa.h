#include <windows.h>
#include <GL/gl.h>
#include "glut.h"
#include <iostream>
#include <math.h>


class Lokomotywa
{
public:
	Lokomotywa();
	void draw();
	void drawWheel(GLfloat x, GLfloat y, GLfloat z, GLdouble innerradius);
	void move();
	GLfloat getNextWheelXCord(int i, GLfloat radius);
	GLfloat getNextWheelYCord(int i, GLfloat radius);
	void clouds();
	GLfloat inline getAlpha() { return this->cloudAlpha; }
private:
	// promien toru lokomotywy
	const float R = 5.5;
	// wspolrzedne
	GLfloat x = 0.0, z = -4.0;
	GLfloat alfa = 0.0;
	GLfloat cloudUp = 0.0;
	GLfloat cloudAlpha = 1.0;
	
	// wskaz�wki jako�ci generacji mg�y
	GLint fog_hint = GL_DONT_CARE;
	// pocz�tek i koniec oddzia�ywania mg�y liniowej
	GLfloat fog_start = 0.0;
	GLfloat fog_end = 2.0;
	// g�sto�� mg�y
	GLfloat fog_density = 0.5;
	// rodzaj mg�y
	GLfloat fog_mode = GL_LINEAR;
};

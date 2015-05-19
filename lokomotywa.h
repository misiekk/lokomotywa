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
	
	// wskazówki jakoœci generacji mg³y
	GLint fog_hint = GL_DONT_CARE;
	// pocz¹tek i koniec oddzia³ywania mg³y liniowej
	GLfloat fog_start = 0.0;
	GLfloat fog_end = 2.0;
	// gêstoœæ mg³y
	GLfloat fog_density = 0.5;
	// rodzaj mg³y
	GLfloat fog_mode = GL_LINEAR;
};

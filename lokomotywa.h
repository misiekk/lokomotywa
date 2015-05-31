#include <windows.h>
#include <GL/gl.h>
#include "glut.h"
#include <iostream>
#include <math.h>
#include "Effects.h"


class Lokomotywa
{
public:
	Lokomotywa();
	void draw();
	void drawWheel(GLfloat x, GLfloat y, GLfloat z, GLdouble innerradius);
	void move();
	GLfloat getNextWheelXCord(int i, GLfloat radius);
	GLfloat getNextWheelYCord(int i, GLfloat radius);
	
	inline GLfloat getChimneyX() { return x; }
	inline GLfloat getChimneyZ() { return z; }
	inline int getLapsToGo() { return lapsToGo; }
	inline void setLapsToGo(int laps) { this->lapsToGo = laps; }
	inline void incrementAlfa(){ this->dalfa += 0.1; }
	inline void decrementAlfa(){ this->dalfa -= 0.1; }
	inline GLfloat getdAlfa(){ return this->dalfa; }
private:
	// promien toru lokomotywy
	const float R = 5.5;
	// wspolrzedne
	GLfloat x = 0.0, z = -4.0;
	GLfloat alfa = 0.0;
	GLfloat dalfa = 1.0;
	GLfloat cloudUp = 0.0;
	
	int lapNumber = 0,
		lapsToGo = 4;
	bool lap = false;

	// wskazówki jakoœci generacji mg³y
	GLint fog_hint = GL_DONT_CARE;
	// pocz¹tek i koniec oddzia³ywania mg³y liniowej
	GLfloat fog_start = 0.0;
	GLfloat fog_end = 2.0;
	// gêstoœæ mg³y
	GLfloat fog_density = 0.5;
	// rodzaj mg³y
	GLfloat fog_mode = GL_LINEAR;

	Effects *effect;
};

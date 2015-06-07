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
	void drawWheel(GLfloat x, GLfloat y, GLfloat z, GLdouble innerradius, bool shadow);
	void move();
	GLfloat getNextWheelXCord(int i, GLfloat radius);
	GLfloat getNextWheelYCord(int i, GLfloat radius);
	void generateLoco(bool shadow);
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

	GLfloat xSmoke = 0.0,
		zSmoke = 0.0;
	bool nextSmoke = true;
	
	int lapNumber = 0,
		lapsToGo = 10;
	bool lap = false;



	Effects *effect;
};

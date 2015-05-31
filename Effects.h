#pragma once

#include <windows.h>
#include <GL/gl.h>
#include "glut.h"

class Effects
{
public:
	Effects();
	~Effects();

	void smoke(GLfloat x, GLfloat z);
	inline GLfloat getAlpha() { return this->smokeAlpha; }
	inline int getCounter() { return this->counter; }
	inline int getsmokeNumber() { return this->smokeNumber; }
	inline void setsmokeNumber() { this->smokeNumber = 0; }
	inline GLfloat getSmokeAlpha() { return this->smokeAlpha; }
	inline void incrementCounter() { this->counter++; }
	inline void incrementsmokeNumber() { this->smokeNumber++; }
	inline void setSmokeAlphaToOne() { smokeAlpha = 1.0; }
	inline void setDefaultYSmoke() { y = 2.5; }
	inline void setDefaultRSmoke() { R = 0.3; }
private:
	GLfloat smokeAlpha = 1.0;
	int counter = 0;
	int smokeNumber = 0;
	bool smokeUp = false,
		smokeDown = true;
	// defaultowa wspolrzedna dymu (nad kominem)
	GLfloat y = 2.5;
	// defaultowy promien kuli reprezentujacej oblok dymu
	GLdouble R = 0.2;

};


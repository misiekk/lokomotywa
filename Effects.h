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
	inline GLfloat getSmokeAlpha() { return this->smokeAlpha; }
	inline void incrementCounter() { this->counter++; }
	inline void incrementsmokeNumber() { this->smokeNumber++; }
	inline void setSmokeAlphaToOne() { smokeAlpha = 1.0; }
private:
	GLfloat smokeAlpha = 1.0;
	int counter = 0;
	int smokeNumber = 0;
	bool smokeUp = false,
		smokeDown = true;

};


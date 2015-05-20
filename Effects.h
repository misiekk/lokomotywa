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
	inline void incrementCounter() { this->counter++; }
private:
	GLfloat smokeAlpha = 1.0;
	int counter = 0;

};


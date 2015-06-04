#pragma once
#define M_PI 3.1415
#include <windows.h>
#include <GL/gl.h>
#include "glut.h"
#include <iostream>
#include <math.h>

class Tory
{
public:
	Tory();
	~Tory();
	
	void drawTory();
	void fillVertexArray(GLdouble pr1, GLdouble pr2);
private:
	static const int size = 48;
	GLfloat tory_xyz[6 * size];
	// promienie torow
	GLdouble R1 = 5.0,		
		R2 = 6.0;
};


#pragma once
#include <windows.h>
#include <GL/gl.h>
#include "glut.h"
class Tory
{
public:
	Tory();
	~Tory();
	static const int size = 8;
	GLfloat tory_xyz[8];

	void drawTory();
	void Lines();
};


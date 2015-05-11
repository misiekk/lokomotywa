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
	void move();
private:
	// promien toru lokomotywy
	const int R = 2;
	// wspolrzedne
	float x, z;

};

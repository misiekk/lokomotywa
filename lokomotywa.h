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
	const int R = 3;
	// wspolrzedne
	float x = 0.0, z = -4.0;
	float alfa = 0;

};

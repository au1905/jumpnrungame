#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include "Figur.h"



Figur::Figur(double x, double y,
		GLuint texturNr) :
		Object(x, y, 0.3, 0.4, texturNr) {

}

Figur::~Figur() {

}

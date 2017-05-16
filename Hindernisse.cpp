/*
 * Hindernisse.cpp
 *
 *  Created on: 07.03.2017
 *      Author: nopper06
 */

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include "Hindernisse.h"

Hindernisse::Hindernisse(double x, double y, double size, GLuint texturNr) :
		Object(x, y, 0.3 * size, 0.4 * size, texturNr) {

}

Hindernisse::Hindernisse(double x, double y, double sizeX, double sizeY,
		GLuint texturNr) :
		Object(x, y, sizeX, sizeY, texturNr) {

}

Hindernisse::~Hindernisse() {
	// TODO Auto-generated destructor stub
}

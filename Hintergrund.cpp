/*
 * Hintergrund.cpp
 *
 *  Created on: 04.04.2017
 *      Author: nopper06
 */

#include "Hintergrund.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <string>

Hintergrund::Hintergrund(double x, double y,
		GLuint texturNr) :
		Object(x, y, 2, 2, texturNr) {

}

Hintergrund::~Hintergrund() {
	// TODO Auto-generated destructor stub
}


/*
 * Hintergrund.h
 *
 *  Created on: 04.04.2017
 *      Author: nopper06
 */

#ifndef HINTERGRUND_H_
#define HINTERGRUND_H_

#include "Object.h"
#include<GL/glut.h>

class Hintergrund: public Object   {
public:
	Hintergrund(double x, double y, GLuint texturNr);
	virtual ~Hintergrund();

private:
};

#endif /* HINTERGRUND_H_ */


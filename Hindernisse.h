/*
 * Hindernisse.h
 *
 *  Created on: 07.03.2017
 *      Author: nopper06
 */

#ifndef HINDERNISSE_H_
#define HINDERNISSE_H_

#include "Object.h"
#include<GL/glut.h>

class Hindernisse: public Object {
public:
	Hindernisse(double x, double y, double size, GLuint texturNr);
	Hindernisse(double x, double y, double sizeX, double sizeY, GLuint texturNr);
	virtual ~Hindernisse();

private:
};

#endif /* HINDERNISSE_H_ */


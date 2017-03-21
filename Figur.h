/*
 * Figur.h
 *
 *  Created on: Feb 12, 2017
 *      Author: Hocceruser
 */

#ifndef FIGUR_H
#define FIGUR_H

#include "Object.h"

class Figur: public Object {
public:
	Figur(double x, double y, GLuint texturNr);
	virtual ~Figur();

private:
	void initFlat(
			GLfloat dirx,  GLfloat, GLfloat dirz,
			int shift);
};

#endif /* Figur_H_ */

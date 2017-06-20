/*
 * Boden.h
 *
 *  Created on: 30.05.2017
 *      Author: nopper09
 */

#ifndef SRC_BODEN_H_
#define SRC_BODEN_H_

#include<GL/glut.h>
#include "Object.h"

class Boden: public Object {

public:
	Boden(double x, double y, GLuint texturNr);
	virtual ~Boden();

private:
};

#endif /* SRC_BODEN_H_ */

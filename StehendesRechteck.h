/*
 * StehendesRechteck.h
 *
 *  Created on: 23.05.2017
 *      Author: nopper09
 */

#ifndef SRC_STEHENDESRECHTECK_H_
#define SRC_STEHENDESRECHTECK_H_
#include "Hindernisse.h"

class StehendesRechteck: public Hindernisse {
public:
	StehendesRechteck(double x, double y, double size, GLuint texturNr);
	virtual ~StehendesRechteck();
};

#endif /* SRC_STEHENDESRECHTECK_H_ */

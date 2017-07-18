/*
 * Hindernisse.h
 *
 *  Created on: 07.03.2017
 *      Author: nopper06
 */

#ifndef HINDERNISSE_H_
#define HINDERNISSE_H_

#include "Object.h"
#include <GL/glut.h>
#include "Figur.h"

class Hindernisse: public Object {
public:
	Hindernisse(double x, double y, double size, GLuint texturNr);
	Hindernisse(double x, double y, double sizeX, double sizeY,
			GLuint texturNr);
	virtual ~Hindernisse();

	enum Kollision {
		KEINE_KOLLISION = 0, VON_LINKS, VON_RECHTS, VON_OBEN, VON_UNTEN
	};
	virtual Kollision collision(Figur* figur);
	Kollision collisionQuader(Figur* figur, double linkesX, double unteresY,
			double breite, double hoehe);
private:
	static uint ladeTextur();
};

#endif /* HINDERNISSE_H_ */


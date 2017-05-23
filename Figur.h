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
	Figur(double x, double y, double size, GLuint texturNr);
	virtual ~Figur();

	void move(int time);
	void tasteDruck(unsigned char key);
	void tasteLos(unsigned char key);

	double getx();

	float kameraposx=0;
	float kameraposy=0;
private:
	double dx=0.0;
	double dy=0.0;

	bool tasteHochGedrueckt=false;
	bool tasteRechtsGedrueckt=false;
	bool tasteLinksGedrueckt=false;
};

#endif /* Figur_H_ */

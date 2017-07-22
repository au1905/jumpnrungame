/*
 * HindernisTreppe.cpp
 *
 *  Created on: 09.05.2017
 *      Author: nopper03
 */

#include "HindernisTreppe.h"


HindernisTreppe::HindernisTreppe(double x, double y, double size, GLuint texturNr) :
		Hindernisse(x, y, size*2.0, size*1.0, texturNr) {

	// TODO Auto-generated constructor stub

}


HindernisTreppe::~HindernisTreppe() {
	// TODO Auto-generated destructor stub
}

Hindernisse::Kollision HindernisTreppe::collision(Figur * figur) {

	// Der "untere" Quader
	Hindernisse::Kollision kollision = collisionQuader(figur, _x, _y, _breite, _hoehe/2);
	if (kollision != KEINE_KOLLISION) {
		return kollision;
	}

	// Der "obere" Quader
	return collisionQuader(figur, _x + _breite/5, _y + _hoehe/2.0, _breite*3/5, _hoehe/2);
}

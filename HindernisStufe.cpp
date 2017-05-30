/*
 * HindernisStufe.cpp
 *
 *  Created on: 25.04.2017
 *      Author: nopper03
 */

#include "HindernisStufe.h"
#include "Figur.h"

Hindernis_Stufe::Hindernis_Stufe(double x, double y, double size, GLuint texturNr) :
		Hindernisse(x, y, size, texturNr) {
	// TODO Auto-generated constructor stub

}

Hindernis_Stufe::~Hindernis_Stufe() {
	// TODO Auto-generated destructor stub
}

void Hindernis_Stufe::collision(double px, double py) {
	//px = X-Position der Figur    py = Y-Position der Figur
	//double posx = Figur->getx;
	//double posy = Figur->gety;
	if(py <= _y){  	//Wenn Figur nicht springt; _y höchster Punkt des Hindernisses
		double pxr = px+0.6; //rechte obere Ecke Figur
		double dl = _x - pxr; //Abstand links Figur - Rechteck
		if (dl==0){
			//figur->tasteLos(d);
		}

		double dr = (_x ) - px;
		if(dr == 0){
			//abprallen in x-Richtung
		}
	}
}

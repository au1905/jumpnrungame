/*
 * HindernisStufe.cpp
 *
 *  Created on: 25.04.2017
 *      Author: nopper03
 */

#include "HindernisStufe.h"
#include "Figur.h"
#include <iostream>

Hindernis_Stufe::Hindernis_Stufe(double x, double y, double size, GLuint texturNr) :
		Hindernisse(x, y, size, texturNr) {
	// TODO Auto-generated constructor stub

}

Hindernis_Stufe::~Hindernis_Stufe() {
	// TODO Auto-generated destructor stub
}

void Hindernis_Stufe::collision(Figur* figur) {
	//px = X-Position der Figur    py = Y-Position der Figur
	double figurx = figur->getx();
	double figury = figur->gety();
	if(figury <= _y){  	//Wenn Figur nicht springt; _y höchster Punkt des Hindernisses
		double pxr = figurx+0.6; //rechte obere Ecke Figur
		double dl = _x - pxr; //Abstand links Figur - Rechteck
		if (dl==0){
			//figur->tasteLos(d);
		}

		double dr = (_x ) - figurx;
		if(dr == 0){
			std::cout<<"Kollisionx"<<std::endl;
			//abprallen in x-Richtung
		}
	}
}

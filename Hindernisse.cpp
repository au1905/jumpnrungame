/*
 * Hindernisse.cpp
 *
 *  Created on: 07.03.2017
 *      Author: nopper06
 */

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include "Hindernisse.h"

double min(double values[], int arraysize);

Hindernisse::Hindernisse(double x, double y, double size, GLuint texturNr) :
		Object(x, y, 0.3 * size, 0.4 * size, texturNr) {

}

Hindernisse::Hindernisse(double x, double y, double sizeX, double sizeY,
		GLuint texturNr) :
		Object(x, y, sizeX, sizeY, texturNr) {

}

Hindernisse::~Hindernisse() {
	// TODO Auto-generated destructor stub
}

Hindernisse::Kollision Hindernisse::collision(Figur* figur) {
	collisionQuader(figur, _x, _y, _breite, _hoehe);
}

enum Kollision {
	KEINE_KOLLISION = 0, VON_LINKS, VON_RECHTS, VON_OBEN, VON_UNTEN
};
Hindernisse::Kollision Hindernisse::collisionQuader(Figur* figur, double linkesX, double unteresY,
		double breite, double hoehe) {

	double figurLinkesX = figur->getx();
	double figurUnteresY = figur->gety();

	double figurRechtesX = figurLinkesX + figur->getBreite();
	double figurOberesY = figur->getHoehe();

	double rechtesX = linkesX + breite;
	double oberesY = unteresY + hoehe;

	if (figurRechtesX < linkesX || figurLinkesX > rechtesX) {
		// Die Figuren beruehren sich nicht.
		return KEINE_KOLLISION;
	}
	if (figurUnteresY + figurOberesY < unteresY || figurUnteresY > oberesY) {
		// Die Figuren beruehren sich nicht.
		return KEINE_KOLLISION;
	}

	// Die Figuren beruehren sich.
	// TODO An dieser Stelle könnte man testen, ob der Test das nur so ergeben hat, weil bisher an-
	// genommen wurde, dass die Figur ein Quadrat ist.

	// Herausfinden, aus welcher Richtung die Kollision erfolgt ist:

	// Wie weit wäre die Figur von links, von rechts, von oben und von unten "eingedrungen"?
	double vonLinks = figurRechtesX - linkesX;
//	std::cout << "von Links: " << vonLinks;

	double vonRechts = rechtesX - figurLinkesX;
//	std::cout << "von rechts: " << vonRechts;

	double vonUnten = figurOberesY - unteresY;
//	std::cout << "von unten: " << vonUnten;

	double vonOben = oberesY - figurUnteresY;
//	std::cout << "von oben: " << vonOben;


	// Wenn beispielsweise vonLinks am kleinsten ist, ist es am wahrscheinlichsten, dass links die
	// Richtung war, aus der die Figur tatsächlich gekommen ist.

	double values[] = {vonLinks,vonRechts,vonUnten,vonOben};
	double minimum = min(values, 4);

	if (vonLinks == minimum) {
//		std::cout << "von Links" << std::endl;
		return VON_LINKS;
	}
	if (vonOben == minimum) {
//		std::cout << "von Oben" << std::endl;
		return VON_OBEN;
	}
	if (vonRechts == minimum) {
//		std::cout << "von Rechts" << std::endl;
		return VON_RECHTS;
	}
	if (vonUnten == minimum) {
//		std::cout << "von Unten" << std::endl;
		return VON_UNTEN;
	}

	// Jonathan @Aurel
	// Ich habe nicht verstanden, was dieser Code macht:
	/*if(figury <= _y){  	//Wenn Figur nicht springt; _y höchster Punkt des Hindernisses
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
	 }*/

	//Sollte eigentlich nicht passieren
	std::cerr << "Fehler in Hindernisse.collisionQuader" << std::endl;
	return KEINE_KOLLISION;
}


double min(double values[], int arraysize) {
	double minimum = values[0];
	for (int i = 1; i < arraysize; ++i) {
		if (values[i] < minimum) {
			minimum = values[i];
		}
	}
	return minimum;
}

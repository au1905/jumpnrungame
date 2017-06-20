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

int min(int values[], int arraysize);

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

void Hindernisse::collision(Figur* figur) {
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

	if (figurRechtesX < linkesX && figurLinkesX > rechtesX) {
		// Die Figuren beruehren sich nicht.
		return KEINE_KOLLISION;
	}
	if (figurUnteresY + figurOberesY < unteresY && figurUnteresY > oberesY) {
		// Die Figuren beruehren sich nicht.
		return KEINE_KOLLISION;
	}

	// Die Figuren beruehren sich.
	// TODO An dieser Stelle könnte man testen, ob der Test das nur so ergeben hat, weil bisher an-
	// genommen wurde, dass die Figur ein Quadrat ist.

	// Herausfinden, aus welcher Richtung die Kollision erfolgt ist:

	// Wie weit wäre die Figur von links, von rechts, von oben und von unten "eingedrungen"?
	int vonLinks = figurRechtesX - linkesX;
	int vonRechts = rechtesX - figurLinkesX;
	int vonUnten = figurOberesY - unteresY;
	int vonOben = oberesY - figurUnteresY;

	// Wenn beispielsweise vonLinks am kleinsten ist, ist es am wahrscheinlichsten, dass links die
	// Richtung war, aus der die Figur tatsächlich gekommen ist.

	int values[] = {vonLinks,vonRechts,vonUnten,vonOben};
	int minimum = min(values, 4);

	if (vonLinks == minimum) {
		return VON_LINKS;
	}
	if (vonOben == minimum) {
		return VON_OBEN;
	}
	if (vonRechts == minimum) {
		return VON_RECHTS;
	}
	if (vonUnten == minimum) {
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
}


int min(int values[], int arraysize) {
	int minimum = values[0];
	for (int i = 1; i < arraysize; ++i) {
		if (values[i] < minimum) {
			minimum = values[i];
		}
	}
	return minimum;
}

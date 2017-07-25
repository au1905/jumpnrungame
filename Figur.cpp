#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include "Figur.h"


Figur::Figur(double x, double y, double size, GLuint texturNr) :
	Object(x, y, 0.3*size, 0.4*size, texturNr) {

}

Figur::~Figur() {

}


void Figur::move(int time) {
	dy -= 0.0005;

	_y += ((dy * time) / 5);
	if (_y < -0.9) {
		dy = -dy;
		dy /= 1.5;
		_y += ((dy * time) / 5);
	}

	//Die Figur springen lassen.
	if (_y < -0.89 && tasteHochGedrueckt) {
		springen();
	}

//	_x += ((dx * time) / 5);
	if (tasteRechtsGedrueckt) {
		_x += time / 400.0;
	}
	if (tasteLinksGedrueckt) {
		_x -= time / 400.0;
	}

	_y += ((dy * time) / 5);


	if (kameraposx +_x > 0.0){
		kameraposx -= kameraposx +_x - 0.0;
	}
	if (kameraposx +_x < -0.5){
		kameraposx -= kameraposx +_x + 0.5;
	}


}

void Figur::tasteDruck(unsigned char key) {
	switch (key) {
	case 'w':
		tasteHochGedrueckt = true;
		break;
	case 'd':
		tasteRechtsGedrueckt=true;
		break;
	case 'a':
		tasteLinksGedrueckt=true;
		break;
	default:
		break;
	}
}

void Figur::tasteLos(unsigned char key) {

	switch (key) {
	case 'w':
		tasteHochGedrueckt=false;
		break;
	case 'd':
		tasteRechtsGedrueckt=false;
		break;
	case 'a':
		tasteLinksGedrueckt=false;
		break;
	default:
		break;
	}

}

void Figur::springen() {
	dy = 0.01;
}

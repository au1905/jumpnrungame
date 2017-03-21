#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <string>

#include "Object.h"

Object::Object(double x, double y, GLuint textureNr) :
		_x(x), _y(y), _textureNr(textureNr) {

	_displaylistNr = glGenLists(1);
	_rotation = 0;
}


Object::~Object() {
	// TODO Auto-generated destructor stub
}

void Object::Display() const {
	// Neues Element auf die Transformationsmatrix
	glPushMatrix();

	// Bewegen
	glTranslatef(_x, _y, 0);

	// Rotieren
	glRotatef(_rotation, 0, 1, 0);

	// Aufrufen der DisplayList
	glCallList(_displaylistNr);

	glPopMatrix();
}

void Object::Down(int time) {
	_y -= time * 0.02;
}

void Object::Up(int time) {
	_y += time * 0.02;
}

void Object::Right(int time) {
	_x += time * 0.02;
}

void Object::Left(int time) {
	_x -= time * 0.02;
}

void Object::RotateRight(int time) {
	_rotation += time * 0.2;
}

void Object::push(std::vector<GLfloat>& vec, GLfloat x, GLfloat y) {
	vec.push_back(x);
	vec.push_back(y);
}

void Object::push(std::vector<GLfloat>& vec, GLfloat x, GLfloat y, GLfloat z) {
	vec.push_back(x);
	vec.push_back(y);
	vec.push_back(z);
}

void Object::push(std::vector<GLuint>& vec, GLint a, GLint b, GLint c) {
	vec.push_back(a);
	vec.push_back(b);
	vec.push_back(c);
}

void Object::push(std::vector<GLuint>& vec, GLint a, GLint b, GLint c,
		GLint d) {
	vec.push_back(a);
	vec.push_back(b);
	vec.push_back(c);
	vec.push_back(d);
}




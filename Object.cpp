#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <string>

#include "Object.h"

Object::Object(double x, double y, double sizeX, double sizeY, GLuint textureNr) :
		_x(x), _y(y), _textureNr(textureNr) {

	_displaylistNr = glGenLists(1);
	_rotation = 0;

	_displaylistNr = glGenLists(1);
	glNewList(_displaylistNr, GL_COMPILE);


	// Neue Listen fuer die Ecken, die Normalen und die Indizes
	std::vector<GLfloat> vertices(0);
	std::vector<GLfloat> textures(0);
	std::vector<GLuint> indices(0);


	push(vertices, sizeX, sizeY);
	push(textures, 1, 1);

	push(vertices, 0, sizeY);
	push(textures, 0, 1);

	push(vertices, 0, 0);
	push(textures, 0, 0);

	push(vertices, sizeX, 0);
	push(textures, 1, 0);


	push(indices, 0, 1, 2, 3);


	if (_textureNr >= 0) {
		// aktiviere die Textur
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, _textureNr);
	}

	glEnableClientState(GL_VERTEX_ARRAY);
	if (_textureNr >= 0)
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(2, GL_FLOAT, 0, &(vertices.at(0)));
	if (_textureNr >= 0)
		glTexCoordPointer(2, GL_FLOAT, 0, &(textures.at(0)));

	glDrawElements(GL_QUADS, indices.size(), GL_UNSIGNED_INT, &(indices.at(0)));
	glDisableClientState(GL_VERTEX_ARRAY);
	if (_textureNr >= 0)
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	glEndList();
}


Object::~Object() {

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

void Object::Down(int distance) {
	_y -= time;
}

void Object::Up(int distance) {
	_y += time;
}

void Object::Right(int distance) {
	_x += time;
}

void Object::Left(int distance) {
	_x -= time;
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




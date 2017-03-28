#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include "Figur.h"

/**
 * dirx, diry, dirz: Normalenvektor
 * shift: 1, wenn die Fläche nach vorne verschoben werden soll (bei 3 Flächen der Fall)
 */
void Figur::initFlat(
		GLfloat dirx,  GLfloat diry, GLfloat dirz,
		int shift) {

	// Neue Listen fuer die Ecken, die Normalen und die Indizes
	std::vector<GLfloat> vertices(0);
	std::vector<GLfloat> textures(0);
	std::vector<GLuint> indices(0);


	push(vertices, 1, 1);
	push(textures, 1, 1);

	push(vertices, 0, 1);
	push(textures, 0, 1);

	push(vertices, 0, 0);
	push(textures, 0, 0);

	push(vertices, 1, 0);
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

}

Figur::Figur(double x, double y,
		GLuint texturNr) :
		Object(x, y, texturNr) {

	_displaylistNr = glGenLists(1);
	glNewList(_displaylistNr, GL_COMPILE);


	// Neue Listen fuer die Ecken, die Normalen und die Indizes
	std::vector<GLfloat> vertices(0);
	std::vector<GLfloat> textures(0);
	std::vector<GLuint> indices(0);


	push(vertices, 1, 1);
	push(textures, 1, 1);

	push(vertices, 0, 1);
	push(textures, 0, 1);

	push(vertices, 0, 0);
	push(textures, 0, 0);

	push(vertices, 1, 0);
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

Figur::~Figur() {
	// TODO Auto-generated destructor stub
}

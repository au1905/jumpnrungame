/*
 * Object.h
 *
 *  Created on: Jan 31, 2017
 *      Author: nopper
 */

#ifndef Object_H_
#define Object_H_

#include <vector>
#include <GL/glut.h>

class Object {
public:
	Object(double x, double y, double sizeX, double sizeY, GLuint textureNr);


	virtual ~Object();

	void Display() const;

	void Up(int);
	void Down(int);
	void Right(int);
	void Left(int);
	void RotateRight(int);
	double getx();
	double gety();
	double getBreite() const;
	double getHoehe() const;

protected:
	double _x;
	double _y;
	double _breite;
	double _hoehe;
	double _rotation;


	GLuint _textureNr;
	GLuint _displaylistNr;

	static void push(std::vector<GLfloat>& vec, GLfloat x, GLfloat y);

	static void push(std::vector<GLfloat>& vec, GLfloat x, GLfloat y,
			GLfloat z);

	static void push(std::vector<GLuint>& vec, GLint a, GLint b, GLint c);

	static void push(std::vector<GLuint>& vec, GLint a, GLint b, GLint c,
			GLint d);

};

#endif /* Object_H_ */

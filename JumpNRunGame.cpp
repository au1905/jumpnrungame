//============================================================================
// Name        : JumpNRunGame.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include<GL/glut.h>
#include <iostream>
#include <map>
#include "Imageloader.h"
#include "Figur.h"


using namespace std;

void display();
void timerEvent();
void tasteDruck(unsigned char key, int, int);
void tasteLos(unsigned char key, int, int);

int zeit = 0;
Figur* figur;

std::map<std::string, GLuint> Texturen;

void ladeTextur(std::string filename) {
	// Lade das Bild in das Objekt image
	Image* myImage = loadBMP(filename.c_str());
	GLuint textureNr = 0;
	// Lege das Bild als Textur an.
	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &textureNr);
	glBindTexture(GL_TEXTURE_2D, textureNr);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, myImage->width, myImage->height, 0,
	GL_RGB, GL_UNSIGNED_BYTE, myImage->pixels);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //GL_NEAREST);//
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	Texturen[filename] = textureNr;
	std::cout << "Bild '" << filename << "' geladen, ist jetzt Textur Nr. "
			<< Texturen[filename] << std::endl;
}

int main(int argc, char*argv[]) {
	glutInit(&argc, argv); //Generiere das OpenGL-Fenster
	glutInitWindowSize(800, 600);
	glutCreateWindow("JumpNRunGame");


	glutDisplayFunc(display); //Verweise auf die Funktion display, die die Anzeige erledigt.

	glutKeyboardFunc(tasteDruck); //Benutzereingaben
	glutKeyboardUpFunc(tasteLos); //Benutzereingaben

	glutIdleFunc(timerEvent); //Animationen

	ladeTextur("src/figur.bmp");
	figur = new Figur(0, 0, Texturen["figur.bmp"]);


	glutMainLoop(); //Hauptschleife

}



void tasteDruck(unsigned char key, int, int) {
	//TODO tasteDruck
}
void tasteLos(unsigned char key, int, int) {
	//TODO tasteLos
}

void display() {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	//TODO display()


	glFlush();
}

void timerEvent() {
	int zeitneu = glutGet(GLUT_ELAPSED_TIME);
	int zeitdiff = zeitneu - zeit;
	if (zeitdiff > 16) {

		//TODO TimerEvent ("echter" Code)

		zeit = zeitneu;
		glutPostRedisplay();
	}
}

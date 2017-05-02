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
#include "Figur.h"
#include "Hintergrund.h"
#include "HindernisStufe.h"
#include "LadeTexturPNG.h"


using namespace std;

void display();
void timerEvent();
void tasteDruck(unsigned char key, int, int);
void tasteLos(unsigned char key, int, int);

int zeit = 0;
Figur* figur;
Hintergrund* hintergrund;
Hindernis_Stufe* einfachesHindernis;

std::map<std::string, GLuint> Texturen;


int main(int argc, char*argv[]) {
	glutInit(&argc, argv); //Generiere das OpenGL-Fenster
	glutInitWindowSize(800, 600);
	glutCreateWindow("JumpNRunGame");


	glutDisplayFunc(display); //Verweise auf die Funktion display, die die Anzeige erledigt.

	glutKeyboardFunc(tasteDruck); //Benutzereingaben
	glutKeyboardUpFunc(tasteLos); //Benutzereingaben

	glutIdleFunc(timerEvent); //Animationen

	Texturen["src/Hintergrund.png"] = LadeTexturPNG("src/Hintergrund.png");
	hintergrund = new Hintergrund(-1, -1, Texturen["src/Hintergrund.png"]);

	Texturen["src/figur.png"] = LadeTexturPNG("src/figur.png");
	figur = new Figur(-0.5, -0.9, 0.6, Texturen["src/figur.png"]);

	Texturen["src/Hindernins_einfach.png"] = LadeTexturPNG("src/Hindernis_einfach.png");
	einfachesHindernis = new Hindernis_Stufe(0.5,0,3,Texturen["src/Hindernins_einfach.png"]);

	glutMainLoop(); //Hauptschleife

}



void tasteDruck(unsigned char key, int, int) {

	switch (key) {
	case 'q':
		exit(0);
	default:
		figur->tasteDruck(key);
		break;
	}
}
void tasteLos(unsigned char key, int, int) {
	switch (key) {
	//eigene TasteLos-Ereignisse
	default:
		figur->tasteLos(key);
		break;
	}
}

void display() {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	//TODO display()
	hintergrund->Display();
	figur->Display();


	glFlush();
}

void timerEvent() {
	int zeitneu = glutGet(GLUT_ELAPSED_TIME);
	int zeitdiff = zeitneu - zeit;
	if (zeitdiff > 16) {

		//TODO TimerEvent ("echter" Code, der 60 Mal pro Sekunde ausgeführt wird)
		figur->move(zeitdiff);

		zeit = zeitneu;
		glutPostRedisplay();
	}
}

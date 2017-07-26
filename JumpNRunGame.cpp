//============================================================================
// Name        : JumpNRunGame.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <GL/glut.h>
#include <iostream>
#include <map>
#include "Figur.h"
#include "Hintergrund.h"
#include "HindernisStufe.h"
#include "LadeTexturPNG.h"
#include "HindernisTreppe.h"
#include "Rechteckklein.h"
#include "StehendesRechteck.h"
#include "Boden.h"
#include "GameOver.h"

using namespace std;

void display();
void timerEvent();
void tasteDruck(unsigned char key, int, int);
void tasteLos(unsigned char key, int, int);
void seedrand();
void newHindernis();
void gameOver();
void initGame();

bool vargameOver = false;
int zeit = 0;
Figur* figur;
Hintergrund* hintergrund;
Boden* boden;
GameOver* gameOverScreen;

double naechstesHindernis;



std::vector<Hindernisse*> hindernisse;

std::map<std::string, GLuint> Texturen;


int main(int argc, char*argv[]) {


	seedrand(); //Initialisiere die Random-Funktion

	glutInit(&argc, argv); //Generiere das OpenGL-Fenster
	glutInitWindowSize(800, 600);
	glutCreateWindow("JumpNRunGame");


	glutDisplayFunc(display); //Verweise auf die Funktion display, die die Anzeige erledigt.

	glutIgnoreKeyRepeat(1);
	glutKeyboardFunc(tasteDruck); //Benutzereingaben
	glutKeyboardUpFunc(tasteLos); //Benutzereingaben

	glutIdleFunc(timerEvent); //Animationen

	Texturen["src/Hintergrund.png"] = LadeTexturPNG("src/Hintergrund.png");
	Texturen["src/Boden.png"] = LadeTexturPNG("src/Boden.png");

	Texturen["src/figur.png"] = LadeTexturPNG("src/figur.png");

	Texturen["src/Hindernins_einfach.png"] = LadeTexturPNG("src/Hindernis_einfach.png");
	Texturen["src/Treppe.png"] = LadeTexturPNG("src/Treppe.png");
	Texturen["src/Rechteckklein.png"] = LadeTexturPNG("src/Rechteckklein.png");
	Texturen["src/StehendesRechteck.png"] = LadeTexturPNG("src/StehendesRechteck.png");

	Texturen["src/GameOver.png"] = LadeTexturPNG("src/GameOver.png");

	initGame();

	glutMainLoop(); //Hauptschleife

}

void tasteDruck(unsigned char key, int, int) {

	if (key == 'q') {
		exit(0);
	}

	if (vargameOver) {
		initGame();
		return;
	}

	figur->tasteDruck(key);

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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	hintergrund->Display();
	boden->Display();

	glPushMatrix();
	glTranslatef(figur->kameraposx, figur->kameraposy, 0);


	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	figur->Display();

	for (uint i = hindernisse.size(); i > 0; i--){
		hindernisse[i-1]->Display();
	}

	glDisable(GL_BLEND);

	glPopMatrix();

	if (vargameOver) {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		gameOverScreen->Display();

		glDisable(GL_BLEND);
	}

	glFlush();



}

void aufKollisionenPrüfen() {
	bool vonOben = false;
	bool vonUnten = false;
	bool vonLinks = false;
	bool vonRechts = false;
	for (uint i = hindernisse.size(); i > 0; i--) {
		Hindernisse::Kollision kollidiert = hindernisse[i - 1]->collision(figur);
		switch (kollidiert) {
		case Hindernisse::VON_OBEN:
			vonOben = true;
			break;
		case Hindernisse::VON_UNTEN:
			vonUnten = true;
			break;
		case Hindernisse::VON_LINKS:
			vonLinks = true;
			break;
		case Hindernisse::VON_RECHTS:
			vonRechts = true;
			break;
		default:
			break;
		}
	}

	if (vonOben) {
		figur->springen();
	} else if (vonUnten) {
		// TODO Was soll passieren, wenn die Figur von unten an ein Hindernis springt?
		// Abprallen oder sterben?
	} else if (vonLinks) {
		gameOver();
	} else if (vonRechts) {
		gameOver();
	}
}

void timerEvent() {
	int zeitneu = glutGet(GLUT_ELAPSED_TIME);
	int zeitdiff = zeitneu - zeit;
	if (zeitdiff > 16 && !vargameOver) {

		figur->move(zeitdiff);
		newHindernis();

		aufKollisionenPrüfen();

		zeit = zeitneu;
		glutPostRedisplay();
	}
}

void seedrand() {
	time_t t;
	time(&t);
	srand((unsigned int) (t));
}

void newHindernis() {
	//static bedeutet, dass die Variable am Anfang des Programms einmal initialisiert wird
	//und dann ihren Wert "behält"

	double x = figur->getx();

	if (x > naechstesHindernis) {
		switch (rand() % 4) {
		case 0:
			hindernisse.push_back(new Hindernis_Stufe(x + 1, -0.9, 1,
					Texturen["src/Hindernins_einfach.png"]));
			break;
		case 1:
			hindernisse.push_back(
					new HindernisTreppe(x + 1, -0.9, 1,
							Texturen["src/Treppe.png"]));
			break;

		case 2:
			hindernisse.push_back(
					new Rechteckklein(x+1, -0.9, 1,
							Texturen["src/Rechteckklein.png"]));
			break;
		case 3:
			hindernisse.push_back(
					new StehendesRechteck(x+1, -0.9, 1,
							Texturen["src/StehendesRechteck.png"]));
			break;
		}

		//Das naechste Hindernis ist mindestens 1.5 entfernt;
		//dazu wird noch eine zufaellige Zahl von 0 bis 1 addiert
		naechstesHindernis = x + 1.5 + (rand()%100)/100;
	}
}

void initGame() {
	zeit = 0;
	hindernisse.clear();
	hintergrund = new Hintergrund(-1, -1, Texturen["src/Hintergrund.png"]);
	boden= new Boden(-1, -1, Texturen["src/Boden.png"]);
	figur = new Figur(-0.5, -0.9, 0.6, Texturen["src/figur.png"]);
	naechstesHindernis = 0;
	vargameOver = false;


	glutPostRedisplay();
}

void gameOver() {
	vargameOver = true;
	gameOverScreen = new GameOver(Texturen["src/GameOver.png"]);//TODO Fehler wegen fehlendem Bild

	glutPostRedisplay();
}

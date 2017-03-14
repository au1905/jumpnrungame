//============================================================================
// Name        : JumpNRunGame.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include<GL/glut.h>

using namespace std;

void display();
void timerEvent();
void tasteDruck(unsigned char key, int, int);
void tasteLos(unsigned char key, int, int);

int zeit = 0;

int main(int argc, char*argv[]) {
	glutInit(&argc, argv); //Generiere das OpenGL-Fenster
	glutInitWindowSize(800, 600);
	glutCreateWindow("JumpNRunGame");


	glutDisplayFunc(display); //Verweise auf die Funktion display, die die Anzeige erledigt.

	glutKeyboardFunc(tasteDruck); //Benutzereingaben
	glutKeyboardUpFunc(tasteLos); //Benutzereingaben

	glutIdleFunc(timerEvent); //Animationen

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

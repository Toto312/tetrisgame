#include "pch.h"
#include <iostream>

#include <GL/glut.h>


#define MOVE(x) 12 + 24 * (x)
#define LOW_COORDENADE 12
#define MAX_COORDENADE 492


enum Color {RED, GREEN, BLUE};

struct Point {
	int x, y;
	Color color;
};

int others[] = { 0, 0, 0, 0, 0, 0 };

float playerX = MOVE(10);
float playerY = MOVE(20);

float gravity = 0;


Color playerColor = RED;

int otherY = 12 + 24 * 0; // cambiar el 3er numero para moverlo
int otherX = 12 + 24 * 0;

void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}


void resize(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, 0, h);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPointSize(20.0);

	glPushMatrix();
	glBegin(GL_POINTS);
	if (playerColor == RED)
	{
		glColor3f(1.0, 0.0, 0.0);
	}
	glVertex2i(playerX, playerY);
	
	glColor3f(0.0, 1.0, 0.0);
	glVertex2i(others[0], others[1]);

	glEnd();
	glPopMatrix();

	glutSwapBuffers();


	//-----------------------------------------------
	//             Gravity Options					|	
	//-----------------------------------------------


	if (playerY > LOW_COORDENADE)
	{
		gravity += 0.005;
	}
	else {
		gravity = 0;
	}

	if (gravity >= 1 && playerY > LOW_COORDENADE)
	{
		if (!(others[0] == playerX && others[1] == playerY - 24))
		{
			playerY -= 24;
			gravity = 0;
		}
	}

	std::cout << "Value of gravity: " << gravity << std::endl; 
}

void specialKeys(int key, int x, int y)
{
	switch (key) {
	/*case GLUT_KEY_UP:
		if (playerY < 492) playerY += 24;
		std::cout << "Apretaste up" << std::endl;
		break;*/
	case GLUT_KEY_DOWN:	
		if (playerY != LOW_COORDENADE)
		{
			if (!(others[0] == playerX - 24 && others[1] == playerY - 24))
			{
				playerY -= 24;
			}
		}
		break;
	case GLUT_KEY_RIGHT:
		if (playerY != LOW_COORDENADE) {
			if (!(others[0] == playerX - 24 && others[1] == playerY - 24))
			{
				playerX += 24;
			}
		}
		break;
	case GLUT_KEY_LEFT:
		if (playerY != LOW_COORDENADE) {
			if (!(others[0] == playerX - 24 && others[1] == playerY - 24))
			{
				 playerX -= 24;
			}
		}
		break;
	}
}

void Timer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(1, Timer, 0);
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 114:
		playerY = MOVE(20);
		playerX = MOVE(10);
		break;
	}
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(506, 506);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("OpenGL Tetris");

	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutSpecialFunc(specialKeys);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(0, Timer, 0);

	init();
	others[0] = MOVE(10);
	others[1] = MOVE(0);

	glutMainLoop();
	return 0;
}

//Inlcudes
#include <iostream>
#include <GL/glut.h>


//Definitions
#define MOVE(x) 12 + 24 * (x)
#define LOW_COORDENADE 12
#define MAX_COORDENADE 492


//Point options
enum Color { RED, GREEN, BLUE };

//Point struct
struct Point {
	int x, y;
	Color color;
} player;

//Other points. The first variable is the value of x, and the second is y. The third variable is x, and the fourth variable is y, etc.
int others[] = { 0, 0, 0, 0, 0, 0 };

//variables for other poinbts
int otherY = MOVE(0); // cambiar el 3er numero para moverlo
int otherX = MOVE(0);

//world options
float gravity = 0;

void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	//playerInit
	player.x = MOVE(10);
	player.y = MOVE(20);
	player.color = RED;

	//Others init
	others[0] = MOVE(10);
	others[1] = MOVE(0);
}

//OpenGL options
void resize(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, 0, h);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

//Render function
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPointSize(20.0);

	glPushMatrix();
	glBegin(GL_POINTS);
	if (player.color == RED)
	{
		glColor3f(1.0, 0.0, 0.0);
	}
	glVertex2i(player.x, player.y);

	glColor3f(0.0, 1.0, 0.0);
	glVertex2i(others[0], others[1]);

	glEnd();
	glPopMatrix();

	glutSwapBuffers();


	//-----------------------------------------------
	//             Gravity Options					|	
	//-----------------------------------------------


	if (player.y > LOW_COORDENADE)
	{
		gravity += 0.001;
	}
	else {
		gravity = 0;
	}

	if (gravity >= 1 && player.y > LOW_COORDENADE)
	{
		if (!(others[0] == player.x && others[1] == player.y - 24))
		{
			player.y -= 24;
			gravity = 0;
		}
	}

	std::cout << "Value of gravity: " << gravity << std::endl;
}

//Keys for input the keyboard
void specialKeys(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_DOWN:
		if (player.y != LOW_COORDENADE)
		{
			if (!(others[0] == player.x - 24 && others[1] == player.y - 24))
			{
				player.y -= 24;
			}
		}
		break;
	case GLUT_KEY_RIGHT:
		if (player.y != LOW_COORDENADE) {
			if (!(others[0] == player.x - 24 && others[1] == player.y - 24))
			{
				player.x += 24;
			}
		}
		break;
	case GLUT_KEY_LEFT:
		if (player.y != LOW_COORDENADE) {
			if (!(others[0] == player.x - 24 && others[1] == player.y - 24))
			{
				player.x -= 24;
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
	//Is the value ascii of "r". This means that if the player input the letter "r", the point is going to reset its position
	case 114:
		player.y = MOVE(20);
		player.x = MOVE(10);
		break;
	}
}


//The main function of the program
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

	glutMainLoop();
	return 0;
}

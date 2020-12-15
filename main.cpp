//Inlcudes
#include <iostream>
#include <GL/glut.h>


//Definitions
#define MOVE(x) 12 + 24 * (x)
#define LOW_COORDENADE 12
#define MAX_COORDENADE 492


//Point options
enum Color { RED, GREEN, BLUE };

struct Position2D {
	int x, y;
};

//Point struct
struct Point {
	Position2D pos;
	Color color;
	Position2D lastMove;
} player;

Point others1[3];

//variables for other poinbts
int otherY;
int otherX;

//world options
float gravityScale = 0;

/*This function is used to override the "gravity" of the game. 
This is so that, when gravity lowers a block to the point, it does not lower more if the player presses the down button at that precise moment.*/
bool playerShouldUseBottonDown;


void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	//---------------------------------------------------------------
	//|                      Funciones del juego			|
	//---------------------------------------------------------------



	//init map
	/*int map[50][20] = {
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};*/


	int playerInit_x = 10;
	int playerInit_y = 20;
	player.lastMove.x = playerInit_x;
	player.lastMove.y = playerInit_y;



	int othersInit_x = 10;
	int othersInit_y = 0;
	others1[0].lastMove.x = othersInit_x;
	others1[0].lastMove.y = othersInit_y;

	//playerInit
	player.pos.x = MOVE(playerInit_x);
	player.pos.y = MOVE(playerInit_y);
	player.color = RED;

	//Others init
	others1[0].pos.x = MOVE(othersInit_x);
	others1[0].pos.y = MOVE(othersInit_y);
	others1[0].color = GREEN;

	/*map[playerInit_y][playerInit_x] = 1;
	map[othersInit_y][othersInit_x] = 1;*/

	playerShouldUseBottonDown = true;

}



void gravityWrld()
{
	if (player.pos.y > LOW_COORDENADE)
	{
		gravityScale += 0.001;
	}
	else {
		gravityScale = 0;
	}

	if (gravityScale >= 1 && player.pos.y > LOW_COORDENADE && playerShouldUseBottonDown)
	{
		if (!(others1[0].pos.x == player.pos.x && others1[0].pos.y == player.pos.y - 24))
		{
			playerShouldUseBottonDown = false;
			player.pos.y -= 24;
			gravityScale = 0;
		}
	}

	playerShouldUseBottonDown = true;
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

	//set the color
	if (player.color == RED)
	{
		glColor3f(1.0, 0.0, 0.0);
	}

	//set the position of the player point
	glVertex2i(player.pos.x, player.pos.y);

	//set color and position of other block
	glColor3f(0.0, 1.0, 0.0);
	glVertex2i(others1[0].pos.x, others1[0].pos.y);
	glEnd();
	glPopMatrix();

	glutSwapBuffers();


	//-----------------------------------------------
	//             Gravity Options			|	
	//-----------------------------------------------


	gravityWrld();

	//map[][]
}

//Keys for input the keyboard
void specialKeys(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_DOWN:
		if (player.pos.y != LOW_COORDENADE && playerShouldUseBottonDown)
		{
			if (!(others1[0].pos.x == player.pos.x - 24 && others1[0].pos.y == player.pos.y - 24))
			{
				player.pos.y -= 24;
			}
		}
		break;
	case GLUT_KEY_RIGHT:
		if (player.pos.y != LOW_COORDENADE) {
			if (!(others1[0].pos.x == player.pos.x - 24 && others1[0].pos.y == player.pos.y - 24))
			{
				player.pos.x += 24;
			}
		}
		break;
	case GLUT_KEY_LEFT:
		if (player.pos.y != LOW_COORDENADE) {
			if (!(others1[0].pos.x == player.pos.x - 24 && others1[0].pos.y == player.pos.y - 24))
			{
				player.pos.x -= 24;
			}
		}
		break;
	}

}

//The OpenGL keyboard
void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	//Is the value ascii of "r". This means that if the player input the letter "r", the point is going to reset its position
	case 114:
		player.pos.y = MOVE(20);
		player.pos.x = MOVE(10);
		break;
	}
}

//the OpenGL resize
void resize(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, 0, h);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

//the OpenGL timer
void Timer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(1, Timer, 0);
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

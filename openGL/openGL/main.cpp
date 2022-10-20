// Bryan King Schilhab
// Assignment 5
// 07/03/2022
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>
#include <fstream>

void Init(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0f, 0.0f, 0.0f);
	glPointSize(4.0);
	glLineWidth(2);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.5, 1.5, -2.5, 2.5, -3.5, 3.5);

}
void histogram() { 
	float bins[150] = {0};
	int binAmount = 150, input;
	float x = -0.97, overMax = 0;
	float dataMin = 1, dataMax = 15000;
	std::string line;
	float graphRange = dataMax - dataMin-1;
	float binRange = graphRange / binAmount;
	std::ifstream file;
	file.open("Bollywood.csv");

	for (int k = 0; k < binAmount; k++) {
		while (file >> input) {
			dataMax = dataMin + binRange - 1;
			if (input >= dataMin && input <= dataMax) {
				bins[k]++;
				
			}
			if (k == 0 && input > 15000)
				overMax++;
		}
		file.clear();
		file.seekg(0, std::ios::beg);
		dataMin += binRange;
	}
	file.close();

	float height = 0.8, width = 0.005;
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);     // clear the screen 
	glColor3f(0.5f, 0.5f, 1.0f);

	for (int i = 0; i < 150; i++) {
		glPushMatrix();
		glTranslatef(x, -0.8, 0);
		glRectf(-width, -height+0.78, width, bins[i]/850);
		x += 0.013;
		glPopMatrix();
	}

	glPushMatrix();
	glTranslatef(x, -0.8, 0);
	glRectf(-width, -height + 0.78, width, overMax / 850);
	glPopMatrix();

	glEnd();
	glFlush();
	glutPostRedisplay();
}
//<<<<<<<<<<<<<<<<<<<<<<<< myKeyboard >>>>>>>>>>>>>>
void keyboard(unsigned char theKey, int mouseX, int mouseY)
{

	switch (theKey)
	{

	case 'Q':
	case 'q':
		exit(0); //terminate the program
	default:
		break;
	}
}
//<<<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>
int	 main(int argc, char** argv)
{
	glutInit(&argc, argv);          // initialize the toolkit
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH); // display with depth for 3d
	glutInitWindowSize(800, 800);     // set window size to 800x800
	glutCreateWindow("Assignment05 - Bryan King Schilhab"); // open the screen window 
	histogram();			// sets a default triangle before anything is pressed
	glutKeyboardFunc(keyboard); // set shapes
	Init(); //initialization settings
	glutMainLoop(); 		     // go into a perpetual loop
}
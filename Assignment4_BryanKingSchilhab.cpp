// Bryan King Schilhab
// Assignment 3
// 11/18/2021
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#pragma warning(disable:4996)

int n;
int m;
float s;
int n1;
int m1;
float s1;
GLuint* pgmImage;
GLuint* image;
GLuint texture;
GLuint textureLoader(const char* fileName);
#define checkImageWidth 64
#define checkImageHeight 64
static GLubyte checkerboard[checkImageHeight][checkImageWidth][4];

void makeCheckerboard(void)
{
	int i, j, c;

	for (i = 0; i < checkImageHeight; i++) {
		for (j = 0; j < checkImageWidth; j++) {
			c = ((((i & 0x8) == 0) ^ ((j & 0x8)) == 0)) * 255;
			checkerboard[i][j][0] = (GLubyte)c;
			checkerboard[i][j][1] = (GLubyte)c;
			checkerboard[i][j][2] = (GLubyte)c;
			checkerboard[i][j][3] = (GLubyte)255;
		}
	}
}
void triangle() {
	glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_TRIANGLES); // makes a triangle
	glTexCoord2f(0.5, 1);
	glVertex3f(0, 0.7, 0);      // 3 points all centered to a triangle
	glTexCoord2f(1, 0.0f);
	glVertex3f(0.8, -0.7, 0);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.8, -0.7, 0);
	glFlush();
	glEnd();
	glutSwapBuffers();
}
void square(float length) {
	glBindTexture(GL_TEXTURE_2D, texture);
	glNormal3f(0.0, 0.0, 1.0);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, 1);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-length, -length, 0);
	glTexCoord2f(1, 0.0f);
	glVertex3f(length, -length, 0);
	glTexCoord2f(1, 1);
	glVertex3f(length, length, 0);
	glTexCoord2f(0.0f, 1);
	glVertex3f(-length, length, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glFlush();
	glEnd();
	glutSwapBuffers();	
}
void ngon(int size, float R, float G, float B, float radius) {
	glBindTexture(GL_TEXTURE_2D, texture);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	int sides;
	sides = size; // the amount of triangles amounting to shape
	float xPos, yPos, angle;
	xPos = 0; yPos = 0; angle = 3.1415926 * 2.f / sides;// seting default x and y setting radius to 1.5														   // the radius to 1.5 and the angle equation

	glBegin(GL_TRIANGLES);
	float xPrev, yPrev;
	xPrev = xPos; yPrev = yPos - radius; //previous triangles for 2nd point
	for (int i = 0; i <= sides; i++) {
		glTexCoord2f(0.0f, 0.0f);
		float newX, newY;
		newX = radius * sin(angle * i); // formuala to find next X and Y with appropiate distance
		newY = -radius * cos(angle * i);
		glTexCoord2f(0.5f, 0.5f); // texture coordinate at center
		glVertex3f(0, 0, 0); // center first point
		glTexCoord2f(xPrev + 0.5, yPrev + 0.5);
		glVertex3f(xPrev, yPrev, 0); //2nd point
		glTexCoord2f(newX +0.5, newY + 0.5);
		glVertex3f(newX , newY , 0); // 3rd new point
		xPrev = newX;
		yPrev = newY;
	}
	glEnd();
	glutSwapBuffers();
}
void cube(float length) {
	float pos = length / 2;
	glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_QUADS); // found works best for this shape
	// bottom
	glNormal3f(0.0, -1.0, 0.0);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(pos, -pos, -pos);
	glTexCoord2f(1, 0.0f);
	glVertex3f(-pos, -pos, -pos);
	glTexCoord2f(1, 1);
	glVertex3f(-pos, -pos, pos);
	glTexCoord2f(0.0f, 1);
	glVertex3f(pos, -pos, pos);

	//back
	glNormal3f(0.0, 0.0, -1.0);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-pos, pos, -pos);
	glTexCoord2f(1, 0.0f);
	glVertex3f(-pos, -pos, -pos);
	glTexCoord2f(1, 1);
	glVertex3f(pos, -pos, -pos);
	glTexCoord2f(0.0f, 1);
	glVertex3f(pos, pos, -pos);

	// right
	glNormal3f(1.0, 0.0, 0.0);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(pos, pos, -pos);
	glTexCoord2f(1, 0.0f);
	glVertex3f(pos, pos, pos);
	glTexCoord2f(1, 1);
	glVertex3f(pos, -pos, pos);
	glTexCoord2f(0.0f, 1);
	glVertex3f(pos, -pos, -pos);

	// left
	glNormal3f(-1.0, 0.0, 0.0);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-pos, pos, pos);
	glTexCoord2f(1, 0.0f);
	glVertex3f(-pos, pos, -pos);
	glTexCoord2f(1, 1);
	glVertex3f(-pos, -pos, -pos);
	glTexCoord2f(0.0f, 1);
	glVertex3f(-pos, -pos, pos);

	 //front
	glNormal3f(0.0, 0.0, 1.0);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(pos, pos, pos);
	glTexCoord2f(1, 0.0f);
	glVertex3f(pos, -pos, pos);
	glTexCoord2f(1, 1);
	glVertex3f(-pos, -pos, pos);
	glTexCoord2f(0.0f, 1);
	glVertex3f(-pos, pos, pos);

	// top 
	glNormal3f(0.0, 1.0, 0.0);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(pos, pos, pos);
	glTexCoord2f(1, 0.0f);
	glVertex3f(-pos, pos, pos);
	glTexCoord2f(1, 1);
	glVertex3f(-pos, pos, -pos);
	glTexCoord2f(0.0f, 1);
	glVertex3f(pos, pos, -pos);
	glEnd();
	glutSwapBuffers();
}
void sphere() {
	glBindTexture(GL_TEXTURE_2D, texture);
	glShadeModel(GL_FLAT);
	int  color = 0;
	float PI = atan(1.0) * 4.0;
	float a, b, x, y, z;
	float da = 6.0, db = 6.0;
	float radius = 1.0;

	for (a = -90.0; a + da <= 90.0; a += da) {

		glBegin(GL_QUAD_STRIP);
		for (b = 0.0; b <= 360.0; b += db) {
			x = radius * cos(b * PI / 180) * cos(a * PI / 180);
			y = radius * sin(b * PI / 180) * cos(a * PI / 180);
			z = radius * sin(a * PI / 180);
			glNormal3f(x, y, z);
			glTexCoord2f(x, y);
			glVertex3f(x, y, z);
			x = radius * cos(b * PI / 180) * cos((a + da) * PI / 180);
			y = radius * sin(b * PI / 180) * cos((a + da) * PI / 180);
			z = radius * sin((a + da) * PI / 180);
			glNormal3f(x, y, z);
			glTexCoord2f(x, y);
			glVertex3f(x, y, z);
			color = 1 - color;
		}

		glEnd();
	}
	glFlush();
}
void background() {
	float len = 2, dep = 1.5;
	glBindTexture(GL_TEXTURE_2D, texture);
	glShadeModel(GL_SMOOTH);
	glBegin(GL_POLYGON); // back
	glNormal3f(0.0, 0.0, -1.0);
	glTexCoord2f(1, 1);
	glVertex3f(len, len, -dep);
	glTexCoord2f(1, 0.0f);
	glVertex3f(len, -len, -dep);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-len, -len, -dep);
	glTexCoord2f(0.0f, 1);
	glVertex3f(-len, len, -dep);
	glEnd();
	glBegin(GL_POLYGON); // right
	glNormal3f(1.0, 0.0, 0.0);
	glTexCoord2f(1, 1);
	glVertex3f(len, len, -dep);
	glTexCoord2f(1, 0.0f);
	glVertex3f(len, len, dep);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(len, -len, dep);
	glTexCoord2f(0.0f, 1);
	glVertex3f(len, -len, -dep);
	glEnd();
	glBegin(GL_POLYGON); // left
	glNormal3f(-1.0, 0.0, 0.0);
	glTexCoord2f(1, 1);
	glVertex3f(-len, len, -dep);
	glTexCoord2f(1, 0.0f);
	glVertex3f(-len, -len, -dep);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-len, -len, dep);
	glTexCoord2f(0.0f, 1);
	glVertex3f(-len, len, dep);
	glEnd();
	glBegin(GL_POLYGON);// top
	glNormal3f(0.0, 1.0, 0.0);
	glTexCoord2f(1, 1);
	glVertex3f(len, len, -dep);
	glTexCoord2f(1, 0.0f);
	glVertex3f(len, len, dep);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-len, len, dep);
	glTexCoord2f(0.0f, 1);
	glVertex3f(-len, len, -dep);

	glEnd();
	glBegin(GL_POLYGON);// bottom
	glColor3f(0.0f, 0.0f, 0.0f);
	glNormal3f(0.0, -1.0, 0.0);
	glTexCoord2f(1, 1);
	glVertex3f(-len, -len, -dep);
	glTexCoord2f(1, 0.0f);
	glVertex3f(len, -len, -dep);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(len, -len, dep);
	glTexCoord2f(0.0f, 1);
	glVertex3f(-len, -len, dep);
	glEnd();
	glutSwapBuffers();
}
void cylinder(float radius, float height, GLubyte R, GLubyte G, GLubyte B) {
	glBindTexture(GL_TEXTURE_2D, texture);
	float res = 0.05, x = 0, y = 0, pi = 3.1415926;
	glBegin(GL_QUAD_STRIP);
	float angle = 0.0;
	while (angle < 2 * pi) {
		x = radius * cos(angle);
		y = radius * sin(angle);
		glNormal3f(x, y, 0.0);
		glTexCoord2f(angle/(2*pi), 1);
		glVertex3f(x, y, height);
		glTexCoord2f(angle/(2*pi), 0);
		glVertex3f(x, y, 0.0);
		angle = angle + res;
	}
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(radius, 0.0, height);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(radius, 0.0, 0.0);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_POLYGON);
	angle = 0.0;
	while (angle < 2 * pi) {
		x = radius * cos(angle);
		y = radius * sin(angle);
		glTexCoord2f(x+0.5, y + 0.5);
		glVertex3f(x, y, height);
		angle = angle + res;
	}
	glVertex3f(radius, 0.0, height);
	glEnd();
}
void keyboard(unsigned char theKey, int mouseX, int mouseY)
{

	switch (theKey) // our switch function that contains all the shapes
	{
	case 'Q':
	case 'q':
		exit(0); //terminate the program
	default:
		break;
	}
}
GLuint textureLoader(const char* fileName) {
	FILE* fd;
	int  k, nm;
	char c;
	int i;
	char b[100];

	int red, green, blue;

	//printf("enter file name\n");
	//scanf("%s", b);
	fd = fopen(fileName, "r");
	fscanf(fd, "%[^\n] ", b);
	if (b[0] != 'P' || b[1] != '3')
	{
		printf("%s is not a PPM file!\n", b);
		exit(0);
	}
	printf("%s is a PPM file\n", b);
	fscanf(fd, "%c", &c);
	while (c == '#')
	{
		fscanf(fd, "%[^\n] ", b);
		printf("%s\n", b);
		fscanf(fd, "%c", &c);
	}
	ungetc(c, fd);
	fscanf(fd, "%d %d %d", &n, &m, &k);

	printf("%d rows  %d columns  max value= %d\n", n, m, k);

	nm = n * m;

	image = (GLuint*)malloc(3 * sizeof(GLuint) * nm);


	s = 255. / k;

	for (i = 0; i < nm; i++)
	{
		fscanf(fd, "%d %d %d", &red, &green, &blue);
		image[3 * nm - 3 * i - 3] = red;
		image[3 * nm - 3 * i - 2] = green;
		image[3 * nm - 3 * i - 1] = blue;
	}
	
}

GLubyte pgmaLoader(const char* fileName) {
	FILE* fd;
	int  k, nm;
	char c;
	int i;
	char b[100];
	int grey;

	fd = fopen(fileName, "r");
	fscanf(fd, "%[^\n] ", b);
	if (b[0] != 'P' || b[1] != '2')
	{
		printf("%s is not a PGM file!\n", b);
		exit(0);
	}
	printf("%s is a PGM file\n", b);
	fscanf(fd, "%c", &c);
	while (c == '#')
	{
		fscanf(fd, "%[^\n] ", b);
		printf("%s\n", b);
		fscanf(fd, "%c", &c);
	}
	ungetc(c, fd);
	fscanf(fd, "%d %d %d", &n1, &m1, &k);

	printf("%d rows  %d columns  max value= %d\n", n1, m1, k);

	nm = n1 * m1;

	pgmImage = (GLuint*)malloc(1*sizeof(GLuint) * nm);

	s1 = 255. / k;

	for (i = 0; i < nm; i++)
	{
		fscanf(fd, "%d", &grey);
		pgmImage[i] = grey;
	}
}

void display(void) {
	glRasterPos3i(-1, -1,0);
	glDrawPixels(n, m, GL_RGB, GL_UNSIGNED_INT, image);
	glFlush();
	glPixelTransferf(GL_RED_SCALE, s);
	glPixelTransferf(GL_GREEN_SCALE, s);
	glPixelTransferf(GL_BLUE_SCALE, s);
	glPixelStorei(GL_UNPACK_SWAP_BYTES, GL_TRUE);
	printf("finished display \n");
}
void drawScene() {
	glPushMatrix();
	glRotatef(180, 0, 0, 1);
	glRotatef(-30, 0, 1, 0);
	glTranslatef(1, 1, 0);
	square(.3);
	glPopMatrix();

	const char* nextTexture = "slick.ppm";
	textureLoader(nextTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, n, m, 0, GL_RGB, GL_UNSIGNED_INT, image);
	glPushMatrix();
	glScalef(.5, .5, .5);
	glRotatef(50, 1, 1.4, 0);
	glTranslatef(-0.6, 1.2, 0);
	triangle();
	glPopMatrix();
	
	nextTexture = "eyes.ppm";
	textureLoader(nextTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, n, m, 0, GL_RGB, GL_UNSIGNED_INT, image);
	glNormal3f(0.0, 0.0, 1.0);
	glPushMatrix();
	glRotatef(30, 1, 1, 0);
	glTranslatef(-1.3, -0.2, 0);
	ngon(8, 0.3, 0.4, 1, 0.5);
	glPopMatrix();
	
	nextTexture = "yang.ppm";
	textureLoader(nextTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, n, m, 0, GL_RGB, GL_UNSIGNED_INT, image);
	glNormal3f(0.0, 0.0, 1.0);
	glPushMatrix();
	glScalef(.6, .6, 1);
	glRotatef(-8, 0, 1, 0);
	glTranslatef(2.5, -2, 0);
	ngon(40, 1, 0.2, 0.4, 0.5);
	glPopMatrix();

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, checkImageWidth, checkImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, checkerboard);
	glPushMatrix();
	glRotatef(40, 1, -.8, 0);
	glTranslatef(-1, 1, 0);
	cube(0.5);
	glPopMatrix();
	
	nextTexture = "barrel.ppm";
	textureLoader(nextTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, n, m, 0, GL_RGB, GL_UNSIGNED_INT, image);
	glPushMatrix();
	glRotatef(45, 1, 1, 0);
	glTranslatef(0.7, 1, 0);
	cylinder(0.4, 0.9, 255, 160, 100);
	glPopMatrix();
	
	nextTexture = "bronze.ppm";
	textureLoader(nextTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, n, m, 0, GL_RGB, GL_UNSIGNED_INT, image);
	glPushMatrix();
	glScalef(.5, .5, .5);
	glRotatef(20, 1, 1, 0);
	glTranslatef(1, -3, 0);
	sphere();
	glPopMatrix();
	
	nextTexture = "marble.ppm";
	textureLoader(nextTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, n, m, 0, GL_RGB, GL_UNSIGNED_INT, image);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	background();
	
	
}
void Init(void)
{
	
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	GLfloat qaDiffuseLight[] = { 1, 1, 1, 1.0 };
	GLfloat qaSpecularLight[] = { 0.99, 0.95, 0.86, 1.0 };
	GLfloat qaLightPosition[] = { 1.5, 1.5, 2, 1 }; // light at finite point
	glLightfv(GL_LIGHT0, GL_DIFFUSE, qaDiffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, qaSpecularLight);
	glLightfv(GL_LIGHT0, GL_POSITION, qaLightPosition);

	glEnable(GL_LIGHT1);
	GLfloat qaDiffuseLight1[] = { 1, 1, 1, 1.0 };
	GLfloat qaSpecularLight1[] = { 1.0, 0.77, 0.56, 1.0 };
	GLfloat qaLightPosition1[] = { 0, 1, 0, 0 }; // light at infinite point
	glLightfv(GL_LIGHT1, GL_DIFFUSE, qaDiffuseLight1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, qaSpecularLight1);
	glLightfv(GL_LIGHT1, GL_POSITION, qaLightPosition1);

	glEnable(GL_LIGHT2);
	GLfloat lightSpot[] = { -1.5, -0.5, 1,1 };
	GLfloat qaDiffuseLight2[] = { 0.9, 0.9, 0.9, 1.0 };
	GLfloat qaAmbientLight2[] = { 0.1, 0.1, 0.1, 1.0 };
	GLfloat qaSpecularLight2[] = { 1, 1, 1, 1.0 };
	GLfloat qaLightPosition2[] = { -1.7, 1.5, 0, 1.0f };
	glLightfv(GL_LIGHT2, GL_POSITION, qaLightPosition2);
	glLightfv(GL_LIGHT2, GL_AMBIENT, qaAmbientLight2);
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, lightSpot);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, qaDiffuseLight2);
	glLightfv(GL_LIGHT2, GL_SPECULAR, qaSpecularLight2);
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 99);
	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 1.0);
	glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 1);
	glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.9);
	glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, .9);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	//glDisable(GL_LIGHTING);

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glPointSize(6.0);
	glLineWidth(2);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_NORMALIZE);
	glPixelStorei(GL_UNPACK_SWAP_BYTES, GL_TRUE);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, 1080, 1080);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(65, 1, 2, 80);
	gluLookAt(0, 0, 4, 0, 0, 0, 0.0, 1.0, 0);

	
	makeCheckerboard();
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	const char* baboon = "baboon.pgm";
	pgmaLoader(baboon);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, n1, m1, 0, GL_LUMINANCE, GL_UNSIGNED_INT, pgmImage);
	drawScene();
	
}
int	 main(int argc, char** argv)
{
	
	glutInit(&argc, argv);          // initialize the toolkit
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GL_DEPTH); // display with depth for 3d
	glutInitWindowSize(1080, 1080);     // set window size
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Assignment03 - Bryan King Schilhab"); // open the screen window 

	Init(); //initialization settings
	glutKeyboardFunc(keyboard);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glutMainLoop(); 		     // go into a perpetual loop
}
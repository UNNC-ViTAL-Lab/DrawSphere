
#include "stdafx.h"
#include <GL/glut.h>
#include <stdlib.h>

static int year = 0, day = 0, moon = 0;

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);

	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 }; 
	GLfloat mat_shininess[] = { 50.0 }; 
	GLfloat light_position[] = { 3.0, 3.0, 3.0, 0.0 };
	GLfloat white_light[] = { 1.0, 1.0, 1.0, 1.0 };  
	GLfloat Light_Model_Ambient[] = { 0.8 , 0.2 , 0.2 , 1.0 }; 

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);  
	glLightfv(GL_LIGHT0, GL_SPECULAR, white_light); 
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, Light_Model_Ambient);  

	glEnable(GL_LIGHTING);  
	glEnable(GL_LIGHT0);    
	glEnable(GL_DEPTH_TEST); 

}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();
	glColor3f(1.0, 0.0, 0.0);
	glutSolidSphere(1.0, 20, 16); /* draw sun */

	glRotatef((GLfloat)year, 0.0, 1.0, 0.0);
	glTranslatef(2.0, 0.0, 0.0);
	glRotatef((GLfloat)day, 0.0, 1.0, 0.0);
	glColor3f(0.0, 0.0, 1.0);
	glutSolidSphere(0.3, 10, 8); /* draw earth */

	glTranslatef(1.0, 0.0, 0.0);
	glRotatef((GLfloat)moon, 0.0, 1.0, 0.0);
	glColor3f(1.0, 1.0, 1.0);
	glutSolidSphere(0.2, 10, 8); /* draw moon */
	glPopMatrix();
	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 5.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'd':
		day = (day + 10) % 360;
		moon = (moon + 5) % 360;
		glutPostRedisplay();
		break;
	case 'D':
		day = (day - 10) % 360;
		glutPostRedisplay();
		break;
	case 'y':
		year = (year + 5) % 360;
		day = (day + 10) % 360;
		moon = (moon + 5) % 360;
		glutPostRedisplay();
		break;
	case 'Y':
		year = (year - 5) % 360;
		glutPostRedisplay();
		break;
	case 'm':
		moon = (moon + 5) % 360;
		glutPostRedisplay();
		break;
	case 27:
		exit(0);
		break;
	default:
		break;
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}
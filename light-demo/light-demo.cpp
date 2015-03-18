/************************************************************************		
\link	www.twinklingstar.cn
\author Twinkling Star
\date	2015/02/03
\file	light-demo.cpp
****************************************************************************/
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")
#include <stdio.h>
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <gl\glaux.h>		// Header File For The Glaux Library


void drawSpherical(float x, float y, float z)
{
	static GLUquadricObj *quadratic = NULL;
	if( !quadratic )
		quadratic=gluNewQuadric();						// Create A Pointer To The Quadric Object (Return 0 If No Memory)
	gluQuadricNormals(quadratic, GLU_SMOOTH);			// Create Smooth Normals 

	//glEnable(GL_COLOR_MATERIAL);
	glPushAttrib(GL_ENABLE_BIT);
	glPushMatrix();
	//glColor3f(1.0f, 0.0f, 0.0f);
	glTranslatef(x, y, z);
		gluSphere(quadratic,1.3f,32,32);
	glPopMatrix();
	glPopAttrib();
}




void draw(void)
{
	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	glTranslatef(0.0f,0.0f,-5.0f);
	drawSpherical(0,0,0);
	glFlush();
}



void init()
{
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glEnable(GL_DEPTH_TEST);

	GLfloat LightSpeclar[]  =	{ 1.0f, 1.0f, 1.0f, 1.0f };	//镜面反射分量
	GLfloat LightAmbient[]	=	{ 0.1f, 0.1f, 0.1f, 1.0f };		//环境光分量
	GLfloat LightDiffuse[]	=	{ 0.7f, 0.7f, 0.7f, 1.0f };		//漫反射分量
	GLfloat LightPosition[]	=	{ 0.0f, 0.0f, 3.0f, 1.0f };		//光照的位置
	glLightfv(GL_LIGHT0, GL_SPECULAR, LightSpeclar);
	glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT0, GL_POSITION,LightPosition);

	GLfloat MaterialSpecular[]	= {0.508273f, 0.508273f, 0.508273f, 1.0f};
	GLfloat MaterialDiffuse[]	= {0.50754f, 0.50754f, 0.50754f, 1.0f};
	GLfloat MaterialAmbient[]	= {0.19225f, 0.19225f, 0.19225f, 1.0f};
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, MaterialSpecular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MaterialDiffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, MaterialAmbient);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 51.2f);

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);


}

void reshape(GLsizei w,GLsizei h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f,(float)w/(float)h,1.0f,1000.0f);

}

int main(int argc,char ** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(400,400);

	glutCreateWindow("light-demo");

	init();
	glutReshapeFunc(reshape);
	glutDisplayFunc(draw);

	glutMainLoop();
	return(0);
}
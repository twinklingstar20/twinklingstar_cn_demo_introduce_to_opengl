/************************************************************************		
\link	www.twinklingstar.cn
\author Twinkling Star
\date	2013/11/30
\file	texture-base-demo.cpp
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
#include "SrImageBmp.h"

SrImageBmp g_textureBMP(IMAGE_READ_ONLY);
unsigned int g_textureId;


void drawScene()
{
	//激活纹理
	glBindTexture(GL_TEXTURE_2D, g_textureId);
	//绘制一个正方体

	glBegin(GL_QUADS);
	// Front Face
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
	// Back Face
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
	// Top Face
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
	// Bottom Face
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
	// Right face
	glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
	// Left Face
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
	glEnd();
}


void draw(void)
{
	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear The Screen And The Depth Buffer
	glLoadIdentity();									// Reset The View
	glTranslatef(0.0f,0.0f,-5.0f);
	glRotatef(45.0f,1.0f,1.0f,1.0f);

	drawScene();

	glFlush();

}


void initTexture()
{
	unsigned char* data;

	int pixelCount,rgbType;

	if( !g_textureBMP.readFile("NeHe.bmp",data,pixelCount,rgbType) )
	{
		return;
	}
	int internalFormat,format;
	

	if( rgbType == IMAGE_RGB)
	{
		internalFormat = 3;
		format = GL_RGB;
	}
	else if( rgbType == IMAGE_RGBA )
	{
		internalFormat = 4;
		format = GL_RGBA;		
	}
	//生成纹理名字
	glGenTextures(1, &g_textureId);
	//绑定纹理
	glBindTexture(GL_TEXTURE_2D, g_textureId);
	//存储纹理数据到硬件内存中
	glTexImage2D(GL_TEXTURE_2D, 0, 3, g_textureBMP.getWidth(), g_textureBMP.getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	//设置纹理放大缩小时的过滤方法
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

}

void init()
{
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	initTexture();
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

	glutCreateWindow("texture-base-demo");

	init();
	glutReshapeFunc(reshape);
	glutDisplayFunc(draw);

	glutMainLoop();
	return(0);
}
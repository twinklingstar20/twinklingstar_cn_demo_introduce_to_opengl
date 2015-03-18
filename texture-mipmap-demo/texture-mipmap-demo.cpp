/************************************************************************		
\link	www.twinklingstar.cn
\author Twinkling Star
\date	2013/11/30
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

GLubyte mipmapImage512[512][512][4];
GLubyte mipmapImage256[256][256][4];
GLubyte mipmapImage128[128][128][4];
GLubyte mipmapImage64[64][64][4];
GLubyte mipmapImage32[32][32][4];
GLubyte mipmapImage16[16][16][4];
GLubyte mipmapImage8[8][8][4];
GLubyte mipmapImage4[4][4][4];
GLubyte mipmapImage2[2][2][4];
GLubyte mipmapImage1[1][1][4];

static GLuint texName;
int distance = -5.0f;

void makeImages(void)
{
	int i, j;
	for (i = 0; i < 512; i++) {
		for (j = 0; j < 512; j++) {
			mipmapImage512[i][j][0] = 255;
			mipmapImage512[i][j][1] = 255;
			mipmapImage512[i][j][2] = 255;
			mipmapImage512[i][j][3] = 255;
		}
	}

	for (i = 0; i < 256; i++) {
		for (j = 0; j < 256; j++) {
			mipmapImage256[i][j][0] = 255;
			mipmapImage256[i][j][1] = 0;
			mipmapImage256[i][j][2] = 0;
			mipmapImage256[i][j][3] = 255;
		}
	}

	for (i = 0; i < 128; i++) {
		for (j = 0; j < 128; j++) {
			mipmapImage128[i][j][0] = 0;
			mipmapImage128[i][j][1] = 255;
			mipmapImage128[i][j][2] = 0;
			mipmapImage128[i][j][3] = 255;
		}
	}

	for (i = 0; i < 64; i++) {
		for (j = 0; j < 64; j++) {
			mipmapImage64[i][j][0] = 0;
			mipmapImage64[i][j][1] = 0;
			mipmapImage64[i][j][2] = 255;
			mipmapImage64[i][j][3] = 255;
		}
	}

	for (i = 0; i < 32; i++) {
		for (j = 0; j < 32; j++) {
			mipmapImage32[i][j][0] = 255;
			mipmapImage32[i][j][1] = 255;
			mipmapImage32[i][j][2] = 0;
			mipmapImage32[i][j][3] = 255;
		}
	}
	for (i = 0; i < 16; i++) {
		for (j = 0; j < 16; j++) {
			mipmapImage16[i][j][0] = 255;
			mipmapImage16[i][j][1] = 0;
			mipmapImage16[i][j][2] = 255;
			mipmapImage16[i][j][3] = 255;
		}
	}
	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++) {
			mipmapImage8[i][j][0] = 255;
			mipmapImage8[i][j][1] = 0;
			mipmapImage8[i][j][2] = 0;
			mipmapImage8[i][j][3] = 255;
		}
	}
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			mipmapImage4[i][j][0] = 0;
			mipmapImage4[i][j][1] = 255;
			mipmapImage4[i][j][2] = 0;
			mipmapImage4[i][j][3] = 255;
		}
	}
	for (i = 0; i < 2; i++) {
		for (j = 0; j < 2; j++) {
			mipmapImage2[i][j][0] = 0;
			mipmapImage2[i][j][1] = 0;
			mipmapImage2[i][j][2] = 255;
			mipmapImage2[i][j][3] = 255;
		}
	}

	mipmapImage1[0][0][0] = 255;
	mipmapImage1[0][0][1] = 255;
	mipmapImage1[0][0][2] = 255;
	mipmapImage1[0][0][3] = 255;
}

void initTexture(void)
{    

	makeImages();
	//生成纹理名字
	glGenTextures(1, &texName);
	//将纹理名字与纹理绑定
	glBindTexture(GL_TEXTURE_2D, texName);
	//设置当纹理坐标超过1后，纹理在s,t方向上的模式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//设置纹理图像放大时，采用的过滤方法
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	//设置纹理图像缩小时，采用的过滤方法
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);

	//从0到9，指定了10个纹理细节层
	int level = 0;
	glTexImage2D(GL_TEXTURE_2D, level++, GL_RGBA, 512, 512, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, mipmapImage512);
	glTexImage2D(GL_TEXTURE_2D, level++, GL_RGBA, 256, 256, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, mipmapImage256);
	glTexImage2D(GL_TEXTURE_2D, level++, GL_RGBA, 128, 128, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, mipmapImage128);
	glTexImage2D(GL_TEXTURE_2D, level++, GL_RGBA, 64, 64, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, mipmapImage64);
	glTexImage2D(GL_TEXTURE_2D, level++, GL_RGBA, 32, 32, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, mipmapImage32);
	glTexImage2D(GL_TEXTURE_2D, level++, GL_RGBA, 16, 16, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, mipmapImage16);
	glTexImage2D(GL_TEXTURE_2D, level++, GL_RGBA, 8, 8, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, mipmapImage8);
	glTexImage2D(GL_TEXTURE_2D, level++, GL_RGBA, 4, 4, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, mipmapImage4);
	glTexImage2D(GL_TEXTURE_2D, level++, GL_RGBA, 2, 2, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, mipmapImage2);
	glTexImage2D(GL_TEXTURE_2D, level++, GL_RGBA, 1, 1, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, mipmapImage1);

	//激活二维纹理的使用
	glEnable(GL_TEXTURE_2D);
}

void drawScene()
{
	//激活纹理
	glBindTexture(GL_TEXTURE_2D, texName);
	//绘制一个正方形
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  0.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  0.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  0.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  0.0f);
	glEnd();
}

void draw(void)
{
	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0.0f,0.0f,distance);
	drawScene();
	glFlush();
}


void keyboards(unsigned char key, int x, int y) 
{
	switch (key) {
	  case 27:
		  exit(0);
		  break;
	  case ' ':
		  distance -= 2.0f;
		  glutPostRedisplay();
		  break;
	  default:
		  break;
	}
	
}

void init()
{
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glEnable(GL_DEPTH_TEST);
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

	glutCreateWindow("texture-mipmap-demo");

	init();
	glutReshapeFunc(reshape);
	glutDisplayFunc(draw);
	glutKeyboardFunc(keyboards);

	glutMainLoop();
	return(0);
}
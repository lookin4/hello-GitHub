#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<assert.h>
#include<windows.h>
#include<stdlib.h>
#include"glut.h"

BITMAPFILEHEADER bf;
BITMAPINFOHEADER bi;
struct RGB{
	unsigned char r, g, b;
};
RGB *pixels;

float bwidth;
float bheight;

void display(){
	glClearColor(0, 0, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(
		60,
		1,
		0.1,
		100);


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(
		0, 1, 1,//GLdouble eyex,eyey,eyez,
		0, 0, 0,//GLdouble centerx,centery,centerz,
		0, 1, 0);//GLdouble upx,upy, upz
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE_MODE);


	static float angle = 90;
	angle += 1;
	glRotatef(angle, 0, 1, 0);//GLfloat angle, GLfloat x, GLfloat y, GLfloat z

	glEnableClientState(GL_VERTEX_ARRAY);//GLenum array
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTranslatef(-0.5f, 0, -0.5f)

	static float width = 256;
	static float height = 256;
	static float *v = (float*)malloc(sizeof(float)*width*height * 3);
	static unsigned int z = 0;
	int count = 0;
	for (int i = 0; i < height; i++){
		for (int n = 0; n < width; n++){
			v[count] = 1 / (width - 1)*n;

			z = pixels[(int)(n + i*width)].r
				+ pixels[(int)(n + i*width)].g
				+ pixels[(int)(n + i*width)].b;

			float iro = z / 3.0f / 255.0f/3;
			v[count + 1] = iro;
			v[count + 2] = 1 / (height - 1)*i;
			count += 3;
		}
	}
	glVertexPointer(
		3,
		GL_FLOAT,
		0,
		v);//GLint size, GLenum type, GLsizei stride, const GLvoid *pointer

	glEnable(GL_TEXTURE_2D);
	static float *textu = (float*)malloc(sizeof(float)*width*height * 2);
	int tcount = 0;
	for (int i = 0; i < height; i++){
		for (int n = 0; n < width; n++){
			textu[tcount] = 1 / (width - 1)*n;
			textu[tcount + 1] = 1 / (height - 1)*i;
			tcount += 2;
		}
	}
	
	glTexCoordPointer(
		2,//GLint size, 
		GL_FLOAT,//GLenum type, 
		0,//GLsizei stride, 
		textu//const GLvoid *pointer
		);

	static unsigned short *indian = (unsigned short*)malloc(sizeof(unsigned short)*(width - 1)*(height - 1) * 6);
	
	int icount = 0;
	for (int i = 0; i < (height - 1); i++){
		for (int n = 0; n < (width - 1); n++){
			indian[icount] = n + (i*width);
			indian[icount + 1] = n + (i*width) + width;
			indian[icount + 2] = n + (i*width) + 1;
			indian[icount + 3] = n + (i*width) + 1;
			indian[icount + 4] = n + (i*width) + width;
			indian[icount + 5] = n + (i*width) + width + 1;
			icount += 6;
		}
	}
	
	glDrawElements(
		GL_TRIANGLES,
		(width - 1)*(height - 1) * 6,
		GL_UNSIGNED_SHORT,
		indian);//GLenum mode, GLsizei count, GLenum type, const GLvoid *indices



	glFlush();
}
void timer(int value){

	glutPostRedisplay();//Ä•`‰æ

	glutTimerFunc(
		1000 / 60,
		timer,
		0); //unsigned int millis, void (GLUTCALLBACK *func)(int value), int value
}


int main(int argc, char* argv[]){
	FILE *ppFile = fopen(
		"texture.bmp",
		"rb"
		);

	assert(ppFile != NULL);

	fread(
		&bf,
		sizeof(BITMAPFILEHEADER),
		1,
		ppFile);

	fread(
		&bi,
		sizeof(BITMAPINFOHEADER),
		1,
		ppFile);


	bwidth = bi.biWidth;
	bheight = bi.biHeight;

	int size = bi.biWidth * bi.biHeight * sizeof(RGB);
	pixels = (RGB*)malloc(size);
	fread(
		pixels,
		size,
		1,
		ppFile);
	for (int i = 0; i < bi.biWidth * bi.biHeight; i++){
		unsigned char temp = pixels[i].r;
		pixels[i].r = pixels[i].b;
		pixels[i].b = temp;
	}
	for (int i = 0; i < bi.biWidth; i++){
		for (int n = 0; n < bi.biHeight / 2; n++){
			RGB temp = pixels[bi.biWidth * n + i];
			pixels[bi.biWidth * n + i] = pixels[bi.biWidth*(bi.biHeight - n - 1) + i];
			pixels[bi.biWidth*(bi.biHeight - n - 1) + i] = temp;
		}
	}
	fclose(ppFile);

	glutInit(&argc, argv);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(display);//void (GLUTCALLBACK *func)(void)
	glTexImage2D(
		GL_TEXTURE_2D,    //GLenum target,
		0,                //GLint level,
		GL_RGB,           //GLint internalformat,
		bi.biWidth,               //GLsizei width,
		bi.biHeight,                //GLsizei height,
		0,                //GLint border,
		GL_RGB,           //GLenum format,
		GL_UNSIGNED_BYTE, //GLenum type,
		pixels             //const GLvoid *pixels
		);
	GLint filter = GL_NEAREST;
	glTexParameteri(
		GL_TEXTURE_2D,        //GLenum target, 
		GL_TEXTURE_MIN_FILTER,//GLenum pname, 
		filter           //GLint param
		);
	glTexParameteri(
		GL_TEXTURE_2D,        //GLenum target, 
		GL_TEXTURE_MAG_FILTER,//GLenum pname, 
		filter           //GLint param
		);

	glutTimerFunc(
		0,
		timer,
		0); //unsigned int millis, void (GLUTCALLBACK *func)(int value), int value


	glutMainLoop();
}
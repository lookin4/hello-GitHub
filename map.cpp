#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<assert.h>
#include<stdlib.h>
#include"glut.h"

#define GET_ARRAY_SIZE(a)   (sizeof(a)/sizeof(a[0]))
#define quadsR (.5f)
#define height (14)
#define width (78)

int* map;

int* readCsv(char* _fileName, const int _width, const int _height){

	char buff[256];
	int num;
	FILE *pFile =
		fopen(
		_fileName,
		"r"
		);

	assert(pFile != NULL);

	int *_p = (int*)malloc(sizeof(int)*_width*_height);

	for (int i = 0; i < _width*_height; i++){
		if (fscanf(pFile, "%d", &num) != NULL){
			_p[i] = num;
			fscanf(pFile, "%1s", buff);
		}
		else{
			printf("ファイルデータが正しくありません。\n");
			getchar();
			exit(0);
		}
	}
	return _p;
}

void display(){
	glClear(GL_COLOR_BUFFER_BIT);


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
		width / 2, 0, 70,//GLdouble eyex,eyey,eyez,
		width / 2, 0, 0,//GLdouble centerx,centery,centerz,
		0, 1, 0);//GLdouble upx,upy, upz
	static unsigned char indices[] = { 0, 1, 2, 1, 3, 2 };
	for (int i = 0; i < height; i++){
		for (int n = 0; n < width; n++){
			if (map[i*width+n]!=0){
				float v[] = {
					-quadsR + n, quadsR - i,
					-quadsR + n, -quadsR - i,
					quadsR + n, quadsR - i,
					quadsR + n, -quadsR - i
				};

				glEnableClientState(GL_VERTEX_ARRAY);	// GLenum array
				glVertexPointer(
					2,
					GL_FLOAT,
					0,
					v);//GLint size, GLenum type, GLsizei stride, const GLvoid *pointer


				glDrawElements(
					GL_TRIANGLES,
					GET_ARRAY_SIZE(indices),
					GL_UNSIGNED_BYTE,
					indices);
			}
		}
	}
	

	glFlush();

}

void timer(int value){





	glutPostRedisplay();//再描画

	glutTimerFunc(
		1000 / 60,
		timer,
		0); //unsigned int millis, void (GLUTCALLBACK *func)(int value), int value
}


void main(int argc,char*argv[]){
	map = readCsv("map.csv", width, height);
	for (int i = 0; i < width * height; i++){
		if ((i + 1) % width == 0){
			printf("%d\n", map[i]);
		}
		else{
			printf("%d", map[i]);
		}
	}
	glutInit(&argc, argv);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(display);//void (GLUTCALLBACK *func)(void)
	glutTimerFunc(
		0,
		timer,
		0); //unsigned int millis, void (GLUTCALLBACK *func)(int value), int value


	glutMainLoop();
}
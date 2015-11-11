#define _USE_MATH_DEFINES

#include<stdio.h>
#include<math.h>
#include"sleep.h"
#include"glut.h"

class Vec3{
public:
	Vec3(){ x = y = z = 0; }
	Vec3(float _x, float _y, float _z);
	float x, y, z;
};

Vec3::Vec3(float _x, float _y, float _z){
	x = _x;
	y = _y;
	z = _z;
}


class Character{
public:
	Character(const float _x, const float _y, const float _z);
	~Character();

	bool jumpFlug;
	float jumpGravity;
	bool rotateFlug;
	bool seityouFlug;
	bool syagamiFlug;
	Vec3 position;
};

Character::Character(const float _x, const float _y, const float _z):jumpFlug(0),jumpGravity(0.7f),rotateFlug(0),seityouFlug(0),syagamiFlug(0){
	position = Vec3(_x,_y,_z);
}
Character *pPlayer;




unsigned char keys[256] = {};
void keyboard(unsigned char key, int x, int y){
	keys[key] = 1;
	if (key == ' '){
		pPlayer->jumpFlug = true;
	}
	if (key == 'o'){
		pPlayer->seityouFlug = true;
	}
}

void keyboardUp(unsigned char key, int x, int y){
	keys[key] = 0;
}


void display(void){
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
		pPlayer->position.x+5, 8, 20,//GLdouble eyex,eyey,eyez,
		pPlayer->position.x+5, 8, 0,//GLdouble centerx,centery,centerz,
		0, 1, 0);//GLdouble upx,upy, upz
	glColor3f(1, 1, 0.5);
	/*for (int i = -20; i < 20; i++){
		glBegin(GL_LINES);
		{
			glVertex3f(i, -20, 0);
			glVertex3f(i, 20, 0);
		}
		{
			glVertex3f(-20, i, 0);
			glVertex3f(20, i, 0);
		}
		glEnd();
	}*/
	glBegin(GL_QUADS);
	{
		glVertex3f(20,-1,0);
		glVertex3f(-20, -1, 0);
		glVertex3f(-20, -10, 0);
		glVertex3f(20, -10, 0);
	}
	glEnd();
	

	glPushMatrix();
	{
		glColor3f(1, 0,0 );
		glTranslatef(pPlayer->position.x, pPlayer->position.y, pPlayer->position.z);
		if (pPlayer->rotateFlug == 1)
			glRotatef(180.f, 0.f, 1.f, 0.f);
		if (pPlayer->seityouFlug == true){
			//for (int i = 0; i < 5; i++){
				//glScalef(1.f, 10.f, 1.f);
				//glutWireTeapot(1);
				//glScalef(1.f, 0.5f, 1.f);
				//glutWireTeapot(1);
				//sleep(100);
			//}
			glTranslatef(0,0.7f,0);
			//pPlayer->seityouFlug = false;
			glScalef(1.f, 2.f, 1.f);
		}
		if (keys['s']){
			glTranslatef(0, -0.3f, 0);
			glScalef(1.f, .5f, 1.f);
			pPlayer->syagamiFlug = true;
		}
		else{
			pPlayer->syagamiFlug = false;
		}
		glutWireTeapot(1);
	}
	glPopMatrix();
	glFlush();


}


void timer(int value){

	if (keys['d'] == 1 && (pPlayer->syagamiFlug ==false||pPlayer->jumpFlug==true)){
		if (pPlayer->rotateFlug == 1){
			pPlayer->rotateFlug = 0;
		}
		pPlayer->position.x += .1f;
	}
	if (keys['a'] == 1 && (pPlayer->syagamiFlug == false || pPlayer->jumpFlug == true)){
		if (pPlayer->rotateFlug == 0){
			pPlayer->rotateFlug = 1;
		}
		pPlayer->position.x -= .1f;
	}
	

	if (keys[0x0a] == 1){

	}

	if (pPlayer->jumpFlug == true){
		pPlayer->position.y += pPlayer->jumpGravity;
		pPlayer->jumpGravity -= 0.05f;
	}
	if (pPlayer->position.y <= 0 && pPlayer->jumpFlug == true){
		pPlayer->jumpFlug = false;
		pPlayer->jumpGravity = 0.7f;
	}


	glutPostRedisplay();//çƒï`âÊ

	glutTimerFunc(
		1000 / 60,
		timer,
		0); //unsigned int millis, void (GLUTCALLBACK *func)(int value), int value
}


int main(int argc, char *argv[]){
	pPlayer = new Character(0, 0, 0);

	glutInit(&argc, argv);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(display);//void (GLUTCALLBACK *func)(void)
	glutTimerFunc(
		0,
		timer,
		0); //unsigned int millis, void (GLUTCALLBACK *func)(int value), int value

	glutKeyboardFunc(keyboard); //void (GLUTCALLBACK *func)(unsigned char key, int x, int y)
	glutKeyboardUpFunc(keyboardUp); //void (GLUTCALLBACK *func)(unsigned char key, int x, int y)
	glutIgnoreKeyRepeat(GL_TRUE);//(int ignore)

	glutMainLoop();
}
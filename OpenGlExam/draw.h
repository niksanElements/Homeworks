#ifndef DRAW_H_
#define DRAW_H_

#include <cstdio>
#include <gl\gl.h>
#include <gl\glu.h>

#include "models.h"
#include "textures.h"

namespace draw
{

const char ClassName[] = "MainWindowClass";
HWND hWnd;
HDC hDC;
HGLRC hRC;
RECT ScreenRect, ClientRect;
float RotateX = 0.5, RotateY = 0.5, RotateZ = 0.5;
bool anim=true;
    GLfloat lx = 0, ly =1, lz = 0,lightDist=1, zoom=5;
//Rotate of the model
GLfloat rotx = 10, roty = 10,rotz = 40;
 int
    //model for display
    model = 0,
    mot;

int ox = -1, oy = -1;

enum{LGHT=1,ROT};

GLfloat color[4] = { 1.0f, 0.0f, 0.7f, 1.0f };

void hexahedron();
void buildPoints();
void tetrahedron(double);
void hexahedron(double);
void octahedron(double);
void dodecahedron(double);
void icosahedron(double);
//void pyramid(double , Point , int );

void help(void) {
    printf("'ESC'       - exit\n");
    printf("'h'         - help\n");
	printf("'r','g','b' - increase color component\n");
	printf("'R','G','B' - decrease color component\n");
	printf("'a','A'     - rotate/stop\n");
    printf("'l','L''    - light close/far\n");
    printf("'z','Z'     - zoom in/out\n");
    printf("'LEFT'      - switch model\n");
    printf("'RIGHT','w' - toggle solid/wire\n");
    printf("right mouse - rotate model\n");
    printf("left mouse  - move light\n");
}

void genmodel(void)
{

    glNewList(1, GL_COMPILE);

    models::j10(3);

	glEndList();
}


void togglewire(void)
{
    static int toggle = 0;  toggle ^= 1;
    glPolygonMode(GL_FRONT_AND_BACK, toggle ? GL_LINE : GL_FILL);
}

void SetGLProjection(int Width, int Height)
{

    if (Height == 0)
        Height = 1;
    glViewport(0, 0, Width, Height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0 ,(float)Width / (float)Height, 1.0, 200.0);
}

void SetGLView(int Width, int Height)
{
    SetGLProjection(Width, Height);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void InitGL(int Width, int Height)
{
    SetGLView(Width, Height);
    // Цветови компоненти на разсеяната светлина
    GLfloat  ambientLight[] = { 0.3f, 0.3f, 0.3f, 1.0f };
	// Цветови компоненти на дифузно отразената светлина
	GLfloat  diffuseLight[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	// Цветови компоненти на огледално отразената светлина
    GLfloat  specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	// Цветови компоненти на огледалното отражение от повърхнините
    GLfloat  specref[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	// Кое да се визуализира при използване на z буфера
    glDepthFunc(GL_LESS);
	// Задейства използването на z буфера
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);
	// Задаване на цветовете за отделните компоненти на осветяването
    glLightfv(GL_LIGHT0,GL_AMBIENT,ambientLight);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuseLight);
    glLightfv(GL_LIGHT0,GL_SPECULAR, specular);
	// Задейства модела на осветеност
    glEnable(GL_LIGHTING);
	// Включва осветяването
    glEnable(GL_LIGHT0);
	// Задейства проследяването на цвят за всяка повърхнина
    glEnable(GL_COLOR_MATERIAL);
	// За разсеяната и дифузно отразената светлина да се
	// взема цвят от повърхнината независимо от посоката на нормалата
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    // За огледално отразената светлина се задават
    // общи цветови характеристики и максимална отражателност
    glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
    glMateriali(GL_FRONT, GL_SHININESS, 128);
    // Цвят на фона
    glClearColor(0.0f, 0.0f, 0.5f, 1.0f );
    //initColors();
    genmodel();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,textures::names[0]);
}

void ResizeGLScene(int Width, int Height)
{
    SetGLView(Width, Height);
}


void DrawGLScene(bool anim)
{
    GLfloat position[] = { 2.0f*lightDist, 0.0, 3.5f*lightDist, 1.0 };
	//Изчистване на буферите
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//Запомняне на текущото състояние на матрицата на преобразуванията
    glPushMatrix();
		//Транслиране - матрицата се умножава с тази за транслация
		glTranslatef(0.0, 0.0, -zoom);
		glPushMatrix(); //запомняне
		    //ротация около двете оси за завъртане на източника
			glRotatef(ly, 0, 1.0, 0.0);
			glRotatef(lx, 1.0, 0.0, 0.0);
			glRotatef(lz, 0.0, 0.0, 1.0);
			//позициониране на източника
			glLightfv(GL_LIGHT0, GL_POSITION, position);
		glPopMatrix(); //възстановяване след завъртането на източника
		//ново завъртане - този път за модела
		glRotatef(roty, 0., 1., 0.);
		glRotatef(rotx, 1., 0., 0.);
		glRotatef(rotz, 0., 0., 1.);
		glCallList(1); //изобразяване в задния буфер
	glPopMatrix(); //възстановяване на матрицата
	if(anim){ rotx+=0.1; }
}

}


#endif // DRAW_H_

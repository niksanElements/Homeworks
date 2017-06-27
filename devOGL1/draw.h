#ifndef DRAW_H_INCLUDED
#define DRAW_H_INCLUDED
#include <cstdio>
#include <gl\gl.h>
#include <gl\glu.h>
#include "point.h"
#include "LoadTextures.h"
#include "models.h"
extern GLuint textureName[10]; //собствена номерация на заредени текстури
extern GLuint txtNum; //брой заредени текстури

namespace globals{
    const char ClassName[] = "MainWindowClass";
    HWND hWnd;
    HDC hDC;
    HGLRC hRC;
    RECT ScreenRect, ClientRect;
    float RotateX, RotateY, RotateZ;
	//Завъртане на модела
	float rotx=0.0f, roty=0.0f, rotz=0.0f;
    bool anim=true;
    float lx=0, ly=0, lightDist=1, zoom=5;
    int models=7,     //брой модели
		model =0,     //модел за визуализация
		textureNo = 0,//номер на текущо използвана текстура
        level =10;    //равнище на дискретизация
	int ox = -1, oy = -1, mot;//последно положение на мишката
 	//предефинирани режими на управление:PAN -за източника, ROT- за модела
	enum{PAN=1,ROT};

	//Индивидуални цветове за до 20 модела
    float colors[20][4];

}

// Polyhedra - implemented in "models.cpp"
void tetrahedron(double);
void hexahedron(double);
void octahedron(double);
void dodecahedron(double);
void icosahedron(double);
void pyramid(double);


//Текстов help - излиза в конзолния прозорец
void help(void) {
    printf("'ESC'           - exit\n");
    printf("'h'             - help\n");
	printf("'r','g','b'     - increase color component\n");
	printf("'R','G','B'     - decrease color component\n");
	printf("'a','A'         - rotate/stop\n");
	printf("'s','S'         - shade smooth/flat\n");
    printf("'l','L''        - light close/far\n");
    printf("'z','Z'         - zoom in/out\n");
    printf("'w'             - toggle solid/wire\n");
    printf("'m'             - switch model\n");
	printf("'t'             - toggle texturing\n");
	printf("'T'             - change the texture\n");
    printf("'RIGHT'         - rotate model around Y\n");
    printf("'LEFT'          - rotate model around Y\n");
    printf("'UP'            - rotate model around X\n");
    printf("'DOWN'          - rotate model around X\n");
    printf("'HOME'          - rotate model around Z\n");
    printf("'END'           - rotate model around Z\n");
    printf("mouse LB&move   - rotate light\n");
    printf("mouse RB&move   - rotate model\n");
}


// Създаване на модел по избор
void genmodel(void) {
	//Моделът се запаметява в списък за ускоряване на визуализацията
    glNewList(1, GL_COMPILE);
		//задава се цвят - еднакъв за всички елементи на конкретния модел
		glColor4fv(globals::colors[globals::model]);
		//създават се геометричните данни за избрания модел
		dodecahedron(5);
	glEndList();
}

//Включване/изключване на текстурирането
void tglTexture(){
	static bool txtr=true;
	txtr=!txtr;
	if(txtr)glEnable(GL_TEXTURE_2D);
	else glDisable(GL_TEXTURE_2D);
}
//Включване на текстурирането и смяна на текстурата
void setTexture(){
    using globals::textureNo;
	glEnable(GL_TEXTURE_2D);
	textureNo=(textureNo+1)%txtNum;
	glBindTexture(GL_TEXTURE_2D, textureName[textureNo]);
}

// Инициализация на цветовете на моделите - всички в сиво
void initColors(){
	for(int i=0;i<20;i++)
		for(int j=0;j<4;j++)globals::colors[i][j]=0.5;
}

// Промяна на цветова компонента за отделен модел
// no - номер на модела,  comp - номер на компонента
void incCol(int no,int comp){
	globals::colors[no][comp]+=0.1f;
	if(globals::colors[no][comp]>1.)globals::colors[no][comp]=1.f;
	//genmodel();
}
void decCol(int no,int comp){
	globals::colors[no][comp]-=0.1f;
	if(globals::colors[no][comp]<0.)globals::colors[no][comp]=0.;
	//genmodel();
}
// Смяна на режима за изобразяване на повърхнинните елементи
void togglewire(void) {
    static int toggle = 0;  toggle ^= 1;
    glPolygonMode(GL_FRONT_AND_BACK, toggle ? GL_LINE : GL_FILL);
}

void SetGLProjection(int Width, int Height){
    if (Height == 0)
        Height = 1;
    glViewport(0, 0, Width, Height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0 ,(float)Width / (float)Height, 1.0, 200.0);
}

void SetGLView(int Width, int Height){
    SetGLProjection(Width, Height);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void InitGL(int Width, int Height){
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
    initColors();
    genmodel();
}

void ResizeGLScene(int Width, int Height){
    SetGLView(Width, Height);
}

void DrawGLScene(bool anim){
     using namespace globals;
 	//Актуализация на положението на източника
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
// Промяна на завъртането на модела или на източника
void move(int x, int y, GLfloat & rx, GLfloat & ry) {
    using globals::ox; using globals::oy;
    rx += (x-ox);ry += (y-oy);
    ox = x; oy = y;
}

//За ръчно управление на положението на модела и източника
void motion(int x, int y) {
    using namespace globals;
    if (mot == PAN) move(x, y, lx, ly);
    else if (mot == ROT) move(x,y,rotx,roty);
}

#endif // DRAW_H_INCLUDED

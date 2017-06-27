#ifndef DRAW_H_INCLUDED
#define DRAW_H_INCLUDED
#include <stdio.h>
#include <gl\gl.h>
#include <gl\glu.h>

namespace globals{
    const char ClassName[] = "MainWindowClass";
    HWND hWnd;
    HDC hDC;
    HGLRC hRC;
    RECT ScreenRect, ClientRect;
 	//предефинирани режими на управление:PAN -за източника, ROT- за модела
	enum{PAN=1,ROT};
	//Индивидуални цветове за до 20 модела
    float colors[20][4];
	//Завъртане на модела
    bool anim=true;
	float rotx=0.0f, roty=0.0f, rotz=0.0f;
    float lx=0, ly=0, lightDist=1, zoom=5;
	int ox = -1, oy = -1, mot;//последно положение на мишката
    int models=9,     //брой модели
		model =0,     //модел за визуализация
		textureNo = 0,//номер на текущо използвана текстура
        level =10;    //равнище на дискретизация
	int modelIntPar=5;
	double modelPar1=1., modelPar2=1.5;
}


void hexahedron();
void buildPoints();
void tetrahedron(double);
void hexahedron(double);
void octahedron(double);
void dodecahedron(double);
void icosahedron(double);
void pyramid(double R, double H, int n);
void prism(double R, double H, int n);
void antiprism(double R, double H, int n);
void reg_prism(double a, int n);
void reg_antiprism(double a, int n);
void cupola(double a, int n);
void rotunda5(double);
//void pyramid(double , Point , int );
//Текстов help - излиза в конзолния прозорец
void help(void) {
    printf("'ESC'           - exit\n");
    printf("'h'             - help\n");
	printf("'r','g','b'     - increase color component\n");
	printf("'R','G','B'     - decrease color component\n");
	printf("'a','A'         - rotate/stop\n");
    printf("'l','L''        - light close/far\n");
    printf("'z','Z'         - zoom in/out\n");
    printf("'m'             - switch model\n");
    printf("'w'             - toggle solid/wire\n");
    printf("right mouse     - rotate model\n");
    printf("left mouse      - move light\n");
	printf("'HOME','END'    - increase/decrease sides number\n");
	printf("'RIGHT','LEFT'  - increase/decrease size 1\n");
	printf("'UP','DOWN'     - increase/decrease size 2\n");
}

// Създаване на модел по избор
void genmodel(void) {
	//Моделът се запаметява в списък за ускоряване на визуализацията
    glNewList(1, GL_COMPILE);
		//задава се цвят - еднакъв за всички елементи на конкретния модел
		glColor4fv(globals::colors[globals::model]);
		//създават се геометричните данни за избрания модел
		switch(globals::model){
			case 0:tetrahedron(globals::modelPar1);			    break;
			case 1:hexahedron(globals::modelPar1);				break;
			case 2:octahedron(globals::modelPar1);				break;
			case 3:dodecahedron(globals::modelPar1);			break;
			case 4:icosahedron(globals::modelPar1);				break;
			case 5:pyramid(globals::modelPar1,
				globals::modelPar2,globals::modelIntPar);
				break;
			case 6:prism(globals::modelPar1,
				globals::modelPar2,globals::modelIntPar);
				break;
			case 7:antiprism(globals::modelPar1,
				globals::modelPar2,globals::modelIntPar);
				break;
			case 8:reg_prism(globals::modelPar1,globals::modelIntPar);
				break;
			case 9:reg_antiprism(globals::modelPar1,globals::modelIntPar);
				break;
			case 10:cupola(globals::modelPar1,globals::modelIntPar);
                break;
			case 11:rotunda5(globals::modelPar1);
				break;
		}
	glEndList();
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
// Промяна на цветова компонента за отделен модел
// no - номер на модела,  comp - номер на компонента
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

void SetGLView(int Width, int Height){
    if (Height == 0) Height = 1;
    glViewport(0, 0, Width, Height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0 ,(float)Width / (float)Height, 1.0, 200.0);
    glMatrixMode(GL_MODELVIEW);
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
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
    initColors();
    //genmodel();
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
			glRotatef(ly, 0,0, 1.0);
			glRotatef(lx, 1.0, 0.0, 0.0);
			//позициониране на източника
			glLightfv(GL_LIGHT0, GL_POSITION, position);
		glPopMatrix(); //възстановяване след завъртането на източника
		//ново завъртане - този път за модела
		glRotatef(rotx, 1., 0., 0.);
		glRotatef(roty, 0., 1., 0.);
		glRotatef(rotz, 0., 0., 1.);
		glCallList(1); //изобразяване в задния буфер
	glPopMatrix(); //възстановяване на матрицата
	if(anim){ rotz+=0.01; }
}
// Промяна на завъртането на модела или на източника
void motion(int x, int y, GLfloat & rx, GLfloat & ry) {
    using globals::ox; using globals::oy;
    rx += (x-ox);ry += (y-oy);
    ox = x; oy = y;
}

//За ръчно управление на положението на модела и източника
void motion(int x, int y) {
    using namespace globals;
    if (mot == PAN) motion(x, y, lx, ly);
    else if (mot == ROT) motion(x,y,rotx,roty);
}
void keyPressed(WPARAM wParam){
    using globals::hWnd; using globals::level;
    using globals::modelIntPar;
    using globals::modelPar1;using globals::modelPar2;
    switch (wParam){

        case VK_ESCAPE:
            SendMessage(hWnd, WM_CLOSE, 0, 0);
        break;

        case VK_HOME: modelIntPar++; genmodel();
        break;

        case VK_END:
            if(modelIntPar>3)modelIntPar--;
            genmodel();
        break;

        case VK_LEFT: modelPar1*=0.8; genmodel();
        break;

        case VK_RIGHT: modelPar1*=1.25; genmodel();
        break;

        case VK_UP: modelPar2*=1.25; genmodel();
        break;

        case VK_DOWN: modelPar2*=0.8; genmodel();
        break;

        case VK_RETURN: level+=5; break;
        case VK_SPACE:if(level>10)level-=5; break;
        default: return;
      }
}
void charPressed(WPARAM wParam){
    using namespace globals;
    switch(wParam){
        case 'A': anim=false;        break;
        case 'a': anim=true;rotx=0, roty=0, rotz=0;
            break;
        case 'r': incCol(model,0);   break;
        case 'g': incCol(model,1);   break;
        case 'b': incCol(model,2);   break;
        case 'R': decCol(model,0);   break;
        case 'G': decCol(model,1);   break;
        case 'B': decCol(model,2);   break;
        case 'w': togglewire();		 break;
        case 'm': model=(model+1)%models;
                                     break;
        case 'h': help();			 break;
        case 'L': lightDist++;		 break;
        case 'l': lightDist--;		 break;
        case 'Z': zoom++;			 break;
        case 'z': zoom--;			 break;
        case 's': glShadeModel(GL_SMOOTH); break;
        case 'S': glShadeModel(GL_FLAT); break;
    }
}
void mouseAct(UINT msg, LPARAM lParam){
    using globals::mot; using globals::PAN; using globals::ROT;
    static bool ld=false, rd=false;
    if(msg==WM_LBUTTONDOWN){ld=true;return;}
    if(msg==WM_RBUTTONDOWN){rd=true;return;}
    int x = LOWORD (lParam), y = HIWORD (lParam);
    switch(msg){
        case WM_MOUSEMOVE:
            if(ld){mot = PAN;}
            if(rd){mot = ROT;}
            motion(x,y );
        break;
        case WM_LBUTTONUP: ld=false; mot=0;
        break;
        case WM_RBUTTONUP: rd=false; mot=0;
        break;
     }
 }


#endif // DRAW_H_INCLUDED





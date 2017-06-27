#include <gl\gl.h>
#include "point.h"

template <typename T> void swap(T & a, T& b){T c;c=a;a=b;b=c;}

//Плосък триъгълник с наложена текстура
//Върховете са в масива t
inline void flatTri(Point t[]){
	glBegin(GL_TRIANGLES);
	Point n = !((t[1]-t[0])*(t[2]-t[1]));
		glNormal3dv(n.arr());
		glTexCoord2f(0.0f, 0.0f);
		glVertex3dv(t[0].arr());
		glTexCoord2f(1.0f, 0.0f);
		glVertex3dv(t[1].arr());
		glTexCoord2f(0.5f,1.0f);
		glVertex3dv(t[2].arr());
	glEnd();
}

//Плосък триъгълник с наложена текстура
//Върховете са
inline void flatTri(Point v1, Point v2, Point v3 ){
	Point n = !((v2 - v1)*(v3 - v1));
	glBegin(GL_TRIANGLES);
	glNormal3dv(n.arr());
	glTexCoord2f(0.0f, 0.0f);
	glVertex3dv(v1.arr());
	glTexCoord2f(1.0f, 0.0f);
	glVertex3dv(v2.arr());
	glTexCoord2f(0.5f, 1.0f);
	glVertex3dv(v3.arr());
	glEnd();
}

//Плосък четириъгълник с наложена текстура
//Върховете са в масива t
inline void flatQuad(Point v1, Point v2, Point v3, Point v4){
	Point n = !((v2 - v1)*(v3 - v1));
	glBegin(GL_QUADS);
		glNormal3dv(n.arr());
		glTexCoord2f(1.0f, 0.0f);
		glVertex3dv(v1.arr());
		glTexCoord2f(1.0f, 1.0f);
		glVertex3dv(v2.arr());
		glTexCoord2f(0.0f, 1.0f);
		glVertex3dv(v3.arr());
		glTexCoord2f(0.0f, 0.0f);
		glVertex3dv(v4.arr());
	glEnd();
}

//Плосък четириъгълник с наложена текстура
//Върховете са
inline void flatQuad(Point t[]){
	glBegin(GL_QUADS);
	Point n = !((t[1] - t[0])*(t[2] - t[0]));
	glNormal3dv(n.arr());
	glTexCoord2f(1.0f, 0.0f);
	glVertex3dv(t[0].arr());
	glTexCoord2f(1.0f, 1.0f);
	glVertex3dv(t[1].arr());
	glTexCoord2f(0.0f, 1.0f);
	glVertex3dv(t[2].arr());
	glTexCoord2f(0.0f, 0.0f);
	glVertex3dv(t[3].arr());
	glEnd();
}

//Плосък петоъгълник с наложена текстура
//Върховете са в масива p
void flatPenta(Point p []){
	static double tx[6][2]={{0.2,0.},
                            {.8,0.},
                            {1.,.6},
                            {0.5,1.},
                            {0.,0.6},
                            {0.2,0.} };
	Point n=!((p[2]-p[0])*(p[1]-p[0]));
	glBegin(GL_POLYGON);
		glNormal3dv(n.arr());
		for(int i=0;i<=5;i++){
			glTexCoord2d(tx[i][0], tx[i][1]);
			glVertex3dv(p[i].arr());
		}
	glEnd();
}

//Плосък многоъгълник с наложена текстура
//Върховете са в масива p
//Брой на ъглите N
void flatPoly(Point p [], int N, bool rev){
	//Налагането на текстурата е при предположение,
	//че многоъгълникът е в равнината XY
	//Намиране на минимални и максимални x и y
	double x=1e5,y=1e5,X=-1e5,Y=-1e5;
	for(int i=0;i<N;i++){
		double xt=p[i].arr()[0], yt=p[i].arr()[1];
		x=xt<x?xt:x; y=yt<y?yt:y;
		X=xt>X?xt:X; Y=yt>Y?yt:Y;
	}
	//X и Y стават размери по хоризонтала и вертикала
	X=X-x;Y=Y-y;
	Point n=!((p[1]-p[0])*(p[2]-p[0]));
	glBegin(GL_POLYGON);
		glNormal3dv(n.arr());
		for(int i=0;i<=N;i++){
			//Разполагане на текстурата според координатите на точките
			double u = (p[i].arr()[0]-x)/X, v = (p[i].arr()[1]-y)/Y;
			if(rev)u=1.-u;
			glTexCoord2d(u, v);
			glVertex3dv(p[i].arr());
		}
	glEnd();
}

//Тетраедър
//Ползва flatTri и може да е текстуриран
//R - радиус на описаната сфера
void tetrahedron(double R){
	static double Z = sqrt(2./3.), X = sqrt(3.)/3.;
	static Point v[4] = {
		Point(X, 0., -Z*0.25), Point( -0.5*X,-0.5, -Z*0.25),
		Point(-0.5*X, 0.5, -Z*0.25), Point(0., 0., Z*0.75)
	};
	static int ind[4][3] = {{0,1,2},  {0,3,1},  {0,2,3},  {1,3,2}};
	Point t[3];
	for (int i = 0; i < 4; i++) {
		for(int j=0;j<3;j++)t[j]=v[ind[i][j]]*R;
		flatTri(t);
	}
}

//Куб. Ползва flatQuad и може да е текстуриран
//R - радиус на описаната сфера
void hexahedron(double R){
	static Point v[8] = {
		Point(0.5, 0.5, 0.5), Point( -0.5, 0.5, 0.5),
		Point( -0.5, -0.5, 0.5), Point(0.5, -0.5, 0.5),
		Point(0.5, 0.5, -0.5), Point( -0.5, 0.5, -0.5),
		Point( -0.5, -0.5, -0.5), Point(0.5, -0.5, -0.5),
	};
	static int ind[6][4] = {{0,4,5,1},  {0,1,2,3},  {0,3,7,4},
							{6,2,1,5}, {6,7,3,2}, {6,5,4,7}};
	Point t[4];
	for (int i = 0; i < 6; i++) {
		for(int j=0;j<4;j++)t[j]=v[ind[i][j]]*R;
		flatQuad(t);
	}
}

//Октаедър
//Ползва flatTri и може да е текстуриран
//R - радиус на описаната сфера
void octahedron(double R){
	static Point v[6] = {
		Point(1., 0., 0.), Point( 0.,1., 0.),Point( 0., 0.,1.),
		Point(-1., 0., 0.), Point( 0.,-1., 0.),Point( 0., 0.,-1.)
	};
	static int ind[8][3] = {
		{0,1,2},  {1,3,2},  {3,4,2},  {4,0,2},
		{0,1,5},  {1,3,5},  {3,4,5},  {4,0,5}
	};
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < 8; i++) {
		Point t[3];
		for(int k=0;k<3;k++)t[k]=v[ind[i][k]];
		flatTri(t);
	}
	glEnd();
}

//Додекаедър )12-стен, стените са петоъгълници)
void dodecahedron(double R){
    double a0=0.,a1=0.149071, a2=0.28355,a3=0.390273,
           a4=0.458794, a48=0.482405, a6=0.631476,
           a7=0.742344, a78=0.780547, a24=0.241202;
    Point vdod[4][6] = {
        {Point(a2,a3,a6),Point(a4,-a1,a6), Point(a0,-a48,a6),
        Point(-a4,-a1,a6),Point(-a2,a3,a6), Point(a2,a3,a6)},
        {Point(a4,a6,a1), Point(a7,-a24,a1),Point(a0,-a78,a1),
        Point(-a7,-a24,a1),Point(-a4,a6,a1),Point(a4,a6,a1)},
        {Point(a7,a24,-a1),Point(a4,-a6,-a1),Point(-a4,-a6,-a1),
        Point(-a7,a24,-a1),Point(a0,a78,-a1),Point(a7,a24,-a1)},
        {Point(a4,a1,-a6),Point(a2,-a3,-a6),Point(-a2,-a3,-a6),
        Point(-a4,a1,-a6),Point(a0,a48,-a6),Point(a4,a1,-a6)}};
	Point v[4][6];
	for(int k=0;k<4;k++)
		for(int i=0;i<=5;i++)v[k][i]=!vdod[k][i]*R;
	flatPenta(v[0]);
	swap(v[3][1],v[3][4]);swap(v[3][2],v[3][3]);
	flatPenta(v[3]);
	Point t[6];
	for(int i=0;i<5;i++){
		t[0]=v[0][i];t[1]=v[1][i];t[2]=v[2][i];
		t[3]=v[1][i+1];t[4]=v[0][i+1];t[5]=t[0];
		flatPenta(t);
		t[0]=v[2][i];t[1]=v[3][5-i];t[2]=v[3][4-i];
		t[3]=v[2][i+1];t[4]=v[1][i+1];t[5]=t[0];
		flatPenta(t);
	}
	std::cout<<"Dodecahedron generated\n";
}

//Икосаедър (20-стен, стените са триъгълници)
void icosahedron(double R){
    double z=0.447214,x=0.276393,y=0.723607,u=0.894427,
           v=0.850651,w=0.525731;
            Point vico1[]={
                Point(0,u,z),Point(v,x,z),Point(w,-w,z),
                Point(-w,-y,z),Point(-v,x,z),Point(0,u,z)};
            Point vico2[]={
                Point(w,y,-z),Point(v,-x,-z),Point(0.,-u,-z),
                Point(-v,-x,-z),Point(-w,y,-z),Point(w,y,-z)};
	for(int i=0;i<5;i++){
		Point t[3];
		t[0]=Point(0.,0.,1.);t[2]=vico1[i];t[1]=vico1[i+1];
		for(int j=0;j<3;j++)t[j]=t[j]*R;
		flatTri(t);
		t[0]=vico1[i];t[2]=vico2[i];t[1]=vico1[i+1];
		for(int j=0;j<3;j++)t[j]=t[j]*R;
		flatTri(t);
		t[0]=vico2[i];t[2]=vico2[i+1];t[1]=vico1[i+1];
		for(int j=0;j<3;j++)t[j]=t[j]*R;
		flatTri(t);
		t[0]=vico2[i];t[2]=Point(0.,0.,-1.);t[1]=vico2[i+1];
		for(int j=0;j<3;j++)t[j]=t[j]*R;
		flatTri(t);
	}
	std::cout<<"Icosahedron generated\n";
}

#ifndef MODELS_H_
#define MODELS_H_

#include "draw.h"
#include "util.h"
#include <cmath>

using namespace util;


namespace models
{

    static const double PI =  3.1415926536;

    void flatTri(Point points[])
    {
        Point vectorA =
        {
            points[1].x - points[2].x,
            points[1].y - points[2].y,
            points[1].z - points[2].z
        };

        Point vectorB =
        {
            points[0].x - points[1].x,
            points[0].y - points[1].y,
            points[0].z - points[1].z
        };

        Point normal = vectorProduct(vectorA,vectorB);

        glBegin(GL_TRIANGLES);
            glNormal3dv(&normal.x);
            glTexCoord2f(0.0f, 0.0f);
            glVertex3dv(&points[0].x);
            glTexCoord2f(1.0f, 0.0f);
            glVertex3dv(&points[1].x);
            glTexCoord2f(0.5f, 1.0f);
            glVertex3dv(&points[2].x);
        glEnd();
    }

    void flatQuad(Point p[])
    {
        Point vectorA =
        {
            p[1].x - p[2].x,
            p[1].y - p[2].y,
            p[1].z - p[2].z
        };

        Point vectorB =
        {
            p[0].x - p[1].x,
            p[0].y - p[1].y,
            p[0].z - p[1].z
        };

        Point normal = vectorProduct(vectorA,vectorB);

        glBegin(GL_QUADS);

        static double tx[4][2]={{1.,0.},
                            {1.0,1.},
                            {0.,1.},
                            {0.0,0.}};

        glNormal3dv(&normal.x);
        for(int i = 0;i < 4;i++)
        {
            glTexCoord2f(tx[i][0],tx[i][1]);
            glVertex3dv(&p[i].x);
        }
        glEnd();
    }

    void flagPenta(Point p[])
    {
        Point vectorA =
        {
            p[1].x - p[2].x,
            p[1].y - p[2].y,
            p[1].z - p[2].z
        };

        Point vectorB =
        {
            p[0].x - p[1].x,
            p[0].y - p[1].y,
            p[0].z - p[1].z
        };

        Point normal = vectorProduct(vectorA,vectorB);

        glBegin(GL_POLYGON);

        static double tx[6][2]={{0.2,0.},
                            {.8,0.},
                            {1.,.6},
                            {0.5,1.},
                            {0.,0.6},
                            {0.2,0.} };

        glNormal3dv(&normal.x);

        for(int i = 0;i < 5;i++)
        {
            glTexCoord2d(tx[i][0], tx[i][1]);
            glVertex3dv(&p[i].x);
        }

        glEnd();
    }

    void tetrohedron(double R)
    {
        static double Z = sqrt(2./3.);
        static double X = sqrt(3.)/3.;
        Point points[4] =
        {
            {X,0.,-Z * 0.25},
            {-0.5*X,-0.5,-Z*0.25},
            {-0.5*X,0.5,-Z*0.25},
            {0., 0., Z*0.75}
        };

        static int ind[4][3] = {{0,1,2},  {0,3,1},  {0,2,3},  {1,3,2}};
        Point t[3];
        for (int i = 0; i < 4; i++) {
            for(int j=0;j<3;j++)
            {
                t[j].x=points[ind[i][j]].x*R;
                t[j].y=points[ind[i][j]].y*R;
                t[j].z=points[ind[i][j]].z*R;
            }
            flatTri(t);
        }
    }

    void hexahedron(double R)
    {
        static float proecX = 0.5f;
        static float proecY = 0.5f;
        static float proecZ = 0.5f;

        Point points[8] =
        {
            {-proecX,-proecY,proecZ}, // a
            {-proecX,proecY,proecZ}, // b
            {proecX,proecY,proecZ}, // c
            {proecX,-proecY,proecZ}, // d

            {-proecX,-proecY,-proecZ}, // a'
            {-proecX,proecY,-proecZ}, // b'
            {proecX,proecY,-proecZ}, // c'
            {proecX,-proecY,-proecZ} // d'
        };

        static int imp[6][4] =
        {
            {0,1,2,3},
            {3,2,6,7},
            {4,5,6,7},
            {4,5,1,0},
            {4,0,3,7},
            {5,1,2,6}
        };
        for(int i = 0;i < 6;i++)
        {
            Point t[4];
            for(int j = 0;j < 4;j++)
            {
                t[j].x = points[imp[i][j]].x * R;
                t[j].y = points[imp[i][j]].y * R;
                t[j].z = points[imp[i][j]].z * R;
            };

            flatQuad(t);
        }
    }

    void j1(double R)
    {
        Point vecOr = {0.5,0.5,0.5}; // vector origin

        Point points[5] =
        {
            {-vecOr.x,vecOr.y,vecOr.z}, // a
            {vecOr.x,vecOr.y,vecOr.z}, // b
            {vecOr.x,-vecOr.y,-vecOr.z}, // c
            {-vecOr.x,-vecOr.y,-vecOr.z}, // d
            {0,0.5,-0.5} // f
        };

        static int imp[4][3] =
        {
            {0,1,4},
            {1,2,4},
            {2,3,4},
            {3,0,4},
        };

        for(int i = 0;i < 4;i++)
        {
            Point temp[3];
            for(int j = 0;j < 3;j++)
            {
                temp[j].x = points[imp[i][j]].x * R;
                temp[j].y = points[imp[i][j]].y * R;
                temp[j].z = points[imp[i][j]].z * R;
            }
            flatTri(temp);
        }
        Point temp[4] =
        {
            {points[0].x*R,points[0].y*R,points[0].z*R},
            {points[1].x*R,points[1].y*R,points[1].z*R},
            {points[2].x*R,points[2].y*R,points[2].z*R},
            {points[3].x*R,points[3].y*R,points[3].z*R},
        };

        flatQuad(temp);

    }
    void j2(double R)
    {
        double rad = 0.5;
        Point points [6];

        for(int i = 0;i < 5;i++)
        {
            points[i] = {rad * cos(2*PI*i/5) *R,0.0,rad * sin(2*PI*i/5) * R};
        }

        double a = sqrt
        (
            pow(points[0].x - points[1].x,2)+
            pow(points[0].y - points[1].y,2)+
            pow(points[0].z - points[1].z,2)
        );
        double h = sqrt(pow(a,2)-pow(0.5,2));
        points[5] = {0,-h,0};

        flagPenta(points);

        static int imp[5][3] =
        {
            {0,1,5},
            {1,2,5},
            {2,3,5},
            {3,4,5},
            {4,0,5},
        };
        for(int i = 0;i < 5;i++)
        {
            Point temp[3];
            for(int j = 0;j < 3;j++)
            {
                temp[j].x = points[imp[i][j]].x;
                temp[j].y = points[imp[i][j]].y;
                temp[j].z = points[imp[i][j]].z;
            }

            flatTri(temp);
        }
    }

    void j8(double R)
    {
 Point vecOr = {0.5,0.5,0.5}; // vector origin

        Point points[9] =
        {
            {-vecOr.x,vecOr.y,vecOr.z}, // a
            {vecOr.x,vecOr.y,vecOr.z}, // b
            {vecOr.x,-vecOr.y,-vecOr.z}, // c
            {-vecOr.x,-vecOr.y,-vecOr.z}, // d
            {0,0.5,-0.5}, // f
            {-vecOr.x,vecOr.y - 0.5,vecOr.z + 0.5}, // a'
            {vecOr.x,vecOr.y- 0.5,vecOr.z+ 0.5}, // b'
            {vecOr.x,-vecOr.y- 0.5,-vecOr.z+ 0.5}, // c'
            {-vecOr.x,-vecOr.y- 0.5,-vecOr.z+ 0.5}, // d'
        };

        static int imp[4][3] =
        {
            {0,1,4},
            {1,2,4},
            {2,3,4},
            {3,0,4},
        };

        for(int i = 0;i < 4;i++)
        {
            Point temp[3];
            for(int j = 0;j < 3;j++)
            {
                temp[j].x = points[imp[i][j]].x * R;
                temp[j].y = points[imp[i][j]].y * R;
                temp[j].z = points[imp[i][j]].z * R;
            }
            flatTri(temp);
        }

        static const int imp2[5][4] =
        {
            {5,6,7,8},
            {0,1,6,5},
            {1,2,7,6},
            {2,7,8,3},
            {3,8,5,0}
        };

        for(int i =0 ;i < 5;i++)
        {
            Point temp[4];
            for(int j = 0;j < 4;j++)
            {
                temp[j].x = points[imp2[i][j]].x * R;
                temp[j].y = points[imp2[i][j]].y * R;
                temp[j].z = points[imp2[i][j]].z * R;
            }
            flatQuad(temp);
        }
    }

    void j10(double R)
    {
        Point baseTop[4] =
        {
            {-0.5,0,0.5}, // a
            {0.5,0,0.5}, // b
            {0.5,0,-0.5}, // c
            {-0.5,0,-0.5}, // d
        };

        Point baseBottom[4]; // a' b' c' d'
        double ar = 45*PI / 180.;
        for(int i = 0;i < 4;i++)
        {
            baseBottom[i].x = baseTop[i].x* cos(ar) - baseTop[i].z * sin(ar);
            baseBottom[i].y = baseTop[i].y - 1;
            baseBottom[i].z = baseTop[i].z*cos(ar) + baseTop[i].x * sin(ar);
        }

        Point midd[8][3] =
        {
            {baseTop[0],baseTop[1],baseBottom[1]},
            {baseTop[1],baseTop[2],baseBottom[2]},
            {baseTop[2],baseTop[3],baseBottom[3]},
            {baseTop[3],baseTop[0],baseBottom[0]},
            {baseBottom[0],baseBottom[1],baseTop[0]},
            {baseBottom[1],baseBottom[2],baseTop[1]},
            {baseBottom[2],baseBottom[3],baseTop[2]},
            {baseBottom[3],baseBottom[0],baseTop[3]},
        };

        Point edge = {0,0.75,0};

        Point tetro[4][3]
        {
            {baseTop[0],baseTop[1],edge},
            {baseTop[1],baseTop[2],edge},
            {baseTop[2],baseTop[3],edge},
            {baseTop[3],baseTop[0],edge},
        };

        for(int i = 0;i < 8;i++)
        {
            flatTri(midd[i]);
        }

        for(int i = 0;i < 4;i++)
        {
            flatTri(tetro[i]);
        }


        flatQuad(baseBottom);
        //flatQuad(baseTop);
    }
}


#endif // MODELS_H_

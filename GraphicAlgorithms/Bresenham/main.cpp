#include <iostream>

#define MAX_N 10000

using namespace std;

char plot[MAX_N][MAX_N] = { 0 };

typedef struct
{
	int x, y;
}point_t;

void setPix(int x, int y)
{
	if (x >= 0 && x < MAX_N && y >= 0 && y < MAX_N)
	{
		plot[x][y] = '#';
	}
}

void bresenham(const point_t &p0, const point_t &p1)
{
	int dx = p1.x - p0.x;
	int dy = p1.y - p0.y;
	double derr = abs(dy / dx);

	double err = derr - 0.5;
	int y = p0.y;
	for (int x = p0.x; x <= p1.x;x++)
	{
		setPix(x, y);
		err = err + derr;
		if (err >= 0.5 + derr)
		{
			y = y + 1;
			err += 1;
		}
	}
}

void bresenham2(const point_t &p0, const point_t &p1)
{
	int dx = p1.x - p0.x;
	int dy = abs(p1.y - p0.y);
	int err = 0;
	int yst = (p0.y < p1.y) ? 1 : -1;
	int y = p0.y;
	for (int x = p0.x; x <= p1.x;x++)
	{
		setPix(x, y);
		err += dy;
		if (2 * err >= dx)
		{
			 y += yst; 
			 err -= dx; 
		}
	}
}

void disply(const point_t& p0, const point_t& p1)
{
	int x_e = (p0.x > p1.x) ? p0.x : p1.x;
	int y_e = (p0.y > p1.y) ? p0.y : p1.y;
	int x_b = (p0.x < p1.x) ? p0.x : p1.x;
	int y_b = (p0.y < p1.y) ? p0.y : p1.y;
	for (int i = y_b; i <= y_e; i++)
	{
		for (int j = x_b; j <= x_e;j++)
		{
			if (plot[i][j] != 0)
			{
				cout << plot[i][j];
			}
			else
			{
				cout << ' ';
			}
		}
		cout << endl;
	}
}

void Michen(const point_t& p,int r)
{
	int x0 = p.x;
	int y0 = p.y;
	int x = 0;
	int y = r;
	int d = 3 - 2 * r;
	while (x < y)
	{
		setPix(x0 + x, y0+y);
		if (d < 0)
		{
			d = d + 4 * x + 6;
			x++;
		}
		else
		{
			d = d + 4 * x - y + 10; 
			x++; y--;
		}
	}
}

int main()
{
	point_t p0;
	while (cin >> p0.x >> p0.y)
	{
		Michen(p0,30);
		disply(point_t{ 0,0 }, point_t{ 100,100 });
	}
	//bresenham(p0);
}
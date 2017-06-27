
#include "shapes.h"
#include <stdio.h>

#define MAXOBJECTS 1000

// Глобални променливи за регистрация на графични обекти
// и режими. Ползват се от обработващите функции.
// Достъпът е ограничен само да този файл чрез анонимно:
namespace {
	Shape * pt[MAXOBJECTS];       //масив от указатели към обекти
	UINT iCount = 0;              //брой обекти
	char objType = 'p';           //тип на текущо въвежданите обекти
	char charBuf[120];            //буфер за текстови съобщения
	POINT pntBuf[100];            //буфер за въвеждани точки
	int pntGot;                   //брой получени точки за обект
	int pntsToTake = 1;           //брой изисквани точки за обект
	int sidesRegPoly =3;          //страни на правилен полигон
	bool scaleIsotropic = false;  //еднакъв мащаб по двете координати
	bool snapOn = false;          //режим Snap за моделната област
	int gridDens = 1;             //брой деления в Snap мрежата
	double mx, my;                //мащаби по осите [1/pix]
}

//Размери на графичния прозорец в потребителски единици и в пиксели.
int USERX = 12, USERY = 10, WW = 1200, HH = 800;

//Премащабиране (при смяна на размерите на прозореца)
void rescale(){
	mx = 2.*USERX/WW, my = 2.*USERY/HH;
	if(scaleIsotropic) if(mx>my) my=mx; else mx=my;
	pntGot=0;
}

//Преизчисляване на потребителска координата за режим snap
inline double roundd(double x){
	x*= gridDens;
	return (x>0.?(int)(x+.5):(int)(x-.5))*(1./gridDens);
}

//Преобразуване от дисплейни в потребителски координати
Point dispToUser(POINT p){
	if(!snapOn) return Point(mx*(p.x-WW/2.), my*(HH/2.-p.y));
	else return Point(roundd(mx*(p.x-WW/2.)), roundd(my*(HH/2.-p.y)));
}

//Преобразуване от потребителски  в дисплейни координати
POINT userToDisp(Point p){
	POINT r;
	r.x = (int)(p.getX() / mx + WW / 2.);
	r.y = (int)(HH / 2. - p.getY() / my);
	return r;
}

//Изобразяване на координатни оси с деления в потребителски единици
void drawAxes(HWND hwnd){
	Line(Point(-USERX + 1, 0), Point(USERX - 1, 0)).draw(hwnd);
	Line(Point(0, -USERY + 1), Point(0, USERY - 1)).draw(hwnd);
	for (double x = -USERX + 1; x<USERX; x += 1)
		Line(Point(x, 0), Point(x, 0.15)).draw(hwnd);
	for (double y = -USERY + 1; y<USERY - 1; y += 1)
		Line(Point(0, y), Point(-0.15, y)).draw(hwnd);
}

//Изобразяване на квадратен маркер в работната област
void drawMarker(HWND hwnd, POINT p){
	HDC hdc = GetDC(hwnd);
	Rectangle(hdc, p.x - 2, p.y - 2, p.x + 3, p.y + 3);
	ReleaseDC(hwnd, hdc);
}

//Цифрово ехо на текущите координати на мишката в клиентския прозорец
void mouseEcho(HWND hwnd, LPARAM lParam){
	static const int place = DT_SINGLELINE | DT_BOTTOM | DT_LEFT;
	char mouf[30] = "",
		 spac[] = "                             ";
	RECT rect; HDC hdc; POINT pd; Point pu;
	pd.x = LOWORD(lParam), pd.y = HIWORD(lParam);
	pu = dispToUser(pd);
	//sprintf_s(mouf, 30, "%6.2f   %6.2f", pu.getX(), pu.getY());
	hdc = GetDC(hwnd);
		GetClientRect(hwnd, &rect);
		DrawText(hdc, spac, -1, &rect, place);
		DrawText(hdc, mouf, -1, &rect, place);
}

//Показва текст в средата на долния ред на клиентския прозорец
void showMess(HWND hwnd, const char * mess){
	char spac[] = "                                                           "
		          "                                                           ";
	RECT rect; HDC hdc;
	UINT mode = DT_BOTTOM | DT_CENTER | DT_SINGLELINE;
	hdc = GetDC(hwnd);
	GetClientRect(hwnd, &rect);
	DrawText(hdc, spac, -1, &rect, mode);
	DrawText(hdc, mess, -1, &rect, mode);
	ReleaseDC(hwnd, hdc);
	memcpy(charBuf, mess, 120);
}

void regShape(); //регистрация на създаден обект

//Приемане на съобщения за събития от мишка
LRESULT getMouseEvent(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
	POINT pp;
	switch (message){
	case WM_LBUTTONUP: //приемане на точка с ляв клик
		pp.x = LOWORD(lParam); pp.y = HIWORD(lParam);
		pntBuf[pntGot++] = pp; //запомняне в буфера
		if(!snapOn)drawMarker(hwnd, pp); //маркиране
		//корекция на положението на маркера при включен snap
		else pp=userToDisp(dispToUser(pp)), drawMarker(hwnd, pp);
		break;
	case WM_MOUSEMOVE:
		mouseEcho(hwnd, lParam);
		break;
	case WM_RBUTTONDOWN:
		//създаване на обект по достатъчен брой точки
		if (pntGot == pntsToTake || pntsToTake == -1)regShape();
		pntGot = 0; //подготовка за следващо въвеждане
		break;
	case WM_RBUTTONUP:
		InvalidateRect(hwnd, NULL, TRUE);
		break;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}

//Повторно изобразяване на клиентската област
void redrawAll(HWND hwnd){
	PAINTSTRUCT ps; HDC hdc; UINT i;
	//Следващото е необходима реакция на WM_PAINT:
	hdc = BeginPaint(hwnd, &ps);	EndPaint(hwnd, &ps);
	//Полиморфно изчертаване на всички обекти
	for (i = 0; i < iCount; i++)
        pt[i]->draw(hwnd);
	drawAxes(hwnd);
	showMess(hwnd, charBuf);
}

//=====================================================================================
//Следващите три функции се допълват при добавяне на нов тип геометричен обект
//=====================================================================================

//Текст с описание на наличната функционалност
void help(){
    /*
	//using std::cout; using std::endl;
	cout<<"\tГЕНЕРАТОР НА РАСТЕРИЗИРАНИ РАВНИННИ ГЕОМЕТРИЧНИ ОБЕКТИ\n\n";
	cout<<"Параметри на обектите са точки, задавани чрез ляв клик в работната област.\n";
	cout<<"Въведените точки са отбелязани с квадратен маркер.\n"
		  "Въвеждането се потвърждава с десен клик.\n"
		  "Тип на обект се избира с функционалните клавиши както следва:\n";
	cout<<"F1 - точка (по подразбиране). Въвежда се и се потвърждава незабавно.\n"
		  "F2 - отсечка. Въвеждат се две точки и се потвърждава.\n"
		  "F3 - отворен многоъгълник. Въвеждат се точки и се потвърждава.\n"
		  "F4 - затворен многоъгълник. Въвеждат се точки и се потвърждава.\n"
		  "F5 - правилен многоъгълник. Въвеждат се 2 точки и се потвърждава.\n"
		  "     Първата точка е център на описаната окръжност, а втората - връх.\n"
		  "     С клавишите за цифри 0-9 се избира брой на върховете (по подразбиране 3).\n"
		  "F6 - Окръжност. Задават се две точки: център и една периферна.\n"
		  "F7 - Квадрат. Задават се две точки: краища на диагонала.\n"
		  "F8 - Правоъгълник. Задават се 3 точки: краища на страна и точка,\n"
		  "     през която минава насрещната страна\n"
		  "F9 - Окръжност през три точки\n"
		  ;
	cout<<"С клавиш 'I' се превключва режимът на мащабиране: анизотропен/изотропен."<<endl;
	*/
}

//Приемане на съобщения от клавиатура
LRESULT getKbdEvent(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
	//Данни за активиране на различни типове примитиви чрез функционалните клавиши
	static char messages[][60] = { //текстови подсещания в полето
		"INPUT POINTS","INPUT LINES","INPUT POLYGON",
		"CLOSED POLYGON", "REGULAR POLYGON", "CIRCLE", "SQUARE",
		"RECTANGLE", "CIRCLE THROUGH 3 POINTS"
	};
	static int controlPointsNum[] = {1, 2, -1, -1, 2, 2, 2, 3 , 3};//изискван брой точки
	static char typeSymbols[] = {'p','L','P','C','R','O','S','E','T'};//означения

	int currentTypes = sizeof(controlPointsNum)/sizeof(int);//текущ брой типове
	if (message == WM_KEYDOWN){
		if(wParam>=VK_F1 && wParam<=VK_F12){
			int choice = wParam - VK_F1;
			if(choice>=currentTypes)choice=0; //защита от недопустим избор
			pntsToTake = controlPointsNum[choice];
			objType = typeSymbols[choice];
			showMess(hwnd,	messages[choice]);
		}
		//Други управляващи клавиши
		switch (wParam) {
			case VK_UP:
				if(snapOn)gridDens*=2; else snapOn=true;
				break;
			case VK_DOWN:
				if(snapOn)gridDens/=2;
				if(gridDens==0) gridDens=1, snapOn=false;
				break;
		}
	}
	if(message == WM_CHAR){//използвани символни клавиши
		char cc = wParam;
		switch(cc){
			case 27: exit(0); //Esc
			//За брой страни на правилен многоъгълник
			case '3': case '4': case '5': case '6': case '7':
			case '8': case '9':	sidesRegPoly = cc - '0';
				break;
			case 'I': //смяна на типа мащабиране
				scaleIsotropic = !scaleIsotropic;
				rescale();
				InvalidateRect(hwnd, NULL, TRUE);
				break;
			case 'h': case 'H': help();
				break;
		}
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}

//Създаване на геометричен обект в динамичната памет и регистрирне в масива
void regShape(){//работи с глобални променливи
	switch (objType){
	case 'p':
		pt[iCount] = new Point(pntBuf[0]);
		break;
	case 'L':
		pt[iCount] = new Line(pntBuf[0],pntBuf[1]);
		break;
	case 'P':
		pt[iCount] = new PolyOpen(pntBuf, pntGot);
		break;
	case 'C':
		pt[iCount] = new PolyClosed(pntBuf, pntGot);
		break;
	case 'R':
		pt[iCount] = new PolyRegular(pntBuf[0],pntBuf[1], sidesRegPoly);
		break;
	case 'O':
		pt[iCount] = new EquilateralTriengle(pntBuf[0],pntBuf[1]);
		break;
	case 'S':
		pt[iCount] = new Square(pntBuf[0],pntBuf[1]);
		break;
	case 'E':
		pt[iCount] = new CRectangle(pntBuf[0],pntBuf[1],pntBuf[2]);
		break;
	case 'T':
		pt[iCount] = new Circumscriber(pntBuf[0],pntBuf[1],pntBuf[2]);
		break;
	}
	iCount++;
}


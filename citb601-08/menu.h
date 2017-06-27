#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

//Идентификатори на избор от меню
	//елементи от хоризонталното меню
	const UINT IDM_PLATO      = 50001;
	const UINT IDM_POLYHEDRA  = 50002;
	const UINT IDM_JOHNSON    = 50003;
	//елементи за избор на тип (разчита се да са последователни):
	const UINT IDM_TETRAHEDRON    = 50010;
	const UINT IDM_HEXAHEDRON     = 50011;
	const UINT IDM_OCTAHEDRON     = 50012;
	const UINT IDM_DODECAHEDRON   = 50013;
	const UINT IDM_ICOSAHEDRON    = 50014;
	const UINT IDM_PYRAMID        = 50015;
	const UINT IDM_PRISM          = 50016;
	const UINT IDM_ANTIPRISM      = 50017;
	const UINT IDM_REG_PRISM      = 50018;
	const UINT IDM_REG_ANTIPRISM  = 50019;
	const UINT IDM_CUPOLA         = 50020;
	const UINT IDM_ROTUNDA        = 50021;


//Конструиране на меню
HMENU mkMenu(){
	//Идентификаторита IDM_ са декларирани в началото на файла
	HMENU hMenu, hMenuPopup;
	//два манипулатора за меню: хоризонтално и падащо
	hMenu = CreateMenu () ;
	hMenuPopup = CreateMenu () ;

	//Добавят се елементи към падащото меню...
	AppendMenu (hMenuPopup, MF_STRING,    IDM_TETRAHEDRON,   "&Tetrahedron") ;
	AppendMenu (hMenuPopup, MF_STRING,    IDM_HEXAHEDRON,    "&Hexahedron") ;
	AppendMenu (hMenuPopup, MF_STRING,    IDM_OCTAHEDRON,    "&Octahedron") ;
	AppendMenu (hMenuPopup, MF_STRING,    IDM_DODECAHEDRON,  "&Dodecahedron") ;
	AppendMenu (hMenuPopup, MF_STRING,    IDM_ICOSAHEDRON,   "&Icosahedron") ;
	//...и то се прикача като първи елемент на хоризонталното
	AppendMenu (hMenu, MF_POPUP, (UINT_PTR) hMenuPopup,       "&Plato solids") ;

	//Взема се нов манипулатор за следващо падащо меню
	hMenuPopup = CreateMenu () ;
	//Изгражда се
	AppendMenu (hMenuPopup, MF_STRING,    IDM_PYRAMID,       "P&yramid") ;
	AppendMenu (hMenuPopup, MF_STRING,    IDM_PRISM,         "P&rism") ;
	AppendMenu (hMenuPopup, MF_STRING,    IDM_ANTIPRISM,     "&Antiprism") ;
	AppendMenu (hMenuPopup, MF_SEPARATOR, 0, "");
	AppendMenu (hMenuPopup, MF_STRING,    IDM_REG_PRISM,      "&Regular prism") ;
	AppendMenu (hMenuPopup, MF_STRING,    IDM_REG_ANTIPRISM,  "R&egular antiprism") ;
	//и се прикача:
	AppendMenu (hMenu, MF_POPUP, (UINT_PTR) hMenuPopup,       "P&olyhedra");
	hMenuPopup = CreateMenu () ;
	//Изгражда се
	AppendMenu (hMenuPopup, MF_STRING,    IDM_CUPOLA,      "&Cupola") ;
	AppendMenu (hMenuPopup, MF_STRING,    IDM_ROTUNDA,     "&Rotunda") ;
	AppendMenu (hMenu, MF_POPUP, (UINT_PTR) hMenuPopup,        "&Johnson solids");
	return hMenu;
}
//Действия при избор от меню
LRESULT getMenuEvent(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
    globals::model = wParam - IDM_TETRAHEDRON; genmodel();
	return 0;
}



#endif // MENU_H_INCLUDED

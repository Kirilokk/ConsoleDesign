#include <windows.h>
#include <iostream>
#include <conio.h>
#include <ctime>


using namespace std;
CONSOLE_SCREEN_BUFFER_INFO csbiInfo;			  //Структура для зберігання інформації про вікно консолі


void draw(HWND hwnd, HDC hdc, HANDLE hStdOut);
int myRand();							  //Функція що задає потрібні координати для комет
void stars(HDC hdc);
void comets(HDC hdc);


void main()
{

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);	  //Отримуємо  дескриптор(структ данних що використ консоль вікна консолі
    GetConsoleScreenBufferInfo(hStdOut, &csbiInfo);	  //Отримуємо інформацію про буфер консолі

    HWND hwnd = GetConsoleWindow();				  // идентификатор окна консоли
    HDC hdc = GetDC(hwnd);					  // дескриптор контекста консольного окна

    Sleep(100);							  //Для того щоб малюнок не створився раніше того коли консоль стане видимою


    COORD bufferSize = { 1700, 900 };
    MoveWindow(hwnd, 0, 0, 1700, 900, TRUE);		  //Встановлємо розмір вікна
    draw(hwnd, hdc, hStdOut);					  //Виклик функції графіки


    int iKey = 1;
    while (iKey != 27) {					   // Задержка и выход по клавише ESC
	  if (_kbhit()) {
		iKey = _getch();
		switch (iKey)
		{
		case 112:
		    draw(hwnd, hdc, hStdOut);			   // перерисовка консоли по клавише 'p'
		    break;
		}
	  }
    }
    ReleaseDC(hwnd, hdc);					   //освобождаем дескрипторы консоли
}

void draw(HWND hwnd, HDC hdc, HANDLE hStdOut)
{
    SetConsoleTitle("Star Space");
    COLORREF COLOR = RGB(255, 255, 255);			  //COLORREF структура яка створює макос ргб
    

									   //Структура POINT для зберігання координат точок що знаходять в масиві

    POINT Africa[19] = { {525,540} ,{500,527} ,{470,530} ,{425,560},{402,580},{405,610},{460,620},{480,690},	  //Координати точок для Африки
    {483,700},{476,720},{500,740},{510,740},{520,720},{530,670},{550,630},{545,620},{575,570},{550,570} ,{540,560} };

    POINT Madagaskar[7] = { {565,680},{545,690} ,{547,730} ,{555,735} ,{573,710} ,{571,690},{ 565,680} };		  //Координати точок для мадагаскару

    POINT Europe[30] = { { 470,462} , { 490,466} ,{ 500,466} ,{ 520,466} ,{ 540,466} , { 550,474} , { 580,480} ,	  //Координати точок для Європи
    { 610,500} ,{ 595,550} ,{ 575,565} ,{ 565,550} ,{ 535,535} ,{ 560,530} ,{ 545,505} ,{ 525,500} , { 520,520} ,
    { 510,530} ,{ 500,520} ,{ 510,510} ,{ 510,500}, {500,505}, {475,510}, {465,530},{455,520} ,{445,525} ,{435,505},
    {425,475} ,{450,485},{ 460,478} };

    //Координати точок для астероїдів

    POINT Ast[6] = { {500,300} ,{530,310},{520,330},{500,330},{480,310},{500,300} };
    POINT Ast1[6] = { {1400,600} ,{1435,595},{1435,615},{1420,635},{1400,600}};
    POINT Ast2[7] = { {1000,100} ,{1020,140},{1015,150},{1000,150},{998,142},{990,120},{1000,100}};
    POINT Ast3[8] = { {205,500} ,{220,505},{240,500},{243,515},{237,530},{222,530},{205,515},{205,500} };
    POINT Ast4[8] = { {800,495} ,{815,500},{845,523},{810,523},{803,508},{800,495} };
    //Координати точок для астероїдів
    

    stars(hdc);
    comets(hdc);



    COLORREF penSaturn = RGB(159, 145, 130);
    SelectObject(hdc, CreatePen(PS_SOLID, 3, penSaturn));		  //Поміщуємо перо в контекст
    SelectObject(hdc, CreateSolidBrush(RGB(176, 164, 151)));
    Ellipse(hdc, 100, 100, 200, 200);					  //Малюємо планету сатурн

    COLORREF penRing = RGB(130, 130, 130);
    SelectObject(hdc, CreatePen(PS_SOLID, 9, penRing));
    Arc(hdc, 80, 120, 220, 180, 118, 135, 183, 135);			  //Кільце сатурна

    COLORREF penSun = RGB(255, 186, 117);
    SelectObject(hdc, CreatePen(PS_SOLID, 3, penSun));
    SelectObject(hdc, CreateSolidBrush(RGB(244, 248,91)));
    Ellipse(hdc, 1300, 75, 1500, 275);					  //Малємо сонце


    COLORREF penEarth = RGB(0, 0, 255);
    HBRUSH brush = CreateSolidBrush(RGB(83, 83, 255));		  //Створюємо суцільний пензлик для замальовування вмісту
    SelectObject(hdc, CreatePen(PS_SOLID, 3, penEarth));		  //Робимо пензлик активним для роботи
    HRGN rgnEll = CreateEllipticRgn(350, 450, 650, 750);		  //Cтворюємо область(коло) для замальовування
    FillRgn(hdc, rgnEll, brush);						  //Заповнюємо область пензликом

    HRGN rgnEll1 = CreateEllipticRgn(460, 450, 550, 470);		  //Створюємо область(коло) для імітації полюсу
    FillRgn(hdc, rgnEll1, CreateSolidBrush(RGB(255, 255, 255)));	  //Заповнюємо область пензликом
   
    HBRUSH brshCont = CreateSolidBrush(RGB(43, 233, 15));		  //Створюємо пензлик для замальовування континенту
    HRGN bgRgn1 = CreatePolygonRgn(Africa, 19, ALTERNATE);		  //Cтворюємо область(многокутник) для замальовування
    FillRgn(hdc, bgRgn1, brshCont);						  //Заповнюємо область пензликом
    HRGN bgRgn2 = CreatePolygonRgn(Madagaskar, 7, ALTERNATE);//
    FillRgn(hdc, bgRgn2, brshCont);//
    HRGN bgRgn3 = CreatePolygonRgn(Europe, 29, ALTERNATE);//
    FillRgn(hdc, bgRgn3, brshCont);//


    HBRUSH brsh2 = CreateSolidBrush(RGB(80, 80, 250));		  //Створюємо пензлик для замальовування планети Уран
    HRGN Uran = CreateEllipticRgn(1100, 600,1225, 725);//
    FillRgn(hdc, Uran, brsh2);//
    COLORREF penUran = RGB(195, 195, 195);
    SelectObject(hdc, CreatePen(PS_SOLID, 0.5, penUran));
    SelectObject(hdc, CreateSolidBrush(RGB(103, 95, 103)));
    Ellipse(hdc,1120, 650, 1152, 672);
    Ellipse(hdc, 1182, 682, 1205, 695);


    COLORREF penAst = RGB(255, 255, 255);
    HBRUSH brushAst = CreateSolidBrush(RGB(0, 0, 0));
    SelectObject(hdc, brushAst);
    SelectObject(hdc, CreatePen(PS_SOLID, 1, penAst));

    Polyline(hdc, Ast, 6);							//Функція малює ламану що проходить через точки
    Polyline(hdc, Ast1, 5);//
    Polyline(hdc, Ast2, 7);//
    Polyline(hdc, Ast3, 8);//
    Polyline(hdc, Ast4, 6);//

}

int myRand()						   //Видозмінена функція rand
{
    int res = rand() % 60;
    if (res < 30) {
	  return res + 20;
    }
    return res;
}

void stars(HDC hdc) {					  //Функція, що створює зірки
    COLORREF COLOR = RGB(255, 255, 255);		  //Задаємо колір для зірок
    int x, y;

    for (int i = 1; i < 1000; i++) {		//Цикл, що створює 1000 зірок з координатами
	  x = rand() % 1700;				//що задаються за допомогою rand() з урахуванням 
	  y = rand() % 900;				//Розміру вікна
	  SetPixel(hdc, x, y, COLOR);			//Встановлюємо піксель білого кольору в координатах х та у
    }
}

void comets(HDC hdc) {					 //Функція, що створює комети

    int xCom, yCom;
    HPEN Pen2 = CreatePen(PS_SOLID, 1, RGB(198, 255, 255));
    SelectObject(hdc, Pen2);

    for (int i = 0; i < 10; i++) {			    //Цикл, що створює 10 комет з координатами
	  xCom = rand() % 1650;				    //що задаються за допомогою rand() з урахуванням
	  yCom = rand() % 900;				    //Розміру вікна

	  MoveToEx(hdc, xCom - myRand(), yCom - 15, NULL);
	  LineTo(hdc, xCom, yCom);			    //Малюємо лінію після комети
    }
}



////////////////////////////////////////////////////////////////

///// PROYECTO FINAL
//// LENGUAJES ENSAMBLADOR
/// LESLIE SARAHY CAZARES MENDOZA
// GRUPO 02

////////////////////////////////////////////////////////////////



#define WIN32_LEAN_AND_MEAN


#include <stdio.h>
#include <dinput.h>
#include <gdiplus.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <string>
#include <mmsystem.h>
#include <windows.h>
#include <fstream>
#include <CommDlg.h>
#include <conio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include "string"
#include <cstring>
#include <iostream>
#pragma comment(lib, "winmm.lib")


using namespace Gdiplus;
using namespace std;

// ESTRUCTURAS

// coordenadas de los sprites en pantalla en un plano 2D
struct POSITION {
	int X;
	int Y;
};
//dimensiones de los sprites
struct DIMENSION {
	int ANCHO;
	int ALTO;
};
//teclas
struct Input
{
	enum Keys
	{
		Backspace = 0x08, Tab,
		Clear = 0x0C, Enter,
		Shift = 0x10, Control, Alt,
		Escape = 0x1B,
		Space = 0x20, PageUp, PageDown, End, Home, Left, Up, Right, Down,
		Zero = 0x30, One, Two, Three, Four, Five, Six, Seven, Eight, Nine,
		A = 0x41, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
		NumPad0 = 0x60, NumPad1, NumPad2, NumPad3, NumPad4, NumPad5, NumPad6, NumPad7, NumPad8, NumPad9,
		F1 = 0x70, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12
	};
}input;



// VARIABLES 
const int ANCHO_VENTANA = 800;
const int ALTO_VENTANA = 500;
const int BPP = 4;
const int TICK = 100;
int Escalar = 2;
const unsigned int BLUE = 0xFF0000FF;
const unsigned int GREEN = 0xFF00FF00;
const unsigned int RED = 0xFFFF0000;
const unsigned int WHITE = 0xFFFFFFFF;
const unsigned int BLACK = 0x00000000;

POSITION posSprite;
POSITION posSprite02;
POSITION posSprite03;
POSITION posRectangulo02;
POSITION posRectangulo03;
POSITION posRectangulo04;
POSITION pospan;
DIMENSION fondoso;
DIMENSION nycanffso;
DIMENSION nycanffsocaminando;
DIMENSION nycanffsocolor;
DIMENSION espaciaffles;
DIMENSION espaciaffles01;
DIMENSION espaciaffles02;
DIMENSION panso;

DIMENSION otroFondoso;
DIMENSION otroFondoso01;



int *ptrBuffer;

unsigned char * fondo;
unsigned char * otroFondo;
unsigned char * otroFondo01;
unsigned char * nycatcaminando;
unsigned char * nycat;
unsigned char * nycatcolor;
unsigned char * Espacial;
unsigned char * Espacial01;
unsigned char * Espacial02;
unsigned char * pan;


bool KEYS[256];
int IndiceDelSprite = 0;
int MovimientosoVentana;
int MoverSprite;
int coloroso = 0;
bool movimientoso = false;
bool movimientoso02 = false;
bool movimientoso03 = true;
bool movimientoso04 = true;
bool movimientoso05 = false;
bool movimientoso06 = false;
bool movimientoso07 = false;
bool aparecernycat = false;
bool aparecerpan = true;
bool caminanycat = false;
bool cantanycat = true;
bool colornycat = false;
bool hacercolor = true;
bool aparecerEspacial = false;
bool escalarEspacial = false;
bool escalarse = false;
bool cambiofondo = false;
bool colortrue = false;
int contador = 0;
int contador01 = 0;

char mp3[MAX_PATH] = "", comando[MAX_PATH];


//Funciones
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
void MainRender(HWND hWnd);
void Init();
void KeysEvents();
unsigned char * CargaImagen(WCHAR rutaImagen[], DIMENSION * dmn);
POSITION setPosition(int x, int y);
void DibujaFondo(int *buffer, int *imagen, DIMENSION fondoso);
void Dibujanycatcaminando(int *buffer, int *imagen, DIMENSION nycanffsocaminando);
void Dibujanycat(int *buffer, int *imagen, DIMENSION nycanffso);
void DibujaEspacial(int *buffer, int *imagen, DIMENSION espaciaffles);
void DibujaEspacial02(int *buffer, int *imagen, DIMENSION espaciaffles02);
void Dibujapan(int *buffer, int *imagen, DIMENSION panso);


int WINAPI wWinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,PWSTR pCmdLine,	int nCmdShow)
{

	

	WNDCLASSEX wc;									
	HWND hWnd;
	MSG msg;

	TCHAR szAppName[] = TEXT("PROYECTO_LENS");
	TCHAR szAppTitle[] = TEXT("NYPAN");

	hInstance = GetModuleHandle(NULL);				

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc = (WNDPROC)WndProc;					// WndProc Handles Messages
	wc.cbClsExtra = 0;									// No Extra Window Data
	wc.cbWndExtra = 0;									// No Extra Window Data
	wc.hInstance = hInstance;							// Set The Instance	
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);			// No Background Required For GL
	wc.lpszMenuName = NULL;									// We Don't Want A Menu	
	wc.lpszClassName = szAppName;							// Set The Class Name
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&wc))									// Attempt To Register The Window Class
	{
		MessageBox(NULL,
			L"Fallo al registrar clase (Failed To Register The Window Class).",
			L"ERROR",
			MB_OK | MB_ICONEXCLAMATION);
		return 0;
	}

	hWnd = CreateWindowEx(
		WS_EX_CLIENTEDGE | WS_EX_APPWINDOW | WS_EX_WINDOWEDGE,	// Extended Style For The Window
		szAppName,							// Class Name
		szAppTitle,							// Window Title
		WS_OVERLAPPEDWINDOW |				// Defined Window Style
		WS_CLIPSIBLINGS |					// Required Window Style
		WS_CLIPCHILDREN,					// Required Window Style
		0, 0,								// Window Position
		ANCHO_VENTANA,						// Calculate Window Width
		ALTO_VENTANA,						// Calculate Window Height
		NULL,								// No Parent Window
		NULL,								// No Menu
		hInstance,							// Instance
		NULL);								// Pass this class To WM_CREATE								

	if (hWnd == NULL) {
		MessageBox(NULL,
			L"Error al crear ventana (Window Creation Error).",
			L"ERROR",
			MB_OK | MB_ICONEXCLAMATION);
		return 0;
	}

	SetForegroundWindow(hWnd);						// Slightly Higher Priority
	Init();
	ShowWindow(hWnd, nCmdShow);
	SetFocus(hWnd);

	SetTimer(hWnd, TICK, TICK, NULL);
	ZeroMemory(&msg, sizeof(MSG));

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return(int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)									
	{
	case WM_CREATE:

		PlaySound(TEXT("dave_guetta.mp3"), NULL, SND_ASYNC);
		/*strcpy(mp3, "dave_guetta.mp3");
		sprintf_s(comando, "open \"%s\" alias MP3", mp3);
		mciSendString((LPCWSTR)comando, NULL, 0, 0);
		mciSendString(TEXT("play MP3"), NULL, 0, 0);*/

		break;
	case WM_TIMER:
		if (wParam == TICK)
		{
			MainRender(hWnd);
		}
		break;
	case WM_PAINT:
	{
		HDC hdc;
		PAINTSTRUCT ps;
		hdc = BeginPaint(hWnd, &ps);

		BITMAP bm;
		HBITMAP h_CMC = CreateBitmap(ANCHO_VENTANA, ALTO_VENTANA, 1, 32, ptrBuffer);
		HDC hdcMem = CreateCompatibleDC(hdc);
		HBITMAP hbmOld = (HBITMAP)SelectObject(hdcMem, h_CMC);
		GetObject(h_CMC, sizeof(bm), &bm);

		BitBlt(hdc, 0, 0, ANCHO_VENTANA, ALTO_VENTANA, hdcMem, 0, 0, SRCCOPY);

		DeleteObject(h_CMC);
		SelectObject(hdcMem, hbmOld);
		DeleteDC(hdcMem);
		DeleteObject(hbmOld);
	}
	break;
	case WM_KEYDOWN:
	{
		KEYS[wParam] = true;
	}
	break;
	case WM_KEYUP:
	{
		KEYS[wParam] = false;
	}
	break;
	case WM_CLOSE:
	{
		DestroyWindow(hWnd);
	}
	break;
	case WM_DESTROY:
	{
		mciSendString(TEXT("stop MP3"), NULL, 0, 0);
		mciSendString(TEXT("close MP3"), NULL, 0, 0);
		KillTimer(hWnd, TICK);
		PostQuitMessage(0);
	}
	break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	return 0;
}




// Funcion usada para la inicializacion de variables y reserva de espacio en memoria.
void Init()
{
	posSprite = setPosition(200, 350);
	posSprite02 = setPosition(600, 10);
	posSprite03 = setPosition(50, 10);
	pospan = setPosition(10,20);

	for (int i = 0; i < 256; i++)
	{
		KEYS[i] = false;
	}

	//Inicializar el puntero tipo int 'ptrBuffer' que contiene la direccion inicial  del area de memoria reservada para el despliegue de sprites/imagenes.
	ptrBuffer = new int[ANCHO_VENTANA * ALTO_VENTANA];


	otroFondo01 = CargaImagen(TEXT("fondojigglypuffso00.jpg"), &otroFondoso01);
	otroFondo = CargaImagen(TEXT("nypan_fondo.jpg"), &otroFondoso);
	fondo = CargaImagen(TEXT("nypan_fondo02.jpg"), &fondoso);
	nycatcaminando = CargaImagen(TEXT("nypan_arcoiris.png"), &nycanffsocaminando);
	nycat = CargaImagen(TEXT("nypan.png"), &nycanffso);
	nycatcolor = CargaImagen(TEXT("spritesjigglypuffcambiodecolor.png"), &nycanffsocolor);
	Espacial = CargaImagen(TEXT("sun.png"), &espaciaffles);
	Espacial01 = CargaImagen(TEXT("moon.png"), &espaciaffles01);
	Espacial02 = CargaImagen(TEXT("star.png"), &espaciaffles02);
	pan = CargaImagen(TEXT("pan.png"), &panso);
	
}

// Funcion principal. Encargada de hacer el redibujado en pantalla cada intervalo (o "tick") del timer que se haya creado.
void MainRender(HWND hWnd)
{
	KeysEvents();

	if (cambiofondo == false) {
		DibujaFondo(ptrBuffer, (int*)fondo, fondoso);	
		
		if (aparecerpan == true) {


			Dibujapan(ptrBuffer, (int*)pan, panso);

			if (movimientoso04 == true) {
				if (movimientoso05 == true) {
					pospan.Y += 10;
					if (pospan.Y > 250) {
						movimientoso05 = false;
					}
				}
				else {
					pospan.Y -= 10;
					if (pospan.Y == 0) {
						movimientoso05 = true;
					}
				}


				if (movimientoso06 == true) {
					pospan.X += 10;
					if (pospan.X > 600) {
						movimientoso06 = false;
					}
				}
				else {
					pospan.X -= 10;
					if (pospan.X == 0) {
						movimientoso06 = true;
					}
				}
			}
		}
		else {
			DibujaEspacial(ptrBuffer, (int*)Espacial01, espaciaffles01);

		}
	}	
		else {

		DibujaFondo(ptrBuffer, (int*)otroFondo, otroFondoso);
		DibujaEspacial(ptrBuffer, (int*)Espacial, espaciaffles);
		DibujaEspacial02(ptrBuffer, (int*)Espacial02, espaciaffles02);

		switch (contador) {

		case 0:

			posSprite03 = setPosition(50, 10);
			contador++;
			break;
		case 1:

			posSprite03 = setPosition(100, 200);
			contador++;
			break;
		case 2:
			posSprite03 = setPosition(600, 100);
			contador++;
			break;
		case 3:
			posSprite03 = setPosition(700, 150);
			contador++;
			break;
		case 4:
			posSprite03 = setPosition(550, 350);
			contador++;
			break;
		case 5:
			posSprite03 = setPosition(750, 400);
			contador++;
			break;
		case 6:
			posSprite03 = setPosition(10, 400);
			contador++;
			break;
		case 7:
			posSprite03 = setPosition(400, 300);
			contador = 0;
			break;
		}
		cambiofondo = false;
	}

		

	if (aparecernycat == true && cantanycat == true) {


			Dibujanycat(ptrBuffer, (int*)nycat, nycanffso);
		}
	

	if (caminanycat == true) {

		Dibujanycatcaminando(ptrBuffer, (int*)nycatcaminando, nycanffsocaminando);
		if (movimientoso03 == true) {
			if (movimientoso02 == true) {
				posSprite.Y += 10;
				if (posSprite.Y > 350) {
					movimientoso02 = false;
				}
			}
			else {
				posSprite.Y -= 10;
				if (posSprite.Y == 0) {
					movimientoso02 = true;
				}
			}
		}
		
		caminanycat = false;
		cantanycat = true;
		movimientoso03 = false;
	}

	if (colortrue == true) {
		coloroso = 3;
		caminanycat = false;
		cantanycat = true;
	}
	else {

		coloroso = 0;
	}

	/*if (aparecerEspacial == true) {
		if (escalarEspacial == true) {
			
		}

		if (escalarEspacial == false) {
			DibujaEspacial02(ptrBuffer, (int*)Espacial02, espaciaffles02);
		}
	}*/


	//Funciones que deberan estar el final de la funcion de Render.
	InvalidateRect(hWnd, NULL, FALSE);
	UpdateWindow(hWnd);
}

// Funcion que regresa la posicion del sprite en pantalla.
POSITION setPosition(int x, int y) {
	POSITION p;
	p.X = x;
	p.Y = y;
	return p;
}



// Funcion para manejar eventos del teclado dependiendo de la(s) tecla(s) que se haya(n) presionado.
void KeysEvents()
{
	

	if (KEYS[input.D]) {
		if (MovimientosoVentana < 3520 && MovimientosoVentana >= 0) {
			MovimientosoVentana += 880 *4;
			aparecernycat = true;
			movimientoso04 = false;
			aparecerpan = false;

		} 
		
    }

	if (KEYS[input.Up]) {

		

		if (MovimientosoVentana < 13440 && MovimientosoVentana >= 3520) {
			colortrue = true;
		}
		else {
			escalarse = true;
		}

		
		
	}
	if (KEYS[input.Right]) {

		if (MovimientosoVentana < 13440 && MovimientosoVentana >= 3520) {
			cambiofondo = true;
			movimientoso = false;
			MovimientosoVentana += 20*4;
			cantanycat = false;
			caminanycat = true;
			movimientoso03 = true;
			
		}	
	}
	if (KEYS[input.Down]) {
		
		if (MovimientosoVentana < 13440 && MovimientosoVentana >= 3520) {
			colortrue = false;
		}
		else {
			escalarse = false;
		}
	
	}
	if (KEYS[input.Left]) {
		if (MovimientosoVentana <= 13440 && MovimientosoVentana > 3520) {

			
			cambiofondo = true;
			movimientoso = true;
			MovimientosoVentana -= 20*4;
			cantanycat = false;
			caminanycat = true;
			movimientoso03 = true;
			
		}
	}
}

// Funcion para cargar imagenes
unsigned char * CargaImagen(WCHAR rutaImagen[], DIMENSION * dmn)
{
	unsigned char * ptrImagen;
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR  gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	Bitmap *bitmap = new Bitmap(rutaImagen);
	BitmapData *bitmapData = new BitmapData;

	dmn->ANCHO = bitmap->GetWidth();
	dmn->ALTO = bitmap->GetHeight();

	Rect rect(0, 0, dmn->ANCHO, dmn->ALTO);

	//Reservamos espacio en memoria para la imagen
	bitmap->LockBits(&rect, ImageLockModeRead, PixelFormat32bppRGB, bitmapData);

	//"pixels" es el puntero al area de memoria que ocupa la imagen
	unsigned char* pixels = (unsigned char*)bitmapData->Scan0;

	//"tamaño" lo usaremos para reservar los bytes que necesita la imagen. 
	//Para calcular la cantidad de bytes total necesitamos multiplicamos el area de la imagen * 4. 
	//Se multiplica por 4 debido a que cada pixel ocupa 4 bytes de memoria. Noten el 3er parametro de la funcion LockBits, dos lineas de codigo arriba.
	//PixelFormat32bppARGB -> Specifies that the format is 32 bits per pixel; 8 bits each are used for the alpha, red, green, and blue components.
	//Mas info: https://msdn.microsoft.com/en-us/library/system.drawing.imaging.pixelformat(v=vs.110).aspx
	int tamaño;
	tamaño = dmn->ANCHO * dmn->ALTO * 4;
	//hagamos un try de la reserva de memoria
	try
	{
		ptrImagen = new unsigned char[tamaño];
	}
	catch (...)
	{
		return NULL;
	}

	//Después de este for, ptrImagen contiene la direccion en memoria de la imagen.
	for (int i = 0, j = tamaño; i < j; i++)
	{
		ptrImagen[i] = pixels[i];
	}
	bitmap->UnlockBits(bitmapData);
	delete bitmapData;
	delete bitmap;

	GdiplusShutdown(gdiplusToken);

	return ptrImagen;
}

// Codigo en Lenguaje Ensamblador :c
#pragma region LENS_CODE


/*void DibujaFondo(int * buffer, int * imagen, DIMENSION dmn) {
	__asm {
		; Inicializar registros indices
		; con la direccion inicial en memoria de la imagen a desplegar(fuente->imagen->registro indice fuente->ESI)
		; y del area de memoria reservada para el despliegue(destino->buffer->registro indice destino->EDI)
		mov esi, imagen
		mov edi, buffer

		; Cargar la direccion en memoria de la variable 'dmn' el registro base(EBX). 'dmn' es la estructura con el ANCHO y ALTO.
		lea ebx, dmn

		; Transferir o copiar 4 bytes en memoria a partir de la direccion en memoria especificada por EBX;
		; son 4 bytes porque el operando destino es de 4 bytes en este caso es el registro acumulador(EAX).
			; Es decir, EBX es un puntero a 'dmn' donde 'dmn' es de 8 bytes(4Bytes de la variable ANCHO y los siguientes 4Bytes de la variable ALTO),
			; entonces EAX = ANCHO
			mov eax, [ebx]

			; sumar 4 al registro puntero(EBX) para apuntar al siguiente elemento de la estructura DIMENSION el cual es ALTO y vendria siendo el otro factor de la multiplicacion
			add ebx, 4

			; Especificar el otro factor en la instruccion de multiplicacion que son los siguientes 4Bytes a partir de la direccion especificada por EBX(variable ALTO de DIMENSION)
			; Se multplican ANCHO(= EAX) * ALTO(= dword ptr[ebx])
			; con 'dword ptr [ebx]' estamos indicando que EBX se comporte como puntero tipo DWORD,
			; es decir, se esta especificando que se desean los 4Bytes(4Bytes = 1Dword) a partir de la direccion en memoria especificada por el registro EBX
			; el cual contiene la direccion inicial de la variable ALTO en la estructura DIMENSION.
			mul dword ptr[ebx]

			; el resultado de la multiplicacion anterior es del doble del tamano de los factores, en este caso los factores son de 4Bytes por lo que el resultado es de 8Bytes
			; y se encuentra en EDX : EAX donde EDX contiene los 4Bytes de mayor peso del producto de la multiplicacion y EAX contiene los 4Bytes de menor peso.
			; Como el producto de la multiplicacion sabemos y esperamos que es un valor con un tamano menor a 4Bytes entonces dicho resultado esta en EAX
			; y con la siguiente instruccion se lo copiamos al registro contador(ECX)
			; para posteriormente hacer el ciclo / bucle de leer cada pixel de la imagen en memoria y pasarlo al buffer(area de mem.reservada para el despliegue)
			mov ecx, eax

			; poner codigo para el bucle de leer pixel por pixel y transferirlo al buffer.
	}

	

}
*/


void DibujaFondo(int * buffer, int * imagen, DIMENSION dmn)
{
	int alto = dmn.ALTO, ancho = dmn.ANCHO;
	int temp;

	__asm {
		mov esi, imagen
		add esi, MovimientosoVentana
		mov edi, buffer
		mov ecx, ALTO_VENTANA
		Alturosho :
		mov temp, ecx
		mov ecx, ANCHO_VENTANA
			Anchosho :
		     mov eax, [esi]

			cmp coloroso, 0
			je Nocolor
			cmp coloroso, 1
			je Verde
			cmp coloroso, 2
			je Azul
			cmp coloroso, 3
			je Rojo

			Verde : and eax, GREEN
			Azul : and eax, BLUE
			Rojo : and eax, RED		
			
			
		    Nocolor:
		    mov[edi], eax
			add esi, BPP
			add edi, BPP
			loop Anchosho
			mov eax, ancho
			mul BPP
			add esi, eax
			mov eax, ANCHO_VENTANA
			mul BPP
			sub esi, eax
			mov ecx, temp
			loop Alturosho
	}
}

void Dibujanycat(int *buffer, int * imagen, DIMENSION dmn)
{
	int X = posSprite.X;
	int Y = posSprite.Y;
	int alto = dmn.ALTO;
	int ancho = dmn.ANCHO;
	int temp;
	int AnchoSprite = 0;
	int TotalSprite = 6;

	//Verifica el numero total de sprites que hay en la tira

	if (IndiceDelSprite <= TotalSprite) {
		IndiceDelSprite++;
	}
	else {
		IndiceDelSprite = 0;
	}



	__asm
	{

		mov edx, 0
		mov eax, ancho
		div TotalSprite
		mov AnchoSprite, eax
		cmp edx, 0
		je InicializarSprite
		inc AnchoSprite


		InicializarSprite :
		mov esi, imagen
			mov edi, buffer

			// Comparacion para ver si existe relacion con movientoso, este determina si hay que realizar un espejo
			//para el movimiento
			cmp movimientoso, 0
			je espejoshosho
			mov eax, TotalSprite
			mul BPP
			add esi, eax
			espejoshosho :
		mov eax, IndiceDelSprite
			mul AnchoSprite
			mul BPP
			add esi, eax

			//X,Y
			mov eax, X
			mul BPP
			add edi, eax
			mov eax, Y
			mul ANCHO_VENTANA
			mul BPP
			add edi, eax
			mov ecx, alto


			AlturochoSprite :
		mov temp, ecx
			mov ecx, AnchoSprite

			AnchochoSprite :
		mov eax, [esi]

			// Espejo para el ancho del sprite
			cmp movimientoso, 0
			je Espejosho
			sub esi, BPP
			jmp QuitarFondoso


			Espejosho :
		add esi, BPP
			QuitarFondoso :
		cmp eax, 0xFFFFFFFF
			je nomostrar




			cmp coloroso, 0
			je Nocolor
			cmp coloroso, 1
			je Rojo
			cmp coloroso, 2
			je Verde
			cmp coloroso, 3
			je Azul

			Rojo: and eax, RED
			Verde : and eax, GREEN
			Azul: and eax, BLUE



			Nocolor :
		mov[edi], eax
			stosd
			jmp Sig
			nomostrar :
		add edi, BPP
			Sig :
		loop AnchochoSprite
			mov eax, ANCHO_VENTANA
			mul BPP
			add edi, eax
			mov eax, AnchoSprite
			mul BPP
			sub edi, eax
			mov eax, ancho
			mul BPP
			add esi, eax
			mov eax, AnchoSprite
			mul BPP


			//Espejo para el largo del sprite
			cmp movimientoso, 0
			je espejoshoshosho
			add esi, eax
			jmp Reinicioso
			espejoshoshosho :
		sub esi, eax

			Reinicioso :
		mov ecx, temp
			dec ecx
			cmp ecx, 0
			je salir
			jmp AlturochoSprite
			salir :


	}

	

}

void Dibujanycatcaminando(int *buffer, int * imagen, DIMENSION dmn)
{
	int X = posSprite.X;
	int Y = posSprite.Y;
	int alto = dmn.ALTO;
	int ancho = dmn.ANCHO;
	int temp;
	int AnchoSprite = 0;
	int TotalSprite = 6;

	//Verifica el numero total de sprites que hay en la tira
	if (IndiceDelSprite <= TotalSprite) {
		IndiceDelSprite++;
	}
	else {
		IndiceDelSprite = 0;
	}
	_asm {
		mov edx, 0
		mov eax, ancho
		div TotalSprite
		mov AnchoSprite, eax
		cmp edx, 0
		je InicializarSprite
		inc AnchoSprite


		InicializarSprite :
		mov esi, imagen
			mov edi, buffer

			// Comparacion para ver si existe relacion con movientoso, este determina si hay que realizar un espejo
			//para el movimiento
			
			cmp movimientoso, 0
			je espejoshosho
			mov eax, TotalSprite
			mul BPP
			add esi, eax
			espejoshosho :
			mov eax, IndiceDelSprite
			mul AnchoSprite
			mul BPP
			add esi, eax


			//X,Y
			mov eax, X
			mul BPP
			add edi, eax
			mov eax, Y
			mul ANCHO_VENTANA
			mul BPP
			add edi, eax
			mov ecx, alto


			AlturochoSprite :
			mov temp, ecx
			mov ecx, AnchoSprite

			AnchochoSprite :
		    mov eax, [esi]
			
			// Espejo para el ancho del sprite
			cmp movimientoso, 0
			je Espejosho
			sub esi, BPP
			jmp QuitarFondoso


			Espejosho :
		    add esi, BPP
			QuitarFondoso :
		    cmp eax, 0xFFFFFFFF
			je nomostrar
			
				
				
				cmp coloroso, 0
				je Nocolor
				cmp coloroso, 1
				je Rojo
				cmp coloroso, 2
				je Verde
				cmp coloroso, 3
				je Azul

				Rojo : and eax, RED
				Verde : and eax, GREEN
				Azul : and eax, BLUE
			
				
				
				
				
			Nocolor :
		    mov[edi], eax
			stosd
			jmp Sig
			nomostrar :
			add edi, BPP
			Sig :
		    loop AnchochoSprite
			mov eax, ANCHO_VENTANA
			mul BPP
			add edi, eax
			mov eax, AnchoSprite
			mul BPP
			sub edi, eax
			mov eax, ancho
			mul BPP
			add esi, eax
			mov eax, AnchoSprite
			mul BPP


			//Espejo para el largo del sprite
			cmp movimientoso, 0
			je espejoshoshosho
			add esi, eax
			jmp Reinicioso
			espejoshoshosho :
		    sub esi, eax

			Reinicioso :
		    mov ecx, temp
			dec ecx
			cmp ecx, 0
			je salir
			jmp AlturochoSprite
			salir :
	}


}

void DibujaEspacial(int *buffer, int * imagen, DIMENSION dmn)
{
	int X = posSprite02.X;
	int Y = posSprite02.Y;
	int alto = dmn.ALTO;
	int ancho = dmn.ANCHO;
	int temp;
	int AnchoSprite = 0;
	int TotalSprite = 10;

	if (IndiceDelSprite <= TotalSprite) {
		IndiceDelSprite++;
	}
	else {
		IndiceDelSprite = 0;
	}

	
	
	__asm
		{

			mov edx, 0
			mov eax, ancho
			div TotalSprite
			mov AnchoSprite, eax
			cmp edx, 0
			je InicializarSprite
			inc AnchoSprite


			InicializarSprite :
			mov esi, imagen
				mov edi, buffer

				// Comparacion para ver si existe relacion con movientoso, este determina si hay que realizar un espejo
				//para el movimiento
				cmp movimientoso, 0
				je espejoshosho
				mov eax, TotalSprite
				mul BPP
				add esi, eax
				espejoshosho :
		     	mov eax, IndiceDelSprite
				mul AnchoSprite
				mul BPP
				add esi, eax

				//X,Y
				mov eax, X
				mul BPP
				add edi, eax
				mov eax, Y
				mul ANCHO_VENTANA
				mul BPP
				add edi, eax
				mov ecx, alto


				AlturochoSprite :
			mov temp, ecx
				mov ecx, AnchoSprite

				AnchochoSprite :
			mov eax, [esi]

				// Espejo para el ancho del sprite
				cmp movimientoso, 0
				je Espejosho
				sub esi, BPP
				jmp QuitarFondoso


				Espejosho :
			add esi, BPP
				QuitarFondoso :
			cmp eax, 0xFFFFFFFF
				je nomostrar



				cmp coloroso, 0
				je Nocolor
				cmp coloroso, 3
				je Verde

				
				Verde : and eax, GREEN
				

				Nocolor :
			mov[edi], eax
				stosd
				jmp Sig
				nomostrar :
			add edi, BPP
				Sig :
			loop AnchochoSprite
				mov eax, ANCHO_VENTANA
				mul BPP
				add edi, eax
				mov eax, AnchoSprite
				mul BPP
				sub edi, eax
				mov eax, ancho
				mul BPP
				add esi, eax
				mov eax, AnchoSprite
				mul BPP


				//Espejo para el largo del sprite
				cmp movimientoso, 0
				je espejoshoshosho
				add esi, eax
				jmp Reinicioso
				espejoshoshosho :
			sub esi, eax

				Reinicioso :
			mov ecx, temp
				dec ecx
				cmp ecx, 0
				je salir
				jmp AlturochoSprite
				salir :


		}
	
		}

void DibujaEspacial02(int *buffer, int * imagen, DIMENSION dmn)
{
	int X = posSprite03.X;
	int Y = posSprite03.Y;
	int alto = dmn.ALTO;
	int ancho = dmn.ANCHO;
	int temp;
	int AnchoSprite = 0;
	int TotalSprite = 4;



	if (IndiceDelSprite <= TotalSprite) {
		IndiceDelSprite++;
	}
	else {
		IndiceDelSprite = 0;
	}

	
		__asm
		{
			mov edx, 0
			mov eax, ancho
			div TotalSprite
			mov AnchoSprite, eax
			cmp edx, 0
			je InicializarSprite
			inc AnchoSprite


			InicializarSprite :
			mov esi, imagen
				mov edi, buffer

				// Comparacion para ver si existe relacion con movientoso, este determina si hay que realizar un espejo
				//para el movimiento
				cmp movimientoso, 0
				je espejoshosho
				mov eax, TotalSprite
				mul BPP
				add esi, eax
				espejoshosho :
			    mov eax, IndiceDelSprite
				mul AnchoSprite
				mul BPP
				add esi, eax

				//X,Y
				mov eax, X
				mul BPP
				add edi, eax
				mov eax, Y
				mul ANCHO_VENTANA
				mul BPP
				add edi, eax
				mov ecx, alto


				AlturochoSprite :
				mov temp, ecx
				mov ecx, AnchoSprite

				AnchochoSprite :
			mov eax, [esi]

				// Espejo para el ancho del sprite
				cmp movimientoso, 0
				je Espejosho
				sub esi, BPP
				jmp QuitarFondoso


				Espejosho :
			    add esi, BPP
				QuitarFondoso :
			    cmp eax, 0xFFFFFFFF
				je nomostrar


				cmp coloroso, 0
				je Nocolor
				cmp coloroso, 3
				je Verde
				
				Verde : and eax, GREEN

				Nocolor :
			    mov[edi], eax ////////// cambios aqui para el escalado
				stosd
				jmp Sig
				nomostrar :
			    add edi, BPP
				Sig :
			    loop AnchochoSprite
				mov eax, ANCHO_VENTANA
				mul BPP
				add edi, eax
				mov eax, AnchoSprite
				mul BPP
				sub edi, eax
				mov eax, ancho
				mul BPP
				add esi, eax
				mov eax, AnchoSprite
				mul BPP

				//Espejo para el largo del sprite
				cmp movimientoso, 0
				je espejoshoshosho
				add esi, eax
				jmp Reinicioso
				espejoshoshosho :
			sub esi, eax

				Reinicioso :
			mov ecx, temp
				dec ecx
				cmp ecx, 0
				je salir
				jmp AlturochoSprite
				salir :


		}
	
}

void Dibujapan(int *buffer, int *imagen, DIMENSION dmn) {

	int X = pospan.X;
	int Y = pospan.Y;
	int alto = dmn.ALTO;
	int ancho = dmn.ANCHO;
	int temp;
	int temp1, temp2 = 0;
	/*int AnchoSprite = 0;
	int TotalSprite = 4;*/


	//if (IndiceDelSprite <= TotalSprite) {
	//	IndiceDelSprite++;
	//}
	//else {
	//	IndiceDelSprite = 0;
	//}


	__asm
	{

		mov esi, imagen
		mov edi, buffer

		mov eax, X
		mul BPP
		add edi, eax

		mov eax, Y
		mul ANCHO_VENTANA
		mul BPP
		add edi, eax

		cmp escalarse, 0
		jne NoEscalar
		cld
		mov ecx, alto
		Alturocho :
		push ecx

			mov ecx, ancho
			Anchocho :
		    mov eax, [esi]
			cmp eax, 0xFFFFFFFF
			je nomostrar
			mov[edi], eax
			nomostrar :
		    add esi, BPP
			add edi, BPP
			loop Anchocho
			mov eax, ANCHO_VENTANA
			mul BPP
			add edi, eax
			mov eax, ancho
			mul BPP
			sub edi, eax

			mov eax, ancho
			mul BPP
			add esi, eax
			mov eax, ancho
			mul BPP
			sub esi, eax
			pop ecx
			loop Alturocho


			////////////////// Escalado
			NoEscalar :
		cmp escalarse, 0
			je Salir

			cld
			mov ecx, alto
			AlturochoEscalado :
		push ecx

			mov ecx, Escalar
			ScalaY :
		    push ecx

			mov ecx, ancho
			AnchochoEscalado :
		    mov eax, [esi]
			push ecx

			mov ecx, Escalar
			ScalarX :
		   cmp eax, 0xFFFFFFFF
			je nomostrarEscalado
			mov[edi], eax
			nomostrarEscalado :
		    add edi, BPP
			loop ScalarX

			pop ecx
			add esi, BPP
			loop AnchochoEscalado

			mov eax, ANCHO_VENTANA
			mul BPP
			add edi, eax
			mov eax, ancho
			mul BPP
			mul Escalar
			sub edi, eax

			mov eax, ancho
			mul BPP
			sub esi, eax
			pop ecx
			loop ScalaY

			mov eax, ancho
			mul BPP
			add esi, eax
			pop ecx
			loop AlturochoEscalado

			Salir :
	}






// Escalado fallido
	/*
	if (escalarse == true)
	{
		_asm{
		    mov esi, imagen
			mov edi, buffer

			mov eax, X
			mul BPP
			add esi, eax
			mov eax, Y
			mul ANCHO_VENTANA
			mul BPP
			add edi, eax

			mov ecx, alto
			AlturochoEscalado :
		    mov temp, ecx
			mov ecx, Escalar
			EscalarochoEscalado01 :
		    mov temp1, ecx

			mov ecx, ancho
			AnchochoEscalado :
		    mov eax, [esi]
		    mov temp2, ecx
			mov ecx, Escalar
			EscalarochoEscalado02 :		////////////////	
			cmp eax, 0xFFFFFFFF
			je nomostrar
			mov[edi], eax
			nomostrar :
			add edi, BPP
			loop EscalarochoEscalado02
			mov ecx, temp2
			add esi, BPP
			loop AnchochoEscalado
		
			mov eax, ANCHO_VENTANA
			mul BPP
			add edi, eax
			mov eax, ancho
			mul BPP
			mul Escalar
			sub edi, eax
			mov eax, ancho
			mul BPP
			sub esi, eax
			mov ecx, temp1
			loop EscalarochoEscalado01
			mov eax, ancho
			mul BPP
			add esi, eax

			mov ecx, temp
			loop AlturochoEscalado
	}

	}
	else{
		__asm
		{
			mov esi, imagen
			mov edi, buffer

			mov eax, X
			mul BPP
			add esi, eax
			mov eax, Y
			mul ANCHO_VENTANA
			mul BPP
			add edi, eax

			mov ecx, alto
			Alturochocho :
			    mov temp, ecx
				mov ecx, ancho
				Anchurochocho :
			    mov eax, [esi]
				cmp eax, 0xFFFFFFFF
				je nomostrarcho
				
				mov[edi], eax
				nomostrarcho :
				add esi, BPP
				add edi, BPP	
				loop Anchurochocho

				mov eax, ANCHO_VENTANA
				mul BPP
				add edi, eax
				mov eax, ancho
				mul BPP
				sub edi, eax
				mov eax, ancho
				mul BPP
				add esi, eax
				mov eax, ancho
				mul BPP
				sub esi, eax
				mov ecx, temp
				loop Alturochocho
		}
	}
	
	*/



// Escalado fallido con movimiento
/*
	if (escalarse == true) {
		
		__asm
		{

			mov edx, 0
			mov eax, ancho
			div TotalSprite
			mov AnchoSprite, eax
			cmp edx, 0
			je InicializarSprite01
			inc AnchoSprite


			InicializarSprite01 :
				mov esi, imagen
				mov edi, buffer

				// Comparacion para ver si existe relacion con movientoso, este determina si hay que realizar un espejo
				//para el movimiento
					cmp movimientoso, 0
					je EspejoEspejo
					mov eax, TotalSprite
					mul BPP
					add esi, eax
					EspejoEspejo :
					mov eax, IndiceDelSprite
					mul AnchoSprite
					mul BPP
					add esi, eax

				//X,Y
				mov eax, X
				mul BPP
				add edi, eax
				mov eax, Y
				mul ANCHO_VENTANA
				mul BPP
				add edi, eax
				mov ecx, alto


				//AlturochoSprite : //////////////
				//mov temp, ecx
				//mov ecx, AnchoSprite


				AlturochochoSprite :
				mov temp, ecx
				mov ecx, Escalar
				EscalarALTO :
				mov temp1, ecx
				mov ecx, AnchoSprite
				jmp fueradelescalado

				escalaraltosho :
				loop EscalarALTO

				fueradelescalado:
				AnchochochoSprite : ///////////////
				mov eax, [esi]
				mov temp2, ecx
				mov ecx, Escalar

				// Espejo para el ancho del sprite
				cmp movimientoso, 0
				je Espejosho01
				sub esi, BPP
				jmp QuitarFondososho


				Espejosho01 :
				add esi, BPP
				QuitarFondososho :
				cmp eax, 0xFFFFFFFF
				je nomostrarsho

				cmp coloroso, 0
				je Nocolorsho
				cmp coloroso, 3
				je Verdosho
				Verdosho : and eax, GREEN

				Nocolorsho :
				//Escalarocho1 :		////////////////
				mov[edi], eax
				add edi, BPP
				loop Nocolorsho
				mov ecx, temp2
				add esi, BPP



				 // mov[edi], eax ////////// cambios aqui para el escalado
				//  stosd
				jmp Sig
				nomostrarsho :
				add edi, BPP
				Sigsho :
				loop AnchochochoSprite
					mov eax, ANCHO_VENTANA
					mul BPP
					add edi, eax
					mov eax, AnchoSprite
					mul BPP
					mul Escalar
					sub edi, eax
					mov eax, AnchoSprite
					mul BPP
					add esi, eax
					mov eax, AnchoSprite
					mul BPP
					mov ecx, temp1
					cmp ecx, 1;
				jne escalaraltosho



				//Espejo para el largo del sprite
				cmp movimientoso, 0
				je espejoshoshoshosho
				add esi, eax
				jmp Reiniciosho
				espejoshoshoshosho :
				sub esi, eax

				Reiniciosho :
				mov ecx, temp
				dec ecx
				cmp ecx, 0
				je salirsho
				jmp AlturochochoSprite
				salirsho :


		}

	}
 else {
	 __asm
	 {
		 mov edx, 0
		 mov eax, ancho
		 div TotalSprite
		 mov AnchoSprite, eax
		 cmp edx, 0
		 je InicializarSprite
		 inc AnchoSprite


		 InicializarSprite :
		 mov esi, imagen
			 mov edi, buffer

			 // Comparacion para ver si existe relacion con movientoso, este determina si hay que realizar un espejo
			 //para el movimiento
			 cmp movimientoso, 0
			 je espejoshosho
			 mov eax, TotalSprite
			 mul BPP
			 add esi, eax
			 espejoshosho :
		 mov eax, IndiceDelSprite
			 mul AnchoSprite
			 mul BPP
			 add esi, eax

			 //X,Y
			 mov eax, X
			 mul BPP
			 add edi, eax
			 mov eax, Y
			 mul ANCHO_VENTANA
			 mul BPP
			 add edi, eax
			 mov ecx, alto


			 AlturochoSprite :
		 mov temp, ecx
			 mov ecx, AnchoSprite

			 AnchochoSprite :
		 mov eax, [esi]

			 // Espejo para el ancho del sprite
			 cmp movimientoso, 0
			 je Espejosho
			 sub esi, BPP
			 jmp QuitarFondoso


			 Espejosho :
		 add esi, BPP
			 QuitarFondoso :
		 cmp eax, 0xFFFFFFFF
			 je nomostrar


			 cmp coloroso, 0
			 je Nocolor
			 cmp coloroso, 3
			 je Verde

			 Verde : and eax, GREEN

			 Nocolor :
		 mov[edi], eax ////////// cambios aqui para el escalado
			 stosd
			 jmp Sig
			 nomostrar :
		 add edi, BPP
			 Sig :
		 loop AnchochoSprite
			 mov eax, ANCHO_VENTANA
			 mul BPP
			 add edi, eax
			 mov eax, AnchoSprite
			 mul BPP
			 sub edi, eax
			 mov eax, ancho
			 mul BPP
			 add esi, eax
			 mov eax, AnchoSprite
			 mul BPP

			 //Espejo para el largo del sprite
			 cmp movimientoso, 0
			 je espejoshoshosho
			 add esi, eax
			 jmp Reinicioso
			 espejoshoshosho :
		 sub esi, eax

			 Reinicioso :
		 mov ecx, temp
			 dec ecx
			 cmp ecx, 0
			 je salir
			 jmp AlturochoSprite
			 salir :


	 }

}
*/

}












#pragma endregion
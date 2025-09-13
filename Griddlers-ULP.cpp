//#include "stdafx.h"
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string>

using namespace std;

bool won = false, boton = true, quit = false;
int x, y, xmin = 8, xmax, ymin = 4, ymax, dificultad = 0, A[15][30], F[15], C[15];

#define ARR 72	//codigos ascii para los botones renombrados
#define ABA 80
#define DER 77
#define IZQ 75
#define ENT 13
HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE); //necesario para gotoxy(), ocultar_cursor() y setcolor()

void gotoxy(int x, int y) {	//posiciona el cursor en las coordenadas X e Y pasadas por parametro 
	COORD posCur;
	posCur.X = x;
	posCur.Y = y;
	SetConsoleCursorPosition(hCon, posCur);
}

void ocultar_cursor() {	//desabilita el cursor parpadeante
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = 10;
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(hCon, &cci);
}

void setcolor(unsigned short color) { SetConsoleTextAttribute(hCon, color); } //cambia los atributos del texto

void setup_facil() { //escribe los numeros de referencia para el tablero de 5x5
	string referenciasF[] = { "     3" ," 1 1 1" ,"   1 1" ," 1 1 1" ,"     3" };
	string referenciasC[] = { "  1 2 1" ,"3 1 2 1 3" };
	ymax = 9;
	xmax = 16;
	for (int i = 0; i < 2; i++) { gotoxy(8, i + 2); cout << referenciasC[i]; }
	for (int i = 0; i < 5; i++) { gotoxy(1, i + 4); cout << referenciasF[i]; }
}

void setup_medio() { //escribe los numeros de referencia para el tablero de 10x10
	string referenciasF[] = { "     3","   1 1","   1 1","   1 4","   5 1"," 2 1 3"," 2 1 1"," 2 1 3"," 2 1 1","     9" };
	string referenciasC[] = { "              1 1" ,"              1 1" ,"    1   5 1 4 1 1" ,"6 6 1 6 1 1 1 1 1 6" };
	ymax = 14;
	xmax = 26;
	for (int i = 0; i < 4; i++) { gotoxy(8, i); cout << referenciasC[i]; }
	for (int i = 0; i < 10; i++) { gotoxy(1, i + 4); cout << referenciasF[i]; }
}

void setup_dificil() { //escribe los numeros de referencia para el tablero de 15x15
	string referenciasF[] = { "     A","   6 5"," 4 3 3"," 4 3 2"," 5 4 2","   B 1","   A 1","   7 1","   5 1","   4 1"," 3 1 2"," 3 3 2"," 3 1 3","   3 5","     A" };
	string referenciasC[] = { "              3   1" ,"          3 2 3 7 5 2" ,"        8 4 3 1 3 1 3 2 3 5" ,"5 9 B D 2 2 1 1 1 1 2 2 3 5 F" };
	ymax = 19;
	xmax = 36;
	for (int i = 0; i < 4; i++) { gotoxy(8, i); cout << referenciasC[i]; }
	for (int i = 0; i < 15; i++) { gotoxy(1, i + 4); cout << referenciasF[i]; }
}

void valores() {
	if (dificultad == 1) {
		int valoresF[] = { 3,3,2,3,3,0,0,0,0,0,0,0,0,0,0 };
		int valoresC[] = { 3,2,4,2,3,0,0,0,0,0,0,0,0,0,0 };
		for (int i = 0; i < 15; i++) {
			F[i] = valoresF[i];
			C[i] = valoresC[i];
		}
	}
	if (dificultad == 2) {
		int valoresF[] = { 3,2,2,5,6,6,4,6,4,9,0,0,0,0,0 };
		int valoresC[] = { 6,6,2,6,6,2,5,4,4,6,0,0,0,0,0 };
		for (int i = 0; i < 15; i++) {
			F[i] = valoresF[i];
			C[i] = valoresC[i];
		}
	}
	if (dificultad == 3) {
		int valoresF[] = { 10,11,10,9,11,12,11,8,6,5,6,8,7,8,10 };
		int valoresC[] = { 5,9,11,13,10,9,6,8,11,8,7,4,6,10,15 };
		for (int i = 0; i < 15; i++) {
			F[i] = valoresF[i];
			C[i] = valoresC[i];
		}
	}
}

void reglas() {
	char hexa[6] = { 'A','B','C','D','E','F' };
	gotoxy(42, 2);
	cout << "Numeros Hexadecimales";
	for (int i = 0; i < 6; i++) {
		gotoxy(47, 4 + i * 2);
		cout << hexa[i];
		setcolor(242);
		cout << " --> ";
		setcolor(240);
		cout << 10 + i;
	}
	int posX = 70, posY = 4;
	string reglas1[5] = { "1- Cada numero de cada fila y columna indica el","numero de cuadros negros seguidos en esa fila.","Si hay varios numeros en una fila, quiere decir",
		"que entre cada numero de cuadrados tiene que","haber por lo menos un espacio en blanco." };
	string reglas2[3] = { "2- Los numeros se dan en el mismo orden en el que","van los grupos de cuadros negros, sin olvidar","ninguno." };
	string reglas3[3] = { "3- No empiezan a contar por el borde, hay que ","pensar, asi que no rellenes hasta que no estes","seguro." };
	string reglas4[11] = { "4- un ","O"," significa que la cantidad de cuadrados","negros en la linea o columna es exactamente la ","que deberia haber (pero no significa que su",
		"posicion este bien), asimismo una ","X"," significa","que la cantidad de cuadrados negros en la linea","o columna en la que esta ubicada supera la ",
		"cantidad de cuadrados negros que deberia haber." };
	gotoxy(posX + 10, posY - 2);
	cout << "Tips a tener en cuenta";
	for (int i = 0; i < 5; i++) {
		gotoxy(posX, posY);
		if (i == 0) gotoxy(posX - 3, posY);
		cout << reglas1[i];
		posY++;
		if (i == 4) posY++;
	}
	for (int i = 0; i < 3; i++) {
		gotoxy(posX, posY);
		if (i == 0) gotoxy(posX - 3, posY);
		cout << reglas2[i];
		posY++;
		if (i == 2) posY++;
	}
	for (int i = 0; i < 3; i++) {
		gotoxy(posX, posY);
		if (i == 0) gotoxy(posX - 3, posY);
		cout << reglas3[i];
		posY++;
		if (i == 2) posY++;
	}
	for (int i = 0; i < 11; i++) {
		if (i != 1 && i != 2 && i != 6 && i != 7) gotoxy(posX, posY);
		if (i == 0) gotoxy(posX - 3, posY);
		if (i == 1) setcolor(242);
		if (i == 6) setcolor(244);
		cout << reglas4[i];
		if (i == 1 || i == 6) setcolor(240);
		if (i != 1 && i != 2 && i != 6 && i != 7) posY++;
	}
}

void menu() { //muestra el menu y setea la dificultad
	int r = 0;
	gotoxy(100, 50);
	cout << "Made by Takzzg";
	string menu[4] = { "1. Facil","2. Intermedio","3. Dificil","4. Salir" };
	gotoxy(2, 0);
	cout << "  ____ ____  ___ ____  ____  _     _____ ____  ____  " << endl << "   / ___|  _ \\|_ _|  _ \\|  _ \\| |   | ____|  _ \\/ ___|" << endl <<
		"  | |  _| |_) || || | | | | | | |   |  _| | |_) \\___ \\ " << endl << "  | |_| |  _ < | || |_| | |_| | |___| |___|  _ < ___) |" << endl <<
		"   \\____|_| \\_\\___|____/|____/|_____|_____|_| \\_\\____/ ";
	int posX = 21, posY = 7, posC = 7;
	bool enter = false;
	for (int i = 0; i < 4; i++) {
		gotoxy(posX, posY++);
		cout << menu[i];
	}
	setcolor(242);
	while (enter != true) {
		gotoxy(19, posC);
		printf("%c", 175);
		char tecla = _getch();
		if (tecla == ABA && posC < 10) { gotoxy(19, posC); cout << ' '; posC++; }
		if (tecla == ARR && posC > 7) { gotoxy(19, posC); cout << ' '; posC--; }
		if (tecla == ENT) enter = true;
	}
	setcolor(240);
	system("cls");
	switch (posC) {
	case 7:
		setup_facil();
		dificultad = 1;
		break;
	case 8:
		setup_medio();
		dificultad = 2;
		break;
	case 9:
		setup_dificil();
		dificultad = 3;
		break;
	case 10:
		quit = true;
	}
	valores();
}

void check() { //checkea cantidad de cuadrados negros en cada linea y columna
	for (int i = 0; i < 15; i++) {
		int cont = 0;
		for (int j = 0; j < 30; j += 2)
			if (A[i][j] == 1) cont++;
		if (dificultad == 1) gotoxy(18, i + 4);
		if (dificultad == 2) gotoxy(28, i + 4);
		if (dificultad == 3) gotoxy(38, i + 4);
		if ((dificultad == 1 && i < 5) || (dificultad == 2 && i < 10) || dificultad == 3) {
			if (cont > F[i]) {
				setcolor(244);
				cout << 'X';
				setcolor(240);
			}
			else if (cont == F[i]) {
				setcolor(242);
				cout << 'O';
				setcolor(240);
			}
			else cout << "  ";
		}
	}
	for (int j = 0; j < 30; j += 2) {
		int cont = 0;
		for (int i = 0; i < 15; i++)
			if (A[i][j] == 1) cont++;
		if (dificultad == 1) gotoxy(j + 8, 9);
		if (dificultad == 2) gotoxy(j + 8, 14);
		if (dificultad == 3) gotoxy(j + 8, 19);
		if ((dificultad == 1 && j < 10) || (dificultad == 2 && j < 20) || dificultad == 3) {
			if (cont > C[j / 2]) {
				setcolor(244);
				cout << "X ";
				setcolor(240);
			}
			else if (cont == C[j / 2]) {
				setcolor(242);
				cout << "O ";
				setcolor(240);
			}
			else cout << "  ";
		}
	}
	bool winF = true, winC = true;
	int contF, contC;
	for (int i = 0; i < 15; i++) {
		contF = 0, contC = 0;
		for (int j = 0; j < 15; j++) {
			if (A[i][j * 2] == 1) contF++;
			if (A[j][i * 2] == 1) contC++;
		}
		if (contF != F[i]) winF = false;
		if (contC != C[i]) winC = false;
	}
	if (winF && winC) won = true;
}

void salir() { //resetea todos los valores cuando se va al menu y cierra el programa
	if (boton == true) {
		boton = false, won = false;
		system("cls");
		system("color F0");
		setcolor(240);
		ocultar_cursor();
		menu();
		salir();
		reglas();
		x = 8, y = 4;
		gotoxy(x, y);
		cout << "><";
		for (int i = 0; i < 15; i++)
			for (int j = 0; j < 30; j += 2)	A[i][j] = 0;
	}
	if (dificultad == 1) gotoxy(10, 10);
	if (dificultad == 2) gotoxy(15, 15);
	if (dificultad == 3) gotoxy(20, 20);
	if (y == ymax) setcolor(15);
	else setcolor(244);
	cout << "SALIR";
	setcolor(240);
}

void mover() { //mover el cursor y pintar
	char tecla = _getch();
	if (tecla == ARR && y > ymin) y--;
	if (tecla == ABA && y < ymax) y++;
	if (tecla == DER && x < xmax) x += 2;
	if (tecla == IZQ && x > xmin) x -= 2;
	if (tecla == ENT) {
		if (y == ymax) boton = true;
		else if (A[y - 4][x - 8] < 2) A[y - 4][x - 8]++;
		else A[y - 4][x - 8] = 0;
	}
	gotoxy(x, y);
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 30; j += 2) {
			gotoxy(j + 8, i + 4);
			if ((dificultad == 1 && j < 10 && i < 5) || (dificultad == 2 && j < 20 && i < 10) || dificultad == 3) {
				if (A[i][j] == 0) cout << "  ";
				if (A[i][j] == 1) printf("%c%c", 219, 219);
				if (A[i][j] == 2) printf("%c%c", 250, 250);
			}
		}
	}
	gotoxy(x, y);
	if (A[y - 4][x - 8] == 1) printf("%c%c", 178, 178);
	else if (A[y - 4][x - 8] == 2) { setcolor(15); printf("%c%c", 250, 250); setcolor(240); }
	else cout << "><";
}

void winner() {
	if (won == true) {
		if (dificultad == 1) gotoxy(3, 10);
		if (dificultad == 2) gotoxy(3, 15);
		if (dificultad == 3) gotoxy(3, 20);
		cout << "_   _    _    ____      ____    _    _   _    _    ____   ___" << endl << "  | | | |  / \\  / ___|    / ___|  / \\  | \\ | |  / \\  |  _ \\ / _ \\ " << endl <<
			"  | |_| | / _ \\ \\___ \\   | |  _  / _ \\ |  \\| | / _ \\ | | | | | | | " << endl << "  |  _  |/ ___ \\ ___) |  | |_| |/ ___ \\| |\\  |/ ___ \\| |_| | |_| | " << endl <<
			"  |_| |_/_/   \\_\\____/    \\____/_/   \\_\\_| \\_/_/   \\_\\____/ \\___/  " << endl;
		if (dificultad == 1) gotoxy(20, 15);
		if (dificultad == 2) gotoxy(20, 20);
		if (dificultad == 3) gotoxy(20, 25);
		Sleep(1000);
		system("pause");
		boton = true;
		salir();
	}
}

int main() {
	while (true) {
		winner();
		salir();
		if (quit == true) return(0);
		if (_kbhit()) {
			mover();
			check();
			Sleep(50);
		}
	}
}
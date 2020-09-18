#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <string.h>
#include <iostream>
#include <fstream>
using namespace std;

//Hằng số 
#define BOARD_SIZE 12 // Kích thức ma trận bàn cờ 
#define LEFT 3 // Tọa độ trái màn hình bàn cờ 
#define TOP 2 // Tọa độ trên màn hình bàn cờ 
void Xwin();
void Owin();
void TextColor(int x);
void setFontSize(int FontSize);
int Menu();
void Khung();
void Huongdan();
void Danhsach();
void LoadData();
void Savefile();
int i, j;
struct _POINT
{
	char a;
	int x, y, c;
}; // x: tọa độ dòng, y: tọa độ cột, c: đánh dấu
_POINT _A[BOARD_SIZE][BOARD_SIZE]; //Ma trận bàn cờ
bool _TURN; //true là lượt người thứ nhất và false là lượt người thứ hai
int _COMMAND; // Biến nhận giá trị phím người dùng nhập
int _X, _Y; //Tọa độ hiện hành trên màn hình bàn cờ

void FixConsoleWindow()
{
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);

}

void GotoXY(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void TextColor(int x) //https://tranhanhuy.wordpress.com/2011/07/10/c-ham-mau-dung-cho-vc-6-0-textcolor/ //
{
	HANDLE mau;
	mau = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(mau, x);
}

void setFontSize(int FontSize) // https://blogkhanhtoan.wordpress.com/2015/03/08/thay-doi-kich-thuoc-font-trong-cc-change-font-size-in-cc/ //
{
	CONSOLE_FONT_INFOEX info = { 0 };
	info.cbSize = sizeof(info);
	info.dwFontSize.Y = FontSize; // leave X as zero
	info.FontWeight = FW_NORMAL;
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), NULL, &info);
}

int Menu()
{
	int y = 0;
	GotoXY(30, 2);
	TextColor(10);
	printf("~~~~~~~~~~~~~~~~~~> Game ConSole <~~~~~~~~~~~~~~~~~~\n");
	Sleep(500);
	GotoXY(40, 3);
	TextColor(11);
	printf("   _____          _____   ____  ");
	GotoXY(40, 4);
	Sleep(500);
	TextColor(11);
	printf("  / ____|   /\\   |  __ \\ / __ \\ ");
	GotoXY(40, 5);
	Sleep(500);
	TextColor(11);
	printf(" | |       /  \\  | |__) | |  | |");
	GotoXY(40, 6);
	Sleep(500);
	TextColor(11);
	printf(" | |      / /\\ \\ |  _  /| |  | |");
	GotoXY(40, 7);
	Sleep(500);
	TextColor(11);
	printf(" | |____ / ____ \\| | \\ \\| |__| |");
	GotoXY(40, 8);
	Sleep(500);
	TextColor(11);
	printf("  \\_____/_/    \\_\\_|  \\_\\\\____/ ");

	GotoXY(50, 15);
	Sleep(150);
	TextColor(100);
	cout << "PLAY GAME";
	GotoXY(50, 17);
	Sleep(150);
	TextColor(15);
	cout << "QUIT";
	do
	{
		_COMMAND = toupper(_getch());
		if (_COMMAND != 27)
		{
			if (_COMMAND == 'S')
			{
				GotoXY(50, 15);
				TextColor(15);
				cout << "PLAY GAME";
				GotoXY(50, 17);
				TextColor(100);
				cout << "QUIT";
				TextColor(7); y = 17;
			}

			else if (_COMMAND == 'W')
			{
				GotoXY(50, 15);
				TextColor(100);
				cout << "PLAY GAME";
				GotoXY(50, 17);
				TextColor(15);
				cout << "QUIT";
				TextColor(7); y = 15;
			}

		}
	} while (_COMMAND != 13);
	return y;
}

void DrawBoard(int pSize) //Hàm vẽ bàn cờ
{
	TextColor(15);
	for (int i = 0; i <= pSize; i++) {

		for (int j = 0; j <= pSize; j++) {

			GotoXY(LEFT + 4 * i, TOP + 2 * j);

			printf(".");
		}
	}
}

void Khung()
{
	short i, n = 5;
	GotoXY(0, 0);
	TextColor(5);
	for (i = 0; i <= 118; i++) {  // hàng ngang trên
		cout << "*"; Sleep(n);
	}



	TextColor(5);
	for (i = 0; i <= 27; i++) {		// hàng dọc bên trái
		GotoXY(0, i + 1);
		Sleep(n);
		cout << "*";
	}


	TextColor(5);
	for (i = 0; i <= 27; i++) {		// hàng dọc bên phải
		GotoXY(118, i + 1);
		Sleep(n);
		cout << "*";
	}


	GotoXY(0, 29);
	TextColor(5);
	for (i = 0; i <= 118; i++)			// hàng ngang dưới
	{
		cout << "*"; Sleep(n);
	}
	TextColor(5);
	for (i = 0; i <= 27; i++) {			// hàng dọc chia nữa bản đồ
		GotoXY(54, i + 1);
		Sleep(n);
		cout << "*" << endl;
	}


	GotoXY(1, 28);
	TextColor(5);
	for (i = 0; i <= 53; i++) {		// hàng ngang dưới chia chỗ chơi 
		cout << "*"; Sleep(n);
	}


	GotoXY(1, 1);
	TextColor(5);
	for (i = 0; i <= 53; i++) {		 // hàng ngang trên chia chỗ chơi
		cout << "*"; Sleep(n);
	}


	GotoXY(55, 15);					// hàng ngang phân cách giữa thông tin nhóm và thông tin trò chơi
	TextColor(5);
	for (i = 0; i <= 62; i++) {
		cout << "*"; Sleep(n);
	}

}

void Huongdan()
{
	TextColor(11);
	GotoXY(56, 1);
	printf("Huong dan choi:");
	TextColor(11);
	GotoXY(58, 2);
	printf("Su dung phim W de di chuyen len tren");
	TextColor(11);
	GotoXY(58, 3);
	printf("Su dung phim S de di chuyen xuong duoi");
	TextColor(11);
	GotoXY(58, 4);
	printf("Su dung phim A de di chuyen qua trai");
	TextColor(11);
	GotoXY(58, 5);
	printf("Su dung phim D de di chuyen qua phai");
	TextColor(11);
	GotoXY(58, 6);
	printf("Su dung phim Enter choi");
	GotoXY(56, 8);
	printf("Ghi chu!!!");
	GotoXY(58, 9);
	printf("Su dung phim L de luu game\n");
	GotoXY(58, 10);
	printf("Su dung phim O de load lai game da luu\n");
	GotoXY(58, 11);
	printf("An Q de quay lai man hinh chinh");
	TextColor(7);
}

void Danhsach()
{
	TextColor(10);
	GotoXY(80, 16);
	setFontSize(15);
	printf("NHOM 10");
	GotoXY(56, 17);
	TextColor(10);
	printf("THANH VIEN:");
	GotoXY(60, 18);
	TextColor(14);
	printf("+LE HOANG CHUONG                          MSSV: 18600033");
	GotoXY(60, 19);
	TextColor(14);
	printf("+NGUYEN NGOC DUC                          MSSV: 18600050");
	GotoXY(60, 20);
	TextColor(14);
	printf("+VU XUAN DUC                              MSSV: 18600053");
	GotoXY(60, 21);
	TextColor(14);
	printf("+LE GIA HUY                               MSSV: 18600108");
	GotoXY(60, 22);
	TextColor(14);
	printf("+LUU MINH HUY                             MSSV: 18600111");
}

void ResetData() //Hàm khởi tạo dữ liệu mặc định ban đầu cho ma trận bàn cờ 
{

	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			_A[i][j].x = 4 * j + LEFT + 2; // Trùng với hoành độ màn hình bàn cờ
			_A[i][j].y = 2 * i + TOP + 1; // Trùng với tung độ màn hình bàn cờ
			_A[i][j].c = 0; // 0 nghĩa là chưa ai đánh dấu, nếu đánh dấu phải theo quy
			//định như sau: -1 là lượt true đánh, 1 là lượt false đánh
		}
	}
	_TURN = true; _COMMAND = -1; // Gán lượt và phím mặc định
	_X = _A[0][0].x; _Y = _A[0][0].y; // Thiết lập lại tọa độ hiện hành ban đầu
}

void StartGame()
{
	system("cls");
	Khung();
	Danhsach();
	GotoXY(60, 2);
	Huongdan();
	ResetData(); // Khởi tạo dữ liệu gốc
	DrawBoard(BOARD_SIZE); // Vẽ màn hình game
}

void GabageCollect() //Hàm dọn dẹp tài nguyên 
{

}

void ExitGame()
{
	system("cls");
	GabageCollect();
	//Có thể lưu game trước khi exit
}

void MoveRight() {

	if (_X < _A[BOARD_SIZE - 1][BOARD_SIZE - 1].x)
	{
		_X += 4;
		GotoXY(_X, _Y);
	}
}
void MoveLeft()
{
	if (_X > _A[0][0].x) {
		_X -= 4;
		GotoXY(_X, _Y);
	}
}
void MoveDown() {
	if (_Y < _A[BOARD_SIZE - 1][BOARD_SIZE - 1].y)
	{
		_Y += 2;
		GotoXY(_X, _Y);
	}
}
void MoveUp() {
	if (_Y > _A[0][0].y) {
		_Y -= 2;
		GotoXY(_X, _Y);
	}
}
int CheckBoard(int pX, int pY) //Hàm đánh dấu vào ma trận bàn cờ khi người chơi nhấn phím ‘enter’.
{
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (_A[i][j].x == pX && _A[i][j].y == pY && _A[i][j].c == 0)
			{
				if (_TURN == true)
				{
					_A[i][j].c = -1;
				}// Nếu lượt hiện hành là true thì c = -1
				else
					_A[i][j].c = 1; // Nếu lượt hiện hành là false thì c = 1

				return _A[i][j].c;
			}
		}
	}
	return 0;
}

int TestBoard() //Hàm kiểm tra xem có người thắng/thua hay hòa
{
	int i, j;

	for (i = 0; i < BOARD_SIZE; i++)
	{
		for (j = 0; j < BOARD_SIZE; j++)
		{
			if (_A[i][j].x == _X && _A[i][j].y == _Y)
			{
				goto abc;
			}
		}
	}
abc:
	{
		for (i = 0; i < BOARD_SIZE; i++)
		{
			//dk xet cot thang
			if (_A[i][j].c == _A[i + 1][j].c && _A[i][j].c == _A[i + 2][j].c && _A[i][j].c == _A[i + 3][j].c && _A[i][j].c == _A[i + 4][j].c)
			{
				if (_A[i][j].c != 0 && _A[i + 1][j].c != 0 && _A[i + 2][j].c != 0 && _A[i + 3][j].c != 0 && _A[i + 4][j].c != 0)
				{
					return _A[i][j].c;

				}
			}
		}


		// dk xet hang doc
		for (i = 0; i < BOARD_SIZE; i++)
		{
			for (j = 0; j < BOARD_SIZE; j++)
			{
				if (_A[i][j].c == _A[i][j + 1].c && _A[i][j].c == _A[i][j + 2].c && _A[i][j].c == _A[i][j + 3].c && _A[i][j].c == _A[i][j + 4].c)
				{
					if (_A[i][j].c != 0 && _A[i][j + 1].c != 0 && _A[i][j + 2].c != 0 && _A[i][j + 3].c != 0 && _A[i][j + 4].c != 0)
					{
						return _A[i][j].c;
					}
				}
			}
		}
		// duong cheo xuong
		for (i = 0; i < BOARD_SIZE; i++)
		{
			for (j = 0; j < BOARD_SIZE; j++)
			{
				if (_A[i][j].c == _A[i + 1][j + 1].c && _A[i][j].c == _A[i + 2][j + 2].c && _A[i][j].c == _A[i + 3][j + 3].c && _A[i][j].c == _A[i + 4][j + 4].c)
				{
					if (_A[i][j].c != 0 && _A[i + 2][j + 2].c != 0 && _A[i + 3][j + 3].c != 0 && _A[i + 1][j + 1].c != 0 && _A[i + 4][j + 4].c != 0)
					{

						return _A[i][j].c;
					}
				}
			}
		}
		// duong cheo len
		for (i = 0; i < BOARD_SIZE; i++)
		{
			for (j = 0; j < BOARD_SIZE; j++)
			{
				if (_A[i][j].c == _A[i - 1][j + 1].c && _A[i][j].c == _A[i - 2][j + 2].c && _A[i][j].c == _A[i - 3][j + 3].c && _A[i][j].c == _A[i - 4][j + 4].c)
				{
					if (_A[i][j].c != 0 && _A[i - 1][j + 1].c != 0 && _A[i - 2][j + 2].c != 0 && _A[i - 3][j + 3].c != 0 && _A[i - 4][j + 4].c)
					{
						return _A[i][j].c;
					}
				}
			}
		}
		int dem = 0;
		for (i = 0; i < BOARD_SIZE; i++)
		{
			for (j = 0; j < BOARD_SIZE; j++)
			{
				if (_A[i][j].c != 0)
				{
					dem++;
				}
			}
		}
		if (dem == BOARD_SIZE * BOARD_SIZE)
		{
			return 0;
		}
		return 2;
	}
}

int ProcessFinish(int pWhoWin) ////Hàm xử lý khi người chơi thắng/thua hay hòa
{
	GotoXY(0, _A[BOARD_SIZE - 1][BOARD_SIZE - 1].y + 2); // Nhảy tới vị trí
	 // thích hợp để in chuỗi thắng/thua/hòa

	switch (pWhoWin) {

	case -1:
		Xwin();
		GotoXY(32, 10);
		setFontSize(15);
		TextColor(12);
		printf("Nguoi choi X da thang va nguoi choi O da thua\n");
		break;
	case 1:
		Owin();
		GotoXY(32, 10);
		setFontSize(15);
		TextColor(14);
		printf("Nguoi choi O da thang va nguoi choi X da thua\n");
		break;
	case 0:

		system("cls");
		GotoXY(38, 10);
		setFontSize(15);
		TextColor(10);
		printf("Nguoi choi X da hoa nguoi choi O\n");
		break;
	case 2:
		_TURN = !_TURN; // Đổi lượt nếu không có gì xảy ra

	}
	GotoXY(_X, _Y); // Trả về vị trí hiện hành của con trỏ màn hình bàn cờ
	return pWhoWin;
}

void Xwin()  //Hiệu ứng người chơi X win
{
	system("cls");
	for (int i = 0; i < 50; i++)
	{
		GotoXY(37, 12);
		TextColor(8 + rand() % 8);
		printf("Nguoi choi X da thang va nguoi choi O da thua\n");
		Sleep(30);
		system("cls");
	}
}
void Owin() //Hiệu ứng người chơi O win 
{
	system("cls");
	for (int i = 0; i < 50; i++)
	{
		GotoXY(37, 12);
		TextColor(8 + rand() % 8);
		printf("Nguoi choi O da thang va nguoi choi X da thua\n");
		Sleep(30);
		system("cls");
	}
}

int AskContinue()
{
	GotoXY(50, 12);
	TextColor(100);
	cout << "CONTINUE";
	GotoXY(50, 14);
	Sleep(150);
	TextColor(15);
	cout << "EXIT";
	int x = 0;
	do
	{
		_COMMAND = toupper(_getch());
		if (_COMMAND != 27)
		{
			if (_COMMAND == 'S') {
				GotoXY(50, 12);
				TextColor(15);
				cout << "Continue";
				GotoXY(50, 14);
				TextColor(100);
				cout << "EXIT";
				TextColor(7); x = 17;
			}

			else if (_COMMAND == 'W')
			{
				GotoXY(50, 12);
				TextColor(100);
				cout << "CONTINUE";
				GotoXY(50, 14);
				TextColor(15);
				cout << "EXIT";
				TextColor(7); x = 15;
			}

		}
	} while (_COMMAND != 13);
	return x;

	return toupper(_getch());
}

void Savefile() //Save file game.....
{
	ofstream fout;
	fout.open("save.txt");
	if (!fout) {
		cout << "Luu file khong thanh cong!" << endl;
	}
	else {
		for (int i = 0; i < BOARD_SIZE; i++) {
			for (int j = 0; j < BOARD_SIZE; j++) {
				fout << _A[i][j].a << ' ' << _A[i][j].x << ' ' << _A[i][j].y << ' ' << _A[i][j].c << endl;
			}
		}
		GotoXY(75, 25);
		cout << "Luu thanh cong!" << endl;
	}
	fout.close();
}

void LoadData() // Hàm load file đã save....
{
	ifstream fin;
	fin.open("save.txt");
	if (!fin) {
	}
	else {
		for (int i = 0; i < BOARD_SIZE; i++) {
			for (int j = 0; j < BOARD_SIZE; j++) {
				fin >> _A[i][j].a >> _A[i][j].x >> _A[i][j].y >> _A[i][j].c;
			}
		}
	}
	fin.close();
	//VE lai ban co voi file da save....
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			GotoXY(_A[i][j].x, _A[i][j].y);
			switch (_A[i][j].c)
			{
			case -1:
				TextColor(14);
				printf("X");
				break;
			case 1:
				TextColor(12);

				printf("O");
				break;
			}
		}
	}
}


int main()
{
	FixConsoleWindow();

a:
	if (Menu() == 17)
	{
		ExitGame();
		return 0;
	}
	else
		StartGame();

	GotoXY(_A[0][0].x, _A[0][0].y);
	bool validEnter = true;
	while (1)
	{
		_COMMAND = toupper(_getch());
		if (_COMMAND == 27)
		{
			ExitGame();
			return 0;
		}
		else
		{
			if (_COMMAND == 'A') MoveLeft();
			else if (_COMMAND == 'W') MoveUp();
			else if (_COMMAND == 'S') MoveDown();
			else if (_COMMAND == 'D') MoveRight();
			else if (_COMMAND == 'L') Savefile();
			else if (_COMMAND == 'O') LoadData();
			else if (_COMMAND == 'Q')
			{
				system("cls");
				goto a;
			}
			else if (_COMMAND == 13)
			{        // Người dùng đánh dấu trên màn hình bàn cờ
				switch (CheckBoard(_X, _Y))
				{
				case -1:
					TextColor(14);
					printf("X");
					_getch();
					break;
				case 1:
					TextColor(12);
					printf("O");
					_getch();
					break;
				case 0:
					validEnter = false; // Khi đánh vào ô đã đánh rồi
				}
				// Tiếp theo là kiểm tra và xử lý thắng/thua/hòa/tiếp tục
				if (validEnter == true)
				{
					switch (ProcessFinish(TestBoard()))
					{
					case -1: case 1: case 0:
						if (AskContinue() == 17)
						{
							do {
								if (_COMMAND == 13)
								{
									ExitGame();
									return 0;
								}
							} while (_COMMAND != 13);
						}
						else StartGame();
					}
				}
				validEnter = true; // Mở khóa
			}
		}
	}
}
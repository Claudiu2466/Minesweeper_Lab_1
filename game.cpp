#include "game.hpp"
#include "constants.hpp"

void play(char** field, int a, int b, int bombs, bool autoplay) {
	HANDLE hIn, hOut;
	INPUT_RECORD InRec;
	DWORD NumRead;
	CONSOLE_CURSOR_INFO Curs;
	CONSOLE_SCREEN_BUFFER_INFO Buff;
	COORD zero = { 0,0 };
	boolean game_over = false, win = false;
	int flag = 0, clean = 2, x, y, i, j, input = 1, marked_bombs = 0, opened_cells = 0, bombs_at_beginning = bombs, xDiv2;
	char** player_view = new char* [a];
	for (i = 0; i < a; i++) {
		player_view[i] = new char[b];
		for (j = 0; j < b; j++)
			player_view[i][j] = Closed_Cell;
	}
	for (i = bombs; (i /= 10) > 0;)
		clean++;
	system("cls");
	hIn = GetStdHandle(STD_INPUT_HANDLE);
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleCursorInfo(hOut, &Curs);
	SetConsoleMode(hIn, ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
	while (!game_over) {
		Curs.bVisible = false;
		SetConsoleCursorInfo(hOut, &Curs);
		SetConsoleCursorPosition(hOut, zero);
		for (i = 0; i < a; i++) {
			for (j = 0; j < b; j++) {
				switch (player_view[i][j]) {
				case Closed_Cell: {
					SetConsoleTextAttribute(hOut, (WORD)(0 | 8));
					WriteConsoleW(hOut, L"⯀ ", wcslen(L"⯀ "), NULL, NULL);
					SetConsoleTextAttribute(hOut, (WORD)(0 | 15));
					break;
				}
				case Exploded_Mine: {
					SetConsoleTextAttribute(hOut, (WORD)(0 | 4));
					WriteConsoleW(hOut, L"💥 ", wcslen(L"💥 "), NULL, NULL);
					SetConsoleTextAttribute(hOut, (WORD)(0 | 15));
					game_over = true;
					break;
				}
				case Opened_Cell: {
					opened_cells++;
					switch (field[i][j]) {
					case Free_Cell: {
						SetConsoleTextAttribute(hOut, (WORD)(0 | 8));
						WriteConsoleW(hOut, L"× ", wcslen(L"× "), NULL, NULL);
						SetConsoleTextAttribute(hOut, (WORD)(0 | 15));
						break;
					}
					case 1: {
						SetConsoleTextAttribute(hOut, (WORD)(0 | 14));
						cout << "1 ";
						SetConsoleTextAttribute(hOut, (WORD)(0 | 15));
						break;
					}
					case 2: {
						SetConsoleTextAttribute(hOut, (WORD)(0 | 10));
						cout << "2 ";
						SetConsoleTextAttribute(hOut, (WORD)(0 | 15));
						break;
					}
					case 3: {
						SetConsoleTextAttribute(hOut, (WORD)(0 | 12));
						cout << "3 ";
						SetConsoleTextAttribute(hOut, (WORD)(0 | 15));
						break;
					}
					case 4: {
						SetConsoleTextAttribute(hOut, (WORD)(0 | 5));
						cout << "4 ";
						SetConsoleTextAttribute(hOut, (WORD)(0 | 15));
						break;
					}
					case 5: {
						SetConsoleTextAttribute(hOut, (WORD)(0 | 4));
						cout << "5 ";
						SetConsoleTextAttribute(hOut, (WORD)(0 | 15));
						break;
					}
					case 6: {
						SetConsoleTextAttribute(hOut, (WORD)(0 | 1));
						cout << "6 ";
						SetConsoleTextAttribute(hOut, (WORD)(0 | 15));
						break;
					}
					case 7: {
						SetConsoleTextAttribute(hOut, (WORD)(0 | 2));
						cout << "7 ";
						SetConsoleTextAttribute(hOut, (WORD)(0 | 15));
						break;
					}
					case 8: {
						SetConsoleTextAttribute(hOut, (WORD)(0 | 8));
						cout << "8 ";
						SetConsoleTextAttribute(hOut, (WORD)(0 | 15));
						break;
					}
					case Mine: {
						SetConsoleTextAttribute(hOut, (WORD)(0 | 15));
						WriteConsoleW(hOut, L"💥 ", wcslen(L"💥 "), NULL, NULL);
					}
					}
					break;
				}
				case Flag: {
					SetConsoleTextAttribute(hOut, (WORD)(0 | 12));
					WriteConsoleW(hOut, L"⚐ ", wcslen(L"⚐ "), NULL, NULL);
					SetConsoleTextAttribute(hOut, (WORD)(0 | 15));
					if (field[i][j] == 9)
						marked_bombs++;
					else
						marked_bombs--;
				}
				}
			}
			cout << endl;
		}
		if (marked_bombs == bombs_at_beginning || opened_cells >= (a * b - bombs_at_beginning))
			win = game_over = true;
		opened_cells = 0;
		marked_bombs = 0;
		cout << "\nMine ramase ";
		for (i = clean; i != 0; i--)
			cout << ' ';
		GetConsoleScreenBufferInfo(hOut, &Buff);
		Buff.dwCursorPosition.X -= clean;
		SetConsoleCursorPosition(hOut, Buff.dwCursorPosition);
		cout << bombs;
		cout << "\nApasa 0 pentru a iesi\n>";
		Curs.bVisible = true;
		SetConsoleCursorInfo(hOut, &Curs);
		if (!autoplay) {
			ReadConsoleInput(hIn, &InRec, 1, &NumRead);
			switch (InRec.EventType) {
			case MOUSE_EVENT: {
				if (InRec.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
					x = InRec.Event.MouseEvent.dwMousePosition.X;
					y = InRec.Event.MouseEvent.dwMousePosition.Y;
					open_space(field, player_view, a, b, x, y);
				}
				if (InRec.Event.MouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED) {
					x = InRec.Event.MouseEvent.dwMousePosition.X;
					y = InRec.Event.MouseEvent.dwMousePosition.Y;
					xDiv2 = x / 2;
					if (y < a && xDiv2 < b && !(x % 2)) {
						if (player_view[y][xDiv2] == Closed_Cell)
							flag = 1;
						if (player_view[y][xDiv2] == Flag)
							flag = 2;
						if (flag == 1) {
							player_view[y][xDiv2] = Flag;
							bombs--;
						}
						if (flag == 2) {
							player_view[y][xDiv2] = Closed_Cell;
							bombs++;
						}
						flag = 0;
					}
				}
				break;
			}
			case KEY_EVENT: {
				if (InRec.Event.KeyEvent.uChar.AsciiChar == '0') {
					game_over = true;
					cout << "0\n";
				}
			}
			}
		}
		else {
			y = rand() % a;
			x = rand() % (2 * b);
			open_space(field, player_view, a, b, x, y);
		}
	}
	if (game_over) {
		GetConsoleScreenBufferInfo(hOut, &Buff);
		Buff.dwCursorPosition.X--;
		Buff.dwCursorPosition.Y--;
		SetConsoleCursorPosition(hOut, Buff.dwCursorPosition);
		if (!win) {
			SetConsoleTextAttribute(hOut, (WORD)(0 | 4));
			cout << "GAME OVER              \n";
		}
		if (win) {
			SetConsoleTextAttribute(hOut, (WORD)(0 | 10));
			cout << "YOU WIN                \n";
		}
		SetConsoleTextAttribute(hOut, (WORD)(0 | 15));
		cout << "Apasa orice buton pentru a iesi...";
		do {
			ReadConsoleInput(hIn, &InRec, 1, &NumRead);
		} while (InRec.EventType != KEY_EVENT);
	}
	system("cls");
}

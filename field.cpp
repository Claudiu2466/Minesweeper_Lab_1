#include "field.hpp"
#include "constants.hpp"

char** gen_field(char** field, int a, int b, int bombs, bool autoplay) {
	int i, j, used_space = 0, skip = 0;
	field = new char* [a];
	for (i = 0; i < a; i++) {
		field[i] = new char[b];
		for (j = 0; j < b; j++)
			field[i][j] = Free_Cell;
	}
	for (i = 0; i < a; i++) {
		for (j = 0; j < b; j++) {
			if (bombs <= 0) {
				break;
			}
			if (field[i][j] == Mine) {
				skip++;
				continue;
			}
			if (rand() % ((a * b) - (i * b) - j - used_space + skip) == 0) {
				field[i][j] = Mine;
				bombs--;
				used_space++;
				skip = i = 0;
				j = -1;
			}
		}
	}
	for (i = 0; i < a; i++) {
		for (j = 0; j < b; j++) {
			if (field[i][j] > 8) {
				if (i - 1 >= 0)
					field[i - 1][j]++;
				if (i + 1 < a)
					field[i + 1][j]++;
				if (j - 1 >= 0)
					field[i][j - 1]++;
				if (j + 1 < b)
					field[i][j + 1]++;
				if (i - 1 >= 0 && j - 1 >= 0)
					field[i - 1][j - 1]++;
				if (i - 1 >= 0 && j + 1 < b)
					field[i - 1][j + 1]++;
				if (i + 1 < a && j - 1 >= 0)
					field[i + 1][j - 1]++;
				if (i + 1 < a && j + 1 < b)
					field[i + 1][j + 1]++;
			}
		}
	}
	for (i = 0; i < a; i++) {
		for (j = 0; j < b; j++) {
			if (field[i][j] > 8)
				field[i][j] = Mine;
		}
	}
	cout << endl;
	cout << "campul a fost generat cu SUCCES\n\n";
	std::cout << std::string(50, '-') << std::endl;
	return field;
}

int check_near_cell(char** field, char** player_view, int check, int i, int j) {
	if (field[i][j] == Free_Cell && player_view[i][j] == Closed_Cell) {
		player_view[i][j] = Unchecked_Cell;
		check++;
	}
	if (field[i][j] > 0 && field[i][j] < 9 && player_view[i][j] == Closed_Cell) {
		player_view[i][j] = Opened_Cell;
	}
	return check;
}

void open_space(char** field, char** player_view, int a, int b, int x, int y) {
	int i, j, check = 0, xDiv2 = x / 2;
	if (!(x % 2)) {
		if (y < a && xDiv2 < b) {
			if (player_view[y][xDiv2] == Closed_Cell && field[y][xDiv2] > 0 && field[y][xDiv2] < 9) {
				player_view[y][xDiv2] = Opened_Cell;
			}
			if (player_view[y][xDiv2] == Closed_Cell && field[y][xDiv2] == Free_Cell) {
				player_view[y][xDiv2] = Unchecked_Cell;
				check++;
				for (i = 0; i < a; i++) {
					for (j = 0; j < b; j++) {
						if (player_view[i][j] == Unchecked_Cell) {
							player_view[i][j] = Opened_Cell;
							check--;
							if (i - 1 >= 0) {
								check = check_near_cell(field, player_view, check, i - 1, j);
							}
							if (i - 1 >= 0 && j - 1 >= 0) {
								check = check_near_cell(field, player_view, check, i - 1, j - 1);
							}
							if (j - 1 >= 0) {
								check = check_near_cell(field, player_view, check, i, j - 1);
							}
							if (i + 1 < a && j - 1 >= 0) {
								check = check_near_cell(field, player_view, check, i + 1, j - 1);
							}
							if (i + 1 < a) {
								check = check_near_cell(field, player_view, check, i + 1, j);
							}
							if (i + 1 < a && j + 1 < b) {
								check = check_near_cell(field, player_view, check, i + 1, j + 1);
							}
							if (j + 1 < b) {
								check = check_near_cell(field, player_view, check, i, j + 1);
							}
							if (i - 1 >= 0 && j + 1 < b) {
								check = check_near_cell(field, player_view, check, i - 1, j + 1);
							}
							if (check > 0)
								i = 0;
							j = -1;
						}
					}
				}
			}
			if (field[y][xDiv2] == Mine && player_view[y][xDiv2] != Flag)
				player_view[y][xDiv2] = Exploded_Mine;
		}
	}
}

#include "main.hpp"

int main() {
	srand(time(NULL));
	int input, a, b, x, bombs;
	char** field = new char*;
	bool field_was_generated = false;
	do {
		cout << "Alege o optiune\n\n1.genereaza campul\n2.joaca\n3.autotest\n0.iesi\n>";
		cin >> input;
		cout << '\n';
		std::cout << std::string(50, '-') << std::endl;
		switch (input) {
		case 1: {
			cout << "Alege o dificultate, sau creaza una personalizata\n\n1.usor(9x9 10 mine)\n2.mediu(25x25 110 mine)\n3.expert(30x70 190 mine)\n4.personalizeaza\n0.mergi la pagina principala\n>";
			cin >> x;
			cout << '\n';
			std::cout << std::string(50, '-') << std::endl;
			switch (x) {
			case 1: {
				field = gen_field(field, 9, 9, 10, false);
				a = b = 9;
				bombs = 10;
				field_was_generated = true;
				continue;
			}
			case 2: {
				field = gen_field(field, 25, 25, 95, false);
				a = b = 25;
				bombs = 95;
				field_was_generated = true;
				continue;
			}
			case 3: {
				field = gen_field(field, 30, 70, 441, false);
				a = 30;
				b = 70;
				bombs = 441;
				field_was_generated = true;
				continue;
			}
			case 4: {
				cout << "Alege inaltimea campului:";
				cin >> a;
				if (a > 48)
					a = 48;
				cout << "Alege latimea campului:";
				cin >> b;
				if (b > 105)
					b = 105;
				cout << "Alege numarul de mine:";
				cin >> bombs;
				if (bombs > a * b)
					bombs = a * b;
				field = gen_field(field, a, b, bombs, false);
				field_was_generated = true;
				continue;
			}
			default: {
				x = 0;
				continue;
			}
			}
		}
		case 2: {
			if (field_was_generated) {
				play(field, a, b, bombs, false);
				cout << "Joaca din nou\n\n";
				std::cout << std::string(50, '-') << std::endl;
			}
			else {
				cout << "Mai intai genereaza un camp\n\n";
			}
			break;
		}
		case 3: {
			a = rand() % 48 + 1;
			b = rand() % 105 + 1;
			bombs = rand() % (a * b);
			field = gen_field(field, a, b, bombs, true);
			play(field, a, b, bombs, true);
			break;
		}
		default:input = 0;
		}
	} while (input != 0);
}

#ifndef FIELD_HPP
#define FIELD_HPP

#include <iostream>
using namespace std;

char** gen_field(char** field, int a, int b, int bombs, bool autoplay);
int check_near_cell(char** field, char** player_view, int check, int i, int j);
void open_space(char** field, char** player_view, int a, int b, int x, int y);

#endif // FIELD_HPP

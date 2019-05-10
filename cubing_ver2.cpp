#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#define MAXLEN	100001

#define EXIT	0
#define PRINT	1
#define ROTATE	2

#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

class Cube {

public:

	char components[6][9];
	char colors[6] = { 'w','y','r','o','g','b' };
	char face[6] = { 'U','D','F','B','L','R' };
	// order : top down front back left right

	char rotate_pattern[24][5] = { 
		"U", "U\'", "UM" ,"UM\'",
		"D", "D\'", "DM" ,"DM\'" ,
		"F", "F\'", "FM", "FM\'" ,
		"B", "B\'", "BM", "BM\'" ,
		"L", "L\'", "LM", "LM\'" ,
        "R", "R\'", "RM", "RM\'"
	};

	// rotate pattern :
	// U U' UM UM' D D' DM DM' F F' FM FM' B B' BM BM' L L' LM LM' R R' RM RM'  

	int rotate_data[6][2][4][4] = {

	{ { { 2,0,1,2 },{ 5,0,1,2 },{ 3,0,1,2 },{ 4,0,1,2 } },{ { 2,3,4,5 },{ 5,3,4,5 },{ 3,3,4,5 },{ 4,3,4,5 } } },  //w upper middle

	{ { { 2,6,7,8 },{ 4,6,7,8 },{ 3,6,7,8 },{ 5,6,7,8 } },{ { 2,3,4,5 },{ 4,3,4,5 },{ 3,3,4,5 },{ 5,3,4,5 } } },  //y upper middle

	{ { { 0,6,7,8 },{ 4,8,5,2 },{ 1,2,1,0, },{ 5,0,3,6 } },{ { 0,3,4,5 },{ 4,7,4,1 },{ 1,5,4,3 },{ 5,1,4,7 } } }, //r upper middle

	{ { { 0,2,1,0 },{ 5,8,5,2 },{ 1,6,7,8 },{ 4,0,3,6 } },{ { 0,3,4,5 },{ 5,1,4,7 },{ 1,5,4,3 },{ 4,7,4,1 } } },  //o upper middle

	{ { { 0,0,3,6 },{ 3,8,5,2 },{ 1,0,3,6 },{ 2,0,3,6 } },{ { 0,1,4,7 },{ 3,7,4,1 },{ 1,7,4,1 },{ 2,1,4,7 } } },  //g upper middle

	{ { { 0,2,5,8 },{ 2,2,5,8 },{ 1,2,5,8 },{ 3,6,3,0 } },{ { 0,1,4,7 },{ 2,1,4,7 },{ 1,1,4,7 },{ 3,7,4,1 } } } // b upper middle

	};

	Cube() {
		int i, j;
		for (i = 0; i < 6; i++)
			for (j = 0; j < 9; j++)
				components[i][j] = colors[i];
	}

	void reset_cube() {

		for (int i = 0; i < 6; i++)
			for (int j = 0; j < 9; j++)
				components[i][j] = colors[i];
	}

	void own_rotate(int side, int dir) {

		// dir== 0 if clockwise else 1 counterclockwise

		int i;
		int data1[2][4] = { { 0,6,8,2 },{ 0,2,8,6 } }, data2[2][4] = { { 1,3,7,5 },{ 1,5,7,3 } };
		char temp_data1 = components[side][0], temp_data2 = components[side][1];

		for (i = 0; i < 3; i++)
			components[side][data1[dir][i]] = components[side][data1[dir][i + 1]];
		components[side][data1[dir][3]] = temp_data1;

		for (i = 0; i < 3; i++)
			components[side][data2[dir][i]] = components[side][data2[dir][i + 1]];
		components[side][data2[dir][3]] = temp_data2;
	}

	void rotate(char * command) {

		int i, j, target, mid = strchr(command,'M') != NULL ? 1 : 0, dir = strchr(command, '\'') == NULL ? 0 : 1;
		char side;
		char temp_data[3];

		//ToDo: command exception handling
		// ex) situations like weird characters included in command

		side = command[0];

		for (int i = 0; i<6; i++)
			if (face[i] == side) {
				target = i;
				break;
			}

		for (i = 0; i < 3; i++)
			temp_data[i] = components[rotate_data[target][mid][0][0]][rotate_data[target][mid][0][i + 1]];

		if (strchr(command, '\'') == NULL) {  // clockwise

			for (i = 0; i < 3; i++)
				for (j = 0; j < 3; j++)
					components[rotate_data[target][mid][i][0]][rotate_data[target][mid][i][j + 1]] = components[rotate_data[target][mid][i + 1][0]][rotate_data[target][mid][i + 1][j + 1]];

			for (i = 0; i < 3; i++)
				components[rotate_data[target][mid][3][0]][rotate_data[target][mid][3][i + 1]] = temp_data[i];
		}
		else { //counterclockwise

			for (i = 0; i < 3; i++)
				components[rotate_data[target][mid][0][0]][rotate_data[target][mid][0][i + 1]] = components[rotate_data[target][mid][3][0]][rotate_data[target][mid][3][i + 1]];

			for (i = 3; i > 1; i--)
				for (j = 0; j < 3; j++)
					components[rotate_data[target][mid][i][0]][rotate_data[target][mid][i][j + 1]] = components[rotate_data[target][mid][i - 1][0]][rotate_data[target][mid][i - 1][j + 1]];

			for (i = 0; i < 3; i++)
				components[rotate_data[target][mid][1][0]][rotate_data[target][mid][1][i + 1]] = temp_data[i];
		}

		if(strchr(command,'M') == NULL) //if rotate middle part then, don't need to own_rotate
			own_rotate(target, dir);
	}

	void print_side(char side) {

		int target;

		for (int i = 0; i < 6; i++)
			if (side == face[i])
				target = i;

		for (int i = 0; i < 9; i++) {
			printf("%c", components[target][i]);
			if (i == 2 || i == 5 || i == 8)
				printf("\n");
		}

		printf("\n\n");

	}

	void make_random_state() {

		srand((time(0)));

		int rotate_num = (rand() % 5) + 1;
		int rotate_pat;

		for (int i = 0; i < rotate_num; i++) {

			rotate_pat = rand() % 24;
			printf("%s ", rotate_pattern[rotate_pat]);
			rotate(rotate_pattern[rotate_pat]);
		}

		printf("\n\n\n");

	}

};

int manage_command(char * command) {

	if (_strcmpi(command, "exit") == 0)
		return EXIT;
	else if (_strcmpi(command, "print") == 0)
		return PRINT;
	else
		return ROTATE;

}

int main(void)
{
	Cube cube;
	char command[MAXLEN];
	int order;

	cube.make_random_state();
	
	while (1) {

		cin.getline(command,MAXLEN);

		order = manage_command(command);

		switch (order) {

		case PRINT:
			for (int i = 0; i < 6; i++) {
				cube.print_side(cube.face[i]);
			}
			break;
		case ROTATE:
			cube.rotate(command);
		}

		if (order == EXIT)
			break;
	}

	return 0;
}
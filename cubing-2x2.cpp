#define _CRT_SECURE_NO_WARNINGS

#include <algorithm>
#include <vector>
#include <queue>
#include <iostream>
#include <string>

#define UP		0
#define DOWN	1
#define FRONT	2
#define BACK	3
#define LEFT	4
#define RIGHT	5


using namespace std;

// 2x2 cube
char cube[6][4] = {

	{'w','w','w','w'}, // UP 1 2 3 4
	{'y','y','y','y'}, // DOWN 9 10 11 12
	{'r','r','r','r'}, // FRONT 5 6 7 8
	{'o','o','o','o'}, // BACK 21 22 23 24
	{'g','g','g','g'}, // LEFT 13 14 15 16
	{'b','b','b','b'}  // RIGHT 17 18 19 20

};


int cube_relation[6][4][3] = {

	{{RIGHT,0,1},{FRONT,0,1},{LEFT,0,1},{BACK,0,1}}, // UP
	{{FRONT,2,3},{RIGHT,2,3},{BACK,2,3},{LEFT,2,3}}, // DOWN
	{{UP,2,3},{RIGHT,0,2},{DOWN,1,0},{LEFT,1,3}}, // FRONT
	{{UP,1,0},{LEFT,0,2},{DOWN,3,2},{RIGHT,1,3}}, // BACK
	{{UP,0,2},{FRONT,0,2},{DOWN,0,2},{BACK,1,3}}, // LEFT
	{{UP,3,1},{BACK,0,2},{DOWN,1,3},{FRONT,1,3}} // RIGHT

};

string rotate_method[12] = {
	"U+","U-", "D+", "D-", 
	"F+", "F-", "B+", "B-", 
	"L+", "L-", "R+", "R-"

};


void init_cube() {

	string color_list = "wyrogb";

	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 9; j++)
			cube[i][j] = color_list[i];

}


void set_cube(int cube_info[]) {

	string color_list = "wyrogb";
	int order[6] = { 0,2,1,4,5,3 };

	for (int i = 0; i < 24; i++) {

		cube[order[i / 4]][i%4] = color_list[cube_info[i] - 1];
	}


}





int get_side(char side) {

	switch (side) {

	case 'U':
		return UP;

	case 'D':
		return DOWN;

	case 'F':
		return FRONT;

	case 'B':
		return BACK;

	case 'L':
		return LEFT;

	case 'R':
		return RIGHT;

	}

}



void print_side(int side) {

	for (int i = 0; i < 9; i++) {

		printf("%c", cube[side][i]);
		if (i % 3 == 2)
			printf("\n");
	}

}


void rotate(int side, bool is_clockwise) {

	int corner_points[4] = { 0,1,3,2 };
	
	if (is_clockwise) {

		// rotate target side 
		int corner_last_value = cube[side][corner_points[3]];
		for (int i = 3; i > 0; i--) {
			cube[side][corner_points[i]] = cube[side][corner_points[i - 1]];
		}

		cube[side][corner_points[0]] = corner_last_value;
		
		// rotate other 4 sides 
		int first_side_values[2] = { cube[cube_relation[side][0][0]][cube_relation[side][0][1]],cube[cube_relation[side][0][0]][cube_relation[side][0][2]] };

		for (int i = 3; i >= 0; i--) {

			if (i != 0) {
				cube[cube_relation[side][(i + 1) % 4][0]][cube_relation[side][(i + 1) % 4][1]] = cube[cube_relation[side][i][0]][cube_relation[side][i][1]];
				cube[cube_relation[side][(i + 1) % 4][0]][cube_relation[side][(i + 1) % 4][2]] = cube[cube_relation[side][i][0]][cube_relation[side][i][2]];
			}
			else
			{
				cube[cube_relation[side][(i + 1) % 4][0]][cube_relation[side][(i + 1) % 4][1]] = first_side_values[0];
				cube[cube_relation[side][(i + 1) % 4][0]][cube_relation[side][(i + 1) % 4][2]] = first_side_values[1];
			}

		}
	}
	else
	{
		// rotate target side 
		int corner_last_value = cube[side][corner_points[0]];
		for (int i = 0; i < 3; i++)
		{
			cube[side][corner_points[i]] = cube[side][corner_points[i + 1]];
		}

		cube[side][corner_points[3]] = corner_last_value;

		// rotate other 4 sides 
		int first_side_values[2] = { cube[cube_relation[side][0][0]][cube_relation[side][0][1]],cube[cube_relation[side][0][0]][cube_relation[side][0][2]]};

		for (int i = 0; i < 4; i++)
		{
			if (i != 3) {
				cube[cube_relation[side][i][0]][cube_relation[side][i][1]] = cube[cube_relation[side][i + 1][0]][cube_relation[side][i + 1][1]];
				cube[cube_relation[side][i][0]][cube_relation[side][i][2]] = cube[cube_relation[side][i + 1][0]][cube_relation[side][i + 1][2]];
			}
			else
			{
				cube[cube_relation[side][3][0]][cube_relation[side][3][1]] = first_side_values[0];
				cube[cube_relation[side][3][0]][cube_relation[side][3][2]] = first_side_values[1];
			}

		}

	}



}


bool is_solved() {

	for (int i = 0; i < 6; i++)
	{
		char target_color = cube[i][0];
		for (int j = 1; j < 4; j++)
			if (target_color != cube[i][j])
				return false;
	
	}

	return true;
}


int main()
{
	int cube_input[24];
	for (int i = 0; i < 24; i++)
		scanf("%d", &cube_input[i]);

	for (int i = 0; i < 12;i++) {

		set_cube(cube_input);
		int side = get_side(rotate_method[i][0]);  bool is_clockwise = (rotate_method[i][1] == '+' ? true : false);
		rotate(side, is_clockwise);
		if (is_solved() == true)
		{
			printf("1\n");
			return 0;
		}
	}

	printf("0\n");
	return 0;
}


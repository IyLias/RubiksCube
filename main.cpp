#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>

class Cube {

public:

	char components[6][9];
	char colors[6] = { 'w','y','r','o','g','b' };
	char face[6] = { 'U','D','F','B','L','R' };
	// order : top down front back left right

	int rotate_data[6][4][4] = {

		{ { 2,0,1,2 },{ 5,0,1,2 },{ 3,0,1,2 },{ 4,0,1,2 } }, //w
	{ { 2,6,7,8 },{ 4,6,7,8 },{ 3,6,7,8 },{ 5,6,7,8 } },  //y
	{ { 0,6,7,8 },{ 4,8,5,2 },{ 1,2,1,0, },{ 5,0,3,6 } }, //r
	{ { 0,2,1,0 },{ 5,8,5,2 },{ 1,6,7,8 },{ 4,0,3,6 } },  //o 
	{ { 0,0,3,6 },{ 3,8,5,2 },{ 1,0,3,6 },{ 2,0,3,6 } },  //g
	{ { 0,2,5,8 },{ 2,2,5,8 },{ 1,2,5,8 },{ 3,6,3,0 } }

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

	void own_rotate(int side, char dir) {

		int i;
		int data1[2][4] = { { 0,6,8,2 },{ 0,2,8,6 } }, data2[2][4] = { { 1,3,7,5 },{ 1,5,7,3 } };
		char temp_data1 = components[side][0], temp_data2 = components[side][1];

		for (i = 0; i < 3; i++)
			components[side][data1[dir == '+' ? 0 : 1][i]] = components[side][data1[dir == '+' ? 0 : 1][i + 1]];
		components[side][data1[dir == '+' ? 0 : 1][3]] = temp_data1;

		for (i = 0; i < 3; i++)
			components[side][data2[dir == '+' ? 0 : 1][i]] = components[side][data2[dir == '+' ? 0 : 1][i + 1]];
		components[side][data2[dir == '+' ? 0 : 1][3]] = temp_data2;
	}

	void rotate(char side, char dir) {

		int i, j, target;
		char temp_data[3];

		for (int i = 0; i<6; i++)
			if (face[i] == side) {
				target = i;
				break;
			}

		for (i = 0; i < 3; i++)
			temp_data[i] = components[rotate_data[target][0][0]][rotate_data[target][0][i + 1]];

		if (dir == '+') {  // clockwise

			for (i = 0; i < 3; i++)
				for (j = 0; j < 3; j++)
					components[rotate_data[target][i][0]][rotate_data[target][i][j + 1]] = components[rotate_data[target][i + 1][0]][rotate_data[target][i + 1][j + 1]];

			for (i = 0; i < 3; i++)
				components[rotate_data[target][3][0]][rotate_data[target][3][i + 1]] = temp_data[i];
		}
		else { //counterclockwise

			for (i = 0; i < 3; i++)
				components[rotate_data[target][0][0]][rotate_data[target][0][i + 1]] = components[rotate_data[target][3][0]][rotate_data[target][3][i + 1]];

			for (i = 3; i > 1; i--)
				for (j = 0; j < 3; j++)
					components[rotate_data[target][i][0]][rotate_data[target][i][j + 1]] = components[rotate_data[target][i - 1][0]][rotate_data[target][i - 1][j + 1]];

			for (i = 0; i < 3; i++)
				components[rotate_data[target][1][0]][rotate_data[target][1][i + 1]] = temp_data[i];
		}

		own_rotate(target, dir);
	}

	void print_top() {
		for (int i = 0; i < 9; i++) {
			printf("%c", components[0][i]);
			if (i == 2 || i == 5 || i == 8)
				printf("\n");
		}
	}

};

int main(void)
{
	Cube cube;





	return 0;
}
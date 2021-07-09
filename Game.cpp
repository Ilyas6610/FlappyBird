#include "Engine.h"
#include <stdlib.h>
#include <memory.h>
#include <ctime>
#include <algorithm>
#include <chrono>
#include <thread>
#include <stdio.h>
#include <iostream>
#include <vector>

#define _CRT_SECURE_NO_DEPRECATE

#define WINDOW 200
#define TUBECOLOR 0x00ff00
#define BACKGROUND 0x00bfff
#define BIRD 0xff0000
#define SCORE 0xfff000
//
//  You are free to modify this file
//

//  is_key_pressed(int button_vk_code) - check if a key is pressed,
//                                       use keycodes (VK_SPACE, VK_RIGHT, VK_LEFT, VK_UP, VK_DOWN, 'A', 'B')
//
//  get_cursor_x(), get_cursor_y() - get mouse cursor position
//  is_mouse_button_pressed(int button) - check if mouse button is pressed (0 - left button, 1 - right button)
//  clear_buffer() - set all pixels in buffer to 'black'
//  is_window_active() - returns true if window is active
//  schedule_quit_game() - quit game after act()

int res;
bool drawType;
int height = 0;
int x;
int y;
int BirdState = 0;
float timeOut = 100.;
int points;
bool result = 0;
void drawNum(int num, int x, int y) {
	if (num == 0) {
		for (int i = x - 10; i < x + 11; i++) {
			buffer[y - 20][i] = SCORE;
			buffer[y + 20][i] = SCORE;
		}
		for (int i = y - 20; i < y + 21; i++) {
			buffer[i][x - 10] = SCORE;
			buffer[i][x + 10] = SCORE;
		}
	}
	else if (num == 1) {
		for (int i = y - 20; i < y + 21; i++) {
			buffer[i][x + 10] = SCORE;
			buffer[i][x + 10] = SCORE;
		}
	}else if (num == 2) {
		for (int i = x - 10; i < x + 11; i++) {
			buffer[y - 20][i] = SCORE;
			buffer[y][i] = SCORE;
			buffer[y + 20][i] = SCORE;
		}
		for (int i = y - 20; i <= y; i++) {
			buffer[i][x + 10] = SCORE;
			buffer[i + 20][x - 10] = SCORE;
		}
	}
	else if (num == 3) {
		for (int i = x - 10; i < x + 11; i++) {
			buffer[y - 20][i] = SCORE;
			buffer[y][i] = SCORE;
			buffer[y + 20][i] = SCORE;
		}
		for (int i = y - 20; i < y + 21; i++) {
			buffer[i][x + 10] = SCORE;
		}
	}
	else if (num == 4) {
		for (int i = x - 10; i < x + 11; i++) {
			buffer[y][i] = SCORE;
		}
		for (int i = y - 20; i < y + 21; i++) {
			buffer[i][x + 10] = SCORE;
			if (i <= y)
				buffer[i][x - 10] = SCORE;
		}
	}
	else if (num == 5) {
		for (int i = x - 10; i < x + 11; i++) {
			buffer[y - 20][i] = SCORE;
			buffer[y][i] = SCORE;
			buffer[y + 20][i] = SCORE;
		}
		for (int i = y - 20; i <= y; i++) {
			buffer[i][x - 10] = SCORE;
			buffer[i + 20][x + 10] = SCORE;
		}
	}
	else if (num == 6) {
		for (int i = x - 10; i < x + 11; i++) {
			buffer[y - 20][i] = SCORE;
			buffer[y][i] = SCORE;
			buffer[y + 20][i] = SCORE;
		}
		for (int i = y - 20; i < y + 21; i++) {
			buffer[i][x - 10] = SCORE;
			if (i >= y)
				buffer[i][x + 10] = SCORE;
		}
	}
	else if (num == 7) {
		for (int i = x - 10; i < x + 11; i++) {
			buffer[y - 20][i] = SCORE;
		}
		for (int i = y - 20; i < y + 21; i++) {
			buffer[i][x + 10] = SCORE;
		}
	}
	else if (num == 8) {
		for (int i = x - 10; i < x + 11; i++) {
			buffer[y - 20][i] = SCORE;
			buffer[y][i] = SCORE;
			buffer[y + 20][i] = SCORE;
		}
		for (int i = y - 20; i < y + 21; i++) {
			buffer[i][x - 10] = SCORE;
			buffer[i][x + 10] = SCORE;
		}
	}
	else if (num == 9) {
		for (int i = x - 10; i < x + 11; i++) {
			buffer[y - 20][i] = SCORE;
			buffer[y][i] = SCORE;
			buffer[y + 20][i] = SCORE;
		}
		for (int i = y - 20; i < y + 21; i++) {
			buffer[i][x + 10] = SCORE;
			if (i <= y)
				buffer[i][x - 10] = SCORE;
		}
	}
}

void drawScore() {
	int x = 330, y = 368;
	for (int i = x - 10; i < x + 11; i++) {
		buffer[y - 20][i] = SCORE;
		buffer[y][i] = SCORE;
		buffer[y + 20][i] = SCORE;
	}
	for (int i = y - 20; i <= y; i++) {
		buffer[i][x - 10] = SCORE;
		buffer[i + 20][x + 10] = SCORE;
	}
	x += 30;
	for (int i = x - 10; i < x + 11; i++) {
		buffer[y - 20][i] = SCORE;
		buffer[y + 20][i] = SCORE;
	}
	for (int i = y - 20; i < y + 21; i++) {
		buffer[i][x - 10] = SCORE;
	}
	x += 30;
	for (int i = x - 10; i < x + 11; i++) {
		buffer[y - 20][i] = SCORE;
		buffer[y + 20][i] = SCORE;
	}
	for (int i = y - 20; i < y + 21; i++) {
		buffer[i][x - 10] = SCORE;
		buffer[i][x + 10] = SCORE;
	}
	x += 30;
	for (int i = x - 10; i < x + 11; i++) {
		buffer[y - 20][i] = SCORE;
	}
	for (int i = y - 20; i < y + 21; i++) {
		buffer[i][x - 10] = SCORE;
	}
	x += 30;
	for (int i = x - 10; i < x + 11; i++) {
		buffer[y - 20][i] = SCORE;
		buffer[y][i] = SCORE;
		buffer[y + 20][i] = SCORE;
	}
	for (int i = y - 20; i < y + 21; i++) {
		buffer[i][x - 10] = SCORE;
	}
	x += 30;
	for (int i = x - 10; i < x - 5; i++) {
		for( int j = y - 20; j < y - 15; j++ )
			buffer[j][i] = SCORE;
		for (int j = y + 20; j > y + 15; j--)
			buffer[j][i] = SCORE;
	}
}

void drawFin() {
	clear_buffer();
	drawScore();
	int x = 500, y = 368, z = 0;
	std::vector<int> score = {};
	do {
		int f = points % 10;
		points /= 10;
		score.push_back(f);
	} while (points != 0);
	std::reverse(score.begin(), score.end());
	for (auto it = score.begin(); it != score.end(); it++) {
		drawNum(*it, x + z * 30, y);
		z++;
	}
}


void drawBird() {
	if (BirdState == 0) {
		for (int i = y - 20; i < y + 20; i++)
			for (int j = x - 20; j < x + 20; j++)
				buffer[i][j] = BIRD;
		BirdState = 1;
	}
	else if (BirdState == 1) {
		y += 2;
		if (y < 0 || y > SCREEN_HEIGHT - 1) {
			drawFin();
			schedule_quit_game();
			return;
		}
		for (int i = y - 20; i < y + 20; i++)
			for (int j = x - 20; j < x + 20; j++) {
				if (buffer[i][j] == TUBECOLOR) {
					drawFin();
					schedule_quit_game();
					return;
				}
				buffer[i][j] = BIRD;
			}
	}else if (BirdState == 2) {
		y -= 100;
		if (y < 0 || y > SCREEN_HEIGHT - 1) {
			drawFin();
			schedule_quit_game();
			return;
		}
		for (int i = y - 20; i < y + 20; i++)
			for (int j = x - 20; j < x + 20; j++) {
				if (buffer[i][j] == TUBECOLOR) {
					drawFin();
					schedule_quit_game();
					return;
				}
				buffer[i][j] = BIRD;
			}
		BirdState = 1;
	}
	if (buffer[0][x - 21] == TUBECOLOR && buffer[0][x - 20] != TUBECOLOR)
		points++;
}
// initialize game data in this function
void initialize()
{
	res = 0;
	drawType = 0;
	x = 200;
	y = 300;
	points = 0;
	draw();
}

// this function is called to update game data,
// dt - time elapsed since the previous update (in seconds)
void act(float dt)
{
	timeOut += dt;
	if (is_key_pressed(VK_SPACE)) {
		if (timeOut > 0.2) {
			BirdState = 2;
			timeOut = 0.;
		}
	}
	else if (is_key_pressed(VK_ESCAPE)) {
		schedule_quit_game();
	}
}

// fill buffer in this function
// uint32_t buffer[SCREEN_HEIGHT][SCREEN_WIDTH] - is an array of 32-bit colors (8 bits per R, G, B)
void draw()
{
	std::srand(rand() % 1000);
	if (drawType == 0) {
		for( int i = 0; i < SCREEN_HEIGHT; i++ )
			for (int j = 0; j < SCREEN_WIDTH; j++) {
				buffer[i][j] = BACKGROUND;
			}
		int step = 100;
		int sz = rand() % 330;
		for (int j = 823; j < 1023; j++) {
			for (int k = 0; k < sz; k++)
				buffer[k][j] = TUBECOLOR;
			for (int d = SCREEN_HEIGHT - 1; d > sz + WINDOW; d--)
				buffer[d][j] = TUBECOLOR;
		}
		sz = rand() % 330;
		for (int j = 423; j < 623; j++) {
			for (int k = 0; k < sz; k++)
				buffer[k][j] = TUBECOLOR;
			for (int d = SCREEN_HEIGHT - 1; d > sz + WINDOW; d--)
				buffer[d][j] = TUBECOLOR;
		}
		drawType = 1;
		drawBird();
	}
	else if(drawType == 1){
		if (buffer[0][824] != TUBECOLOR){
			for (int i = 0; i < SCREEN_WIDTH - 1; i++)
				for (int j = 0; j < SCREEN_HEIGHT; j++) {
					buffer[j][i] = buffer[j][i + 1];
					if (buffer[j][i] == BIRD)
						buffer[j][i] = BACKGROUND;
				}
			if (height == 0)
				height = rand() % 330;
			for (int d = SCREEN_HEIGHT - 1; d > height + WINDOW; d--)
				buffer[d][SCREEN_WIDTH - 1] = TUBECOLOR;
			for (int d = 0; d < height; d++)
				buffer[d][SCREEN_WIDTH - 1] = TUBECOLOR;
		}
		else {
			height = 0;
			for (int i = 0; i < SCREEN_WIDTH - 1; i++)
				for (int j = 0; j < SCREEN_HEIGHT; j++) {
					buffer[j][i] = buffer[j][i + 1];
					if (buffer[j][i] == BIRD)
						buffer[j][i] = BACKGROUND;
				}

			for (int j = 0; j < SCREEN_HEIGHT; j++)
				buffer[j][SCREEN_WIDTH - 1] = BACKGROUND;
		}
		drawBird();
	}
	else if (drawType == 2) {
		for (int i = 0; i < SCREEN_HEIGHT; i++)
			for (int j = 0; j < SCREEN_WIDTH; j++) {
				buffer[i][j] = BACKGROUND;
			}

		drawFin();
	}
}

// free game data in this function
void finalize()
{
	while (!is_key_pressed(VK_SPACE)) {
		continue;
	}
	clear_buffer();
}


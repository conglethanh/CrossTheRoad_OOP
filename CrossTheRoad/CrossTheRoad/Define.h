#pragma once
#define WIDTH 80
#define HEIGHT 25
#define MAX_LEVEL 2

#define NUM_LANE 5
static int LANE[5] = { 20, 16, 12, 8, 4 };
static bool drawAll = false;

#define CONST_DELAY_CAR 40
#define CONST_MOVE_CAR 200
#define CONST_DELAY_TRUCK 50
#define CONST_MOVE_TRUCK 100//100*(200/speed) (s)
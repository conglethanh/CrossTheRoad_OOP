#pragma once
#include <iostream>
#include <Windows.h>
#include <cstdlib>
#include <thread>
#include <string>
#include <conio.h>
#include <vector>
#include <fstream>
using namespace std;

#pragma comment(lib,"winmm.lib")

void GotoXY(int x, int y);
void FixConsoleWindow();

void resizeConsole(int width, int height);

void ShowCur(bool CursorVisibility);
void SetColor(WORD color);

void DrawBoard(int x, int y, int width, int height);
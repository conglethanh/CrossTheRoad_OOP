#pragma once
#include "CPEOPLE.h"
#include "CVEHICLE.h"
#include "CANIMAL.h"
#include "CLIGHT.h"
#include "Define.h"
#include <vector>

class CGAME
{
private:
	CPEOPLE cn;

	int xhSize;
	int xtSize;
	int klSize;
	int chSize;

	vector<CCAR> axh;
	vector<CTRUCK> axt;
	vector<CDINOSAUR> akl;
	vector<CBIRD> ach;
	vector<CLIGHT> aden;

	bool IS_RUNNING;
	int level;
	int index;

	int velocity;
	int numOfObj;

	int score;
	bool isSound;
public:
	CGAME();
	CGAME(int speed, int numObj, bool _isSound);

	void levelUp(int index);
	bool getSound();

	vector<CCAR> getCar();
	vector<CTRUCK> getTruck();
	vector<CDINOSAUR> getDinosaur();
	vector<CBIRD> getBird();

	void updatePosPeople(int);
	void updatePosVehicle();

	int getNumObj();
	int getSpeed();

	CPEOPLE& getPeople();
	vector<CVEHICLE*> getVehicle();
	vector<CANIMAL*> getAnimal();

	void drawLane();
	void clearGame();
	void drawGame();

	void processFinish();

	void startGame();
	void resetGame();

	void pauseGame(thread &t1, thread &t2);
	void resumeGame(thread &t1, thread &t2);
	void exitGame(thread &t1, thread &t2);

	bool& isRunning();
	void processDead();

	void saveGame();
	void loadGame();
	void loadGame(int&);
	void menu();
};
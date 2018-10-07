#pragma once
#include "Library.h"
#include "CPEOPLE.h"
#include "CGAME.h"
#include "Define.h"

CGAME* cg;
int MOVING;
int temp;

void ThreadSound()
{
	while (cg->isRunning())
	{
		if (cg->getPeople().isLive() && cg->getSound()) {
			if (cg->getPeople().layToaDoY()[1] < LANE[0] && cg->getPeople().layToaDoY()[1] > LANE[1] + 1)
				cg->getPeople().hearSoundCar();
			else if (cg->getPeople().layToaDoY()[1] < LANE[1] && cg->getPeople().layToaDoY()[1] > LANE[2] + 1)
				cg->getPeople().hearSoundTruck();
			else if (cg->getPeople().layToaDoY()[1] < LANE[2] && cg->getPeople().layToaDoY()[1] > LANE[3] + 1)
				cg->getPeople().hearSoundDino();
			else if (cg->getPeople().layToaDoY()[1] < LANE[3] && cg->getPeople().layToaDoY()[1]>LANE[3] - 4)
				cg->getPeople().hearSoundBird();
		}
	}
}

void SubThread()
{
	while (cg->isRunning())
	{
		drawAll = false;
		if (cg->getPeople().isLive())
		{
			cg->clearGame();

			cg->updatePosPeople(MOVING);
			cg->processFinish();

			MOVING = ' ';

			cg->updatePosVehicle();

			cg->drawGame();
			drawAll = true;
			if (cg->getPeople().isImpact(cg->getVehicle()) || cg->getPeople().isImpact(cg->getAnimal())){
				cg->processDead();
			}
		}
		Sleep(200 / cg->getSpeed());
	}
}

void main()
{

	cg = new CGAME();
	cg->menu();
	cg->startGame();

	thread t1(SubThread);
	thread t2(ThreadSound);

	while (1)
	{
		ShowCur(0);
		temp = toupper(getch());

		if (cg->getPeople().isLive() == true){
			if (temp == 'L'&&drawAll == true)
				cg->saveGame();
			if (temp == 'T'&&drawAll == true)
				cg->loadGame();

			if (temp == 'P'&&drawAll == true)
				cg->pauseGame(t1, t2);
			else if (temp == 27)
			{
				cg->exitGame(t1, t2);
				return;
			}
			else if (temp == 'R')
				cg->resumeGame(t1, t2);

			MOVING = temp;
		}
		else
		{
			if (drawAll)
			if (temp == 'Y'){
				cg->resetGame();
				cg->getPeople().isLive() = true;
			}
			else
			{
				cg->exitGame(t1, t2);
				return;
			}
		}
	}
}
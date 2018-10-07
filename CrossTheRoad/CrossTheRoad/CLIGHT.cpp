#include "CLIGHT.h"

CLIGHT::CLIGHT()
{
}

void CLIGHT::init(int x, int y)
{
	mX.push_back(x);
	mY.push_back(y);
	mX.push_back(x);
	mY.push_back(y - 1);
	mSize = 2;
	mState = true;//set green
	count = 0;
}

void CLIGHT::draw(string type)
{
	if (type != "_"&&type != " ")
	{
		if (mState == true)//green
		{
			GotoXY(mX[0], mY[0]);
			SetColor(RED_OFF);
			cout << (char)LIGHT_SHAPE;
			GotoXY(mX[1], mY[1]);
			SetColor(GREEN_ON);
			cout << (char)LIGHT_SHAPE;
		}
		else
		{
			GotoXY(mX[0], mY[0]);
			SetColor(RED_ON);
			cout << (char)LIGHT_SHAPE;
			GotoXY(mX[1], mY[1]);
			SetColor(GREEN_OFF);
			cout << (char)LIGHT_SHAPE;
		}
	}
	else
	{
		GotoXY(mX[0], mY[0]);
		cout << type;
		GotoXY(mX[1], mY[1]);
		cout << type;
	}
	SetColor(15);
}

bool CLIGHT::isGreen(int constMove, int constDelay)
{
	if (mState == true && count%constMove == constMove - 1)
	{
		mState = false;
		count = 0;
	}
	else if (mState == false && count%constDelay == constDelay - 1)
	{
		mState = true;
		count = 0;
	}
	else
		count = count + 1;

	return mState;
}

int& CLIGHT::countDelay()
{
	return count;
}

void CLIGHT::write(ofstream &fo)
{
	fo.write((char*)&mSize, sizeof(int));
	for (int i = 0; i < mSize; i++){
		fo.write((char*)&mX[i], sizeof(int));
		fo.write((char*)&mY[i], sizeof(int));
	}
	fo.write((char*)&mSize, sizeof(int));
	fo.write((char*)&mState, sizeof(bool));
	fo.write((char*)&count, sizeof(int));
}

void CLIGHT::read(ifstream &fi)
{
	fi.read((char*)&mSize, sizeof(int));
	mX.clear();
	mY.clear();
	for (int i = 0; i < mSize; i++){
		mX.push_back(0);
		mY.push_back(0);
		fi.read((char*)&mX[i], sizeof(int));
		fi.read((char*)&mY[i], sizeof(int));
	}
	fi.read((char*)&mSize, sizeof(int));
	fi.read((char*)&mState, sizeof(bool));
	fi.read((char*)&count, sizeof(int));
}

CLIGHT::~CLIGHT()
{
}
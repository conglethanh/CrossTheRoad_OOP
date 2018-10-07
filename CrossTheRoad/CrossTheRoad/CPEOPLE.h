#pragma once
#include "Define.h"
#include "Library.h"
#include "CVEHICLE.h"
#include "CANIMAL.h"

class CPEOPLE
{
private:
	vector<int> mX, mY;
	int mSize;
	bool mState;
public:

	CPEOPLE();

	void Up();
	void Down();
	void Right();
	void Left();

	vector<int> layToaDoX();
	vector<int> layToaDoY();

	bool isImpact(int i, int j);
	bool isImpact(vector<CVEHICLE*> p);
	bool isImpact(vector<CANIMAL*> p);

	void draw(string type);

	bool& isLive();
	
	void hearSoundBird();
	void hearSoundDino();
	void hearSoundCar();
	void hearSoundTruck();
	void soundPeople();

	void write(ofstream &fo);
	void read(ifstream &fi);
};
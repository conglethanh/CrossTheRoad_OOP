#include "CPEOPLE.h"

CPEOPLE::CPEOPLE()
{
	mX.push_back(WIDTH / 2 - 2);
	mY.push_back(HEIGHT - 1);
	mX.push_back(mX[0]);
	mY.push_back(mY[0] - 1);
	mState = true;
	mSize = mX.size();
}

void CPEOPLE::Up()
{
	for (int i = 0; i < mSize; i++)
		mY[i] = (mY[i] <= 1) ? HEIGHT - 1 : mY[i] - 1;
}
void CPEOPLE::Down()
{
	for (int i = 0; i < mSize; i++)
		mY[i] = (mY[i] >= HEIGHT - 1 - i) ? HEIGHT - 1 - i : mY[i] + 1;
}
void CPEOPLE::Right()
{
	for (int i = 0; i < mSize; i++)
		mX[i] = (mX[i] >= WIDTH - 1) ? 1 : mX[i] + 1;
}
void CPEOPLE::Left()
{
	for (int i = 0; i < mSize; i++)
		mX[i] = (mX[i] <= 1) ? WIDTH - 1 : mX[i] - 1;
}

vector<int> CPEOPLE::layToaDoX(){
	return mX;
}
vector<int> CPEOPLE::layToaDoY(){
	return mY;
}

bool CPEOPLE::isImpact(int i, int j){
	for (int k = 0; k < mSize; k++)
	{
		if (mX[k] == i&&mY[k] == j)
			return true;
	}
	return false;
}

void CPEOPLE::draw(string type){
	if (type != "_"&&type != " ")
	{
		GotoXY(mX[0], mY[0]);
		cout << (char)197;
		GotoXY(mX[1], mY[1]);
		cout << (char)254;
	}
	else
	{
		for (int i = 0; i < mSize; i++)
		{
			GotoXY(mX[i], mY[i]);
			cout << type;
		}
	}
}

bool& CPEOPLE::isLive(){
	return mState;
}

bool CPEOPLE::isImpact(vector<CVEHICLE*> p){
	int pSize = p.size();
	for (int i = 0; i < pSize; i++){
		for (int j = 0; j < mSize; j++)
		if (p[i]->isImpact(mX[j], mY[j]))
		{
			mState = false;
			return true;
		}
	}
	return false;
}

bool CPEOPLE::isImpact(vector<CANIMAL*> p){
	int pSize = p.size();
	for (int i = 0; i < pSize; i++){
		for (int j = 0; j < mSize; j++)
		if (p[i]->isImpact(mX[j], mY[j]))
		{
			mState = false;
			return true;
		}
	}
	return false;
}

void CPEOPLE::hearSoundBird()
{
	PlaySound(L"sound\\bird.wav", NULL, SND_FILENAME);
}

void CPEOPLE::hearSoundDino()
{
	PlaySound(L"sound\\dinosaur.wav", NULL, SND_FILENAME);
}

void CPEOPLE::hearSoundCar()
{
	PlaySound(L"sound\\car.wav", NULL, SND_FILENAME);
}

void CPEOPLE::hearSoundTruck()
{
	PlaySound(L"sound\\truck.wav", NULL, SND_FILENAME);
}

void CPEOPLE::soundPeople()
{
	PlaySound(L"sound\\people.wav", NULL, SND_FILENAME);
}

void CPEOPLE::write(ofstream &fo){
	for (int i = 0; i < mSize; i++){
		fo.write((char*)&mX[i], sizeof(int));
		fo.write((char*)&mY[i], sizeof(int));
	}
}

void CPEOPLE::read(ifstream &fi){
	for (int i = 0; i < mSize; i++){
		fi.read((char*)&mX[i], sizeof(int));
		fi.read((char*)&mY[i], sizeof(int));
	}
}
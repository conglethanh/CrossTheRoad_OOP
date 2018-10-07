#include "CANIMAL.h"

CANIMAL::CANIMAL(){
}

CANIMAL::CANIMAL(int x, int y){
	mX.push_back(x);
	mY.push_back(y);
	mSize = mX.size();
}

void CANIMAL::init(int x, int y)
{
	mX.push_back(x);
	mY.push_back(y);
	mSize = mX.size();
}

void CANIMAL::move(int x, int y)
{
	for (int i = 0; i < mSize; i++)
	{
		mX[i] += x;
		mY[i] += y;
	}
}

void CANIMAL::draw(string type){
	if (type == "_"){
		for (int i = 0; i < mSize; i++){
			GotoXY(mX[i], mY[i]);
			if (mY[i] % 4 == 0)
				cout << type;
			else
				cout << " ";
		}
		return;
	}
	for (int i = 0; i < mSize; i++){
		GotoXY(mX[i], mY[i]);
		cout << (char)219;
	}
}

bool CANIMAL::isImpact(int i, int j){
	for (int k = 0; k < mSize; k++){
		if (mX[k] == i&&mY[k] == j)
			return true;
	}
	return false;
}

void CANIMAL::write(ofstream &fo)
{
	fo.write((char*)&mSize, sizeof(int));
	for (int i = 0; i < mSize; i++){
		fo.write((char*)&mX[i], sizeof(int));
		fo.write((char*)&mY[i], sizeof(int));
	}
}

void CANIMAL::read(ifstream &fi)
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
}

void CDINOSAUR::init(int x, int y)
{
	if (x > WIDTH - 4)
		x -= 3;
	CANIMAL::init(x, y);
	mX.push_back(x + 1);
	mY.push_back(y);
	mX.push_back(x + 2);
	mY.push_back(y);

	mX.push_back(x + 2);
	mY.push_back(y - 1);
	mX.push_back(x + 3);
	mY.push_back(y - 1);

	mX.push_back(x + 3);
	mY.push_back(y - 2);
	mSize = mX.size();
}

void CDINOSAUR::move(int x, int y)
{
	CANIMAL::move(x, y);
	for (int i = 0; i < mSize; i++)
	if (mX[i] >= WIDTH) mX[i] = 1;
}

void CBIRD::init(int x, int y)
{
	if (x < 3)
		x += 1;
	CANIMAL::init(x, y - 2);
	mX.push_back(x + 1);
	mY.push_back(y - 1);
	mX.push_back(x + 2);
	mY.push_back(y - 2);
	mSize = mX.size();
}

void CBIRD::move(int x, int y)
{
	CANIMAL::move(x, y);
	for (int i = 0; i < mSize; i++)
	if (mX[i] <= 0) mX[i] = WIDTH - 1;
}
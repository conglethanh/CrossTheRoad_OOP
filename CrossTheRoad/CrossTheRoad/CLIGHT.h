#pragma once
#include "Library.h"
#include "Define.h"

#define GREEN_ON 10
#define GREEN_OFF 2
#define RED_ON 12
#define RED_OFF 4
#define LIGHT_SHAPE 219

class CLIGHT
{
private:
	vector<int> mX, mY;
	int mSize;
	bool mState;//green=true & red=false
	int count;
public:
	CLIGHT();
	~CLIGHT();

	void init(int x, int y);
	void draw(string type);
	bool isGreen(int constMove, int constDelay);
	int& countDelay();

	void write(ofstream &fo);
	void read(ifstream &fi);
};
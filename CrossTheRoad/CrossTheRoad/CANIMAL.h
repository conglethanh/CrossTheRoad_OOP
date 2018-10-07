#pragma once
#include "Library.h"
#include "Define.h"

class CANIMAL
{
protected:
	vector<int>	mX, mY;
	int mSize;
public:
	CANIMAL();
	CANIMAL(int, int);
	void init(int x, int y);
	virtual void move(int x, int y);

	void draw(string type);
	bool isImpact(int i, int j);
	void write(ofstream &fo);
	void read(ifstream &fi);
};

class CDINOSAUR :public CANIMAL
{
public:
	void init(int x, int y);
	void move(int x, int y);
};

class CBIRD :public CANIMAL
{
public:
	void init(int x, int y);
	void move(int x, int y);
};
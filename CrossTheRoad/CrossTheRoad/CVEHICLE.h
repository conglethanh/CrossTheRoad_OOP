#pragma once
#include "Library.h"
#include "Define.h"

class CVEHICLE
{
protected:
	vector<int>	mX, mY;
	int mSize;
public:
	CVEHICLE();
	CVEHICLE(int, int);
	void init(int x, int y);
	virtual void move(int x, int y);

	bool isImpact(int i, int j);
	void draw(string type);

	void write(ofstream &fo);
	void read(ifstream &fi);
};

class CCAR :public CVEHICLE
{
public:
	void init(int x, int y);
	void move(int x, int y);
};

class CTRUCK :public CVEHICLE
{
public:
	void init(int x, int y);
	void move(int x, int y);
};
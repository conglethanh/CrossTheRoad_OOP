#include "CGAME.h"

string stringEnd = "Dead, type y to continue or anykey to exit";

CGAME::CGAME(){
	isSound = false;
	velocity = 4;
	numOfObj = 2;
	index = numOfObj;//level mac dinh
	for (int i = 0; i < index; i++){
		axh.push_back(CCAR());
		axh[i].init(WIDTH / index * i + 1, LANE[0]);

		axt.push_back(CTRUCK());
		axt[i].init(WIDTH / index * i + 1, LANE[1]);

		akl.push_back(CDINOSAUR());
		akl[i].init(WIDTH / index * i + 14, LANE[2]);

		ach.push_back(CBIRD());
		ach[i].init(WIDTH / index * i + 14, LANE[3]);
	}

	aden.push_back(CLIGHT());
	aden[0].init(WIDTH - 1, LANE[0] - 2);

	aden.push_back(CLIGHT());
	aden[1].init(1, LANE[1] - 2);

	xhSize = axh.size();
	xtSize = axt.size();
	klSize = akl.size();
	chSize = ach.size();
	level = 0;
	score = 0;
}

CGAME::CGAME(int speed, int numObj, bool _isSound)
{
	isSound = _isSound;
	velocity = speed;
	numOfObj = numObj;

	index = numOfObj;//level mac dinh
	for (int i = 0; i < index; i++){
		axh.push_back(CCAR());
		axh[i].init(WIDTH / index * i + 1, LANE[0]);

		axt.push_back(CTRUCK());
		axt[i].init(WIDTH / index * i + 1, LANE[1]);

		akl.push_back(CDINOSAUR());
		akl[i].init(WIDTH / index * i + 14, LANE[2]);

		ach.push_back(CBIRD());
		ach[i].init(WIDTH / index * i + 14, LANE[3]);
	}

	aden.push_back(CLIGHT());
	aden[0].init(WIDTH - 1, LANE[0] - 2);

	aden.push_back(CLIGHT());
	aden[1].init(1, LANE[1] - 2);

	xhSize = axh.size();
	xtSize = axt.size();
	klSize = akl.size();
	chSize = ach.size();
	level = 0;
	score = 0;
}

void CGAME::levelUp(int index){
	index += numOfObj;
	axh.clear();
	axt.clear();
	akl.clear();
	ach.clear();
	for (int i = 0; i < index; i++){
		axh.push_back(CCAR());
		axh[i].init(WIDTH / index * i + 1, LANE[0]);

		axt.push_back(CTRUCK());
		axt[i].init(WIDTH / index * i + 1, LANE[1]);

		akl.push_back(CDINOSAUR());
		akl[i].init(WIDTH / index * i + 14, LANE[2]);

		ach.push_back(CBIRD());
		ach[i].init(WIDTH / index * i + 14, LANE[3]);
	}
	xhSize = axh.size();
	xtSize = axt.size();
	klSize = akl.size();
	chSize = ach.size();
}

vector<CCAR> CGAME::getCar(){
	return axh;
}

vector<CTRUCK> CGAME::getTruck(){
	return axt;
}

vector<CDINOSAUR> CGAME::getDinosaur(){
	return akl;
}
vector<CBIRD> CGAME::getBird(){
	return ach;
}

void CGAME::updatePosPeople(int temp)
{
	switch (temp)
	{
	case 'A':
		cn.Left();
		break;
	case 'S':
		cn.Down();
		break;
	case 'D':
		cn.Right();
		break;
	case 'W':
		cn.Up();
		break;
	}
}

void CGAME::processFinish(){
	if (cn.layToaDoY()[1] == HEIGHT - 1)
	{
		cn.Up();
		level++;
		score++;
		int temp = score;
		if (isSound)
			PlaySound(L"sound\\finish.wav", NULL, SND_FILENAME);
		if (level > MAX_LEVEL){
			resetGame();
			score = temp;
			this->getPeople().isLive() = true;
		}
		else
			this->levelUp(level);
	}
}

void CGAME::processDead(){
	this->getPeople().isLive() = false;

	GotoXY(WIDTH / 5 + 2, HEIGHT + 1);
	cout << stringEnd;
	if (isSound)
		this->getPeople().soundPeople();
	int i = 0;
	while (i < 5 && cn.isLive() == false && IS_RUNNING)
	{
		SetColor(i + 10);
		cn.draw("Y");
		Sleep(300);
		i++;
		if (i == 4)
			i = 0;
	}
	if (IS_RUNNING)
	{
		SetColor(15);
		this->drawLane();
	}
}

CPEOPLE& CGAME::getPeople(){
	return this->cn;
}

int CGAME::getNumObj()
{
	return numOfObj;
}

int CGAME::getSpeed()
{
	return velocity;
}

vector<CVEHICLE*> CGAME::getVehicle(){
	vector<CVEHICLE*> tmp;

	for (int i = 0; i < xhSize; i++){
		tmp.push_back(&axh[i]);
	}

	for (int i = 0; i < xtSize; i++){
		tmp.push_back(&axt[i]);
	}
	return tmp;
}

vector<CANIMAL*> CGAME::getAnimal(){
	vector<CANIMAL*> tmp;

	for (int i = 0; i < klSize; i++){
		tmp.push_back(&akl[i]);
	}

	for (int i = 0; i < chSize; i++){
		tmp.push_back(&ach[i]);
	}
	return tmp;
}

void CGAME::drawLane()
{
	//in làn đường
	for (int i = 1; i < WIDTH; i++)
	for (int j = 1; j < HEIGHT; j++){
		if (j % 4 == 0)
		{
			if (j != HEIGHT - 1)
			{
				GotoXY(i, j);
				cout << "_";
			}
		}
	}
}

void CGAME::updatePosVehicle()
{
	if (this->getPeople().isLive())
	{
		if (aden[0].isGreen(CONST_MOVE_CAR, CONST_DELAY_CAR))
		{
			for (int i = 0; i < xhSize; i++)
				axh[i].move(1, 0);
		}
		if (aden[1].isGreen(CONST_MOVE_TRUCK, CONST_DELAY_TRUCK))
		for (int i = 0; i < xtSize; i++)
			axt[i].move(-1, 0);

		for (int i = 0; i < klSize; i++)
			akl[i].move(1, 0);
		for (int i = 0; i < chSize; i++)
			ach[i].move(-1, 0);
	}
}

void CGAME::clearGame(){
	for (int i = 0; i < xhSize; i++)
		this->getCar()[i].draw("_");
	for (int i = 0; i < xtSize; i++)
		this->getTruck()[i].draw("_");

	for (int i = 0; i < klSize; i++)
		this->getDinosaur()[i].draw("_");
	for (int i = 0; i < chSize; i++)
		this->getBird()[i].draw("_");

	int xCNSize = this->getPeople().layToaDoX().size();
	for (int i = 0; i < xCNSize; i++)
	if (this->getPeople().layToaDoY()[i] % 4 == 0 && this->getPeople().layToaDoY()[i] != HEIGHT - 1 - i)
		this->getPeople().draw("_");
	else
		this->getPeople().draw(" ");

	for (int i = 0; i < NUM_LANE; i++)
	{
		GotoXY(this->getPeople().layToaDoX()[0], LANE[i]);
		cout << "_";
		GotoXY(this->getPeople().layToaDoX()[0], LANE[i] + 1);
		cout << " ";
	}
}

void CGAME::drawGame(){
	aden[0].draw("L");
	aden[1].draw("L");
	GotoXY(1, HEIGHT + 1);
	cout << "LEVEL: " << level;
	GotoXY(WIDTH / 2 - 5, HEIGHT + 1);
	cout << "SCORE: " << score;
	GotoXY(WIDTH - 13, HEIGHT + 1);
	cout << "MAX LEVEL: " << MAX_LEVEL;
	this->getPeople().draw("Y");

	for (int i = 0; i < xhSize; i++)
		this->getCar()[i].draw("C");

	for (int i = 0; i < xtSize; i++)
		this->getTruck()[i].draw("T");

	for (int i = 0; i < klSize; i++)
		this->getDinosaur()[i].draw("D");

	for (int i = 0; i < chSize; i++)
		this->getBird()[i].draw("B");

}

void CGAME::pauseGame(thread &t1, thread &t2) {
	GotoXY(WIDTH / 6 * 4 + 2, HEIGHT + 3);
	cout << "RESUME (R)";
	SuspendThread(t1.native_handle());
	SuspendThread(t2.native_handle());
}
void CGAME::resumeGame(thread &t1, thread &t2){
	GotoXY(WIDTH / 6 * 4 + 2, HEIGHT + 3);
	cout << "PAUSE (P) ";
	ResumeThread(t1.native_handle());
	ResumeThread(t2.native_handle());
}

void CGAME::exitGame(thread &t1, thread &t2) {
	cn.isLive() = false;
	t2.detach();
	t1.detach();
	IS_RUNNING = false;
	system("cls");
	GotoXY(WIDTH / 2 - 2, HEIGHT / 2);
	cout << "GAME OVER";
	GotoXY(WIDTH / 2 - 2 - 7, HEIGHT / 2 + 1);
	cout << "THANK YOU FOR PLAYING " << (char)254;
	GotoXY(2, HEIGHT + 2);
	Sleep(1000);
}

bool& CGAME::isRunning(){
	return this->IS_RUNNING;
}

void CGAME::startGame(){
	system("cls");
	DrawBoard(0, 0, WIDTH, HEIGHT);
	this->drawLane();

	GotoXY(WIDTH / 6 + 2, HEIGHT + 3);
	cout << "SAVE (L)";
	GotoXY(WIDTH / 6 * 2 + 2, HEIGHT + 3);
	cout << "LOAD (T)";
	GotoXY(WIDTH / 6 * 3 + 2, HEIGHT + 3);
	cout << "EXIT (ESC)";
	GotoXY(WIDTH / 6 * 4 + 2, HEIGHT + 3);
	cout << "PAUSE (P) ";

	this->getPeople().isLive() = true;
}

void CGAME::resetGame(){
	SetColor(15);
	clearGame();

	int sizeStr = stringEnd.length();
	GotoXY(WIDTH / 5 + 2, HEIGHT + 1);
	for (int i = 0; i < sizeStr; i++) cout << " ";
	CGAME* cg = new CGAME(velocity, numOfObj, isSound);
	*this = *cg;

	this->getPeople().isLive() = false;
}

void CGAME::saveGame()
{
	this->getPeople().isLive() = false;
	GotoXY(0, HEIGHT + 5);
	string title = "Save FileSave's name: ";
	cout << title;
	string fileName;
	cin >> fileName;

	ofstream fo(fileName, ios::binary);

	if (fo)
	{
		cn.write(fo);
		fo.write((char*)&xhSize, sizeof(int));
		fo.write((char*)&xtSize, sizeof(int));
		fo.write((char*)&klSize, sizeof(int));
		fo.write((char*)&chSize, sizeof(int));
		for (int i = 0; i < xhSize; i++) axh[i].write(fo);
		for (int i = 0; i < xtSize; i++) axt[i].write(fo);
		for (int i = 0; i < klSize; i++) akl[i].write(fo);
		for (int i = 0; i < chSize; i++) ach[i].write(fo);
		for (int i = 0; i < 2; i++) aden[i].write(fo);
		fo.write((char*)&IS_RUNNING, sizeof(bool));
		fo.write((char*)&level, sizeof(int));
		fo.write((char*)&index, sizeof(int));
		fo.write((char*)&velocity, sizeof(int));
		fo.write((char*)&numOfObj, sizeof(int));
		fo.write((char*)&score, sizeof(int));
		//fo.write((char*)&isSound, sizeof(bool));
	}
	fo.close();
	//Xu ly effects 
	Sleep(500);
	GotoXY(0, HEIGHT + 5);
	for (int i = 0; i < title.length() + fileName.length(); i++)
		cout << " ";
	GotoXY(0, HEIGHT + 5);
	if (fo)
		cout << "...DONE!";
	else
		cout << "...FAIL!";
	Sleep(500);
	GotoXY(0, HEIGHT + 5);
	cout << "        ";
	this->getPeople().isLive() = true;
}

void CGAME::loadGame()
{
	this->getPeople().isLive() = false;
	GotoXY(0, HEIGHT + 5);
	string title = "Load FileSave's name: ";
	cout << title;
	string fileName;
	cin >> fileName;

	ifstream fi(fileName, ios::binary);
	if (fi)
	{
		clearGame();
		cn.read(fi);
		fi.read((char*)&xhSize, sizeof(int));
		fi.read((char*)&xtSize, sizeof(int));
		fi.read((char*)&klSize, sizeof(int));
		fi.read((char*)&chSize, sizeof(int));
		axh.clear();
		axt.clear();
		akl.clear();
		ach.clear();
		aden.clear();
		for (int i = 0; i < xhSize; i++)
		{
			axh.push_back(CCAR());
			axh[i].read(fi);
		}
		for (int i = 0; i < xtSize; i++)
		{
			axt.push_back(CTRUCK());
			axt[i].read(fi);
		}
		for (int i = 0; i < klSize; i++)
		{
			akl.push_back(CDINOSAUR());
			akl[i].read(fi);
		}
		for (int i = 0; i < chSize; i++)
		{
			ach.push_back(CBIRD());
			ach[i].read(fi);
		}
		for (int i = 0; i < 2; i++)
		{
			aden.push_back(CLIGHT());
			aden[i].read(fi);
		}

		fi.read((char*)&IS_RUNNING, sizeof(bool));
		fi.read((char*)&level, sizeof(int));
		fi.read((char*)&index, sizeof(int));
		fi.read((char*)&velocity, sizeof(int));
		fi.read((char*)&numOfObj, sizeof(int));
		fi.read((char*)&score, sizeof(int));
		//fi.read((char*)&isSound, sizeof(bool));
	}
	fi.close();
	//Xu ly effects 
	Sleep(500);
	GotoXY(0, HEIGHT + 5);
	for (int i = 0; i < title.length() + fileName.length(); i++)
		cout << " ";
	GotoXY(0, HEIGHT + 5);
	if (fi)
		cout << "...DONE!";
	else
		cout << "...FAIL!";
	Sleep(500);
	GotoXY(0, HEIGHT + 5);
	cout << "        ";

	this->getPeople().isLive() = true;
}

void CGAME::loadGame(int &x)
{
	system("cls");
	system("mode 90, 15");
	string title = "Load FileSave's name: ";
	cout << title;
	string fileName;
	cin >> fileName;
	ifstream fi(fileName, ios::binary);
	if (fi)
	{
		cn.read(fi);
		fi.read((char*)&xhSize, sizeof(int));
		fi.read((char*)&xtSize, sizeof(int));
		fi.read((char*)&klSize, sizeof(int));
		fi.read((char*)&chSize, sizeof(int));
		axh.clear();
		axt.clear();
		akl.clear();
		ach.clear();
		aden.clear();
		for (int i = 0; i < xhSize; i++)
		{
			axh.push_back(CCAR());
			axh[i].read(fi);
		}
		for (int i = 0; i < xtSize; i++)
		{
			axt.push_back(CTRUCK());
			axt[i].read(fi);
		}
		for (int i = 0; i < klSize; i++)
		{
			akl.push_back(CDINOSAUR());
			akl[i].read(fi);
		}
		for (int i = 0; i < chSize; i++)
		{
			ach.push_back(CBIRD());
			ach[i].read(fi);
		}
		for (int i = 0; i < 2; i++)
		{
			aden.push_back(CLIGHT());
			aden[i].read(fi);
		}

		fi.read((char*)&IS_RUNNING, sizeof(bool));
		fi.read((char*)&level, sizeof(int));
		fi.read((char*)&index, sizeof(int));
		fi.read((char*)&velocity, sizeof(int));
		fi.read((char*)&numOfObj, sizeof(int));
		fi.read((char*)&score, sizeof(int));
		//fi.read((char*)&isSound, sizeof(bool));
	}
	fi.close();
	if (fi)
	{
		cout << "...DONE!";
		x = 1;
	}
	else
	{
		cout << "...FAIL!";
		x = 0;
	}
	Sleep(1000);
}

void CGAME::menu()
{
	system("mode 30, 15");	// Chỉnh kích thước console
	system("Title Menu");	// Đặt tiêu đề cho console
	char choose;
	do
	{
		system("cls");
		cout << "\n\n\n\t1. NEW GAME\n\n\t2. LOAD GAME\n\n\t3. SETTINGS\n\n\t4. EXIT\n\n\t-> ";	// Thực đơn
		cin.get(choose);
		if (choose == '2')
		{
			int x = 0;
			this->loadGame(x);
			if (x != 0) break;
			else
			{
				system("mode 30, 15");
			}
		}
		if (choose == '3')
		{
			system("cls");
			system("mode 90, 15");
			cout << "Set Sound (On: 1, Off: 0, Default is Off): ";
			cin >> isSound;
			cout << "Set the speed game (Default is 4): ";
			cin >> velocity;
			cout << "Set the number of obstacles at Start game (Default is 2): ";
			cin >> numOfObj;
			CGAME* cg = new CGAME(velocity, numOfObj, isSound);
			*this = *cg;
		}
		if (choose == '4')
			exit(0);
	} while (choose != '1');

	FixConsoleWindow();
	resizeConsole(665, 570);
	system("Title 1612842 Lê Thành Công");

	//Xử lí hiệu ứng Loading
	system("cls");
	GotoXY(WIDTH / 3 + 12, HEIGHT / 2 + 2);
	cout << "LOADING";
	GotoXY(WIDTH / 3, HEIGHT / 2);
	ShowCur(0);
	for (int i = 0; i < 30; i++)
	{
		cout << (char)219;
		Sleep(50);
	}
}

bool CGAME::getSound()
{
	return isSound;
}
#pragma once
#pragma comment(lib, "vJoyInterface")

#include <Windows.h>
#include "public.h"
#include "vjoyinterface.h"
#include <stdexcept>
#include <string>
#include <sstream>

class Joystick
{
private:
	int id;
	JOYSTICK_POSITION_V2 jp;
public:
	Joystick(int id);
private:
	static int convertFloatToInt(float n);
	static float convertIntToFloat(int n);
public:
	void update();
	void setX(float x);
	void setY(float y);
	void setZ(float z);
	void setRx(float rx);
	void setRy(float ry);
	void setRz(float rz);
	void setSl0(float sl0);
	void setSl1(float sl1);
	void setButton(int index,bool value);

	float getX();
	float getY();
	float getZ();
	float getRx();
	float getRy();
	float getRz();
	float getSl0();
	float getSl1();
	bool getButton(int index);
	~Joystick();
};


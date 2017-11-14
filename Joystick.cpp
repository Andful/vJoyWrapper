#include "Joystick.h"



Joystick::Joystick(int id)
{
	this->id=id;
	jp.bDevice = id;
	jp.lButtons = 0x0;
	jp.wAxisX = 0;
	jp.wAxisY = 0;
	jp.wAxisZ = 0;
	jp.wAxisXRot = 0;
	jp.wAxisYRot = 0;
	jp.wAxisZRot = 0;
	jp.wSlider = 0;

	VjdStat status = GetVJDStatus(id);

	if (status != VJD_STAT_FREE) {
		if(status == VJD_STAT_OWN) {
			std::ostringstream stringStream;
			stringStream << "vJoy device " << id << " is owned by the program but used by an other instance";
			throw std::runtime_error(stringStream.str());
		} else if (status == VJD_STAT_BUSY) {
			std::ostringstream stringStream;
			stringStream << "vJoy device " << id << " is owned by an other program";
			throw std::runtime_error(stringStream.str());
		} else if (status == VJD_STAT_MISS) {
			std::ostringstream stringStream;
			stringStream << "vJoy device " << id << " is not existing";
			throw std::runtime_error(stringStream.str());
		} else {
			std::ostringstream stringStream;
			stringStream << "vJoy device " << id << " has a general error";
			throw std::runtime_error(stringStream.str());
		}
	}

	if (!AcquireVJD(id)) {
		std::ostringstream stringStream;
		stringStream << "vJoy device " << id << ", error while acquireing the device";
		throw std::runtime_error(stringStream.str());
	}
	update();
}

void Joystick::update() {
	if (!UpdateVJD(this->id, (void*)(&jp))) {
		std::ostringstream stringStream;
		stringStream << "vJoy device " << id << ", could not update joystick";
		throw std::runtime_error(stringStream.str());
	}
}

int Joystick::convertFloatToInt(float n) {
	if(n<0 || n>1) {
		throw std::logic_error("value out of bounds");
	}
	return int(32768*n);
}

float Joystick::convertIntToFloat(int n) {
	return float(n)/32768.0f;
}

void Joystick::setX(float x) {
	jp.wAxisX = convertFloatToInt(x);
}

void Joystick::setY(float y) {
	jp.wAxisY = convertFloatToInt(y);
}

void Joystick::setZ(float z) {
	jp.wAxisZ = convertFloatToInt(z);
}

void Joystick::setRx(float rx) {
	jp.wAxisXRot = convertFloatToInt(rx);
}

void Joystick::setRy(float ry) {
	jp.wAxisYRot = convertFloatToInt(ry);
}

void Joystick::setRz(float rz) {
	jp.wAxisZRot = convertFloatToInt(rz);
}

void Joystick::setSl0(float sl0) {
	jp.wSlider = convertFloatToInt(sl0);
}

void Joystick::setSl1(float sl1) {
	jp.wDial = convertFloatToInt(sl1);
}

void Joystick::setButton(int index, bool value) {
	if (value) {
		jp.lButtons |= (1UL << index);
	} else {
		jp.lButtons &= ~(1UL << index);
	}
}

float Joystick::getX() {
	return convertIntToFloat(jp.wAxisX);
}

float Joystick::getY() {
	return convertIntToFloat(jp.wAxisY);
}

float Joystick::getZ() {
	return convertIntToFloat(jp.wAxisZ);
}

float Joystick::getRx() {
	return convertIntToFloat(jp.wAxisXRot);
}

float Joystick::getRy() {
	return convertIntToFloat(jp.wAxisYRot);
}

float Joystick::getRz() {
	return convertIntToFloat(jp.wAxisZRot);
}

float Joystick::getSl0() {
	return convertIntToFloat(jp.wSlider);
}

float Joystick::getSl1() {
	return convertIntToFloat(jp.wSlider);
}

bool Joystick::getButton(int index) {
	return bool((jp.lButtons & ( 1UL << index )) >> index);
}

Joystick::~Joystick() {
	RelinquishVJD(id);
}

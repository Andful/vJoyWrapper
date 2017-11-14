#include <stdio.h>
#include <iostream>

#include "Joystick.h"

int main(int argc,char* argv[]) {
	try {
		Joystick joystick(1);
		printf("enter to start");
		getchar();
		joystick.setButton(1,false);
		joystick.setSl1(0.5);
		joystick.update();
		printf("enter to end");
		getchar();
	} catch (std::exception& e) {
		std::cout<<e.what()<<std::endl;
		getchar();
	}
}
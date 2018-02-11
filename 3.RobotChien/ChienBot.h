// ChienBot.h

#ifndef _CHIENBOT_h
#define _CHIENBOT_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#include "Servo.h" 
#else
#include "WProgram.h"
#endif

class ChienBot
{
public:
	ChienBot();
	void Start();
	void Avance();
	void Recule();


private:
	Servo patteAvant;
	Servo patteArriere;
	int avant[8];
	int distance;
	int distMin;
	int QuelleDistance();
};

#endif


#include <NewPing.h>
#include <Servo.h>

NewPing sonar(2, 4, 200); //cr�er l'obj sonar => le trigger pin 2, l'echo pin 4, la distance en cm

#pragma once
class Chien
{
	
private: Servo patteAvant, patteArriere;		 

		 int avant[8] = { 60,100,100,100,100,60,60,60 }; // cr�� un array �avant[]�
		 int distance = 0; // initialise la distance mesur�e
		 int distMin = 20; // d�finit la distance minimale pour avancer

public:
	Chien()
	{ 
		this->patteAvant.attach(6); // lie un moteur au pin 6
		this->patteArriere.attach(8); // lie un moteur au pin 8
	}

	~Chien()
	{
	}

	//lancement du chien
	void Start() {
		distance = 0;

		while (distance == 0) {
			distance = QuelleDistance();
			Serial.print(distance);
		}

		if (distance > distMin) {  //Tant que la distance mesur�e est inf�rieure � 20cm nous avan�ons
			Avance();
		}
	}

	//fait avancer le chien
	void Avance()
	{
		for (int n = 0; n<4; n++)
		{
			this->patteAvant.write(avant[2 * n]);          // envoie au moteur une valeur pair de la liste avant[]
			this->patteArriere.write(avant[(2 * n) + 1]); // envoie au moteur une valeur impair de la liste
			delay(350);
		}
	}

	void Recule()
	{

	}

	//Interroge le sonar sur la distance de l'obstacle
	int QuelleDistance()
	{
		delay(70);
		unsigned int uS = sonar.ping();
		int cm = uS / US_ROUNDTRIP_CM; 

		return cm;
	}

};


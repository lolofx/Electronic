// 
// 
// 

#if ARDUINO < 100
#include <WProgram.h>
#else
#include <Arduino.h>
#endif

#include "ChienBot.h"
#include <NewPing.h>
#include <Servo.h>

NewPing sonar(2, 4, 200); //créer l'obj sonar => le trigger pin 2, l'echo pin 4, la distance en cm


int avant[8] = { 60,100,100,100,100,60,60,60 }; // créé un array ‘avant[]’
int distance = 0; // initialise la distance mesurée
int distMin = 20; // définit la distance minimale pour avancer

ChienBot::ChienBot()
{
	this->patteAvant.attach(6); // lie un moteur au pin 6
	this->patteArriere.attach(8); // lie un moteur au pin 8

	this->patteAvant.write(90);
	this->patteArriere.write(90);
	delay(5000);
}



//lancement du chien
void ChienBot::Start() {
	distance = 0;

	//empeche d'avoir une valeur à 0 (erreur du capteur), on recommence tant que c'est =0
	while (distance == 0) {
		distance = QuelleDistance();
		Serial.print(distance);
	}

	if (distance > distMin) {  //Tant que la distance mesurée est inférieure à 20cm nous avançons
		Avance();
	}
	else {
		this->patteAvant.write(90);
		this->patteArriere.write(90);
	}
}

//fait avancer le chien
void ChienBot::Avance()
{
	for (int n = 0; n < 4; n++)
	{
		this->patteAvant.write(avant[2 * n]);          // envoie au moteur une valeur pair de la liste avant[]
		this->patteArriere.write(avant[(2 * n) + 1]); // envoie au moteur une valeur impair de la liste
		delay(350);
	}
}

void ChienBot::Recule()
{

}


//Interroge le sonar sur la distance de l'obstacle
int ChienBot::QuelleDistance()
{
	delay(70);
	unsigned int uS = sonar.ping();
	int cm = uS / US_ROUNDTRIP_CM;

	return cm;
}




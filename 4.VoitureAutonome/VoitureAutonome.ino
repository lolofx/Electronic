/*
 Name:		VoitureAutonome.ino
 Created:	16/09/2017 14:50:05
 Author:	Loïc
*/

#include <Servo.h>
#include <NewPing.h>


int pin1Moteur1 = 12;
int pin2Moteur1 = 8;
int pinPMoteur1 = 11;
int pin1Moteur2 = 2;
int pin2Moteur2 = 4;
int pinPMoteur2 = 5;

int TRIG_PIN = 10;
int ECHO_PIN = 9;

int pinServoTete = 13;

int DIST_MAX = 200;
int i = 90;
int distActuelle = 0;
int cm;

Servo servoTete;
NewPing sonar(TRIG_PIN, ECHO_PIN, 200); // créé l'objet sonar

// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(9600); //initialise la communication série
	pinMode(pin1Moteur1, OUTPUT);
	pinMode(pin2Moteur1, OUTPUT);
	pinMode(pinPMoteur1, OUTPUT);
	pinMode(pin1Moteur2, OUTPUT);
	pinMode(pin2Moteur2, OUTPUT);
	pinMode(pinPMoteur2, OUTPUT);

	pinMode(pinServoTete, OUTPUT);

	servoTete.attach(pinServoTete);
}

// the loop function runs over and over again until power down or reset
void loop() {
	
	distActuelle = lectureDistance();

	if (distActuelle > 20) {
		avance();
	}
	if (distActuelle < 20) {
		stop();
	//	//Regarde s'il peut aller à droite
		if (RegardeADroite()) {
			//Si oui recule et tourne
			recule();
			tourneDroite();
		}
		else //Sinon, regarde s'il peut aller à gauche
			if (RegardeAGauche()) {

				//Si oui recule et tourne
				recule();
				tourneGauche();
			}
			else //sinon demi-tour
			{
				recule();
				demitour();
			}
	}
	delay(300);
}

/* Lance un moteur
moteur : quel moteur 1 ou 2
sens : marche avant (1) ou marche arriere (-1) et arret (0)
pourcentage : pourcentage de la puissance max  du moteur
*/
void dirMoteur(int moteur, int sens, int pourcentage) {
	int pin1, pin2, pinP; //pin ou envoyer le signal
	int etat1; //avance si = 1
	int  etat2; //recule si = 1
	int puissance;

	//Pin du moteur
	if (moteur == 1) {
		pin1 = pin1Moteur1;
		pin2 = pin2Moteur1;
		pinP = pinPMoteur1;
		//FIXUP : moteur 2 monté en mirroir par rapport au 1 => donc j'inverse le sens
		sens = -1 * sens;
	}
	else {
		pin1 = pin1Moteur2;
		pin2 = pin2Moteur2;
		pinP = pinPMoteur2;
		
	}
	if (sens == 1) {
		etat1 = 1;
		etat2 = 0;
	}
	else if (sens == -1) {
		etat1 = 0;
		etat2 = 1;
	}
	else {
		etat1 = 0;
		etat2 = 0;
	}
	puissance = map(pourcentage, 0, 100, 0, 255); //map permet de transformer la valeur compris entre 0 et 100 en valeur équivalente entre 0 et 255

	//On envoi le signal à travers les pins
	analogWrite(pinP, puissance);
	digitalWrite(pin1, etat1);
	digitalWrite(pin2, etat2);
}


void stop() {
	//regardeDevant();
	//Avance les 2 moteurs à 100% de la puissance
	dirMoteur(1, 0, 0);
	dirMoteur(2, 0, 0);

}
void avance() {
	regardeDevant();
	//Avance les 2 moteurs à 100% de la puissance
	dirMoteur(1, 1, 100);
	dirMoteur(2, 1, 100);
	
}

void recule() {
	regardeDevant();
	//Arrete les 2 moteurs
	dirMoteur(1, 0, 100);
	dirMoteur(2, 0, 100);
	delay(1000);
	//fait reculer les 2 moteurs
	dirMoteur(1, -1, 100);
	dirMoteur(2, -1, 50);
}

void tourneDroite() {
	regardeDevant();
	delay(1000);

	//moteur 1 recule
	dirMoteur(1, -1, 100);
	//moteur 2 ne bouge pas
	dirMoteur(2, 0, 0);
	delay(1000);
	
	//moteur 1 recule
	dirMoteur(1, -1, 100);
	//moteur 2 avance
	dirMoteur(2, 1, 50);
	delay(1000);
}

void tourneGauche() {
	regardeDevant();
	delay(1000);

	//moteur 2 recule
	dirMoteur(2, -1, 100);
	//moteur 1 ne bouge pas
	dirMoteur(1, 0, 0);
	delay(1000);

	//moteur 2 recule
	dirMoteur(2, -1, 100);
	//moteur 1 avance
	dirMoteur(1, 1, 50);
	delay(1000);
}

void demitour(){
	
	//moteur 1 recule
	dirMoteur(1, -1, 100);
	//moteur 2 avance
	dirMoteur(2, 1, 1000);
	delay(1000);
}

int lectureDistance() { // Envoi la distance mesurée par le capteur de distance
	delay(70);

	unsigned int uS = sonar.ping(); // lance la function ‘ping’ de l’objet ‘sonar’
	cm = uS / US_ROUNDTRIP_CM; // converti la distance en
	if (cm == 0) {
		lectureDistance();
	}
	else {
		Serial.println(cm);
		return cm;
	}
}

void regardeDevant() {
	int posiServo = servoTete.read();
	if (posiServo <= 90) {
		for (int i = posiServo; i <= 90; i++) {
			servoTete.write(i);
			delay(15);
		}
	}
	else if (posiServo >= 90) {
		for (int i = posiServo; i >= 90; i--) {
			servoTete.write(i);
			delay(15);
		}
	}
}
bool RegardeADroite() {	
	int posiServo = servoTete.read();
	for (int i = posiServo; i >= 0; i--) {
		servoTete.write(i);
		delay(15);
	}
	distActuelle = lectureDistance();

	return distActuelle > 20;
}

bool RegardeAGauche() {
	int posiServo = servoTete.read();
	for (int i = posiServo; i <= 180; i++) {
		servoTete.write(i);
		delay(15);
	}
	distActuelle = lectureDistance();

	return distActuelle > 20;
}

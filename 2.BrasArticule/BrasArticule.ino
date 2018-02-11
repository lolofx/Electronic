int BP1 = 8; //bouton poussoir 1
int BP2 = 7; //bouton poussoir 2
int bras = 0;
int avbras = 0;


#include<Servo.h>
Servo monservo1;
Servo monservo2;
int posiMoteur = 0;





void setup() {
	monservo1.attach(2);// definit les servo et leur sortie
	monservo2.attach(4);
	pinMode(BP1, INPUT);//definit les bouton comme des sorties.
	pinMode(BP2, INPUT);

}

void loop() {
	bras = digitalRead(BP1);
	avbras = digitalRead(BP2);

	if (bras == HIGH&&posiMoteur <= 120)
	{
		posiMoteur += 1;
		monservo1.write(posiMoteur);
		monservo2.write(posiMoteur);
		delay(15);
	}

	if (avbras == HIGH&&posiMoteur >= 10)
	{
		posiMoteur -= 1;
		monservo1.write(posiMoteur);
		monservo2.write(posiMoteur);
		delay(15);
	}
}
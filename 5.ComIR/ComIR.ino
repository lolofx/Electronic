#include <boarddefs.h>
#include <ir_Lego_PF_BitStreamEncoder.h>
#include <IRremote.h>
#include <IRremoteInt.h>

long val;
int IRpin = 10;
int LEDpin = 4;

IRrecv irrecv(IRpin);
decode_results results;

void setup(){
    Serial.begin(9600);
    irrecv.enableIRIn(); //active l'IR sur l'entrée
    pinMode(LEDpin,OUTPUT);
}


void dump(decode_results *results)
{
    int count = results->rawlen; //recup de la longueur du signal
    Serial.println("signal recu");
    Serial.print("Longueur du signal (");
    Serial.print(count,DEC);
    Serial.println(") : ");

    for(int i=0;i<count;i++){ //pour chaque resultat de la liste recupérer
        if((i%2)== 1){ //resultats impair = 0v et les resultats pair 5v
        //Resultat pairs
        Serial.println(results->rawbuf[i]*USECPERTICK,DEC); //1 tick tous les 50µs donc traduction de la valeur du signal en µs
        }else{
        //resultats impairs
        Serial.println(-(int)results->rawbuf[i]*USECPERTICK,DEC);
        }
    }

}

void loop(){
if(irrecv.decode(&results)==1){
    //val = results.value;
    //Serial.println(val,DEC);//sort sur le moniteur la valeur du bouton en DEC
    dump(&results);
    irrecv.resume();//pres pour la reception de la prochaine valeur
}
if(val== 16738455){ //bouton 0 de la telecommande
    digitalWrite(LEDpin,HIGH);
}else{
    digitalWrite(LEDpin,LOW);
}

}



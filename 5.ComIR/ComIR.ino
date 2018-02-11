#include <boarddefs.h>
#include <ir_Lego_PF_BitStreamEncoder.h>
#include <IRremote.h>
#include <IRremoteInt.h>

long val;
int IRpin = 10;
//int LEDpin = 4;

IRrecv irrecv(IRpin);
decode_results results;

void setup(){
    Serial.begin(9600);
    irrecv.enableIRIn(); //active l'IR sur l'entrée
    //pinMode(LEDpin,OUTPUT);
}


void dump(decode_results *results)
{
    int count = results->rawlen; //recup de la longueur du signal (d'apres me monitor, 68)
    Serial.println("signal recu");
    Serial.print("Longueur du signal (");
    Serial.print(count,DEC); //affiche les valeurs sur le monitor arduino
    Serial.println(") : ");

    for(int i=0;i<count;i++){ //pour chaque resultat de la liste recupérer => on a la frequence du signal
        if((i%2)== 1){ //resultats impair = 0v et les resultats pair 5v
        //Resultat pairs
        Serial.println(results->rawbuf[i]*USECPERTICK,DEC); //1 tick tous les 50µs donc traduction de la valeur du signal en µs (1/T pour avoir la frequence)
        //Ici recup des valeurs positives donc 5V => 1 en binaire
        }else{
        //resultats impairs
        Serial.println(-(int)results->rawbuf[i]*USECPERTICK,DEC);
        //Ici recup des valeurs negative donc 0V => 0 en binaire
        }
    }

}

void loop(){
if(irrecv.decode(&results)==1){//reception d'un signal
    //val = results.value;
    //Serial.println(val,DEC);//sort sur le moniteur la valeur du bouton en DEC
    dump(&results); //Analyse du signal
    irrecv.resume();//pres pour la reception de la prochaine valeur
}
// if(val== 16738455){ //bouton 0 de la telecommande
//     digitalWrite(LEDpin,HIGH);
// }else{
//     digitalWrite(LEDpin,LOW);
// }

}



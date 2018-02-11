//Bravo à LEPEL3577f7 pour cette innovation !!

int speakerPin = 6; // buzzer
int inputPin = 2; // capteur de mouvement
int ledPin = 5; // LED
int pirState = LOW;           
int val = 0;  

// Frequences des notes
#define cL 129
#define cLS 139
#define dL 146
#define dLS 156
#define eL 163
#define fL 173
#define fLS 185
#define gL 194
#define gLS 207
#define aL 219
#define aLS 228
#define bL 232

#define c 261
#define cS 277
#define d 294
#define dS 311
#define e 329
#define f 349
#define fS 370
#define g 391
#define gS 415
#define a 440
#define aS 455
#define b 466

#define cH 523
#define cHS 554
#define dH 587
#define dHS 622
#define eH 659
#define fH 698
#define fHS 740
#define gH 784
#define gHS 830
#define aH 880
#define aHS 910
#define bH 933

void setup()
{
  pinMode(ledPin, OUTPUT);
  pinMode(speakerPin, OUTPUT);
}

void beep (int speakerPin, int freqHz, long timeMs)
{
  digitalWrite(ledPin, HIGH);
  
  double timeDelay = (double)(1000000/freqHz);
  double timeLoop = (double)((timeMs*1000)/(timeDelay*2));
  
  for(int i = 0; i < timeLoop; i++)
  {
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(timeDelay);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(timeDelay);
  }
  
  digitalWrite(ledPin, LOW);
  delay(20);
}

void playTone()
{
  beep(speakerPin, a, 500); 
  beep(speakerPin, a, 500);
  beep(speakerPin, a, 500);
  beep(speakerPin, f, 350);
  beep(speakerPin, cH, 150);
  
  beep(speakerPin, a, 500);
  beep(speakerPin, f, 350);
  beep(speakerPin, cH, 150);
  beep(speakerPin, a, 1000);
  beep(speakerPin, eH, 500);
  
  beep(speakerPin, eH, 500);
  beep(speakerPin, eH, 500);
  beep(speakerPin, fH, 350);
  beep(speakerPin, cH, 150);
  beep(speakerPin, gS, 500);
  
  beep(speakerPin, f, 350);
  beep(speakerPin, cH, 150);
  beep(speakerPin, a, 1000);
  beep(speakerPin, aH, 500);
  beep(speakerPin, a, 350);
  
  beep(speakerPin, a, 150);
  beep(speakerPin, aH, 500);
  beep(speakerPin, gHS, 250);
  beep(speakerPin, gH, 250);
  beep(speakerPin, fHS, 125);
  
  beep(speakerPin, fH, 125);
  beep(speakerPin, fHS, 250);
  
  delay(250);
  
  beep(speakerPin, aS, 250);
  beep(speakerPin, dHS, 500);
  beep(speakerPin, dH, 250);
  beep(speakerPin, cHS, 250);
  beep(speakerPin, cH, 125);
  
  beep(speakerPin, b, 125);
  beep(speakerPin, cH, 250);
  
  delay(250);
  
  beep(speakerPin, f, 125);
  beep(speakerPin, gS, 500);
  beep(speakerPin, f, 375);
  beep(speakerPin, a, 125);
  beep(speakerPin, cH, 500);
  
  beep(speakerPin, a, 375);
  beep(speakerPin, cH, 125);
  beep(speakerPin, eH, 1000);
  beep(speakerPin, aH, 500);
  beep(speakerPin, a, 350);
  
  beep(speakerPin, a, 150);
  beep(speakerPin, aH, 500);
  beep(speakerPin, gHS, 250);
  beep(speakerPin, gH, 250);
  beep(speakerPin, fHS, 125);
  
  beep(speakerPin, fH, 125);
  beep(speakerPin, fHS, 250);
  
  delay(250);
  
  beep(speakerPin, aS, 250);
  beep(speakerPin, dHS, 500);
  beep(speakerPin, dH, 250);
  beep(speakerPin, cHS, 250);
  beep(speakerPin, cH, 125);
  
  beep(speakerPin, b, 125);
  beep(speakerPin, cH, 250);
  
  delay(250);
  
  beep(speakerPin, f, 250);
  beep(speakerPin, gS, 500);
  beep(speakerPin, f, 375);
  beep(speakerPin, cH, 125);
  beep(speakerPin, a, 500);
  
  beep(speakerPin, f, 375);
  beep(speakerPin, c, 125);
  beep(speakerPin, a, 1000);
}

void loop()
{
  val = digitalRead(inputPin); 

  if (val == HIGH) {
    digitalWrite(ledPin, HIGH);  
    playTone();
    delay(150);
    } 
  
  else {
      digitalWrite(ledPin, LOW);
      delay(300);    
   }
}

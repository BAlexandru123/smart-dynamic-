
const int Pozitii_R =  9  ; 
const int Pozitii_L =  10  ; 
const int Pozitii_B =  11  ; 
const int Semnal_R  =  5  ; 
const int Semnal_L  =  6  ;  
const int Avarii    =  4   ;  
const int sensorPin =  1  ;
int dutyCycle = 50;
#define SL  3
#define SR  2
//intreruperile doar la pinul 2 si 3 
int cont  = 0 ;
int cont1 = 0;
int cont2 =0;
int lightOn   =0 ;
int contor    =0 ;
int lightOnThreshold =500;
int lightOnThreshold1= 550;
int lunga = 350;
int lu=0;

void setup() {
  // put your setup code here, to run once:
  pinMode(sensorPin, INPUT);
  pinMode(SL,        INPUT);
  pinMode(SR,        INPUT);
  pinMode(Avarii,    INPUT);
  pinMode(Pozitii_R, OUTPUT);
  pinMode(Pozitii_L, OUTPUT);
  pinMode(Pozitii_B, OUTPUT);
  pinMode(Semnal_R,  OUTPUT);  
  pinMode(Semnal_L,  OUTPUT);
  attachInterrupt(0,ISR_SL,INPUT_PULLUP);
  attachInterrupt(1,ISR_SR,INPUT_PULLUP);
 Serial.begin(9600); 
}

void loop() {
    digitalWrite(Semnal_L, LOW);
    digitalWrite(Semnal_R, LOW);
Serial.println("LOOP");
    senzor();
      
 int AvariiState = digitalRead(Avarii);
 if(AvariiState==1) 
    avarii();
 else{
    digitalWrite(Semnal_L,  LOW);
    digitalWrite(Semnal_R,  LOW);
 }
}

                                                            //Avarii
void avarii()
{  senzor();
  digitalWrite(Semnal_L,  HIGH);
  digitalWrite(Semnal_R,  HIGH);
  delay(700);
  digitalWrite(Semnal_L,  LOW);
  digitalWrite(Semnal_R,  LOW);
  senzor();
  delay(700);
  cont=1;

}

                                                        //citire lumina exterior
void senzor()
{
  int lightValue = analogRead(sensorPin);
  if( lightValue<lunga)
  {
  lu=1;
      digitalWrite(Pozitii_L, HIGH);
      digitalWrite(Pozitii_R, HIGH);
      digitalWrite(Pozitii_B, HIGH);
      lightOn = 0;
  }
  
  else lu=0;
  
  if ( lightValue < lightOnThreshold && lightOn == 0 && lightValue > lunga+50 )
  {
       analogWrite(Pozitii_L, dutyCycle);
       analogWrite(Pozitii_R, dutyCycle);
       analogWrite(Pozitii_B, dutyCycle);
       lightOn = 1;
       lu=0;
  }
  // Lumina exterioara e prea puternica SI sursa noastra de lumina e deja aprinsa
  else if (lightValue > lightOnThreshold1 && lightOn == 1 && lu==0 )
  {
      digitalWrite(Pozitii_L, LOW);
      digitalWrite(Pozitii_R, LOW);
      digitalWrite(Pozitii_B, LOW);
      lightOn = 0;
      lu=0;
  }
   else if (lightOn == 1 && cont ==1  )
  {
       analogWrite(Pozitii_L, dutyCycle);
       analogWrite(Pozitii_R, dutyCycle);
       analogWrite(Pozitii_B, dutyCycle);
      lightOn = 1;
      cont=0;
      lu=0;
  }
}

void senzor_R_B()
{
   int lightValue = analogRead(sensorPin);
   if( lightValue<lunga)
  {
  lu=1;
      digitalWrite(Pozitii_L, HIGH);
      digitalWrite(Pozitii_R, HIGH);
      digitalWrite(Pozitii_B, HIGH);
      lightOn = 0;
  }
  
  else lu=0;
  if (lightValue < lightOnThreshold && lightOn == 0 && lightValue > lunga+50 )
  {    digitalWrite(Pozitii_L, LOW);
       analogWrite(Pozitii_R, dutyCycle);
       analogWrite(Pozitii_B, dutyCycle);
       lightOn = 1;
  }
  // Lumina exterioara e prea puternica SI sursa noastra de lumina e deja aprinsa
  else if (lightValue > lightOnThreshold1 && lightOn == 1)
  {   digitalWrite(Pozitii_L, LOW);
      digitalWrite(Pozitii_R, LOW);
      digitalWrite(Pozitii_B, LOW);
      lightOn = 0;
  }
   else if (lightOn == 1 && cont ==1  )
  {    digitalWrite(Pozitii_L, LOW);
       analogWrite(Pozitii_R, dutyCycle);
       analogWrite(Pozitii_B, dutyCycle);
      lightOn = 1;
  }
}
void senzor_L_B()
{
  int lightValue = analogRead(sensorPin);
  if( lightValue<lunga)
  {
  lu=1;
      digitalWrite(Pozitii_L, HIGH);
      digitalWrite(Pozitii_R, HIGH);
      digitalWrite(Pozitii_B, HIGH);
      lightOn = 0;
  }
  
  else lu=0;
  if (lightValue < lightOnThreshold && lightOn == 0 && lightValue > lunga+50 )
  {    digitalWrite(Pozitii_R, LOW);
       analogWrite(Pozitii_L, dutyCycle);
       analogWrite(Pozitii_B, dutyCycle);
       lightOn = 1;
  }
  // Lumina exterioara e prea puternica SI sursa noastra de lumina e deja aprinsa
  else if (lightValue > lightOnThreshold1 && lightOn == 1)
  {   digitalWrite(Pozitii_R, LOW);
      digitalWrite(Pozitii_L, LOW);
      digitalWrite(Pozitii_B, LOW);
      lightOn = 0;
  }
   else if (lightOn == 1 && cont ==1  )
  {    digitalWrite(Pozitii_R, LOW);
       analogWrite(Pozitii_L, dutyCycle);
       analogWrite(Pozitii_B, dutyCycle);
      lightOn = 1;
  }
}
  
                                              // INTRERUPERI !!
  
void ISR_SL()
{ //semnal stanga
  digitalWrite(Semnal_L,  HIGH);
  senzor_R_B();
  delay(100000);
   senzor_R_B();
  digitalWrite(Semnal_L, LOW);
  delay(100000) ;
   senzor_R_B();
  cont=1;
  
}
void ISR_SR()
{//semnal dreapta
  Serial.println("semnal");
  digitalWrite(Semnal_R,  HIGH);
  senzor_L_B();
  delay(100000);
  digitalWrite(Semnal_R, LOW);
  senzor_L_B();
  delay(100000) ;
  cont=1;
  senzor_L_B();
}





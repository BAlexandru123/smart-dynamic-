
#include "BluetoothSerial.h"
#include "esp32-hal-ledc.h"
const char forward = 'F';       int Forward = 20;
const char reverse = 'B';       int Reverse = 18;
const char left = 'L';          int Left    = 17;
const char right = 'R';         int Right   = 16;
const char forward_left = 'W';  
const char reverse_left = 'A';  
const char forward_right = 'S'; 
const char reverse_right = 'D'; 
                                 int Brake    = 15;
const char Semnal_L = 'Q';       int Semnal__L= 14;
const char Semnal_R = 'E';       int Semnal__R= 13;
const char Avarii   = 'J';       int Avarii_  = 12;
                                 int echoPin  = 21;
                                 int trigPin  = 22;
                                 
int cont=0,cont1=0,cont2=0;
int duration = 0 , distance = 0;
 

BluetoothSerial SerialBT; 
void setup() {

  Serial.begin(9600); 
  
  pinMode(Forward,  OUTPUT);
  pinMode(Reverse,  OUTPUT);
  pinMode(Left,  OUTPUT);
  pinMode(Right,  OUTPUT);
  pinMode(Brake,  OUTPUT);
  pinMode(Semnal__L,  OUTPUT);
  pinMode(Semnal__R,  OUTPUT);
  pinMode(Avarii_,  OUTPUT);
  
  SerialBT.begin("ESP32_Alex");
  Serial.print("Bluetooth Device is Ready to Pair");
  
}

void loop() {
//~~~~~~~~~~~~~I N I T    B L U E T O O T H~~~~~~~~~~~~ 
int receivedChar = (char)SerialBT.read();

  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
  if(SerialBT.available()){
    steering_control(receivedChar);
      
  }
 
   //~~~~~~U L T R A   S O N I C~~~~~~~~~~

   }

  //~~~~~~~~~~ S T E E R I N G    C O N T R O L ~~~~~~~~~~~~~

void steering_control(char control) {                             // Steering_control ~ ! ! !
  if(control == 'F' )
  {
    
      Serial.print("forward");  
     digitalWrite(Reverse ,LOW ); 
     digitalWrite(Left  ,LOW );
     digitalWrite(Right ,LOW );
     digitalWrite(Forward ,HIGH );
     
  }
   else if(control == 'B' )
  {
      Serial.print("Reverse");  
     digitalWrite(Reverse ,HIGH); 
     digitalWrite(Forward ,LOW);
     digitalWrite(Left  ,LOW );
     digitalWrite(Right ,LOW );  
  }
     else if(control == 'L' )
  {
      Serial.print("Left");  
      digitalWrite(Left  ,HIGH );
     digitalWrite(Reverse ,LOW); 
     digitalWrite(Forward ,LOW);
     digitalWrite(Right ,LOW );  
  }
     else if(control == 'R' )
  {
      Serial.print("Right"); 
     digitalWrite(Right ,HIGH );  
     digitalWrite(Reverse ,LOW); 
     digitalWrite(Forward ,LOW);
     digitalWrite(Left  ,LOW );
  }
      else if(control == 'W' )
  {
      Serial.print("Forward_Left"); 
     digitalWrite(Right ,LOW );  
     digitalWrite(Reverse ,LOW); 
     digitalWrite(Forward ,HIGH);
     digitalWrite(Left  ,HIGH );
  }
      else if(control == 'S' )
  {
      Serial.print("Forward_Right"); 
     digitalWrite(Right ,HIGH );  
     digitalWrite(Reverse ,LOW); 
     digitalWrite(Forward ,HIGH);
     digitalWrite(Left  ,LOW );
  }
      else if(control == 'A' )
  {
      Serial.print("Reverse_Left"); 
     digitalWrite(Right ,LOW );  
     digitalWrite(Reverse ,HIGH); 
     digitalWrite(Forward ,LOW);
     digitalWrite(Left  ,HIGH );
  }
      else if(control == 'D' )
  {
      Serial.print("Reverse_Right"); 
     digitalWrite(Right ,HIGH );  
     digitalWrite(Reverse ,HIGH); 
     digitalWrite(Forward ,LOW);
     digitalWrite(Left  ,LOW );
  }
      else 
      {
        digitalWrite(Reverse ,LOW ); 
        digitalWrite(Left  ,LOW );
        digitalWrite(Right ,LOW );
        digitalWrite(Forward ,LOW );
      }
 if(control == 'Q')
 {
    cont++;
      if(cont==1)
    {
    digitalWrite(Semnal__L,HIGH );
     digitalWrite(Semnal__R,LOW);
    }
    else
    {
    digitalWrite(Semnal__L,LOW );
    digitalWrite(Semnal__R,LOW);
    cont=0;
    }
   
    
}

 if(control == 'E')
 {
    cont++;
      if(cont==1)
      {      
        digitalWrite(Semnal__R,HIGH );
        digitalWrite(Semnal__L,LOW );
      }
      else 
      {
        digitalWrite(Semnal__R,LOW);
        digitalWrite(Semnal__L,LOW );
         cont=0;
      }  
 }
 if(control =='J')
 {
    cont2++;
    if(cont2==1)
    {
       digitalWrite(Avarii_,HIGH );
    }
   else
   {
    digitalWrite(Avarii_,LOW);
    cont2=0;
   }
 }
  
}


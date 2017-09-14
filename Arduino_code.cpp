#include <Servo.h>


 Servo servo;
void setup()
{
 
 int servoPosition = 90;
  servo.attach(3);         // attaches the servo on pin 8to the servo object
  servo.write(servoPosition);   // set the servo at the mid position
  Serial.begin(115200);

  pinMode(7,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(4,OUTPUT);
  digitalWrite(7,LOW);
  digitalWrite(6,LOW);
  digitalWrite(5,LOW);
  digitalWrite(4,LOW);
}

void loop()
{   int servoPosition = 90;
   int output;
   char ch;
  while(1)
{delay(100);
 if (Serial.available() > 0)
 {    

     char k=Serial.read();

     switch(k)
       {
         case'0':                      //stop
         digitalWrite(7,LOW);
         digitalWrite(6,LOW);
         digitalWrite(5,LOW);
         digitalWrite(4,LOW);
         break;
 
         case'8':               //forward
         Serial.println(k);
                                     // delay(500);
          if(Serial.available() > 0)
             {         
                   ch=  Serial.read();
                   Serial.println(ch);
             }
           else
              { 
                   ch=2;
              }
                  
                  
           output=28.33*(ch-48);
           analogWrite(7,output);
           analogWrite(6,LOW);
           analogWrite(5,LOW);
           analogWrite(4,output);
    
         break;
 
 
         case'5':                   //backward
                                    // delay(1000);
          if (Serial.available() > 0)
          ch=  Serial.read();
        
         output=28.33*(ch-48);
         analogWrite(7,LOW);
         analogWrite(6,output);
         analogWrite(5,output);
         analogWrite(4,LOW);
         break;
 
 
         case'4': //left
        //delay(1000);
          if (Serial.available() > 0)
        ch=  Serial.read();
     
         output=28.33*(ch-48);
         analogWrite(7,output);
         analogWrite(6,LOW);
         analogWrite(5,output);
         analogWrite(4,LOW);
         break;
 
        case'6'://right
       //delay(1000);
          if (Serial.available() > 0)
        ch=  Serial.read();
      
         output=28.33*(ch-48);
        analogWrite(7,LOW);
        analogWrite(6,output);
        analogWrite(5,LOW);
        analogWrite(4,output);
        break;
 
 
        case'9':
       // delay(1000);
          if (Serial.available() > 0)
         ch=  Serial.read();
    
         output=28.33*(ch-48);
        analogWrite(7,LOW);
        analogWrite(6,output);
        analogWrite(5,LOW);
       analogWrite(4,output);
        break;


        case'3':                   //servo up
        
         
          //if(k=='0'|| k=='4'|| k=='6')
         // break;
         
        
      if(servoPosition>=175)
         break;

          servo.write(servoPosition+=10);
     
         
         // delay(30);
         // if (servoPosition > 180)
          //   servoPosition = 180
              
         
                  
        break;


       
        case'7':                     //servo down 
          
         // if(k=='0'|| k=='4'|| k=='6')
          //break; 
 if(servoPosition<=5)
         break; 
         
        servo.write(servoPosition-=10);
       // delay(30);
        //if (servoPosition<0)
          //   servoPosition =0;    
       
                  
        break;

      }
 }
}

}

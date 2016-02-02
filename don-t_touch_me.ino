int servoPin = A5;
Servo myServo;
int servoPos = 0;
int lightPin1 = A0;
int lightPin2 = A1;
String trigger = "50";
int switchPin = D0;



void setup() {

 // attaches the servo on the A7 pin to the servo object
 myServo.attach( A5 );

  //Register our Particle to control the servo
  Particle.function("servo", servoControl);

 // Keep a cloud variable for the current position
 Particle.variable(  "servoPosition" , servoPos);
 Serial.begin(9600);  //Begin serial communcation
     pinMode( A1, OUTPUT );
     pinMode(lightPin1, INPUT);
     pinMode(lightPin2, INPUT);
 pinMode( switchPin , INPUT_PULLUP);
}

void loop() {
  //Write the value of the photoresistor to the serial monitor.
      //analogWrite(A1, analogRead(lightPin)/4);  //send the value to the ledPin. Depending on value of resistor
              //Serial.println(A1);
              int buttonState = digitalRead( switchPin );
    int a1 =  analogRead(lightPin1)/4;
    int a2 =  analogRead(lightPin2)/4;
    Serial.println((a1-a2));                                   //you have  to divide the value. for example,
if( buttonState == HIGH )
{
    if(a1>=a2)
    {
      if((a1-a2)<=50)
      {
        servoControl( "90" );
        }                                       //with a 10k resistor divide the value by 2, for 100k resistor divide by 4.
     else if((a1-a2)<=100)
     {
       servoControl( "110" );
     }else if((a1-a2)<=150)
     {
       servoControl( "130");
     }else if((a1-a2)<=200){
       servoControl( "150");
     }else if((a1-a2)<=250){
        servoControl( "170");
     }else if((a1-a2)<=300){
       servoControl( "180");
     }
     } else if(a1<a2)
     {
       if((a2-a1)<=50)
       {
         servoControl( "90" );
         }                                       //with a 10k resistor divide the value by 2, for 100k resistor divide by 4.
      else if((a2-a1)<=100)
      {
        servoControl( "70" );
      }else if((a2-a1)<=150)
      {
        servoControl( "50");
      }else if((a2-a1)<=200){
        servoControl( "30");
      }else if((a2-a1)<=250){
         servoControl( "10");
      }else if((a2-a1)<=300){
        servoControl( "5");
      }

     }
   }
}


int servoControl(String trigger)
{    // Convert
  int newPos = trigger.toInt();
  // Make sure it is in the right range
  // And set the position
  servoPos = constrain( newPos, 0 , 180);

  // Set the servo
  myServo.write( servoPos );

  // done

  return 1;
}

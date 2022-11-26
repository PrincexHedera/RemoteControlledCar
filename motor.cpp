#include <Adafruit_MotorShield.h>
//Arduino Bluetooth Controlled Car//
//// Before uploading the code you have to install the necessary library//
//AFMotor Library https://learn.adafruit.com/adafruit-motor-shield/library-install //

//initial motors pin
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *motor1 = AFMS.getMotor(1);
Adafruit_DCMotor *motor2 = AFMS.getMotor(2);
/*AF_DCMotor motor1(1); 
AF_DCMotor motor2(2); 
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);*/

char previouscommand;
char command; 
int  speed  = 0;

void setup() 
{       
  Serial.begin(9600);  //Set the baud rate to your Bluetooth module.
}

void loop(){
  if(Serial.available() > 0)
      keyPressed();
  else
      deccelerate();
}


void keyPressed()
{
    //previouscomamnd  = command;
    command = Serial.read(); 
    Stop(); //initialize with motors stoped
    //Change pin mode only if new command is different from previous.   
    //Serial.println(command);
    switch(command){
    case 'A':
      accelerate();
      break;
    case 'F':  
      forward();
      break;
    case 'B':  
       back();
      break;
    case 'L':  
      left();
      break;
    case 'R':
      right();
      break;
    default:
      deccelerate();
      break;
    }
}


void accelerate()
{
   if(speed < 240) speed = speed + 10;
   
   speed = speed + 10;
   motor1->setSpeed(speed); 
   motor1->run(FORWARD);


}

void deccelerate()
{
  if(speed > 10) speed = speed - 10;
  else speed = 0;

  motor1->setSpeed(speed);
  motor1->run(FORWARD);
}

void forward()
{
  motor1->setSpeed(255); //Define maximum velocity
   //rotate the motor clockwise
  motor2->setSpeed(255); //Define maximum velocity
  motor2->run(FORWARD); //rotate the motor clockwise
}

void back()
{
  motor1->setSpeed(255); //Define maximum velocity
  motor1->run(BACKWARD); //rotate the motor anti-clockwise
  motor2->setSpeed(255); //Define maximum velocity
  motor2->run(BACKWARD); //rotate the motor anti-clockwise
}


void left()
{
  motor2->setSpeed(50); //Define maximum velocity
  motor2->run(BACKWARD); //rotate the motor anti-clockwise
  motor2->run(RELEASE);   
  delay(5000);
  motor2->setSpeed(50);
  motor2->run(BACKWARD);
}


void right()
{
  motor2->setSpeed(50); //Define maximum velocity
  motor2->run(FORWARD); //rotate the motor anti-clockwise
  motor2->run(RELEASE);  
  delay(5000);
  motor2->setSpeed(50);
  motor2->run(BACKWARD);
} 

void Stop()
{
  motor1->setSpeed(0); //Define minimum velocity
  motor1->run(RELEASE); //stop the motor when release the button
  motor2->setSpeed(0); //Define minimum velocity
  motor2->run(RELEASE); //rotate the motor clockwise
}

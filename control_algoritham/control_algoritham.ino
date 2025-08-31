#include<Servo.h>
Servo Base_servo;
Servo Sholder_servo;
Servo Elbow_servo;
Servo Gripper_servo;
#define Base_servopin 14
#define Sholder_servopin 12
#define Elbow_servopin 13
#define Gripper_servopin 1
int Base_Angle,Sholder_Angle,Elbow_Angle,Gripper_Angle;
void setup() {
Base_servo.attach(Base_servopin);
Sholder_servo.attach(Sholder_servopin);
Elbow_servo.attach(Elbow_servopin);
Gripper_servo.attach(Gripper_servopin);
Serial.begin(9600);
Home_position(0,108,127,0);
}

void loop() {
if(Serial.available()>0){
String input=Serial.readStringUntil('\n');
int commaindex=input.indexOf(',');
if(commaindex>0){
  int x=input.substring(0,commaindex).toInt();
  int y=input.substring(commaindex+1).toInt();
  int z=input.substring(commaindex+2).toInt();
  Inverse_kin(x,y,0);
}
}
Serial.print("Base Angle:");
Serial.print(Base_Angle);
Serial.print(" Sholder Angle:");
Serial.print(Sholder_Angle);
Serial.print(" Elbow Angle:");
Serial.println(Elbow_Angle);
delay(250);
}

void  Home_position(int home_base,int home_sholder,int home_elbow,int home_gripper){
  Base_servo.write(home_base);
  Sholder_servo.write(home_sholder);
  Elbow_servo.write(home_elbow);
  Gripper_servo.write(home_gripper);
  
}
void Inverse_kin(int x,int y,int z){
  float b=asin(y/sqrt(x*x+y*y))*180.0/PI;
  float l=sqrt(x*x+y*y);
  float h=sqrt(z*z+l*l);
  float phi=atan(z/l)*180.0/PI;
  float theta=acos(h/2*75)*180.0/PI;
  int  a1=phi+theta;
  int  a2=phi-theta;
  Base_Angle=constrain(b,0,180);
  Sholder_Angle=constrain(a1,0,180);
  Elbow_Angle=constrain(a2,0,180);
  Base_servo.write(Base_Angle);
  Sholder_servo.write(Sholder_Angle);
  Elbow_servo.write(Elbow_Angle);
  
}

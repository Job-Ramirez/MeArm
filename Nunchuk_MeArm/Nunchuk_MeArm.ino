/*
to do list:
set and test limits
add led code to give some feedback about the 
*/

#include <meArm.h>
#include <Servo.h>
#include <Wiichuck.h>
#include <Wire.h>



// servo pinouts   
int basePin = 11;
int shoulderPin = 6;
int elbowPin = 10;
int gripperPin = 3;

// I forgot what's this
float Gripangle = 10;

Wiichuck wii;  // instances for the controler and the arm.
meArm arm;

void setup() {
  arm.begin(basePin, shoulderPin, elbowPin, gripperPin);
  wii.init();                    // initialize the control and the arm pin configuration
  wii.calibrate(); 
  arm.goDirectlyTo(100,100,100); // initialize a position so that meArm library has values for (x,y,z)
  Serial.begin(9600);
}

void loop() {
if(wii.poll()){
  
    if (wii.buttonC() && wii.buttonZ()){
      
      while (wii.buttonC() && wii.buttonZ()){
           wii.poll();
             if ((wii.joyX() <100 || wii.joyX() > 150)|| (wii.joyY() <100 || wii.joyY() > 150)){
             Z_move(wii.joyY());
            
       }
   Serial.println("Z function used");
    }
    }
    else{
    if (wii.buttonC() || wii.buttonZ()){
      Dgripper(wii.buttonC(), wii.buttonZ());

        
    }
    if ((wii.joyX() <100 || wii.joyX() > 150)|| (wii.joyY() <100 || wii.joyY() > 150)){
        RT_move(wii.joyX(),wii.joyY());  
        }
   /* else if ((wii.joyX() <120 || wii.joyX() > 130)|| (wii.joyY() <120 || wii.joyY() > 130)){
    RT_move(wii.joyX(),wii.joyY());
    
   */ }
   }
}
void RT_move(int x, int y) {
  float theta;
  float radio;
if (arm.getTheta()< 1.35 && arm.getTheta() > -1.50){
  theta = map(float(x),30,220,-10,10);
}
else {
  if (arm.getTheta()>1.35){
  theta = map(float(x),30,220,-10,0);
  }
  else {
   theta = map(float(x),30,220,0,10); 
  }
  }
if (arm.getR()<2000 && arm.getR()>-10){  //prevent forcing the servos 
  radio = map(float(y),30,220,-10,10);   // convert this into a function(lower_limit,upper_limit,mspping_var[30,220,-10,10])
} 
else{
  if (arm.getR()>2000){
  radio = map(float(y),30,220,-10,0);
  }
  else{
  radio = map(float(y),30,220,0,10); 
  }
}
  
arm.goDirectlyToCylinder( arm.getTheta()+ theta*pi/180, arm.getR()+radio, arm.getZ());
Serial.println(arm.getTheta()+ theta*pi/180);
Serial.println(arm.getR()+radio);
}


void Z_move(int z){
  
 float high;
 if (arm.getZ()<200 && arm.getZ()>-10){
 high = map(float(z),30,220,-10,10);
} 
else{
  if (arm.getR()>200){
  high = map(float(z),30,220,-10,0);
  }
  else{
  high = map(float(z),30,220,0,10); 
  }
}

arm.goDirectlyToCylinder( arm.getTheta(), arm.getR(), arm.getZ()+ high);
Serial.println(arm.getZ()+high);
}

void Dgripper(bool c, bool z){
 if (c == HIGH){
     if(Gripangle < 50){
        Gripangle=Gripangle + 10;
     }
 }
 else {
     if(Gripangle > -40){
        Gripangle=Gripangle - 10;
         }
 }
      arm.Garra((Gripangle*pi/180));
  //Serial.println(Gripangle);
  //Serial.println(Gripangle*pi/180);
 }
//convert this into a function(lower_limit,upper_limit,mspping_var[30,220,-10,10])
//void servolimit(lower_limit,upper_limit,mspping_var[30,220,-10,10])

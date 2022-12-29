#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define SERVOMIN  150 
#define SERVOMAX  600
#define step 5

int getCurAngle(int);



// call the PWMServoDriver class
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
void setup() {
  
  pwm.begin();

}

void loop() {
  

}

// Get Current servo angle
int getCurAngle(int channel)
{
  return map(pwm.getPWM(channel),0,180,SERVOMIN,SERVOMAX);
}
//


void servo(uint8_t s1,uint8_t s2, uint8_t s3)
{
  // Get the current angles of the 3 servos
  uint8_t CurAngle1 = getCurAngle(1);
  uint8_t CurAngle2 = getCurAngle(2);
  uint8_t CurAngle3 = getCurAngle(3);  
  // claculate the Remainder for the first loop then replace it with the angle step
  uint8_t servo1step = (s1-CurAngle1)%step;
  uint8_t servo2step = (s2-CurAngle2)%step;
  uint8_t servo3step = (s3-CurAngle3)%step;
  // Get the Max iteration to avoid using While
  uint8_t iteration = max(abs((s1-CurAngle1)/step),max(abs((s2-CurAngle2)/step), abs((s3-CurAngle3)/step)));
  if (iteration  ==  0) iteration = 1;


  for(int i = 0; i < iteration; i++){
    if(CurAngle1!= s1) {
      pwm.setPWM(1, 0, map(CurAngle1 + servo1step ,0,180,SERVOMIN,SERVOMAX));
      CurAngle1 += servo1step;
      // replace the Remainder with the step angle and take the direction in the the claculation
      servo1step = step * (s1-CurAngle1) / abs(s1-CurAngle1);
    }
    
    if(CurAngle2!= s2) {
      pwm.setPWM(2, 0, map(CurAngle2 + servo2step ,0,180,SERVOMIN,SERVOMAX));
      CurAngle2 += servo2step;
      servo2step = step * (s2-CurAngle2) / abs(s2-CurAngle2);
    }

    if(CurAngle3!= s3) {
      pwm.setPWM(3, 0, map(CurAngle3 + servo3step ,0,180,SERVOMIN,SERVOMAX));
      CurAngle3 += servo3step;
      servo3step = step * (s3-CurAngle3) / abs(s3-CurAngle3);
    }
    delay(2);    
  }
}

#define Right_Motor_Forward 18 // Correct motor Pin
#define Right_Motor_Reverse 8 // Correct motor Pin
#define Left_Motor_Forward 6 // Correct motor Pin
#define Left_Motor_Reverse 5 // Correct motor Pin


void setup() {
  Serial.begin(115200); //set your serial monitor to this baud
  initMotors();

  delay(1000);

  accelerateForward(4000);

  delay(500);
  turnLeft(90);
  delay(500);

  accelerateForward(4000);

}

void accelerateForward(){
  analogWrite(Left_Motor_Reverse, 0);
  analogWrite(Right_Motor_Reverse, 0);
  for (int  i = 0; i<255; i=i+4){
    analogWrite(Right_Motor_Forward,i);
    analogWrite(Left_Motor_Forward,i);
    delay(10);
  }
}

void accelerateForward(int duration){
  analogWrite(Left_Motor_Reverse, 0);
  analogWrite(Right_Motor_Reverse, 0);

  for (int  i = 0; i<255; i=i+4){
    analogWrite(Right_Motor_Forward,i);
    analogWrite(Left_Motor_Forward,i);
    delay(10);
  }

  delay(duration);

  for (int  i = 255; i>=0; i=i-4){
    analogWrite(Right_Motor_Forward,i);
    analogWrite(Left_Motor_Forward,i);
    delay(5);
  }
}
void accelerateBackward(){
  analogWrite(Left_Motor_Forward, 0);
  analogWrite(Right_Motor_Forward, 0);

  for (int  i = 0; i<255; i=i+4){
    analogWrite(Right_Motor_Reverse,i);
    analogWrite(Left_Motor_Reverse,i);
    delay(10);
  }
}

void accelerateBackward(int duration){
  analogWrite(Left_Motor_Forward, 0);
  analogWrite(Right_Motor_Forward, 0);

  for (int  i = 0; i<255; i=i+4){
    analogWrite(Right_Motor_Reverse,i);
    analogWrite(Left_Motor_Reverse,i);
    delay(10);
  }

  delay(duration);

  for (int  i = 255; i>=0; i=i-4){
    analogWrite(Right_Motor_Reverse,i);
    analogWrite(Left_Motor_Reverse,i);
    delay(5);
  }
}

void turnLeft(int degrees){
  int duration = int(degrees * 4.0);

  analogWrite(Left_Motor_Forward, 0);
  analogWrite(Right_Motor_Reverse, 0);

  analogWrite(Right_Motor_Forward,255);
  analogWrite(Left_Motor_Reverse,255);

  delay(duration);
  analogWrite(Right_Motor_Forward,0);
  analogWrite(Left_Motor_Reverse,0);

}

void rightMotorForward() {
  analogWrite(Right_Motor_Reverse, 0);

  for (int  i = 0; i<255; i=i+4){
    analogWrite(Right_Motor_Reverse,i);
    delay(8);
  }
}
void leftMotorForward() {
  analogWrite(Left_Motor_Reverse, 0);

  for (int  i = 0; i<255; i=i+4){
    analogWrite(Left_Motor_Forward,i);
    delay(8);
  }
}

void rightMotorReverse() {
  analogWrite(Right_Motor_Reverse, 0);

  for (int  i = 0; i<255; i=i+4){
    analogWrite(Right_Motor_Forward,i);
    delay(8);
  }
}
void leftMotorReverse() {
  analogWrite(Left_Motor_Forward, 0);

  for (int  i = 0; i<255; i=i+4){
    analogWrite(Left_Motor_Reverse,i);
    delay(8);
  }
}

void rightMotorStop() {
    analogWrite(Right_Motor_Forward, 0);
    analogWrite(Right_Motor_Reverse, 0);
}


void leftMotorStop() {
  analogWrite(Left_Motor_Forward, 0);
  analogWrite(Left_Motor_Reverse,0);
}
void initMotors(){
    pinMode(Left_Motor_Forward, OUTPUT);
    pinMode(Left_Motor_Reverse, OUTPUT);
    pinMode(Right_Motor_Forward, OUTPUT);
    pinMode(Right_Motor_Reverse, OUTPUT);
}

void turnRight(int degrees){
  int duration = int(degrees * 4.0);

  analogWrite(Left_Motor_Forward, 0);
  analogWrite(Right_Motor_Reverse, 0);

  analogWrite(Right_Motor_Reverse,255);
  analogWrite(Left_Motor_Forward,255);

  delay(duration);

  analogWrite(Right_Motor_Reverse,0);
  analogWrite(Left_Motor_Forward,0);
}

void forward(){
  leftMotorForward();
  rightMotorForward();
}

void reverse(){
  leftMotorReverse();
  rightMotorReverse();
}

void stop() {
  analogWrite(Right_Motor_Forward, 0);
  analogWrite(Left_Motor_Reverse, 0);
  leftMotorStop();
  rightMotorStop();
}

void loop() {


}

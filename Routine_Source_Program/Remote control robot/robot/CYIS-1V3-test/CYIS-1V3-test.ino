
#define MotorR_F 18 // Correct motor Pin
#define MotorR_R 8 // Correct motor Pin
#define MotorL_F 6 // Correct motor Pin
#define MotorL_R 5 // Correct motor Pin


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
  analogWrite(MotorL_R, 0);
  analogWrite(MotorR_R, 0);
  for (int  i = 0; i<255; i=i+4){
    analogWrite(MotorR_F,i);
    analogWrite(MotorL_F,i);
    delay(10);
  }
}

void accelerateForward(int duration){
  analogWrite(MotorL_R, 0);
  analogWrite(MotorR_R, 0);

  for (int  i = 0; i<255; i=i+4){
    analogWrite(MotorR_F,i);
    analogWrite(MotorL_F,i);
    delay(10);
  }

  delay(duration);

  for (int  i = 255; i>=0; i=i-4){
    analogWrite(MotorR_F,i);
    analogWrite(MotorL_F,i);
    delay(5);
  }
}
void accelerateBackward(){
  analogWrite(MotorL_F, 0);
  analogWrite(MotorR_F, 0);

  for (int  i = 0; i<255; i=i+4){
    analogWrite(MotorR_R,i);
    analogWrite(MotorL_R,i);
    delay(10);
  }
}

void accelerateBackward(int duration){
  analogWrite(MotorL_F, 0);
  analogWrite(MotorR_F, 0);

  for (int  i = 0; i<255; i=i+4){
    analogWrite(MotorR_R,i);
    analogWrite(MotorL_R,i);
    delay(10);
  }

  delay(duration);

  for (int  i = 255; i>=0; i=i-4){
    analogWrite(MotorR_R,i);
    analogWrite(MotorL_R,i);
    delay(5);
  }
}

void turnLeft(int degrees){
  int duration = int(degrees * 4.0);

  analogWrite(MotorL_F, 0);
  analogWrite(MotorR_R, 0);

  analogWrite(MotorR_F,255);
  analogWrite(MotorL_R,255);

  delay(duration);
  analogWrite(MotorR_F,0);
  analogWrite(MotorL_R,0);

}

void rightMotorForward() {
  analogWrite(MotorR_R, 0);

  for (int  i = 0; i<255; i=i+4){
    analogWrite(MotorR_R,i);
    delay(8);
  }
}
void leftMotorForward() {
  analogWrite(MotorL_R, 0);

  for (int  i = 0; i<255; i=i+4){
    analogWrite(MotorL_F,i);
    delay(8);
  }
}

void rightMotorReverse() {
  analogWrite(MotorR_R, 0);

  for (int  i = 0; i<255; i=i+4){
    analogWrite(MotorR_F,i);
    delay(8);
  }
}
void leftMotorReverse() {
  analogWrite(MotorL_F, 0);

  for (int  i = 0; i<255; i=i+4){
    analogWrite(MotorL_R,i);
    delay(8);
  }
}

void rightMotorStop() {
    analogWrite(MotorR_F, 0);
    analogWrite(MotorR_R, 0);
}


void leftMotorStop() {
  analogWrite(MotorL_F, 0);
  analogWrite(MotorL_R,0);
}
void initMotors(){
    pinMode(MotorL_F, OUTPUT);
    pinMode(MotorL_R, OUTPUT);
    pinMode(MotorR_F, OUTPUT);
    pinMode(MotorR_R, OUTPUT);
}

void turnRight(int degrees){
  int duration = int(degrees * 4.0);

  analogWrite(MotorL_F, 0);
  analogWrite(MotorR_R, 0);

  analogWrite(MotorR_R,255);
  analogWrite(MotorL_F,255);

  delay(duration);

  analogWrite(MotorR_R,0);
  analogWrite(MotorL_F,0);
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
  analogWrite(MotorR_F, 0);
  analogWrite(MotorL_R, 0);
  leftMotorStop();
  rightMotorStop();
}

void loop() {


}

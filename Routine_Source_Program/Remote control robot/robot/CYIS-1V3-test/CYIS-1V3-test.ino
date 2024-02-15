
#define MotorR_A_Pin 18 // Correct motor Pin
#define MotorR_B_Pin 8 // Correct motor Pin
#define MotorL_A_Pin 6 // Correct motor Pin
#define MotorL_B_Pin 5 // Correct motor Pin


void setup() {
  Serial.begin(115200); //set your serial monitor to this baud

  initMotors();

  delay(1000);

  forward();
  delay(4000);
  stop();

  delay(1000);
  turnLeft(350);
  delay(1000);

  forward();
  delay(4000);
  stop();

}

void rightMotorForward() {
    digitalWrite(MotorR_A_Pin, HIGH);
    digitalWrite(MotorR_B_Pin, LOW);
}
void rightMotorReverse() {
    digitalWrite(MotorR_A_Pin, LOW);
    digitalWrite(MotorR_B_Pin, HIGH);
}
void rightMotorStop() {
    digitalWrite(MotorR_A_Pin, LOW);
    digitalWrite(MotorR_B_Pin, LOW);
}

void leftMotorForward() {
    digitalWrite(MotorL_A_Pin, HIGH);
    digitalWrite(MotorL_B_Pin, LOW);
}
void leftMotorReverse() {
    digitalWrite(MotorL_A_Pin, LOW);
    digitalWrite(MotorL_B_Pin, HIGH);
}
void leftMotorStop() {
    digitalWrite(MotorL_A_Pin, LOW);
    digitalWrite(MotorL_B_Pin, LOW);
}
void initMotors(){
    pinMode(MotorL_A_Pin, OUTPUT);
    pinMode(MotorL_B_Pin, OUTPUT);
    pinMode(MotorR_A_Pin, OUTPUT);
    pinMode(MotorR_B_Pin, OUTPUT);

}
void turnLeft(int del){
  rightMotorForward();
  leftMotorReverse();
  delay(del);
  rightMotorStop();
  leftMotorStop();
}
void turnRight(int del){
  leftMotorForward();
  rightMotorReverse();
  delay(del);
  leftMotorStop();
  rightMotorStop();
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
  leftMotorStop();
  rightMotorStop();
}

void loop() {

}

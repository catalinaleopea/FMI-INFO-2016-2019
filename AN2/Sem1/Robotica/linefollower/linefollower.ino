#include <QTRSensors.h>

#define E1 9  // Enable Pin for motor 1
#define E2 10 // Enable Pin for motor 2

#define I1 7  // Control pin 1 for motor 1 (left)
#define I2 8  // Control pin 2 for motor 1
#define I3 13 // Control pin 1 for motor 2 (right)
#define I4 12 // Control pin 2 for motor 2

#define MIN_SPEED 100     //min speed
#define MAX_SPEED 200     //max speed
#define NUM_SENSORS 5     //number of sensors used
#define TIMEOUT 2500      //waits for 2500 milliseconds for sensor outputs to go low
#define EMITTER_PIN 11    //emitterPin is the Arduino digital pin 11 that controls whether the IR LEDs are on or off
#define DEBUG 0           //set to 1 if you want to verify with serial monitor

QTRSensorsRC qtrrc((unsigned char[]) {
  3, A5, A4, A3, A2 //2, 3, 4, 5, 6 sensor pins
},
NUM_SENSORS, TIMEOUT, EMITTER_PIN);

void setup() {
  pinMode(E1, OUTPUT);
  pinMode(E2, OUTPUT);

  pinMode(I1, OUTPUT);
  pinMode(I2, OUTPUT);
  pinMode(I3, OUTPUT);
  pinMode(I4, OUTPUT);

  digitalWrite(I1, LOW);
  digitalWrite(I2, LOW);
  digitalWrite(I3, LOW);
  digitalWrite(I4, LOW);

  for (int i = 0; i < 200; i++) { // make the calibration take about 5 seconds
    qtrrc.calibrate();       // reads all sensors 10 times at 2500 milliseconds per read
  }
  setMotors(0, 0);
}

int lastError = 0;

void loop() {
  unsigned int sensorValues[NUM_SENSORS];
  int position = qtrrc.readLine(sensorValues); //get calibrated readings along with the line position,
  int error = position - 2500;
  Serial.begin(9600);
  for (unsigned char i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(sensorValues[i]);
    Serial.print('\t');
  }

  int motorSpeed = error + 2 * (error - lastError);
  lastError = error; //used to know the last position

  int leftMotorSpeed = MIN_SPEED + motorSpeed;
  int rightMotorSpeed = MIN_SPEED - motorSpeed;

  // set motors speed using the two variables above
  setMotors(leftMotorSpeed, rightMotorSpeed);
}

void setMotors(int motor1Speed, int motor2Speed) {
  //make sure to not exceed the lower and upper bounds
  if (motor1Speed > MAX_SPEED) motor1Speed = MAX_SPEED;
  if (motor2Speed > MAX_SPEED) motor2Speed = MAX_SPEED;
  if (motor1Speed < 0) motor1Speed = 0;
  if (motor2Speed < 0) motor2Speed = 0;

  analogWrite(E1, motor1Speed);
  analogWrite(E2, motor2Speed);

  digitalWrite(I1, HIGH);
  digitalWrite(I2, LOW);
  digitalWrite(I3, HIGH);
  digitalWrite(I4, LOW);
}

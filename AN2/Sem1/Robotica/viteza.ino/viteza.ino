#define E1 9  // Enable Pin for motor 1
#define E2 10  // Enable Pin for motor 2

#define I1 7  // Control pin 1 for motor 1
#define I2 8  // Control pin 2 for motor 1
#define I3 13  // Control pin 1 for motor 2
#define I4 12  // Control pin 2 for motor 2
//11
void setup() {
 
    pinMode(E1, OUTPUT);
    pinMode(E2, OUTPUT);
 
    pinMode(I1, OUTPUT);
    pinMode(I2, OUTPUT);
    pinMode(I3, OUTPUT);
    pinMode(I4, OUTPUT);
}
 
void loop() {
 
    analogWrite(E1, 153); // Run in half speed
    analogWrite(E2, 255); // Run in full speed
 
    digitalWrite(I1, HIGH);
    digitalWrite(I2, LOW);
    digitalWrite(I3, HIGH);
    digitalWrite(I4, LOW);
 
    delay(10000);
 /*
    // change direction
 
    digitalWrite(E1, LOW);
    digitalWrite(E2, LOW);
 
    delay(200);
 
    analogWrite(E1, 255);  // Run in full speed
    analogWrite(E2, 153);  // Run in half speed
 
    digitalWrite(I1, LOW);
    digitalWrite(I2, HIGH);
    digitalWrite(I3, LOW);
    digitalWrite(I4, HIGH);
 
    delay(10000);*/
}

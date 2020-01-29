void setup() {
  // put your setup code here, to run once:
  pinMode(13,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int val=analogRead(A0);
  if(val>500){
    analogWrite(13,HIGH);
    delay(1000);
  }else{
    analogWrite(13,LOW);
    delay(1000);
  }
}
